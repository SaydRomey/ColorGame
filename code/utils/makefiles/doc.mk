

# ==============================
##@ 📚 Documentation
# ==============================

# Documentation
URL_GODOT		:= https://docs.godotengine.org/en/stable/index.html
URL_GDEXTENSION	:= https://godotengine.org/article/introducing-gd-extensions/

# Godot Tutorials
URL_2D_GUIDE	:= https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/the-guide-to-implementing-2d-platformers-r2936/
URL_KCC_CHAR	:= https://kidscancode.org/godot_recipes/4.x/2d/platform_character/index.html
URL_STATE_MA	:= https://www.gdquest.com/tutorial/godot/design-patterns/finite-state-machine/

# Git Repos
URL_GODOT_CPP	:= https://github.com/godotengine/godot-cpp
URL_PICOJSON	:= https://github.com/kazuho/picojson

doc: ## Show documentation links
	@clear
	@echo "Select documentation subject:"
	@echo "\n$(ORANGE)Documentation$(RESET)"
	@echo "  0. Godot Engine"
	@echo "  1. GDExtention (cpp with godot)"
	@echo "\n$(ORANGE)Godot Tutorials$(RESET)"
	@echo "  10. Guide to Implementing 2D Platformers"
	@echo "  11. Platform Character"
	@echo "  12. State Machine"
	@echo "\n$(ORANGE)Useful Git Repositories$(RESET)"
	@echo "  100. Godot-CPP Bindings"
	@echo "  101. PicoJSON parser/serializer"

	@read url_choice; \
	case $$url_choice in \
		0) CHOICE=$(URL_GODOT);; \
		1) CHOICE=$(URL_GDEXTENSION);; \
		10) CHOICE=$(URL_2D_GUIDE);; \
		11) CHOICE=$(URL_KCC_CHAR);; \
		12) CHOICE=$(URL_STATE_MA);; \
		100) CHOICE=$(URL_GODOT_CPP);; \
		101) CHOICE=$(URL_PICOJSON);; \
		*) $(call ERROR,Invalid choice:,$$CHOICE, Exiting.); exit 1;; \
	esac; \
	$(OPEN) $$CHOICE
	@clear
	@$(call INFO,,Opening documentation...)

.PHONY: doc
