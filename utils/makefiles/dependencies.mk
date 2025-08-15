
# ==============================
##@ 📦 Dependency setup
# ==============================
LIB_DIR			?= lib
DEPS_DIR		:= build/sentinel-markers
DEPS_SENTINEL	:= $(DEPS_DIR)/.deps-initialized
MODULE_SENTINEL	:= $(DEPS_DIR)/.submodules-initialized



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
	fi;
endef

# **************************************************************************** #
.PHONY: deps deps-clean

deps: $(MODULE_SENTINEL) ## Initialize and update all git submodules

$(MODULE_SENTINEL): .gitmodules
	@$(MKDIR) $(DEPS_DIR)
	@if [ -f .gitmodules ]; then \
		$(call INFO,Dependencies,Initializing and updating submodules...); \
		git submodule init; \
		git submodule update --remote --recursive; \
		touch $(MODULE_SENTINEL); \
		$(call SUCCESS,Dependencies,Ready!); \
	else \
		$(call WARNING,Dependencies,No submodules found. Skipping deps.); \
	fi

deps-clean:
	@$(call SILENT_CLEANUP,Dependencies,Sentinel Markers,$(MODULE_SENTINEL))

# ==============================
# picoJSON
# ==============================
PICOJSON_REPO	:= https://github.com/kazuho/picojson.git
PICOJSON_PATH	:= $(LIB_DIR)/picojson
# PICOJSON_SENTINEL	:= $(DEPS_DIR)/.picoJSON-initialized

deps-picojson: ## Add picoJSON as a submodule
	@$(call INFO,Dependencies,Adding picoJSON as a submodule)
	@if [ ! -d "$(PICOJSON_PATH)" ]; then \
		git submodule add $(PICOJSON_REPO) $(PICOJSON_PATH); \
		git -C $(PICOJSON_PATH) submodule update --init --recursive; \
		$(call SUCCESS,Dependencies,picoJSON added); \
	else \
		$(call WARNING,Dependencies,$(PICOJSON_PATH) already exists. Skipping add.); \
	fi

.PHONY: deps-picojson

# ==============================
# godot-cpp
# ==============================
GODOTCPP_REPO	:= https://github.com/godotengine/godot-cpp.git
GDEXT_DIR		?= gdext
GODOTCPP_DIR	?= $(GDEXT_DIR)/godot-cpp
GODOTCPP_BRANCH	:= 4.4
# GODOTCPP_SENTINEL	:= $(DEPS_DIR)/.godot-cpp-initialized

deps-godotcpp: ## Add godot-cpp (branch 4.4) as a submodule
	@$(call INFO,Dependencies,Adding godot-cpp@$(GODOTCPP_BRANCH) as a submodule)
	@if [ ! -d "$(GODOTCPP_DIR)" ]; then \
		git submodule add -b $(GODOTCPP_BRANCH) $(GODOTCPP_REPO) $(GODOTCPP_DIR); \
		git -C $(GODOTCPP_DIR) submodule update --init --recursive; \
		git config -f .gitmodules submodule.$(GODOTCPP_DIR).branch $(GODOTCPP_BRANCH); \
		$(call SUCCESS,Dependencies,godot-cpp added and pinned to $(GODOTCPP_BRANCH)); \
	else \
		$(call WARNING,Dependencies,$(GODOTCPP_DIR) already exists. Skipping add.); \
	fi

.PHONY: deps-godotcpp
