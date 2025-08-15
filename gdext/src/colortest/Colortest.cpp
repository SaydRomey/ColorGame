// gdext/src/colortest/Colortest.cpp

#include "Colortest.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <cmath> // std::sin, std::cos

using namespace godot;

/* Static function that Godot will call to find out which methods can be called and which properties it exposes
** Bindings needed if we expose properties/methods to the editor/GDScript.
*/
void	Colortest::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_radius", "r"), &Colortest::set_radius);
    ClassDB::bind_method(D_METHOD("get_radius"), &Colortest::get_radius);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "radius", PROPERTY_HINT_RANGE, "1,200,1"), "set_radius", "get_radius");

    ClassDB::bind_method(D_METHOD("set_color", "c"), &Colortest::set_color);
    ClassDB::bind_method(D_METHOD("get_color"), &Colortest::get_color);
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
}

Colortest::Colortest() : _t(0.0)
{
	// Initialization here
	_radius = 20.0f;
	_color = Color(0.9f, 0.2f, 0.3f, 1.0f);
}

Colortest::~Colortest()
{
	// Add our cleanup here if needed
}

void	Colortest::_ready()
{
	const bool	in_editor = Engine::get_singleton()->is_editor_hint();
	set_process(!in_editor);	// disable idle processing in editor
	// set_physics_process(false);	// if we use _physics_process
	if (!in_editor)
		queue_redraw();	// only request redraw at runtime
}

void	Colortest::_process(double delta)
{
	if (Engine::get_singleton()->is_editor_hint())
		return ; // safety guard

	_t += delta;

	// Simple orbit around (200,200) so it's visible by default.
	const float	R = 100.0f;
	Vector2	pos(200.0f + R * std::cos(_t * 1.3), 200.0f + R * std::sin(_t));
	set_position(pos);

	queue_redraw();	// request a redraw each frame
}


void Colortest::_draw()
{
	// Draww a filled circle centered on the node's local origin
	draw_circle(Vector2(0, 0), _radius, _color);

	// Optional: a small white line to show orientation
	draw_line(Vector2(0, 0), Vector2(_radius, 0), Color(1, 1, 1, 1), 2.0f);
}

void Colortest::set_radius(float r)
{
	_radius = r;
	queue_redraw();
}

float Colortest::get_radius() const
{
	return (_radius);
}

void Colortest::set_color(const Color &c)
{
	_color = c;
	queue_redraw();
}

Color Colortest::get_color() const
{
	return (_color);
}
