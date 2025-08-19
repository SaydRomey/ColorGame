
# ==============================
##@ 👾 Godot C++ / GDExtension
# ==============================
ifndef __GODOT_CPP_MK__
__GODOT_CPP_MK__ := 1

GDEXT_DIR				?= gdext
GODOT_CPP_DIR			?= $(GDEXT_DIR)/godot-cpp

TEMPLATE_DIR			?= utils/templates
GDEXT_TEMPLATE_DIR		?= $(TEMPLATE_DIR)/gdext-templates
GDEXTENSION_TEMPLATE	:= $(GDEXT_TEMPLATE_DIR)/libname.gdextension.template

# Godot / platform knobs
GODOT_BIN			?= $(shell command -v godot)
GODOT_VERSION		:= $(shell "$(GODOT_BIN)" --version 2>/dev/null | head -n1)
GODOT_MAJOR_MINOR	:= $(shell printf "%s" "$(GODOT_VERSION)" | cut -d. -f1,2)
GODOT_VERSION_REQ	?= 4.4
GODOT_PLATFORM		?= linux			# linux | windows | macos | ios | android
GODOT_TARGET		?= template_debug	# template_debug | template_release

# Try to guess the arch suffix produced by godot-cpp
UNAME_M	:= $(shell uname -m)
ifeq ($(UNAME_M),x86_64)
	GODOT_ARCH ?= x86_64
else ifeq ($(UNAME_M),aarch64)
	GODOT_ARCH ?= arm64
endif

# godot-cpp outputs: bin/libgodot-cpp.$(platform).$(target).$(arch).a
# We keep detection tolerant, in case arch naming differs.
GODOT_CPP_LIB_GLOB	:= $(GODOT_CPP_DIR)/bin/libgodot-cpp.$(GODOT_PLATFORM).$(GODOT_TARGET).*.*.a
GODOT_CPP_LIB_ANY	:= $(GODOT_CPP_DIR)/bin/libgodot-cpp.*.a
GODOT_CPP_LIB		:= $(firstword $(wildcard $(GODOT_CPP_LIB_GLOB) $(GODOT_CPP_LIB_ANY)))

# SCons knobs
SCONS_JOBS		?= $(shell command -v nproc >/dev/null 2>&1 && nproc || sysctl -n hw.ncpu 2>/dev/null || echo 4)
SCONS_VERBOSE	?= 0	# 0 or 1
PLUGINS			?=		# comma-separated: gdexample,otherexample

# Optional version nudge
# Optional: warn if you expected 4.4 but got something else
ifneq ($(GODOT_VERSION_REQ),$(GODOT_MAJOR_MINOR))
  $(warning Godot version is $(GODOT_MAJOR_MINOR) [full: '$(GODOT_VERSION)'], not $(GODOT_VERSION_REQ). Proceeding anyway.)
endif

# Discover modules (exclude the godot-cpp dir)
CPP_MODULES_DIRS	:= $(wildcard $(GDEXT_DIR)/src/*)
CPP_MODULE_NAMES	:= $(filter-out godot-cpp,$(notdir $(CPP_MODULE_DIRS)))

# Script path (for 'cpp-new' target)
SCRIPT_DIR			?= utils/scripts
GD_SCRIPT_DIR		:= $(SCRIPT_DIR)/godot-scripts
GD_CPP_NEW			:= $(GD_SCRIPT_DIR)/gd-cpp-new-module.sh

# ==============================
# Targets
# ==============================
.PHONY: cpp-new cpp-build cpp-clean cpp-re cpp-status cpp-gdextension-links

cpp-new: ## Create new GDExtension C++ module using templates (w.i.p.)
	@$(call RUN_SCRIPT,cpp module,$(GD_CPP_NEW))

# Ensure bindings exist before building modules
cpp-build: $(GODOT_CPP_LIB) ## Build all GDextension C++ modules
	@$(call INFO,GDExtension,Building C++ modules)
	@scons -C $(GDEXT_DIR) verbose=1

# cpp-build: $(GODOT_CPP_LIB) ## Build all (or a subset) of GDExtension C++ modules
# 	@$(call INFO,GDExtension,Building C++ modules$(if $(PLUGINS), ($(PLUGINS)),))
# 	@scons -C $(GDEXT_DIR) \
# 		platform=$(GODOT_PLATFORM) target=$(GODOT_TARGET) \
# 		$(if $(PLUGINS),plugins=$(PLUGINS),) \
# 		-j$(SCONS_JOBS) verbose=$(SCONS_VERBOSE)

cpp-clean: ## Clean all compiled C++ modules
	@$(call INFO,GDExtension,Cleaning C++ modules)
	@scons -C $(GDEXT_DIR) -c || true

# cpp-clean: ## Clean compiled C++ modules
# 	@$(call INFO,GDExtension,Cleaning C++ modules$(if $(PLUGINS), ($(PLUGINS)),))
# 	@scons -C $(GDEXT_DIR) -c \
# 		$(if $(PLUGINS),plugins=$(PLUGINS),) || true

cpp-re: cpp-clean cpp-build ## Clean and rebuild

cpp-status: ## Show available C++ modules and their contents
	@for mod in $(CPP_MODULE_NAMES); do \
		echo "[C++] Module: $$mod"; \
		ls -lh $(GDEXT_DIR)/src/$$mod; \
	done

# (Optional) Regenerate all .gdextension descriptors from the template
# Use this as a maintenance tool; the generator script now writes directly to game/bin/.
cpp-gdextension-links: ## Regenerate .gdextension files for all C++ modules
	@mkdir -p game/bin/
	@for mod in $(CPP_MODULE_NAMES); do \
		[ "$$mod" = "godot-cpp" ] && continue; \
		echo "[GDExtension] Generating $$mod.gdextension"; \
		sed \
			-e "s/{{ENTRY_SYMBOL}}/$$mod_init/" \
			-e "s/{{LIB_NAME}}/$$mod/" \
			utils/templates/gdext-templates/libname.gdextension.template > game/bin/$$mod.gdextension; \
	done

# ==============================
# godot-cpp (bindings)
# ==============================
.PHONY: godot-cpp-bindings godot-cpp-clean

godot-cpp-bindings: ## Build godot-cpp bindings
	@$(call INFO,Build,godot-cpp $(GODOT_PLATFORM), Building CPP bindings...)
	@scons -C $(GODOT_CPP_DIR) platform=$(GODOT_PLATFORM)
	@$(call SUCCESS,Build,godot-cpp built)

godot-cpp-clean:
	@$(call INFO,Build,Cleaning godot-cpp artifacts)
	@scons -C $(GODOT_CPP_DIR) -c || true

endif # __GODOT_CPP_MK__
