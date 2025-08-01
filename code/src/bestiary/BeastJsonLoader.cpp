// BeastJsonLoader.cpp

#include "BeastJsonLoader.hpp"
#include "picojson.h"
#include <fstream>

// Helpers hidden inside anonymous namespace
namespace
{
	/* test if key exists and is NOT null */
	static bool	hasKey(const picojson::object& obj, const std::string& k)
	{
		return (obj.count(k) && !obj.find(k)->second.is<picojson::null>());
	}

	static	std::string	strOrEmpty(const picojson::object& obj, const std::string& k)
	{
		if (hasKey(obj, k))
			return (obj.find(k)->second.get<std::string>());
		else
			return ("");
	}

	/* Copies a picojson array of strings into a std::vector<string> */
	static void	fillStringVector(const picojson::object& obj, const std::string& k, std::vector<std::string>& out)
	{
		out.clear();
		if (!hasKey(obj, k) || !obj.find(k)->second.is<picojson::array>())
			return ;

		const picojson::array&	a = obj.find(k)->second.get<picojson::array>();
		
		picojson::array::const_iterator	it = a.begin();
		while (it != a.end())
		{
			out.push_back(it->get<std::string>());
			++it;
		}
	}
} //-- anonymous namespace

// public API
namespace BeastJsonLoader
{
	bool loadFromFile(const std::string& path, BeastData& d)
	{
		std::ifstream	in(path.c_str());
		if (!in)
			return (false);

		picojson::value	root;
		in >> root;
		if (!root.is<picojson::object>())
			return (false);

		const picojson::object&	obj = root.get<picojson::object>();

		// ID
		if (!hasKey(obj, "id") || !obj.find("id")->second.is<std::string>())
			return (false);
		d.id = obj.find("id")->second.get<std::string>();

		// Entry
		if (!hasKey(obj, "entry") || !obj.find("entry")->second.is<picojson::object>())
			return (false);
		const picojson::object&	entry = obj.find("entry")->second.get<picojson::object>();

		d.name				= strOrEmpty(entry, "name");
		d.type				= strOrEmpty(entry, "type");
		d.threat_level		= strOrEmpty(entry, "threat_level");
		d.first_emerged		= strOrEmpty(entry, "first_emerged");
		d.description		= strOrEmpty(entry, "description");
		d.hue_interaction	= strOrEmpty(entry, "hue_interaction");
		d.behavior			= strOrEmpty(entry, "behavior");
		d.weaknesses		= strOrEmpty(entry, "weaknesses");
		d.notes				= strOrEmpty(entry, "notes");

		// Lore
		if (hasKey(obj, "lore") && obj.find("lore")->second.is<picojson::object>())
		{
			const picojson::object& lore = obj.find("lore")->second.get<picojson::object>();
			d.lore_title  = strOrEmpty(lore, "title");
			d.lore_quote  = strOrEmpty(lore, "quote");
			d.lore_source = strOrEmpty(lore, "source");

			fillStringVector(lore, "flavor_description", d.lore_flavor_description);
			fillStringVector(lore, "field_notes",        d.lore_field_notes);
		}
		else
		{
			d.lore_title.clear();
			d.lore_quote.clear();
			d.lore_source.clear();
			d.lore_flavor_description.clear();
			d.lore_field_notes.clear();
		}
		
		// Drops (top level)
		fillStringVector(obj, "drops", d.drops);
		
		return (true);
	}
} // namespace BeastJsonLoader
