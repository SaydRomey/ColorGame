
# ==============================
##@ 📚 Documentation
# ==============================
ifndef __DOC_MK__
__DOC_MK__ := 1

# Path for Generated Make Targets Document
TARGET_README	:= README_make_targets.md

# Documentation
URL_GODOT		:= https://docs.godotengine.org/en/stable/index.html
URL_GDEXTENSION	:= https://godotengine.org/article/introducing-gd-extensions/
URL_GD_CLASSES	:= https://docs.godotengine.org/en/4.4/classes/index.html

# Godot Tutorials
URL_2D_GUIDE	:= https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/the-guide-to-implementing-2d-platformers-r2936/
URL_KCC_CHAR	:= https://kidscancode.org/godot_recipes/4.x/2d/platform_character/index.html
URL_STATE_MA	:= https://www.gdquest.com/tutorial/godot/design-patterns/finite-state-machine/
URL_GDEXT_TUTO	:= https://docs.godotengine.org/en/4.4/tutorials/scripting/gdextension/gdextension_cpp_example.html

# Git Repos
URL_GODOT_CPP	:= https://github.com/godotengine/godot-cpp
URL_PICOJSON	:= https://github.com/kazuho/picojson

.PHONY: doc help-md

doc: ## Show documentation links
#	@clear
	@echo "Select documentation subject:"
	@echo "\n$(ORANGE)Documentation$(RESET)"
	@echo "  0. Godot Engine"
	@echo "  1. GDExtention (cpp with godot)"
	@echo "  2. Godot - All Classes"
	@echo "\n$(ORANGE)Godot Tutorials$(RESET)"
	@echo "  10. Guide to Implementing 2D Platformers"
	@echo "  11. Platform Character"
	@echo "  12. State Machine"
	@echo "  13. GDExtension CPP Tutorial"
	@echo "\n$(ORANGE)Useful Git Repositories$(RESET)"
	@echo "  100. Godot-CPP Bindings"
	@echo "  101. PicoJSON parser/serializer"

	@read url_choice; \
	case $$url_choice in \
		0) CHOICE=$(URL_GODOT);; \
		1) CHOICE=$(URL_GDEXTENSION);; \
		2) CHOICE=$(URL_GD_CLASSES);; \
		10) CHOICE=$(URL_2D_GUIDE);; \
		11) CHOICE=$(URL_KCC_CHAR);; \
		12) CHOICE=$(URL_STATE_MA);; \
		13) CHOICE=$(URL_GDEXT_TUTO);; \
		100) CHOICE=$(URL_GODOT_CPP);; \
		101) CHOICE=$(URL_PICOJSON);; \
		*) $(call ERROR,Invalid choice,$$url_choice); exit 1;; \
	esac; \
	$(OPEN) $$CHOICE
#	@clear
	@$(call INFO,,Opening documentation...)

help-md: ## Generate markdown documentation for all Make targets
	@echo "\n# 📘 Makefile Targets" > $(TARGET_README); \
	awk ' \
		BEGIN { print "" } \
		/^##@/ { \
			gsub(/^##@ /, "", $$0); \
			print "\n## " $$0 \
		} \
		/^[a-zA-Z0-9\-_]+:.*##/ { \
			split($$0, parts, ":.*##"); \
			target=parts[1]; \
			desc=substr($$0, index($$0,"##")+2); \
			printf "- `%s`: %s\n", target, desc \
		} \
	' $(MAKEFILE_LIST) >> $(TARGET_README); \
	echo "\n📄 Generated at $$(date)" >> $(TARGET_README); \
	$(call SUCCESS,Docs,Markdown Makefile target index generated)

endif # __DOC_MK__
