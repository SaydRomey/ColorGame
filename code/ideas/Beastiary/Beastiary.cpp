// Bestiary.cpp
#include "Bestiary.hpp"
#include "BestiaryLookup.hpp"	// string→BestiaryID map helper
#include "picojson.h"
#include <fstream>
#include <stdexcept>

// -------------------- LorePage implementation --------------------
LorePage::LorePage() : _name(), _description() {}

LorePage::LorePage(const std::string& name, const std::string& desc)
		: _name(name), _description(desc) {}

LorePage::LorePage(const LorePage& other)
		: _name(other._name), _description(other._description) {}

LorePage::~LorePage() {}

LorePage&	LorePage::operator=(const LorePage& other)
{
	if (this != &other)
	{
		_name = other._name;
		_description = other._description;
	}
	return (*this);
}
const std::string& LorePage::getName() const { return (_name); }
const std::string& LorePage::getDescription() const { return (_description); }

// -------------------- Bestiary implementation --------------------
Bestiary::Bestiary() : _entries() {}

Bestiary::Bestiary(const Bestiary& other) : _entries(other._entries) {}

Bestiary::~Bestiary() {}

Bestiary&	Bestiary::operator=(const Bestiary& other)
{
	if (this != &other) {
		_entries = other._entries;
	}
	return (*this);
}
Bestiary&	Bestiary::instance()
{
	static Bestiary	s_instance;

	return (s_instance);
}

bool	Bestiary::loadFromFile(const std::string& filename)
{
	std::ifstream	in(filename.c_str());
	if (!in)
		return (false);

	picojson::value	root;
	in >> root;
	if (!root.is<picojson::object>())
		return (false);

	const picojson::object&	obj = root.get<picojson::object>();

	picojson::object::const_iterator	it = obj.begin();
	while (it != obj.end())
	{
		// key is a string like "BEAST_ABYSSAL_CURRENT"
		const std::string&	key = it->first;
		const picojson::value&	entry = it->second;

		if (!entry.is<picojson::object>())
		{
			std::cerr << "Warning: Skipping malformed entry for " << key << " (not an object)" << std::endl;
			continue ;
		}
		
		const picojson::object&	eo = entry.get<picojson::object>();

		if (eo.count("name") == 0 || eo.count("description") == 0)
		{
			std::cerr << "Warning: Missing 'name' or 'description' in entry: " << key << std::endl;
			continue ;
		}

		if (!eo.at("name").is<std::string>() || !eo.at("description").is<std::string>())
		{
			std::cerr << "Warning: Invalid 'name' or 'description' type in entry: " << key << std::endl;
			continue ;
		}

		BestiaryID	id;
		try
		{
			id = toBestiaryID(it->first);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Warning: " << e.what() << std::endl;
			continue ;
		}

		std::string	name = eo.at("name").get<std::string>();
		std::string	desc = eo.at("description").get<std::string>();

		_entries[id] = LorePage(name, desc);
		++it;
	}
	return (true);
}

const LorePage&	Bestiary::getLore(BestiaryID id) const
{
	std::map<BestiaryID,LorePage>::const_iterator	it = _entries.find(id);
	if (it == _entries.end())
		// throw (std::runtime_error("Missing fields in bestiary entry: " + it->first));
		throw (std::runtime_error("Lore not found for ID"));
	return (it->second);
}
