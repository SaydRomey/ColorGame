// gdext/src/bestiary/BestiaryFormat.cpp

#include "BestiaryFormat.hpp"
using namespace godot;

namespace BestiaryFormat
{
	static const String	NL("\n");
	static const String	BULLET = String("  ") + String::chr(0x2022) + String(" ");

	static String	indent_lines(const String& s, const String& prefix)
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

	String	format_console(const BeastData& d)
	{
		PackedStringArray	t;

		// Header
		String	header = "\n--- " + String::utf8(d.name.c_str());

		if (!d.lore_title.empty())
			header += " - " + String::utf8(d.lore_title.c_str());
		header += " ---\n";
		t.push_back(header);

		// Quote
		if (!d.lore_quote.empty())
			t.push_back("\"" + String::utf8(d.lore_quote.c_str()) + "\"\n\n");

		// Flavor description bullets
		std::vector<std::string>::const_iterator it = d.lore_flavor_description.begin();
		while (it != d.lore_flavor_description.end())
		{
			t.push_back(String::utf8(it->c_str()) + "\n");
			++it;
		}

		// Table-ish section
		t.push_back("\n---\n\n");
		t.push_back("Bestiary Entry\n");
		t.push_back("Type:           " + String::utf8(d.type.c_str()) + "\n");
		t.push_back("Threat Level:   " + String::utf8(d.threat_level.c_str()) + "\n");
		t.push_back("First Emerged:  " + String::utf8(d.first_emerged.c_str()) + "\n\n");

		// Long sections
		if (!d.description.empty())
		{
			t.push_back("Description:\n");
			t.push_back(indent_lines(String::utf8(d.description.c_str()), "  ") + "\n\n");
		}
		if (!d.hue_interaction.empty())
		{
			t.push_back("Hue Interaction:\n");
			t.push_back(indent_lines(String::utf8(d.hue_interaction.c_str()), BULLET) + "\n\n");
		}
		if (!d.behavior.empty())
		{
			t.push_back("Behavior:\n");
			t.push_back(indent_lines(String::utf8(d.behavior.c_str()), BULLET) + "\n\n");
		}
		if (!d.weaknesses.empty())
		{
			t.push_back("Known Weaknesses:\n");
			t.push_back(indent_lines(String::utf8(d.weaknesses.c_str()), BULLET) + "\n\n");
		}
		if (!d.notes.empty())
		{
			t.push_back("Notes:\n");
			t.push_back(indent_lines(String::utf8(d.notes.c_str()), "  ") + "\n");
		}

		// Lore entry (field notes)
		if (!d.lore_field_notes.empty())
		{
			t.push_back("\n---\n\n");
			String	src = String::utf8(d.lore_source.c_str());
			t.push_back("Lore Entry" + (src.is_empty() ? String() : String(" - ") + src) + "\n\n");
			
			std::vector<std::string>::const_iterator it = d.lore_field_notes.begin();
			while (it != d.lore_field_notes.end())
			{
				t.push_back("\"" + String::utf8(it->c_str()) + "\"\n\n");
				++it;
			}
		}

		// Drops
		if (!d.drops.empty())
		{
			t.push_back("\nDrops:\n");

			std::vector<std::string>::const_iterator it = d.drops.begin();
			while (it != d.drops.end())
			{
				t.push_back("  > " + String::utf8(it->c_str()) + "\n");
				++it;
			}
		}
		return (String("").join(t));
	}

	// BBCode version for RichTextLabel pages
	String	format_bbcode(const BeastData& d)
	{
		const String	B = "[b]";
		const String	EB = "[/b]";
		const String	I = "[i]";
		const String	EI = "[/i]";
		const String	NL = "\n";

		PackedStringArray	t;
		t.push_back("[b]" + String::utf8(d.name.c_str()) +
					(d.lore_title.empty() ? "" : " - " + String::utf8(d.lore_title.c_str())) +
					"[/b]" + NL + NL);

		if (!d.lore_quote.empty())
			t.push_back(I + String::utf8(d.lore_quote.c_str()) + EI + NL + NL);

		std::vector<std::string>::const_iterator it = d.lore_flavor_description.begin();
		while (it != d.lore_flavor_description.end())
		{
			t.push_back("• " + String::utf8(it->c_str()) + NL);
			++it;
		}

		t.push_back(NL + "[b]Bestiary Entry[/b]" + NL);
		t.push_back(B "Type:" EB " "           + String::utf8(d.type.c_str()) + NL);
		t.push_back(B "Threat Level:" EB " "   + String::utf8(d.threat_level.c_str()) + NL);
		t.push_back(B "First Emerged:" EB " "  + String::utf8(d.first_emerged.c_str()) + NL + NL);

		if (!d.description.empty())
			t.push_back(B "Description:" EB + NL + String::utf8(d.description.c_str()) + NL + NL);

		if (!d.hue_interaction.empty())
			t.push_back(B "Hue Interaction:" EB + NL + String::utf8(d.hue_interaction.c_str()) + NL + NL);

		if (!d.behavior.empty())
			t.push_back(B "Behavior:" EB + NL + String::utf8(d.behavior.c_str()) + NL + NL);

		if (!d.weaknesses.empty())
			t.push_back(B "Known Weaknesses:" EB + NL + String::utf8(d.weaknesses.c_str()) + NL + NL);

		if (!d.notes.empty())
			t.push_back(B "Notes:" EB + NL + String::utf8(d.notes.c_str()) + NL);

		if (!d.lore_field_notes.empty())
		{
			t.push_back(NL + "[b]Lore Entry[/b]" +
						(d.lore_source.empty() ? "" : " - " + String::utf8(d.lore_source.c_str())) +
						NL + NL);
			
			std::vector<std::string>::const_iterator it = d.lore_field_notes.begin();
			while (it != d.lore_field_notes.end())
			{
				t.push_back(I + String::utf8(it->c_str()) + EI + NL + NL);
				++it;
			}
		}

		if (!d.drops.empty())
		{
			t.push_back(NL "[b]Drops:[/b]" NL);

			std::vector<std::string>::const_iterator it = d.drops.begin();
			while (it != d.drops.end())
			{
				t.push_back("• " + String::utf8(it->c_str()) + NL);
				++it;
			}
		}
		return (String("").join(t));
	}

} // namespace BestiaryFormat

/*
@onready var rtf: RichTextLabel = $RichTextLabel
var index := BestiaryIndexResource.new()

func _ready():
    index.load_dir("res://data/bestiary")
    var entries = index.list_entries()
    # Pick one (by id or id_str depending on your variant)
    var entry: BestiaryEntryResource = index.load_entry_by_id(entries[0].id)
    rtf.bbcode_enabled = true
    rtf.text = BestiaryFormat.format_bbcode(entry.get_raw()) # if you expose this static via a GDExtension utility
    # or: rtf.text = entry.format_console() for quick console-style view
*/
