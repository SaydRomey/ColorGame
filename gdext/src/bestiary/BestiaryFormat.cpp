// // gdext/src/bestiary/BestiaryFormat.cpp

// #include "BestiaryFormat.hpp"
// #include "godot_includes.h"

// using namespace godot;

// namespace BestiaryFormat
// {
// 	static const String	NL("\n");
// 	static const String	BULLET = String("  ") + String::chr(0x2022) + String(" ");

// 	static String	indent_lines(const String &s, const String &prefix)
// 	{
// 		PackedStringArray	out;
// 		const int			count = s.get_slice_count("\n");

// 		int	i = 0;
// 		while (i < count)
// 		{
// 			out.push_back(prefix + s.get_slice("\n", i));
// 			++i;
// 		}
// 		return (String("\n").join(out));
// 	}

// 	String	format_console(const BeastData &d)
// 	{
// 		PackedStringArray	t;

// 		// Header
// 		String	header = String("\n--- ") + String::utf8(d.name.c_str());

// 		if (!d.lore_title.empty())
// 			header += String(" - ") + String::utf8(d.lore_title.c_str());
// 		header += String(" ---\n");
// 		t.push_back(header);

// 		// Quote
// 		if (!d.lore_quote.empty())
// 			t.push_back(String("\"") + String::utf8(d.lore_quote.c_str()) + String("\"\n\n"));

// 		// Flavor description bullets
// 		std::vector<std::string>::const_iterator it = d.lore_flavor_description.begin();
// 		while (it != d.lore_flavor_description.end())
// 		{
// 			t.push_back(String::utf8(it->c_str()) + String("\n"));
// 			++it;
// 		}

// 		// Summary table
// 		// t.push_back(NL + String("[b]Bestiary Entry[/b]") + NL);
// 		// if (!d.type.empty())
// 		// 	t.push_back(String("[b]Type:[\b] ") + String::utf8(d.type.c_str()) + NL);
// 		// if (!d.threat_level.empty())
// 		// 	t.push_back(String("[b]Threat Level:[\b] ") + String::utf8(d.threat_level.c_str()) + NL);
// 		// if (!d.first_emerged.empty())
// 		// 	t.push_back(String("[b]First Emerged:[\b] ") + String::utf8(d.first_emerged.c_str()) + NL + NL);
// 		// 
// 		t.push_back(NL + String("Bestiary Entry") + NL);
// 		if (!d.type.empty())
// 			t.push_back(String("Type:           ") + String::utf8(d.type.c_str()) + NL);
// 		if (!d.threat_level.empty())
// 			t.push_back(String("Threat Level:   ") + String::utf8(d.threat_level.c_str()) + NL);
// 		if (!d.first_emerged.empty())
// 			t.push_back(String("First Emerged:  ") + String::utf8(d.first_emerged.c_str()) + NL + NL);

// 		// Long sections
// 		if (!d.description.empty())
// 		{
// 			// t.push_back(String("[b]Description:[\b]") + NL);
// 			t.push_back(String("Description:") + NL);
// 			t.push_back(indent_lines(String::utf8(d.description.c_str()), String("  ")) + NL + NL);
// 		}
// 		if (!d.hue_interaction.empty())
// 		{
// 			// t.push_back(String("[b]Hue Interaction:[\b]") + NL);
// 			t.push_back(String("Hue Interaction:") + NL);
// 			t.push_back(indent_lines(String::utf8(d.hue_interaction.c_str()), BULLET) + NL + NL);
// 		}
// 		if (!d.behavior.empty())
// 		{
// 			// t.push_back(String("[b]Behavior:[\b]") + NL);
// 			t.push_back(String("Behavior:") + NL);
// 			t.push_back(indent_lines(String::utf8(d.behavior.c_str()), BULLET) + NL + NL);
// 		}
// 		if (!d.weaknesses.empty())
// 		{
// 			// t.push_back(String("[b]Known Weaknesses:[\b]") + NL);
// 			t.push_back(String("Known Weaknesses:") + NL);
// 			t.push_back(indent_lines(String::utf8(d.weaknesses.c_str()), BULLET) + NL + NL);
// 		}
// 		if (!d.notes.empty())
// 		{
// 			// t.push_back(String("[b]Notes:[\b]") + NL);
// 			t.push_back(String("Notes:") + NL);
// 			t.push_back(indent_lines(String::utf8(d.notes.c_str()), String("  ")) + NL);
// 		}

// 		// Lore entry (field notes)
// 		if (!d.lore_field_notes.empty())
// 		{
// 			// t.push_back(NL + String("[b]Lore Entry[\b]"));
// 			t.push_back(NL + String("Lore Entry"));
// 			if (!d.lore_source.empty())
// 				t.push_back(String(" - ") + String::utf8(d.lore_source.c_str()));
// 			t.push_back(NL + NL);
			
// 			std::vector<std::string>::const_iterator it = d.lore_field_notes.begin();
// 			while (it != d.lore_field_notes.end())
// 			{
// 				t.push_back(String("\"") + String::utf8(it->c_str()) + "\"\n\n");
// 				++it;
// 			}
// 		}

// 		// Drops
// 		if (!d.drops.empty())
// 		{
// 			// t.push_back(NL + String("[b]Drops:[\b]") + NL);
// 			t.push_back(NL + String("Drops:") + NL);

// 			std::vector<std::string>::const_iterator it = d.drops.begin();
// 			while (it != d.drops.end())
// 			{
// 				t.push_back(BULLET + String::utf8(it->c_str()) + NL);
// 				++it;
// 			}
// 		}
// 		return (String("").join(t));
// 	}

// 	// BBCode version for RichTextLabel pages
// 	String	format_bbcode(const BeastData& d)
// 	{
// 		// For now same as console; might customize to use BBCode tags
// 		return (format_console(d));

// 		// const String	B = "[b]";
// 		// const String	EB = "[/b]";
// 		// const String	I = "[i]";
// 		// const String	EI = "[/i]";
// 		// const String	NL = "\n";

// 		// PackedStringArray	t;
// 		// t.push_back("[b]" + String::utf8(d.name.c_str()) +
// 		// 			(d.lore_title.empty() ? "" : " - " + String::utf8(d.lore_title.c_str())) +
// 		// 			"[/b]" + NL + NL);

// 		// if (!d.lore_quote.empty())
// 		// 	t.push_back(I + String::utf8(d.lore_quote.c_str()) + EI + NL + NL);

// 		// std::vector<std::string>::const_iterator it = d.lore_flavor_description.begin();
// 		// while (it != d.lore_flavor_description.end())
// 		// {
// 		// 	t.push_back("• " + String::utf8(it->c_str()) + NL);
// 		// 	++it;
// 		// }

// 		// t.push_back(NL + "[b]Bestiary Entry[/b]" + NL);
// 		// t.push_back(B "Type:" EB " "           + String::utf8(d.type.c_str()) + NL);
// 		// t.push_back(B "Threat Level:" EB " "   + String::utf8(d.threat_level.c_str()) + NL);
// 		// t.push_back(B "First Emerged:" EB " "  + String::utf8(d.first_emerged.c_str()) + NL + NL);

// 		// if (!d.description.empty())
// 		// 	t.push_back(B "Description:" EB + NL + String::utf8(d.description.c_str()) + NL + NL);

// 		// if (!d.hue_interaction.empty())
// 		// 	t.push_back(B "Hue Interaction:" EB + NL + String::utf8(d.hue_interaction.c_str()) + NL + NL);

// 		// if (!d.behavior.empty())
// 		// 	t.push_back(B "Behavior:" EB + NL + String::utf8(d.behavior.c_str()) + NL + NL);

// 		// if (!d.weaknesses.empty())
// 		// 	t.push_back(B "Known Weaknesses:" EB + NL + String::utf8(d.weaknesses.c_str()) + NL + NL);

// 		// if (!d.notes.empty())
// 		// 	t.push_back(B "Notes:" EB + NL + String::utf8(d.notes.c_str()) + NL);

// 		// if (!d.lore_field_notes.empty())
// 		// {
// 		// 	t.push_back(NL + "[b]Lore Entry[/b]" +
// 		// 				(d.lore_source.empty() ? "" : " - " + String::utf8(d.lore_source.c_str())) +
// 		// 				NL + NL);
			
// 		// 	std::vector<std::string>::const_iterator it = d.lore_field_notes.begin();
// 		// 	while (it != d.lore_field_notes.end())
// 		// 	{
// 		// 		t.push_back(I + String::utf8(it->c_str()) + EI + NL + NL);
// 		// 		++it;
// 		// 	}
// 		// }

// 		// if (!d.drops.empty())
// 		// {
// 		// 	t.push_back(NL "[b]Drops:[/b]" NL);

// 		// 	std::vector<std::string>::const_iterator it = d.drops.begin();
// 		// 	while (it != d.drops.end())
// 		// 	{
// 		// 		t.push_back("• " + String::utf8(it->c_str()) + NL);
// 		// 		++it;
// 		// 	}
// 		// }
// 		// return (String("").join(t));
// 	}

// } // namespace BestiaryFormat

// /*
// @onready var rtf: RichTextLabel = $RichTextLabel
// var index := BestiaryIndexResource.new()

// func _ready():
//     index.load_dir("res://data/bestiary")
//     var entries = index.list_entries()
//     # Pick one (by id or id_str depending on your variant)
//     var entry: BestiaryEntryResource = index.load_entry_by_id(entries[0].id)
//     rtf.bbcode_enabled = true
//     rtf.text = BestiaryFormat.format_bbcode(entry.get_raw()) # if you expose this static via a GDExtension utility
//     # or: rtf.text = entry.format_console() for quick console-style view
// */

#include "BestiaryFormat.hpp"
using namespace godot;

static String indent_lines(const String &s, const String &prefix) {
    PackedStringArray out;
    int count = s.get_slice_count("\n");
    for (int i = 0; i < count; ++i) {
        out.push_back(prefix + s.get_slice("\n", i));
    }
    return String("\n").join(out);
}

String BestiaryFormat::format_console(const BeastData &d) {
    const String BULLET = String("  ") + String::chr(0x2022) + String(" ");

    PackedStringArray t;

    // Header
    {
        String header = String("\n--- ") + String::utf8(d.name.c_str());
        if (!d.lore_title.empty()) {
            header += String(" - ") + String::utf8(d.lore_title.c_str());
        }
        header += String(" ---\n");
        t.push_back(header);
    }

    // Quote
    if (!d.lore_quote.empty()) {
        t.push_back(String("\"") + String::utf8(d.lore_quote.c_str()) + String("\"\n\n"));
    }

    // Flavor bullets
    for (size_t i = 0; i < d.lore_flavor_description.size(); ++i) {
        t.push_back(String::utf8(d.lore_flavor_description[i].c_str()) + String("\n"));
    }

    t.push_back(String("\n---\n\n"));
    t.push_back(String("Bestiary Entry\n"));
    t.push_back(String("Type:           ") + String::utf8(d.type.c_str()) + String("\n"));
    t.push_back(String("Threat Level:   ") + String::utf8(d.threat_level.c_str()) + String("\n"));
    t.push_back(String("First Emerged:  ") + String::utf8(d.first_emerged.c_str()) + String("\n\n"));

    if (!d.description.empty()) {
        t.push_back(String("Description:\n"));
        t.push_back(indent_lines(String::utf8(d.description.c_str()), String("  ")) + String("\n\n"));
    }
    if (!d.hue_interaction.empty()) {
        t.push_back(String("Hue Interaction:\n"));
        t.push_back(indent_lines(String::utf8(d.hue_interaction.c_str()), BULLET) + String("\n\n"));
    }
    if (!d.behavior.empty()) {
        t.push_back(String("Behavior:\n"));
        t.push_back(indent_lines(String::utf8(d.behavior.c_str()), BULLET) + String("\n\n"));
    }
    if (!d.weaknesses.empty()) {
        t.push_back(String("Known Weaknesses:\n"));
        t.push_back(indent_lines(String::utf8(d.weaknesses.c_str()), BULLET) + String("\n\n"));
    }
    if (!d.notes.empty()) {
        t.push_back(String("Notes:\n"));
        t.push_back(indent_lines(String::utf8(d.notes.c_str()), String("  ")) + String("\n"));
    }

    if (!d.lore_field_notes.empty()) {
        t.push_back(String("\n---\n\n"));
        String src = String::utf8(d.lore_source.c_str());
        t.push_back(String("Lore Entry") + (src.is_empty() ? String() : String(" - ") + src) + String("\n\n"));
        for (size_t i = 0; i < d.lore_field_notes.size(); ++i) {
            t.push_back(String("\"") + String::utf8(d.lore_field_notes[i].c_str()) + String("\"\n\n"));
        }
    }

    if (!d.drops.empty()) {
        t.push_back(String("\nDrops:\n"));
        for (size_t i = 0; i < d.drops.size(); ++i) {
            t.push_back(String("  • ") + String::utf8(d.drops[i].c_str()) + String("\n"));
        }
    }

    return String("").join(t);
}

String BestiaryFormat::format_bbcode(const BeastData &d) {
    const String NL = String("\n");

    PackedStringArray t;

    // Header
    {
        String header = String("\n[b]") + String::utf8(d.name.c_str());
        if (!d.lore_title.empty())
            header += String(" - ") + String::utf8(d.lore_title.c_str());
        header += String("[/b]") + NL + NL;
        t.push_back(header);
    }

    // Quote
    if (!d.lore_quote.empty()) {
        t.push_back(String("[i]\"") + String::utf8(d.lore_quote.c_str()) + String("\"[/i]") + NL + NL);
    }

    for (size_t i = 0; i < d.lore_flavor_description.size(); ++i) {
        t.push_back(String("• ") + String::utf8(d.lore_flavor_description[i].c_str()) + NL);
    }

    t.push_back(NL + String("[b]Bestiary Entry[/b]") + NL);
    t.push_back(String("[b]Type:[/b] ") + String::utf8(d.type.c_str()) + NL);
    t.push_back(String("[b]Threat Level:[/b] ") + String::utf8(d.threat_level.c_str()) + NL);
    t.push_back(String("[b]First Emerged:[/b] ") + String::utf8(d.first_emerged.c_str()) + NL + NL);

    if (!d.description.empty())
        t.push_back(String("[b]Description:[/b]") + NL + String::utf8(d.description.c_str()) + NL + NL);
    if (!d.hue_interaction.empty())
        t.push_back(String("[b]Hue Interaction:[/b]") + NL + String::utf8(d.hue_interaction.c_str()) + NL + NL);
    if (!d.behavior.empty())
        t.push_back(String("[b]Behavior:[/b]") + NL + String::utf8(d.behavior.c_str()) + NL + NL);
    if (!d.weaknesses.empty())
        t.push_back(String("[b]Known Weaknesses:[/b]") + NL + String::utf8(d.weaknesses.c_str()) + NL + NL);
    if (!d.notes.empty())
        t.push_back(String("[b]Notes:[/b]") + NL + String::utf8(d.notes.c_str()) + NL);

    if (!d.lore_field_notes.empty()) {
        t.push_back(NL + String("[b]Lore Entry[/b]"));
        if (!d.lore_source.empty())
            t.push_back(String(" - ") + String::utf8(d.lore_source.c_str()));
        t.push_back(NL + NL);
        for (size_t i = 0; i < d.lore_field_notes.size(); ++i) {
            t.push_back(String("[i]\"") + String::utf8(d.lore_field_notes[i].c_str()) + String("\"[/i]") + NL + NL);
        }
    }

    if (!d.drops.empty()) {
        t.push_back(NL + String("[b]Drops:[/b]") + NL);
        for (size_t i = 0; i < d.drops.size(); ++i) {
            t.push_back(String("• ") + String::utf8(d.drops[i].c_str()) + NL);
        }
    }

    return String("").join(t);
}
