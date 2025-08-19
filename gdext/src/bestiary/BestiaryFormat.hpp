// gdext/src/bestiary/BestiaryFormat.hpp

#ifndef BESTIARY_FORMAT_HPP
# define BESTIARY_FORMAT_HPP

# include "godot_includes.h"
# include "BeastData.hpp"

namespace BestiaryFormat
{
	// Console-friendly string (Godot Output panel)
	godot::String	format_console(const BeastData& d);

	// BBCode for a RichTextLabel page
	godot::String	format_bbcode(const BeastData& d);
}

#endif // BESTIARY_FORMAT_HPP
