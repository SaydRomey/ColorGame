
# ==============================
##@ 📦 Dependency setup
# ==============================
ifndef __DEPS_MK__
__DEPS_MK__	:= 1

# Marker files so init only happens once unless cleaned
DEPS_DIR			?= .sentinel-markers
SUBMODULE_SENTINEL	= $(DEPS_DIR)/.submodules-initialized

# ---- System dependency list
SYS_DEPS ?= git scons pkg-config clang g++ c++

# If set to 1, 'deps-sys' will fail the build when something is missing
DEPS_FAIL_ON_MISSING ?= 0

# ---- godot-cpp knobs
GDEXT_DIR			?= gdext
GODOT_CPP_DIR		?= $(GDEXT_DIR)/godot-cpp
GODOT_CPP_REPO		?= https://github.com/godotengine/godot-cpp.git
GODOT_CPP_BRANCH	?= 4.4
GODOT_CPP_TAG		?= godot-4.4.1-stable

# ---- godot-cpp SCons knobs used for detection/build
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

# ==============================
# Dependency Utilty Macros
# ==============================

# Macro: SENTINEL_MARKER
# Create a sentinel marker file for dependency management
# 
# Parameters:
# $(1): Name of sentinel marker
# $(2): (Optional) Use "print" to enable confirmation output.
# $(3): (Optional) Use "print skip" to enable skipping output.
# 
# Behavior:
# Creates the sentinel marker file.
# If sentinel file already exists, exits silently.
# If second argument is "print"; Message on sentinel creation.
# If third argument is "print skip"; Message when sentinal already exists.
# 
# Example Usage:
# $(call SENTINEL_MARKER,$(PROJECT_ROOT),print)
# $(call SENTINEL_MARKER,.proof-something-happened,print,print skip)
# 
define SENTINEL_MARKER
	if [ ! -f "$(1)" ]; then \
		touch $(1); \
		if [ "$(2)" = "print" ]; then \
			$(call SUCCESS,Sentinel Marker,$(1) created.); \
		fi; \
	else \
		if [ "$(3)" = "print skip" ]; then \
			$(call WARNING,Sentinel Marker,$(1) already exists. Skipping); \
		fi; \
	fi
endef

# ==============================
# Targets
# ==============================
.PHONY: deps deps-status deps-clean

deps: deps-sys deps-submodules deps-godotcpp-ensure ## Initialize/check all dependencies

deps-status: ## Print a quick overview of dependency state
	@$(MAKE) $(NPD) deps-sys-check
	@$(MAKE) $(NPD) deps-godotcpp-check
	@if [ -f "$(SUBMODULE_SENTINEL)" ]; then \
		$(call SUCCESS,Dependencies,Submodules initialized); \
	else \
		$(call WARNING,Dependencies,Submodules not initialized); \
	fi

deps-clean: ## Remove dependency sentinel markers (does not remove submodules/libs)
	@$(call SILENT_CLEANUP,Dependencies,Sentinel Markers,$(SUBMODULE_SENTINEL))

# ==============================
# System tools
# ==============================
.PHONY: deps-sys deps-sys-check

deps-sys: deps-sys-check ## Verify required system packages (fatal if DEPS_FAIL_ON_MISSING=1)
	@if [ "$(DEPS_FAIL_ON_MISSING)" = "1" ]; then \
		MISSING=$$(for c in $(SYS_DEPS); do command -v $$c >/dev/null 2>&1 || echo $$c; done); \
		if [ -n "$$MISSING" ]; then \
			$(call ERROR,Dependencies,Missing tools: $$MISSING); \
			exit 1; \
		fi; \
	fi

deps-sys-check: ## Show which required system packages are present
	@$(call INFO,Dependencies,Checking required system packages...)
	@for cmd in $(SYS_DEPS); do \
		if command -v $$cmd >/dev/null 2>&1; then \
			printf "  ✅ %s\n" "$$cmd"; \
		else \
			printf "  ❌ %s\n" "$$cmd"; \
		fi; \
	done

# ==============================
# Submodules
# ==============================
.PHONY: deps-submodules deps-submodules-update deps-submodules-clean

deps-submodules: $(SUBMODULE_SENTINEL) ## Initialize and update all git submodules (idempotent)

$(SUBMODULE_SENTINEL): .gitmodules
	@$(MKDIR) $(DEPS_DIR)
	@if [ -f .gitmodules ]; then \
		$(call INFO,Dependencies,Initializing and updating submodules...); \
		git submodule update --init --recursive; \
		$(call SENTINEL_MARKER,$@); \
		$(call SUCCESS,Dependencies,Submodules ready); \
	else \
		$(call WARNING,Dependencies,No .gitmodules found. Skipping submodules.); \
	fi

deps-submodules-update: ## Update submodules to their tracked commit/branch
	@$(call INFO,Dependencies,Updating submodules (remote, recursive)...)
	@git submodule update --remote --recursive
	@$(call SUCCESS,Dependencies,Submodules updated)

deps-submodules-clean: ## Forget we've initialized submodules (so next deps re-inits)
	@$(call SILENT_CLEANUP,Dependencies,Sentinel Markers,$(SUBMODULE_SENTINEL))

# ==============================
# godot-cpp (submodule + bindings)
# ==============================
.PHONY: deps-godotcpp deps-godotcpp-add-submodule deps-godotcpp-update-submodule
.PHONY: deps-godotcpp-ensure deps-godotcpp-check

deps-godotcpp: deps-godotcpp-add-submodule deps-godotcpp-ensure ## Ensure godot-cpp exists and bindings are built

deps-godotcpp-add-submodule: ## Add godot-cpp as a submodule (branch pinned)
	@$(call INFO,Dependencies,Adding godot-cpp@$(GODOT_CPP_BRANCH) as a submodule)
	@if [ ! -d "$(GODOT_CPP_DIR)" ]; then \
		git submodule add -b $(GODOT_CPP_BRANCH) $(GODOT_CPP_REPO) $(GODOT_CPP_DIR); \
		git -C $(GODOT_CPP_DIR) submodule update --init --recursive; \
		git config -f .gitmodules submodule.$(GODOT_CPP_DIR).branch $(GODOT_CPP_BRANCH); \
		$(call SUCCESS,Dependencies,godot-cpp added and pinned to $(GODOT_CPP_BRANCH)); \
	else \
		$(call WARNING,Dependencies,$(GODOT_CPP_DIR) already exists. Skipping add.); \
	fi

deps-godotcpp-update-submodule: ## Checkout a specific tag (e.g., $(GODOT_CPP_TAG))
	@$(call INFO,Dependencies,Updating submodule 'godot-cpp' to $(GODOT_CPP_TAG))
	@cd $(GODOT_CPP_DIR) && git fetch --tags && git checkout $(GODOT_CPP_TAG)
	@$(call SUCCESS,Dependencies,godot-cpp at $(GODOT_CPP_TAG))

# Verify only
deps-godotcpp-check: ## Verify godot-cpp static library exists (non-fatal)
	@LIB="$(GODOT_CPP_LIB)"; \
	if [ -n "$$LIB" ] && [ -f "$$LIB" ]; then \
		$(call SUCCESS,Dependencies,Found $$LIB); \
	else \
		$(call ERROR,godot-cpp bindings,Static library not found in $(GODOT_CPP_DIR)/bin); \
		$(call WARNING,Dependencies,Run 'make godot-cpp-bindings' or 'make deps-godotcpp-ensure'); \
	fi

# Verify OR build if missing
deps-godotcpp-ensure: ## Ensure godot-cpp static library exists (builds if missing)
	@$(call INFO,Dependencies,Ensuring godot-cpp bindings exist...)
	@LIB="$(GODOT_CPP_LIB)"; \
	if [ -n "$$LIB" ] && [ -f "$$LIB" ]; then \
		$(call SUCCESS,Dependencies,Found $$LIB); \
	else \
		$(call WARNING,Dependencies,Bindings not found. Building now...); \
		$(MAKE) $(NPD) godot-cpp-bindings; \
	fi

# ==============================
# picoJSON
# ==============================
LIB_DIR				?= lib
PICOJSON_DIR		:= $(LIB_DIR)/picojson
PICOJSON_REPO		:= https://github.com/kazuho/picojson.git
# PICOJSON_SENTINEL	:= $(DEPS_DIR)/.picoJSON-initialized

.PHONY: deps-picojson-add-submodule

deps-picojson-add-submodule: ## Add picoJSON as a submodule
	@$(call INFO,Dependencies,Adding picoJSON as a submodule)
	@if [ ! -d "$(PICOJSON_DIR)" ]; then \
		git submodule add $(PICOJSON_REPO) $(PICOJSON_DIR); \
		git -C $(PICOJSON_DIR) submodule update --init --recursive; \
		$(call SUCCESS,Dependencies,picoJSON added); \
	else \
		$(call WARNING,Dependencies,$(PICOJSON_DIR) already exists. Skipping add.); \
	fi

endif # __DEPS_MK__
