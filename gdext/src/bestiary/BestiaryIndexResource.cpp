// gdext/src/bestiary/BestiaryIndexResource.cpp

#include "BestiaryIndexResource.h"
#include "BestiaryEntryResource.h"

#include "picojson.h"
#include <fstream>
#include <filesystem>

using namespace godot;

// Helpers
static String	get_string_field(const picojson::object &obj, const char *key)
{
	picojson::object::const_iterator	it = obj.find(key);
	if (it != obj.end() && it->second.is<std::string>())
		return (String::utf8(it->second.get<std::string>().c_str()));
	return (String());
}

static bool read_min_meta(const std::string &abs_path,
						  String &id_str, String &name, String &type, String &threat)
{
	std::ifstream	in(abs_path.c_str());
	if (!in)
		return (false);

	picojson::value	root;
	in >> root;
	if (!root.is<picojson::object>())
		return (false);

	const picojson::object	&obj = root.get<picojson::object>();

	picojson::object::const_iterator	it_id = obj.find("id");
	if (it_id == obj.end() || !it_id->second.is<std::string>())
		return (false);
	id_str = String::utf8(it_id->second.get<std::string>().c_str());

	picojson::object::const_iterator	it_entry = obj.find("entry");
	if (it_entry == obj.end() || !it_entry->second.is<picojson::object>())
		return (false);
	const picojson::object &entry = it_entry->second.get<picojson::object>();

	name   = get_string_field(entry, "name");
	type   = get_string_field(entry, "type");
	threat = get_string_field(entry, "threat_level");

	return (true);
}

void	BestiaryIndexResource::_bind_methods(void)
{
	ClassDB::bind_method(D_METHOD("load_dir", "res_dir"), &BestiaryIndexResource::load_dir);
	ClassDB::bind_method(D_METHOD("list_entries"), &BestiaryIndexResource::list_entries);
	ClassDB::bind_method(D_METHOD("load_entry_by_str_id", "id_str"), &BestiaryIndexResource::load_entry_by_str_id);
	ClassDB::bind_method(D_METHOD("size"), &BestiaryIndexResource::size);
}

// Default Constructor and Destructor
BestiaryIndexResource::BestiaryIndexResource(void) {}
BestiaryIndexResource::~BestiaryIndexResource(void) {}

// API
bool	BestiaryIndexResource::load_dir(const String &res_dir)
{
	by_id_.clear();

	// Convert res:// to absolute for std::filesystem
	const String		abs = ProjectSettings::get_singleton()->globalize_path(res_dir);
	const std::string	abs_s = std::string(abs.utf8().get_data());

	if (!std::filesystem::exists(abs_s) || !std::filesystem::is_directory(abs_s))
		return (false);


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

		// String	id_str, name, type, threat;
		String	id_str;
		String	name;
		String	type;
		String	threat;
		if (!read_min_meta(p.path().string(), id_str, name, type, threat))
			continue ;

		Meta	m;
		m.id_str		= id_str; // remember the original string id
		m.name			= name;
		m.type			= type;
		m.threat		= threat;
		m.json_path_abs	= String::utf8(p.path().string().c_str());
		m.json_path_res	= ProjectSettings::get_singleton()->localize_path(m.json_path_abs);
		by_id_[id_str]	= m;
	}

	return (true);
}

TypedArray<Dictionary>	BestiaryIndexResource::list_entries(void) const
{
	TypedArray<Dictionary>	out;

	std::map<String, Meta>::const_iterator	it = by_id_.begin();
	std::map<String, Meta>::const_iterator	it_end = by_id_.end();
	while ( it != it_end)
	{
		const String	&key = it->first;
		const Meta		&m = it->second;

		Dictionary	d;
		d["id_str"]			= key;
		d["name"]			= m.name;
		d["type"]			= m.type;
		d["threat"]			= m.threat;
		d["json_path_res"]	= m.json_path_res;

		out.push_back(d);
		++it;
	}

	return (out);
}

Ref<BestiaryEntryResource>	BestiaryIndexResource::load_entry_by_str_id(const String &id_str) const
{
	std::map<String, Meta>::const_iterator	it = by_id_.find(id_str);
	if (it == by_id_.end())
		return (Ref<BestiaryEntryResource>());

	Ref<BestiaryEntryResource> res = memnew(BestiaryEntryResource);

	// Prefer res:// for portability
	if (res->load_from_file(it->second.json_path_res))
		return (res);

	// Fallback to abs path if needed
	res->load_from_file(it->second.json_path_abs);
	return (res);
}

int	BestiaryIndexResource::size(void) const
{
	return ((int)by_id_.size());
}
