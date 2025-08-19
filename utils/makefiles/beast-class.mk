
# TODO: Use Variables for template paths

# ==============================
##@ 🐾 Beast stub generator
# ==============================
ifndef __BEAST_CLASS_MK__
__BEAST_CLASS_MK__ := 1

BESTIARY_HEADER		?= ./inc/BestiaryIDs.hpp
BEAST_INC_DIR		:= $(INC_DIR)/enemies
BEAST_SRC_DIR		:= $(SRC_DIR)/enemies

TEMPLATE_DIR		?= utils/templates
BEAST_TEMPLATE_DIR	:= $(TEMPLATE_DIR)/class-templates
BEAST_CPP_TEMPLATE	:= $(BEAST_TEMPLATE_DIR)/Beast.cpp
BEAST_HPP_TEMPLATE	:= $(BEAST_TEMPLATE_DIR)/Beast.hpp

# ==============================
# Beast Class Targets
# ==============================
.PHONY: beasts all-beasts

beast: ## Generate stub Beast class from template
	@echo "Enter the Beast ID (e.g. BigBadWolf): "; \
	read beastname; \
	beast_upper=`echo $$beastname | tr a-z A-Z`; \
	\
	# Prompt for .hpp directory \
	read -p "Use default header directory '$(INC_DIR)'? [y/Y] for yes, or enter custom: " header_dir; \
	if [ "$$header_dir" = "y" ] || [ "$$header_dir" = "Y" ] || [ -z "$$header_dir" ]; then \
		header_dir="$(INC_DIR)"; \
	fi; \
	\
	# Prompt for .cpp directory \
	read -p "Use default source directory '$(SRC_DIR)'? [y/Y] for yes, or enter custom: " source_dir; \
	if [ "$$source_dir" = "y" ] || [ "$$source_dir" = "Y" ] || [ -z "$$source_dir" ]; then \
		source_dir="$(SRC_DIR)"; \
	fi; \
	$(MKDIR) "$$header_dir"; \
	$(MKDIR) "$$source_dir"; \
	\
	# Check for file existence \
	if [ -f "$$header_dir/$$beastname.hpp" ] || [ -f "$$source_dir/$$beastname.cpp" ]; then \
		read -p "Files exist in selected directories. Overwrite? [y/N]: " confirm; \
		if [ "$$confirm" != "y" ] && [ "$$confirm" != "Y" ]; then \
			echo "Canceling class creation"; \
			exit 1; \
		fi; \
	fi; \
	\
	# Generate header and source files from templates \
	cp utils/templates/class-templates/Beast.hpp.template "$$header_dir/$$beastname.hpp"; \
	cp utils/templates/class-templates/Beast.cpp.template "$$source_dir/$$beastname.cpp"; \
	\
	$(SED_INPLACE) "s/CLASSNAME/$$beastname/g" \
		"$$header_dir/$$beastname.hpp" \
		"$$source_dir/$$beastname.cpp"; \
	$(SED_INPLACE) "s/CLASSNAME_UPPER/$$beast_upper/g" \
		"$$header_dir/$$beastname.hpp"; \
	$(SED_INPLACE) "s/BEAST_CLASSNAME_UPPER/BEAST_$$beast_upper/g" \
		"$$source_dir/$$beastname.cpp"; \
	\
	$(call SUCCESS,Beast Class,Beast stub '$$beastname' created!)

all-beasts: ## Auto-generate stub classes for all BestiaryIDs
	@read -p "Use default BestiaryIDs header '$(BESTIARY_HEADER)'? [y/Y] for yes, or enter custom: " bestiary_header; \
	if [ "$$bestiary_header" = "y" ] || [ "$$bestiary_header" = "Y" ] || [ -z "$$bestiary_header" ]; then \
		bestiary_header="$(BESTIARY_HEADER)"; \
	fi; \
	if [ ! -f "$$bestiary_header" ]; then \
		$(call ERROR,Beast Class,BestiaryIDs header not found at: $$bestiary_header); \
		exit 1; \
	fi; \
	\
	# Prompt for .hpp directory \
	read -p "Use default header directory '$(INC_DIR)'? [y/Y] for yes, or enter custom: " header_dir; \
	if [ "$$header_dir" = "y" ] || [ "$$header_dir" = "Y" ] || [ -z "$$header_dir" ]; then \
		header_dir="$(INC_DIR)"; \
	fi; \
	\
	# Prompt for .cpp directory \
	read -p "Use default source directory '$(SRC_DIR)'? [y/Y] for yes, or enter custom: " source_dir; \
	if [ "$$source_dir" = "y" ] || [ "$$source_dir" = "Y" ] || [ -z "$$source_dir" ]; then \
		source_dir="$(SRC_DIR)"; \
	fi; \
	$(MKDIR) "$$header_dir" "$$source_dir"; \
	$(call INFO,Beast Class,Generating stubs from: $$bestiary_header)
	@grep '^	BEAST_' $$bestiary_header | sed 's/[ ,]*$$//' | \
	while read line; do \
		id_raw=$$(echo $$line | cut -d' ' -f1); \
		id=$$(echo $$id_raw | sed 's/BEAST_//'); \
		classname=$$(echo "$$id" | awk -F'_' '{for (i=1;i<=NF;i++) $$i=toupper(substr($$i,1,1)) tolower(substr($$i,2)); print}' | tr -d ' '); \
		classname_upper=$$(echo $$classname | tr a-z A-Z); \
		hpp_file="$$header_dir/$$classname.hpp"; \
		cpp_file="$$source_dir/$$classname.cpp"; \
		if [ -f "$$hpp_file" ] || [ -f "$$cpp_file" ]; then \
			echo "Skipping existing: $$classname"; \
			continue; \
		fi; \
		cp utils/templates/class-templates/Beast.hpp.template "$$hpp_file"; \
		cp utils/templates/class-templates/Beast.cpp.template "$$cpp_file"; \
		$(SED_INPLACE) "s/BEAST_CLASSNAME_UPPER/$$id_raw/g" "$$cpp_file"; \
		$(SED_INPLACE) "s/CLASSNAME_UPPER/$$classname_upper/g" "$$hpp_file"; \
		$(SED_INPLACE) "s/CLASSNAME/$$classname/g" "$$hpp_file" "$$cpp_file"; \
		echo "Generated: $$classname"; \
	done
	@$(call SUCCESS,Beast Class,All beast stubs generated.)

endif # __BEAST_CLASS_MK__
