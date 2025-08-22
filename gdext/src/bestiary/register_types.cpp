// gdext/src/bestiary/register_types.cpp

#include "register_types.h"
#include "BestiaryEntryResource.h"
#include "BestiaryIndexResource.h"
#include "godot_includes.h"

using namespace godot;

// Called when Godot loads our plugin/library
void	initialize_bestiary(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return ;

	UtilityFunctions::print("bestiary: initialize start");
	
	GDREGISTER_CLASS(BestiaryEntryResource);
    UtilityFunctions::print("bestiary: registered BestiaryEntryResource");

	GDREGISTER_CLASS(BestiaryIndexResource);
    UtilityFunctions::print("bestiary: registered BestiaryIndexResource");

}

// Called on shutdown (scene tree level), when Godot unloads our plugin
void	uninitialize_bestiary(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return ;
    UtilityFunctions::print("bestiary: uninitialize");
}

// Exported entry symbol (must match .gdextension's entry_symbol)
extern "C"	GDExtensionBool GDE_EXPORT bestiary_init(
	GDExtensionInterfaceGetProcAddress p_get_proc_address,
	const GDExtensionClassLibraryPtr p_library,
	GDExtensionInitialization *r_initialization)
{
	godot::GDExtensionBinding::InitObject	init_obj(
		p_get_proc_address, p_library, r_initialization
	);
	
	init_obj.register_initializer(initialize_bestiary);
	init_obj.register_terminator(uninitialize_bestiary);
	init_obj.set_minimum_library_initialization_level(
		MODULE_INITIALIZATION_LEVEL_SCENE
	);
	return (init_obj.init());
}
