# **************************************************************************** #
# TOCHECK:

# To wipe generated files completely (without affecting tracked files):
# git clean -Xdf  # -X: remove only ignored files
# **************************************************************************** #

# ==============================
# Project Info
# ==============================
NAME		:= color-game
AUTHOR		:= cdumais
TEAM		:= $(AUTHOR)
REPO_LINK	:= https://github.com/SaydRomey/ColorGame

# ==============================
# Build Configuration
# ==============================
COMPILE		:= c++
STANDARD	:= -std=c++98
C_FLAGS		:= -Wall -Wextra -Werror $(STANDARD)

# Source Code Files
SRC_DIR		:= src
SRCS		:= $(shell find $(SRC_DIR) -name "*.cpp")

# Object Files
OBJ_DIR		:= obj
OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Header Files (including .ipp)
INC_DIR		:= inc
HEADERS		:= $(shell find $(INC_DIR) -name "*.hpp" -o -name "*.ipp")
INCLUDES	:= $(addprefix -I, $(shell find $(INC_DIR) -type d))

# External Libraries
LIB_DIR		:= lib
INCLUDES	+= $(addprefix -I, $(shell find $(LIB_DIR) -type d))

# ==============================
# Code Testing
# ==============================
CODE_DIR	:= code

# Bestiary Test
BESTI_DIR	:= $(CODE_DIR)/bestiary
BESTIARY	:= $(BESTI_DIR)/interactive-bestiary

# ==============================
# Makefile Imports
# ==============================
MK_PATH		:= utils/makefiles

include $(MK_PATH)/utils.mk			# Utility Variables and Macros
include $(MK_PATH)/dependencies.mk	# Submodules and Dependencies
include $(MK_PATH)/doc.mk			# Documentation Targets
include $(MK_PATH)/class.mk			# CPP Class Creator
include $(MK_PATH)/beast-class.mk	# CPP Beast Class Creator
include $(MK_PATH)/scripts.mk		# Scripts Management
include $(MK_PATH)/tree.mk			# File structure output

# ==============================
# Default
# ==============================
.DEFAULT_GOAL	:= all

.DEFAULT:
	$(info make: *** No rule to make target '$(MAKECMDGOALS)'.  Stop.)
	@$(MAKE) help

# ==============================
##@ 🛠  Utility
# ==============================
.PHONY: help repo

help: ## Display available targets
	@echo "\nAvailable targets:"
	@awk 'BEGIN {FS = ":.*##";} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "   $(CYAN)%-15s$(RESET) %s\n", $$1, $$2 \
		} \
		/^##@/ { \
			printf "\n$(BOLD)%s$(RESET)\n", substr($$0, 5) \
		}' $(MAKEFILE_LIST)

repo: ## Open the GitHub repository
	@$(call INFO,$(NAME),Opening $(AUTHOR)'s github repo...)
	@$(OPEN) $(REPO_LINK);

# ==============================
##@ 🎯 Main Targets
# ==============================
.PHONY: all run fast

all: deps $(NAME) ## Build the project/executable

$(NAME): $(OBJS)
	@$(COMPILE) $(C_FLAGS) $(OBJS) $(INCLUDES) -o $@
	@$(call SUCCESS,$@,Build complete)

# Object compilation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(MKDIR) $(@D)
	@$(call INFO,$(NAME),$(ORANGE)Compiling...\t,$(CYAN)$(notdir $<))
	@$(COMPILE) $(C_FLAGS) $(INCLUDES) -c $< -o $@
	@$(call UPCUT)

run: all ## Compile and run the executable
	@$(call INFO,$(NAME),Launching executable...)
	./$(NAME)

fast: ## Fast build using parallel jobs
	@$(MAKE) MAKEFLAGS="$(MAKEFLAGS) -j$(shell nproc)" all

# ==============================
##@ Code Testing
# ==============================
.PHONY: bestiary

bestiary: ## Build interactive bestiary
#	@$(MAKE) run -C $(BESTI_DIR)
	@$(MAKE) run-fast -C $(BESTI_DIR)

# ==============================
##@ 🧹 Cleanup
# ==============================
.PHONY: clean fclean ffclean re

clean: ## Remove object files
	@$(call CLEANUP,$(NAME),object files,$(OBJ_DIR))

fclean: clean ## Remove object files and executable
	@$(call CLEANUP,$(NAME),executable,$(NAME))

ffclean: fclean ## Remove all generated files and folders
	@$(MAKE) deps-clean
	@$(call CLEANUP,Build folder,artifacts,$(DEPS_DIR))
	@$(MAKE) script-clean
	@$(MAKE) tree-clean
	@$(MAKE) ffclean -C $(BESTI_DIR)

re: fclean all ## Rebuild everything
