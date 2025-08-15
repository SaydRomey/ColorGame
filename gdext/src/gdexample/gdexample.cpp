
#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>
#include <cmath> // for std::sin / std::cos
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

/* Static function that Godot will call to find out which methods can be called and which properties it exposes
** Bindings needed if we expose properties/methods to the editor/GDScript.
*/
void	GDExample::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_amplitude"), &GDExample::get_amplitude);
	ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &GDExample::set_amplitude);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");

	ClassDB::bind_method(D_METHOD("get_speed"), &GDExample::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &GDExample::set_speed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed");

	// Signal
	ADD_SIGNAL(MethodInfo("position_changed", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::VECTOR2, "new_pos")));
}

GDExample::GDExample()
: time_passed(0.0), time_emit(0.0), amplitude(10.0), speed(1.0)
{
	// Initialize any variables here.
	
	// time_passed = 0.0;
	// time_emit = 0.0;
	// amplitude = 10.0;
	// speed = 1.0;

	// set_process(true); // crucial?: enable _process callbacks (or in _ready function?)
}

GDExample::~GDExample()
{
	// Add our cleanup here if needed
}

void	GDExample::_ready()
{
	const bool	in_editor = Engine::get_singleton()->is_editor_hint();
	set_process(!in_editor);	// disable idle processing in editor
	// set_physics_process(false);	// if we use _physics_process
}

void	GDExample::_process(double delta)
{
	if (Engine::get_singleton()->is_editor_hint())
		return ; // safety guard
	
	time_passed += speed * delta;

	// Vector2	new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));
	Vector2	new_position = Vector2(
		amplitude + (amplitude * std::sin(time_passed * 2.0)),
		amplitude + (amplitude * std::cos(time_passed * 1.5))
	);

	set_position(new_position);

	time_emit += delta;
	if (time_emit > 1.0)
	{
		emit_signal("position_changed", this, new_position);

		time_emit = 0.0;
	}
}

void	GDExample::set_amplitude(const double p_amplitude) { amplitude = p_amplitude; }
double	GDExample::get_amplitude() const { return (amplitude); }

void	GDExample::set_speed(const double p_speed) { speed = p_speed; }
double	GDExample::get_speed() const { return (speed); }

