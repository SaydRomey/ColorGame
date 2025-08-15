// gdext/src/colortest/register_types.cpp

#include "register_types.h"

#include "Colortest.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

// Called when Godot loads our plugin
// Called once when Godot loads our library (scene tree level init)
void    initialize_colortest(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
    
        // ClassDB::register_class<Colortest>(); // <- ?
        // GDREGISTER_RUNTIME_CLASS(Colortest);
        GDREGISTER_CLASS(Colortest); // <- editor-visible registration
}

// Called on shutdown (scene tree level)
// Called when Godot unloads our plugin
void    uninitialize_colortest(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

// Exported entry symbol (must match .gdextension's entry_symbol)
extern "C" GDExtensionBool GDE_EXPORT colortest_init(
    GDExtensionInterfaceGetProcAddress  p_get_proc_address,
	const GDExtensionClassLibraryPtr    p_library,
	GDExtensionInitialization           *r_initialization) {

	godot::GDExtensionBinding::InitObject	init_obj(p_get_proc_address, p_library, r_initialization);
    
    init_obj.register_initializer(initialize_colortest);
    init_obj.register_terminator(uninitialize_colortest);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
    return init_obj.init();
}
