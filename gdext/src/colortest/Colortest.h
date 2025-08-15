// gdext/src/colortest/Colortest.h

// A minimal Node you can add to a scene. Expand as needed.

#ifndef COLORTEST_H
# define COLORTEST_H

# include "godot_includes.h"

# include <godot_cpp/classes/node2d.hpp>
# include <godot_cpp/variant/color.hpp>

namespace godot
{
	class Colortest : public Node2D
	{
		GDCLASS(Colortest, Node2D)

		private:
			double	_t;
			float	_radius;
			Color	_color;

		protected:
			static void	_bind_methods();

		public:
			// Colortest() = default; // ?
			// ~Colortest() = default;
			Colortest();
			~Colortest();

            void    _ready() override;
			void	_process(double delta) override;
			void	_draw() override;

			// Inspector-exposed properties
			void	set_radius(float r);
			float	get_radius() const;

			void	set_color(const Color &c);
			Color	get_color() const;
			
	};
} // namespace godot

#endif // COLORTEST_H
