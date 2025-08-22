// gdext/src/bestiary/BestiaryEntryResource.cpp

#include "BestiaryEntryResource.h"
#include "BestiaryFormat.hpp"

using namespace godot;

void	BestiaryEntryResource::_bind_methods(void)
{
	// Actions
	ClassDB::bind_method(D_METHOD("load_from_file", "path"), &BestiaryEntryResource::load_from_file);

	// Getters to call from GDScript
	ClassDB::bind_method(D_METHOD("get_id"), &BestiaryEntryResource::get_id);
	ClassDB::bind_method(D_METHOD("get_name"), &BestiaryEntryResource::get_name);
	ClassDB::bind_method(D_METHOD("get_type"), &BestiaryEntryResource::get_type);
	ClassDB::bind_method(D_METHOD("get_threat_level"), &BestiaryEntryResource::get_threat_level);
	ClassDB::bind_method(D_METHOD("get_first_emerged"), &BestiaryEntryResource::get_first_emerged);
	ClassDB::bind_method(D_METHOD("get_description"), &BestiaryEntryResource::get_description);
	ClassDB::bind_method(D_METHOD("get_hue_interaction"), &BestiaryEntryResource::get_hue_interaction);
	ClassDB::bind_method(D_METHOD("get_behavior"), &BestiaryEntryResource::get_behavior);
	ClassDB::bind_method(D_METHOD("get_weaknesses"), &BestiaryEntryResource::get_weaknesses);
	ClassDB::bind_method(D_METHOD("get_notes"), &BestiaryEntryResource::get_notes);
	ClassDB::bind_method(D_METHOD("get_lore_title"), &BestiaryEntryResource::get_lore_title);
	ClassDB::bind_method(D_METHOD("get_lore_quote"), &BestiaryEntryResource::get_lore_quote);
	ClassDB::bind_method(D_METHOD("get_lore_flavor_description"), &BestiaryEntryResource::get_lore_flavor_description);
	ClassDB::bind_method(D_METHOD("get_lore_field_notes"), &BestiaryEntryResource::get_lore_field_notes);
	ClassDB::bind_method(D_METHOD("get_lore_source"), &BestiaryEntryResource::get_lore_source);
	ClassDB::bind_method(D_METHOD("get_drops"), &BestiaryEntryResource::get_drops);
	ClassDB::bind_method(D_METHOD("get_source_path"), &BestiaryEntryResource::get_source_path);

	// Formatters
	ClassDB::bind_method(D_METHOD("format_console"), &BestiaryEntryResource::format_console);
	ClassDB::bind_method(D_METHOD("format_bbcode"), &BestiaryEntryResource::format_bbcode);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "_source_path", PROPERTY_HINT_FILE, "*.json"), "", "get_source_path");
}

String	BestiaryEntryResource::to_gd(const std::string &s)
{
	return (String::utf8(s.c_str()));
}

PackedStringArray	BestiaryEntryResource::to_gd(const std::vector<std::string> &v)
{
	PackedStringArray							out;
	std::vector<std::string>::const_iterator	it = v.begin();
	while (it != v.end())
	{
		out.append(String::utf8(it->c_str()));
		++it;
	}
	return (out);
}

// Default Constructor and Destructor
BestiaryEntryResource::BestiaryEntryResource(void) {}
BestiaryEntryResource::~BestiaryEntryResource(void) {}

// Load one JSON file into _data
bool	BestiaryEntryResource::load_from_file(const String &path)
{
	const String	abs = ProjectSettings::get_singleton()->globalize_path(path);
	BeastData		tmp;

	if (!BeastJsonLoader::loadFromFile(std::string(abs.utf8().get_data()), tmp))
	{
		UtilityFunctions::push_warning("BestiaryEntryResource: failed to load ", path);
		return (false);
	}
	_data = tmp;
	_source_path = path;

	return (true);
}

// Read-only getters exposed to GDScript/Inspector
String	BestiaryEntryResource::get_id(void) const { return (to_gd(_data.id)); }

// Entry section
String	BestiaryEntryResource::get_name(void) const { return (to_gd(_data.name)); }
String	BestiaryEntryResource::get_type(void) const { return (to_gd(_data.type)); }
String	BestiaryEntryResource::get_threat_level(void) const { return (to_gd(_data.threat_level)); }
String	BestiaryEntryResource::get_first_emerged(void) const { return (to_gd(_data.first_emerged)); }
String	BestiaryEntryResource::get_description(void) const { return (to_gd(_data.description)); }
String	BestiaryEntryResource::get_hue_interaction(void) const { return (to_gd(_data.hue_interaction)); }
String	BestiaryEntryResource::get_behavior(void) const { return (to_gd(_data.behavior)); }
String	BestiaryEntryResource::get_weaknesses(void) const { return (to_gd(_data.weaknesses)); }
String	BestiaryEntryResource::get_notes(void) const { return (to_gd(_data.notes)); }

// Lore section
String	BestiaryEntryResource::get_lore_title(void) const { return (to_gd(_data.lore_title)); }
String	BestiaryEntryResource::get_lore_quote(void) const { return (to_gd(_data.lore_quote)); }
PackedStringArray	BestiaryEntryResource::get_lore_flavor_description(void) const { return (to_gd(_data.lore_flavor_description)); }
PackedStringArray	BestiaryEntryResource::get_lore_field_notes(void) const { return (to_gd(_data.lore_field_notes)); }
String	BestiaryEntryResource::get_lore_source(void) const { return (to_gd(_data.lore_source)); }

// Drops
PackedStringArray	BestiaryEntryResource::get_drops(void) const { return (to_gd(_data.drops)); }

// Source path
String	BestiaryEntryResource::get_source_path(void) const { return (_source_path); }

// Expose the raw JSON fields for UI binding
const BeastData&	BestiaryEntryResource::get_raw() const { return (_data); }

String	BestiaryEntryResource::format_console() const
{
	return (BestiaryFormat::format_console(_data));
}

String	BestiaryEntryResource::format_bbcode() const
{
	return (BestiaryFormat::format_bbcode(_data));
}
