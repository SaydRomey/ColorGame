
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
- `deps-picojson`:  Add picoJSON as a submodule
- `deps-godotcpp`:  Add godot-cpp (branch 4.4) as a submodule

## 👾 Godot C++ / GDExtension
- `cpp-new`:  Create new C++ native module using templates (w.i.p.)
- `cpp-build`:  Build all GDextension C++ modules
- `cpp-clean`:  Clean all compiled C++ modules
- `cpp-re`:  Clean and rebuild
- `cpp-status`:  Show available C++ modules and their contents
- `cpp-gdextension-links`:  Regenerate .gdextension files for all C++ modules
- `godot-cpp-bindings`:  Build godot-cpp bindings

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
- `script-edit`:  Interactive: choose a script, then pick an editor (default: EDITOR or $(OPEN))
- `script-clean`:  Clean up test artifacts and logs
- `list-scripts`:  List available scripts
- `script-make-exec`:  Make all scripts in SCRIPT_DIR executable
- `script-make-exec-silent`:  Run script-make-exec but suppress all output

## 🌳 File Structure
- `tree`:  Show file structure (without file listed in TREE_IGNORES)
- `tree-log`:  Logs file structure in TREE_OUTFILE
- `tree-clean`:  Remove 'tree' outfile

📄 Generated at Fri 15 Aug 2025 01:00:20 AM EDT
