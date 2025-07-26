
#include "BeastJsonLoader.hpp"
#include "picojson.h"
#include <fstream>

namespace BeastJsonLoader
{
	bool loadFromFile(const std::string& path, BeastData& data)
	{
		std::ifstream in(path.c_str());
		if (!in) return false;

		picojson::value root;
		in >> root;
		if (!root.is<picojson::object>()) return false;
		const picojson::object& obj = root.get<picojson::object>();

		// ID
		data.id = obj.at("id").get<std::string>();

		// Entry
		const picojson::object& entry = obj.at("entry").get<picojson::object>();
		data.name = entry.at("name").get<std::string>();
		data.type = entry.at("type").get<std::string>();
		data.threat_level = entry.at("threat_level").get<std::string>();
		data.first_emerged = entry.at("first_emerged").get<std::string>();
		data.description = entry.at("description").get<std::string>();
		data.hue_interaction = entry.at("hue_interaction").get<std::string>();
		data.behavior = entry.at("behavior").get<std::string>();
		data.weaknesses = entry.at("weaknesses").get<std::string>();
		data.notes = entry.at("notes").get<std::string>();

		// Lore
		const picojson::object& lore = obj.at("lore").get<picojson::object>();
		data.lore_title = lore.at("title").get<std::string>();
		data.lore_quote = lore.at("quote").get<std::string>();
		data.lore_source = lore.at("source").get<std::string>();

		const picojson::array& flavor = lore.at("flavor_description").get<picojson::array>();
		for (size_t i = 0; i < flavor.size(); ++i)
			data.lore_flavor_description.push_back(flavor[i].get<std::string>());

		const picojson::array& notes = lore.at("field_notes").get<picojson::array>();
		for (size_t i = 0; i < notes.size(); ++i)
			data.lore_field_notes.push_back(notes[i].get<std::string>());

		// Drops
		const picojson::array& arr = obj.at("drops").get<picojson::array>();
		for (size_t i = 0; i < arr.size(); ++i)
			data.drops.push_back(arr[i].get<std::string>());

		return true;
	}
}
