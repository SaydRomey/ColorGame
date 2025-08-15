// gdext/src/greetings/Greetings.cpp

#include "Greetings.h"
// #include <godot_cpp/core/class_db.hpp>

using namespace godot;

/* Static function that Godot will call to find out which methods can be called and which properties it exposes
** Bindings needed if we expose properties/methods to the editor/GDScript.
*/
void	Greetings::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("hello"), &Greetings::hello);
}

Greetings::Greetings()
: _message("hello from Greetings")
{
	// Initialization here
}

Greetings::~Greetings()
{
	// Add our cleanup here if needed
}

void	Greetings::_ready()
{
	const bool	in_editor = Engine::get_singleton()->is_editor_hint();
	set_process(!in_editor);	// disable idle processing in editor
	// set_physics_process(false);	// if we use _physics_process
	if (!in_editor)
		UtilityFunctions::print(hello());	// visible confirmation in output
}

void	Greetings::_process(double delta)
{
	if (Engine::get_singleton()->is_editor_hint())
		return ; // safety guard
	// 
}


String Greetings::hello()
{
	return (_message);
}
