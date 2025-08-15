
# ==============================
##@ 👾 Godot C++ / GDExtension
# ==============================
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
GODOT_PLATFORM		?= linux	# linux | windows | macos | ios | android
GODOT_TARGET		?= template_debug # template_debug | template_release

# SCons knobs
SCONS_JOBS		?= $(shell command -v nproc >/dev/null 2>&1 && nproc || sysctl -n hw.ncpu 2>/dev/null || echo 4)
SCONS_VERBOSE	?= 0	# 0 or 1
PLUGINS			?=		# comma-separated: gdexample,greetings

# Optional version nudge
# Optional: warn if you expected 4.4 but got something else
ifneq ($(GODOT_VERSION_REQ),$(GODOT_MAJOR_MINOR))
  $(warning Godot version is $(GODOT_MAJOR_MINOR) [full: '$(GODOT_VERSION)'], not $(GODOT_VERSION_REQ). Proceeding anyway.)
endif

# Discover modules (exclude the godot-cpp dir)
CPP_MODULES_DIRS	:= $(wildcard $(GDEXT_DIR)/src/*)
CPP_MODULE_NAMES	:= $(filter-out godot-cpp,$(notdir $(CPP_MODULE_DIRS)))

# Script path (for 'cpp-new' target)
GD_CPP_NEW			:= utils/scripts/gd-cpp-new-module.sh

# ==============================
# Targets
# ==============================
.PHONY: cpp-new cpp-build cpp-clean cpp-re cpp-status cpp-gdextension-links

cpp-new: ## Create new C++ native module using templates (w.i.p.)
	@$(call RUN_SCRIPT,cpp module,$(GD_CPP_NEW))

cpp-build: ## Build all GDextension C++ modules
	@$(call INFO,GDExtension,Building C++ modules)
	@scons -C $(GDEXT_DIR) verbose=1

# cpp-build: ## Build all (or a subset) of GDExtension C++ modules
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

# ==============================
# Misc (To check if useful...)
# ==============================

# ===== Helpers ================
# TODO: Macro that takes version req as param

# # Internal: check Godot version line starts with $(GODOT_VERSION_REQ)
# define _CHECK_GODOT_VER
# 	ver="`$(GODOT_BIN) --version 2>/dev/null | head -n1`"; \
# 	case "$$ver" in \
# 	  $(GODOT_VERSION_REQ)*) true ;; \
# 	  *) $(call WARNING,Godot,"Engine version ($$ver) does not start with $(GODOT_VERSION_REQ). Proceeding anyway.");; \
# 	esac
# endef

# ===== Godot API ==============
# Where to put the dumped API
# GODOT_API_JSON     ?= $(GODOT_CPP_DIR)/extension_api.json

# .PHONY: godot-api
# godot-api: ## Dump extension_api.json from the detected Godot binary
# 	@$(call INFO,Godot,Using '$(GODOT_BIN)' ($(GODOT_VERSION)))
# 	@if [ ! -f "$(GODOT_API_JSON)" ]; then \
# 		$(MKDIR) $(GODOT_CPP_DIR); \
# 		cd $(GODOT_CPP_DIR) && "$(GODOT_BIN)" --dump-extension-api "$(GODOT_API_JSON)"; \
# 		$(call SUCCESS,Godot,API dumped → $(GODOT_API_JSON)); \
# 	else \
# 		$(call WARNING,GODOT,API already dumped → $(GODOT_API_JSON)); \
# 	fi

# godot-api: ## Dump extension_api.json from the detected Godot binary
# 	@$(call CHECK_COMMAND,$(GODOT_BIN))
# 	@$(call INFO,Godot,Checking version on '$(GODOT_BIN)')
# 	@bash -c '$(strip $(_CHECK_GODOT_VER))'
# 	@$(call INFO,Godot,Dumping extension API → $(GODOT_API_JSON))
# 	@$(GODOT_BIN) --dump-extension-api $(GODOT_API_JSON)
# 	@test -f $(GODOT_API_JSON) && $(call SUCCESS,Godot,extension_api.json written.)
