
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
C_FLAGS		:= -Wall -Wextra -Werror
STANDARD	:= -std=c++98

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

# * (Replace with the GDExtension cpp .so library...) *
# # Libraries
# LIB_DIR		:= lib
# L_FLAGS		:=

# # Libft
# LIBFT_DIR	:= $(LIB_DIR)/libft
# LIBFT_INC	:= $(LIBFT_DIR)/$(INC_DIR)
# LIBFT		:= $(LIBFT_DIR)/libft.a
# HEADERS		:= $(HEADERS) -I$(LIBFT_INC)

# ==============================
# Makefile Imports
# ==============================
MK_PATH		:= utils/makefiles

include $(MK_PATH)/utils.mk			# Utility Variables and Macros
include $(MK_PATH)/doc.mk			# Documentation Targets
include $(MK_PATH)/class.mk			# CPP Class Creator
include $(MK_PATH)/scripts.mk		# Scripts Management
include $(MK_PATH)/tree.mk			# File structure output

# ==============================
# Default
# ==============================
.DEFAULT_GOAL	:= all

.DEFAULT:
	$(info make: *** No rule to make target '$(MAKECMDGOALS)'.  Stop.)
	@$(MAKE) help $(NPD)

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
.PHONY: all run

all: $(NAME) ## Build the project/executable

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

# # ==============================
# ##@ 🧹 Cleanup
# # ==============================
.PHONY: clean fclean ffclean re

clean: ## Remove object files
	@$(call CLEANUP,$(NAME),object files,$(OBJ_DIR))

fclean: clean ## Remove object files and executable
	@$(call CLEANUP,$(NAME),executable,$(NAME))

ffclean: fclean ## Remove all generated files and folders
	@$(MAKE) script-clean $(NPD)
	@$(MAKE) tree-clean $(NPD)

re: fclean all ## Rebuild everything
