// gdext/src/greetings/register_types.cpp

#include "register_types.h"

#include "Greetings.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

// Called when Godot loads our plugin
// Called once when Godot loads our library (scene tree level init)
void    initialize_greetings(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
    
        // ClassDB::register_class<Greetings>(); // <- ?
        // GDREGISTER_RUNTIME_CLASS(Greetings);
        GDREGISTER_CLASS(Greetings); // <- editor-visible registration
}

// Called on shutdown (scene tree level)
// Called when Godot unloads our plugin
void    uninitialize_greetings(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

// Exported entry symbol (must match .gdextension's entry_symbol)
extern "C" GDExtensionBool GDE_EXPORT greetings_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
	const GDExtensionClassLibraryPtr p_library,
	GDExtensionInitialization *r_initialization) {

	godot::GDExtensionBinding::InitObject	init_obj(p_get_proc_address, p_library, r_initialization);
    
    init_obj.register_initializer(initialize_greetings);
    init_obj.register_terminator(uninitialize_greetings);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
    return init_obj.init();
}
