
# ==============================
##@ 📦 Dependency setup
# ==============================
DEPS_DIR		:= build
DEPS_SENTINEL	:= $(DEPS_DIR)/.deps-initialized

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

deps: $(DEPS_SENTINEL) ## Initialize and update all git submodules

$(DEPS_SENTINEL): .gitmodules
	@$(MKDIR) $(DEPS_DIR)
	@if [ -f .gitmodules ]; then \
		$(call INFO,Dependencies,Initializing and updating submodules...); \
		git submodule init; \
		git submodule update --remote --recursive; \
		touch $(DEPS_SENTINEL); \
		$(call SUCCESS,Dependencies,Ready!); \
	else \
		$(call WARNING,Dependencies,No submodules found. Skipping deps.); \
	fi

deps-clean:
	@$(call SILENT_CLEANUP,Dependencies,Sentinel Markers,$(DEPS_SENTINEL))

# ==============================
# picoJSON
# ==============================
PICOJSON_REPO	:= https://github.com/kazuho/picojson.git
PICOJSON_PATH	:= lib/picojson

picojson: ## Add picoJSON as a submodule
	@$(call INFO,Dependencies,Adding picoJSON as a submodule)
	git submodule add $(PICOJSON_REPO) $(PICOJSON_PATH)

.PHONY: picojson
