// gdext/src/bestiary/BestiaryIndexResource.cpp

#include "BestiaryIndexResource.h"
#include "BestiaryEntryResource.h"
// #include "BestiaryIDs.hpp"

#include "picojson.h"
#include <fstream>
#include <filesystem>

using namespace godot;

void    BestiaryIndexResource::_bind_methods(void)
{
	ClassDB::bind_method(D_METHOD("load_dir", "res_dir"), &BestiaryIndexResource::load_dir);
	ClassDB::bind_method(D_METHOD("list_entries"), &BestiaryIndexResource::list_entries);
	// ClassDB::bind_method(D_METHOD("load_entry_by_id", "id"), &BestiaryIndexResource::load_entry_by_id);
	ClassDB::bind_method(D_METHOD("load_entry_by_str_id", "id_str"), &BestiaryIndexResource::load_entry_by_str_id);

}

// Default Constructor and Destructor
BestiaryIndexResource::BestiaryIndexResource(void) {}
BestiaryIndexResource::~BestiaryIndexResource(void) {}

// Helpers
static String   get_string_field(const picojson::object &obj, const char *key)
{
	picojson::object::const_iterator    it;
	
	it = obj.find(key);
	if (it != obj.end() && it->second.is<std::string>())
		return (String::utf8(it->second.get<std::string>().c_str()));

	return (String());
}

static bool read_min_meta(const std::string &abs_path,
						  String &id_str, String &name, String &type, String &threat)
{
	std::ifstream   in(abs_path.c_str());
	if (!in)
		return (false);

	picojson::value root;
	in >> root;
	if (!root.is<picojson::object>())
		return (false);

	const picojson::object  &obj = root.get<picojson::object>();

	// id (string)
	picojson::object::const_iterator	it_id = obj.find("id");
	if (it_id == obj.end() || !it_id->second.is<std::string>())
		return (false);
	id_str = String::utf8(it_id->second.get<std::string>().c_str());

	// entry object
	picojson::object::const_iterator	it_entry = obj.find("entry");
	if (it_entry == obj.end() || !it_entry->second.is<picojson::object>())
		return (false);
	const picojson::object  &entry = it_entry->second.get<picojson::object>();

	name   = get_string_field(entry, "name");
	type   = get_string_field(entry, "type");
	threat = get_string_field(entry, "threat_level");

	return (true);
}

// API
bool    BestiaryIndexResource::load_dir(const String &res_dir)
{
	by_id_.clear();

	// Convert res:// to absolute for std::filesystem
	const String        abs = ProjectSettings::get_singleton()->globalize_path(res_dir);
	const std::string   abs_s = std::string(abs.utf8().get_data());

	if (!std::filesystem::exists(abs_s) || !std::filesystem::is_directory(abs_s))
		return (false);

	// int	unknown_counter = 0; // for unmapped ids

	std::filesystem::directory_iterator	it(abs_s);
	std::filesystem::directory_iterator	it_end;
	while (it != it_end)
	{
		// Snapshot the entry, advance early so 'continue' paths don't skip ++it
		const std::filesystem::directory_entry	p = *it;
		++it; // <- we advance here so any 'continue' won't skip it

		if (!p.is_regular_file())
			continue ;
		if (p.path().extension() != ".json")
			continue ;

		String  id_str;
		String  name;
		String  type;
		String  threat;
		if (!read_min_meta(p.path().string(), id_str, name, type, threat))
			continue ;

		// // Map string ID -> enum
		// int			id_enum = -1;
		// BestiaryID	idv;
		// std::string	id_std = std::string(id_str.utf8().get_data());

		// if (try_toBestiaryID(id_std, idv))
		// 	id_enum = (int)idv;
		// else
		// 	UtilityFunctions::push_warning("BestiaryIndex: unknown id '", id_str, "'");
		// 	// UtilityFunctions::push_warning("BestiaryIndex: unknown id '", id_str, "' in ", String::utf8(p.path().string().c_str()));

		Meta    m;
		m.id_str        = id_str; // remember the original string id
		m.name          = name;
		m.type          = type;
		m.threat        = threat;
		m.json_path_abs = String::utf8(p.path().string().c_str());
		m.json_path_res = ProjectSettings::get_singleton()->localize_path(m.json_path_abs);
		// m.id_enum       = id_enum;

		// Known enums keep their numeric value; unknowns get stable, positive keys after the enum range
		// const int	key;

		// if (id_enum >= 0)
		// 	key = id_enum;
		// else
		// 	key = (BESTIARY_ID_COUNT + (unknown_counter++));
		// by_id_[key] = m;
		by_id_[id_str] = m;
	}
	return (true);
}

TypedArray<Dictionary>  BestiaryIndexResource::list_entries(void) const
{
	TypedArray<Dictionary> 	out;

	// std::map<int, Meta>::const_iterator it = by_id_.begin();
	// std::map<int, Meta>::const_iterator it_end = by_id_.end();
	std::map<String, Meta>::const_iterator it = by_id_.begin();
	std::map<String, Meta>::const_iterator it_end = by_id_.end();
	while ( it != it_end)
    {
        // const int key = it->first;
        const String &key = it->first;
        const Meta &m = it->second;

        Dictionary d;
        // d["id"]           = key;      // numeric key (enum or stable fallback)
        // d["id_str"]       = m.id_str; // original string id (always present)
		d["id_str"]       = key;
        d["name"]         = m.name;
        d["type"]         = m.type;
        d["threat"]       = m.threat;
        d["json_path_res"]= m.json_path_res;

        out.push_back(d);
		
		++it;
    }
	return (out);
}

Ref<BestiaryEntryResource>  BestiaryIndexResource::load_entry_by_str_id(const String &id_str) const
{
	// std::map<int, Meta>::const_iterator	it = by_id_.find(id);
	std::map<String, Meta>::const_iterator	it = by_id_.find(id_str);
	if (it == by_id_.end())
		return (Ref<BestiaryEntryResource>());

	Ref<BestiaryEntryResource>  res = memnew(BestiaryEntryResource);

	// Prefer res:// for portability
	if (res->load_from_file(it->second.json_path_res))
		return (res);

	// Fallback to abs path if needed
	res->load_from_file(it->second.json_path_abs);
	return (res);
}


// Ref<BestiaryEntryResource>  BestiaryIndexResource::load_entry_by_id(int id) const
// {
// 	std::map<int, Meta>::const_iterator	it = by_id_.find(id);
// 	if (it == by_id_.end())
// 		return (Ref<BestiaryEntryResource>());

// 	Ref<BestiaryEntryResource>  res = memnew(BestiaryEntryResource);

// 	// Prefer res:// for portability
// 	if (res->load_from_file(it->second.json_path_res))
// 		return (res);

// 	// Fallback to abs path if needed
// 	res->load_from_file(it->second.json_path_abs);
// 	return (res);
// }

int BestiaryIndexResource::size(void) const
{
	// return ((int)by_id_.size());
	return (static_cast<int>(by_id_.size()));
}

/* Example usage in GDScript (no Beast objects!)

extends Node

var index := BestiaryIndexResource.new()

func _ready():
	# Assuming your JSON files live under: game/data/bestiary/*.json
	if not index.load_dir("res://data/bestiary"):
		push_error("Failed to load bestiary dir")
		return

	var entries = index.list_entries()
	for d in entries:
		print("[", d.id, "] ", d.name, " (", d.type, ")")

	# Load one entry by ID and show a couple fields
	if entries.size() > 0:
		var id = entries[0].id
		var entry: BestiaryEntryResource = index.load_entry_by_id(id)
		if entry:
			print("Name: ", entry.get_name())
			print("Quote: ", entry.get_lore_quote())
			print("Drops: ", entry.get_drops())
*/