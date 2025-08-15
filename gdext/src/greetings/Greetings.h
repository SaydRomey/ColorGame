// gdext/src/greetings/Greetings.h

// A minimal Node you can add to a scene. Expand as needed.

#ifndef GREETINGS_H
# define GREETINGS_H

# include "godot_includes.h"
# include <godot_cpp/classes/node.hpp>

namespace godot
{
	class Greetings : public Node
	{
		GDCLASS(Greetings, Node)

		private:
            String  _message;

		protected:
			static void	_bind_methods();

		public:
			Greetings();
			~Greetings();

            void    _ready() override;
			void	_process(double delta) override;
			
			String	hello();
	};
} // namespace godot

#endif // GREETINGS_H
