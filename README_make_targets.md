
# 📘 Makefile Targets


## 🛠  Utility
- `help`:  Display available targets
- `repo`:  Open the GitHub repository

## 🎯 Main Targets
- `all`:  Build the project/executable
- `run`:  Compile and run the executable
- `fast`:  Fast build using parallel jobs

## 🧩 Code Testing
- `bestiary`:  Build interactive bestiary

## 🧹 Cleanup
- `clean`:  Remove object files
- `fclean`:  Remove object files and executable
- `ffclean`:  Remove all generated files and folders
- `re`:  Rebuild everything

## 📦 Dependency setup
- `deps`:  Initialize and update all git submodules
- `picojson`:  Add picoJSON as a submodule

## 📚 Documentation
- `doc`:  Show documentation links
- `help-md`:  Generate markdown documentation for all Make targets

## 🤖 Class creator
- `class`:  Prompt assisted class creation

## 🐾 Beast stub generator
- `beast`:  Generate stub Beast class from template
- `all-beasts`:  Auto-generate stub classes for all BestiaryIDs

## 📜 Scripts
- `new-script`:  Create a new script from the template
- `script`:  Interactive script selection menu
- `script-clean`:  Clean up test artifacts and logs
- `list-scripts`:  List available scripts
- `script-make-exec`:  Make all scripts in SCRIPT_DIR executable
- `script-make-exec-silent`:  Run script-make-exec but suppress all output

## 🌳 File Structure
- `tree`:  Show file structure (without file listed in TREE_IGNORES)
- `tree-log`:  Logs file structure in TREE_OUTFILE
- `tree-clean`:  Remove 'tree' outfile

📄 Generated at Thu 07 Aug 2025 04:00:09 PM EDT
