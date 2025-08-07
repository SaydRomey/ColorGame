
# ==============================
##@ 📦 Dependency setup
# ==============================
DEPS_DIR		:= build
DEPS_SENTINEL	:= $(DEPS_DIR)/.deps-initialized

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

deps: $(DEPS_SENTINEL) ## Initialize and update all git submodules

deps-clean:
	@$(call CLEANUP,Dependencies,sentinel,$(DEPS_SENTINEL))

.PHONY: deps deps-clean

# ==============================
# picoJSON
# ==============================
PICOJSON_REPO	:= https://github.com/kazuho/picojson.git
PICOJSON_PATH	:= lib/picojson

picojson: ## Add picoJSON as a submodule
	@$(call INFO,Dependencies,Adding picoJSON as a submodule)
	git submodule add $(PICOJSON_REPO) $(PICOJSON_PATH)

.PHONY: picojson
