
# ==============================
##@ 🐾 Beast stub generator
# ==============================

beast: ## Generate stub Beast class from template
	@echo "Enter the Beast ID (e.g. AlchemicalEcho): "; \
	read beastname; \
	beast_upper=`echo $$beastname | tr a-z A-Z`; \
	\
	read -p "Use default header directory '$(INC_DIR)'? [y/Y] for yes, or enter custom: " header_dir; \
	if [ "$$header_dir" = "y" ] || [ "$$header_dir" = "Y" ] || [ -z "$$header_dir" ]; then \
		header_dir="$(INC_DIR)"; \
	fi; \
	\
	read -p "Use default source directory '$(SRC_DIR)'? [y/Y] for yes, or enter custom: " source_dir; \
	if [ "$$source_dir" = "y" ] || [ "$$source_dir" = "Y" ] || [ -z "$$source_dir" ]; then \
		source_dir="$(SRC_DIR)"; \
	fi; \
	mkdir -p "$$header_dir"; \
	mkdir -p "$$source_dir"; \
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
	cp utils/templates/Beast.hpp.template "$$header_dir/$$beastname.hpp"; \
	cp utils/templates/Beast.cpp.template "$$source_dir/$$beastname.cpp"; \
	\
	sed -i "s/CLASSNAME/$$beastname/g" \
		"$$header_dir/$$beastname.hpp" \
		"$$source_dir/$$beastname.cpp"; \
	sed -i "s/CLASSNAME_UPPER/$$beast_upper/g" \
		"$$header_dir/$$beastname.hpp"; \
	sed -i "s/BEAST_CLASSNAME_UPPER/BEAST_$$beast_upper/g" \
		"$$source_dir/$$beastname.cpp"; \
	\
	echo "$(GREEN)Beast stub '$$beastname' created!$(RESET)"

# ==============================
##@ 🧙 Generate ALL Beast stubs
# ==============================
BESTIARY_HEADER ?= ./inc/BestiaryIDs.hpp
BEAST_INC_DIR	:= $(INC_DIR)/enemies
BEAST_SRC_DIR	:= $(SRC_DIR)/enemies

all-beasts: ## Auto-generate stub classes for all BestiaryIDs
	@echo "Generating stubs from: $(BESTIARY_HEADER)"
	@grep '^	BEAST_' $(BESTIARY_HEADER) | sed 's/[ ,]*$$//' | \
	while read line; do \
		id_raw=$$(echo $$line | cut -d' ' -f1); \
		id=$$(echo $$id_raw | sed 's/BEAST_//'); \
		classname=$$(echo "$$id" | awk -F'_' '{for (i=1;i<=NF;i++) $$i=toupper(substr($$i,1,1)) tolower(substr($$i,2)); print}' | tr -d ' '); \
		classname_upper=$$(echo $$classname | tr a-z A-Z); \
		mkdir -p $(BEAST_INC_DIR) $(BEAST_SRC_DIR); \
		hpp_file="$(BEAST_INC_DIR)/$$classname.hpp"; \
		cpp_file="$(BEAST_SRC_DIR)/$$classname.cpp"; \
		if [ -f "$$hpp_file" ] || [ -f "$$cpp_file" ]; then \
			echo "Skipping existing: $$classname"; \
			continue; \
		fi; \
		cp utils/templates/Beast.hpp.template "$$hpp_file"; \
		cp utils/templates/Beast.cpp.template "$$cpp_file"; \
		sed -i "s/BEAST_CLASSNAME_UPPER/$$id_raw/g" "$$cpp_file"; \
		sed -i "s/CLASSNAME_UPPER/$$classname_upper/g" "$$hpp_file"; \
		sed -i "s/CLASSNAME/$$classname/g" "$$hpp_file" "$$cpp_file"; \
		echo "Generated: $$classname"; \
	done
	@echo "$(GREEN)All beast stubs generated.$(RESET)"

.PHONY: beasts all-beasts
