// gdext/src/bestiary/BestiaryFormat.cpp

#include "BestiaryFormat.hpp"

using namespace godot;

static String	indent_lines(const String &s, const String &prefix)
{
	PackedStringArray	out;
	const int			count = s.get_slice_count("\n");

	int	i = 0;
	while (i < count)
	{
		out.push_back(prefix + s.get_slice("\n", i));
		++i;
	}
	return (String("\n").join(out));
}

// static void	append_header(PackedStringArray &t, const BeastData &d)
// {
// 	String	header = String("\n--- ") + String::utf8(d.name.c_str());

// 	if (!d.lore_title.empty())
// 		header += String(" - ") + String::utf8(d.lore_title.c_str());
// 	header += String(" ---\n");
// 	t.push_back(header);
// }

// static void	append_quote(PackedStringArray &t, const BeastData &d)
// {
// 	if (!d.lore_quote.empty())
// 		t.push_back(String("\"") + String::utf8(d.lore_quote.c_str()) + String("\"\n\n"));
// }

String	BestiaryFormat::format_console(const BeastData &d)
{
	const String	NL("\n");
	const String	BULLET = String("  ") + String::chr(0x2022) + String(" ");
	
	PackedStringArray	t;

	// Header
	{
		String	header = String("\n--- ") + String::utf8(d.name.c_str());

		if (!d.lore_title.empty())
			header += String(" - ") + String::utf8(d.lore_title.c_str());
		header += String(" ---\n");
		t.push_back(header);
	}

	// Quote
	if (!d.lore_quote.empty())
		t.push_back(String("\"") + String::utf8(d.lore_quote.c_str()) + String("\"\n\n"));

	// Flavor description bullets
	std::vector<std::string>::const_iterator it = d.lore_flavor_description.begin();
	while (it != d.lore_flavor_description.end())
	{
		t.push_back(String::utf8(it->c_str()) + NL);
		++it;
	}

	// Summary table
	t.push_back(NL + String("Bestiary Entry") + NL);
	if (!d.type.empty())
		t.push_back(String("Type:           ") + String::utf8(d.type.c_str()) + NL);
	if (!d.threat_level.empty())
		t.push_back(String("Threat Level:   ") + String::utf8(d.threat_level.c_str()) + NL);
	if (!d.first_emerged.empty())
		t.push_back(String("First Emerged:  ") + String::utf8(d.first_emerged.c_str()) + NL + NL);

	// Long sections
	if (!d.description.empty())
	{
		t.push_back(String("Description:") + NL);
		t.push_back(indent_lines(String::utf8(d.description.c_str()), String("  ")) + NL + NL);
	}
	if (!d.hue_interaction.empty())
	{
		t.push_back(String("Hue Interaction:") + NL);
		t.push_back(indent_lines(String::utf8(d.hue_interaction.c_str()), BULLET) + NL + NL);
	}
	if (!d.behavior.empty())
	{
		t.push_back(String("Behavior:") + NL);
		t.push_back(indent_lines(String::utf8(d.behavior.c_str()), BULLET) + NL + NL);
	}
	if (!d.weaknesses.empty())
	{
		t.push_back(String("Known Weaknesses:") + NL);
		t.push_back(indent_lines(String::utf8(d.weaknesses.c_str()), BULLET) + NL + NL);
	}
	if (!d.notes.empty())
	{
		t.push_back(String("Notes:") + NL);
		t.push_back(indent_lines(String::utf8(d.notes.c_str()), String("  ")) + NL);
	}

	// Lore entry (field notes)
	if (!d.lore_field_notes.empty())
	{
		t.push_back(NL + String("Lore Entry"));
		if (!d.lore_source.empty())
			t.push_back(String(" - ") + String::utf8(d.lore_source.c_str()));
		t.push_back(NL + NL);
		
		std::vector<std::string>::const_iterator it = d.lore_field_notes.begin();
		while (it != d.lore_field_notes.end())
		{
			t.push_back(String("\"") + String::utf8(it->c_str()) + "\"\n\n");
			++it;
		}
	}

	// Drops
	if (!d.drops.empty())
	{
		t.push_back(NL + String("Drops:") + NL);

		std::vector<std::string>::const_iterator it = d.drops.begin();
		while (it != d.drops.end())
		{
			t.push_back(BULLET + String::utf8(it->c_str()) + NL);
			++it;
		}
	}

	return (String("").join(t));
}

// BBCode version for RichTextLabel pages
String	BestiaryFormat::format_bbcode(const BeastData& d)
{
	const String	B("[b]");
	const String	EB("[/b]");
	const String	I("[i]");
	const String	EI("[/i]");
	const String	QUOTE = String("\"");
	const String	NL = String("\n");
	const String	BULLET = String("  ") + String::chr(0x2022) + String(" ");

	PackedStringArray t;

	// Header
	{
		String	header = NL + B + String::utf8(d.name.c_str());

		if (!d.lore_title.empty())
			header += String(" - ") + String::utf8(d.lore_title.c_str());
		header += EB + NL + NL;
		t.push_back(header);
	}

	// Quote
	if (!d.lore_quote.empty())
		t.push_back(I + QUOTE + String::utf8(d.lore_quote.c_str()) + QUOTE + EI + NL + NL);

	// Flavor description bullets
	std::vector<std::string>::const_iterator it = d.lore_flavor_description.begin();
	while (it != d.lore_flavor_description.end())
	{
		t.push_back(String::utf8(it->c_str()) + NL);
		++it;
	}

	// Summary table
	t.push_back(NL + B + String("Bestiary Entry") + EB + NL);
	if (!d.type.empty())
		t.push_back(B + String("Type:           ") + EB + String::utf8(d.type.c_str()) + NL);
	if (!d.threat_level.empty())
		t.push_back(B + String("Threat Level:   ") + EB + String::utf8(d.threat_level.c_str()) + NL);
	if (!d.first_emerged.empty())
		t.push_back(B + String("First Emerged:  ") + EB + String::utf8(d.first_emerged.c_str()) + NL + NL);

	// Long sections
	if (!d.description.empty())
	{
		t.push_back(B + String("Description:") + EB + NL);
		t.push_back(indent_lines(String::utf8(d.description.c_str()), String("  ")) + NL + NL);
	}
	if (!d.hue_interaction.empty())
	{
		t.push_back(B + String("Hue Interaction:") + EB + NL);
		t.push_back(indent_lines(String::utf8(d.hue_interaction.c_str()), BULLET) + NL + NL);
	}
	if (!d.behavior.empty())
	{
		t.push_back(B + String("Behavior:") + EB + NL);
		t.push_back(indent_lines(String::utf8(d.behavior.c_str()), BULLET) + NL + NL);
	}
	if (!d.weaknesses.empty())
	{
		t.push_back(B + String("Known Weaknesses:") + EB + NL);
		t.push_back(indent_lines(String::utf8(d.weaknesses.c_str()), BULLET) + NL + NL);
	}
	if (!d.notes.empty())
	{
		t.push_back(B + String("Notes:") + EB + NL);
		t.push_back(indent_lines(String::utf8(d.notes.c_str()), String("  ")) + NL);
	}

	// Lore entry (field notes)
	if (!d.lore_field_notes.empty())
	{
		t.push_back(NL + B + String("Lore Entry") + EB);
		if (!d.lore_source.empty())
			t.push_back(String(" - ") + String::utf8(d.lore_source.c_str()));
		t.push_back(NL + NL);

		std::vector<std::string>::const_iterator it = d.lore_field_notes.begin();
		while (it != d.lore_field_notes.end())
		{
			t.push_back(QUOTE + I + String::utf8(it->c_str()) + QUOTE + EI + NL + NL);
			++it;
		}
	}

	if (!d.drops.empty())
	{
		t.push_back(NL + B + String("Drops:") + EB + NL);

		std::vector<std::string>::const_iterator it = d.drops.begin();
		while (it != d.drops.end())
		{
			t.push_back(BULLET + String::utf8(it->c_str()) + NL);
			++it;
		}
	}

	return (String("").join(t));
}
