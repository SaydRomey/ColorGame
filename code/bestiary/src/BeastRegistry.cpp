// BeastRegistry.cpp

#include "BeastRegistry.hpp"
#include "BeastFactory.hpp"
#include "BestiaryLookup.hpp"
#include "picojson.h"
#include <fstream>
#include <dirent.h>

BeastRegistry::BeastRegistry(void) {}
// BeastRegistry::BeastRegistry(const BeastRegistry& other) { /* shallow copy */ }
// BeastRegistry&	BeastRegistry::operator=(const BeastRegistry& other) { return *this; }
BeastRegistry::~BeastRegistry(void) { unloadAll(); }

void	BeastRegistry::unloadAll(void)
{
	std::map<BestiaryID, Beast*>::iterator	it = _cache.begin();
	while (it != _cache.end())
	{
		delete it->second;
		++it;
	}
	_cache.clear();
}

bool	BeastRegistry::loadMetadataDirectory(const std::string& dir)
{
	DIR*	dp = opendir(dir.c_str());
	if (!dp)
		return (false);

	struct dirent*	entry;
	while ((entry = readdir(dp)) != NULL)
	{
		std::string	fname(entry->d_name);
		if (fname.size() < 5 || fname.substr(fname.size() - 5) != ".json")
			continue;

		std::string		path = dir + "/" + fname;
		std::ifstream	in(path.c_str());
		if (!in)
			continue;

		picojson::value	root;
		in >> root;
		if (!root.is<picojson::object>())
			continue;
		
		const picojson::object&	obj = root.get<picojson::object>();
		if (!obj.count("id") || !obj.at("id").is<std::string>())
			continue;
		
		std::string	idStr = obj.at("id").get<std::string>();

		BestiaryID	id;
		try
		{
			id = toBestiaryID(idStr);
		}
		catch (...)
		{
			continue;
		}

		const picojson::object&	entryObj = obj.at("entry").get<picojson::object>();

		BeastMetadata	md;
		md.name		= entryObj.at("name").get<std::string>();
		md.type		= entryObj.at("type").get<std::string>();
		md.threat	= entryObj.at("threat_level").get<std::string>();
		md.jsonPath	= path;
		_meta[id]	= md;
	}
	closedir(dp);

	return (true);
}

const BeastMetadata*	BeastRegistry::getMetadata(BestiaryID id) const
{
	std::map<BestiaryID, BeastMetadata>::const_iterator	it = _meta.find(id);
	if (it != _meta.end())
		return (&it->second);
	return (NULL);
}

Beast*	BeastRegistry::getBeast(BestiaryID id)
{
	std::map<BestiaryID, Beast*>::iterator	it = _cache.find(id);
	if (it != _cache.end())
		return (it->second);

	const BeastMetadata*	md = getMetadata(id);
	if (!md)
		return (NULL);

	Beast*	b = BeastFactory::createFromFile(md->jsonPath);
	if (b)
		_cache[id] = b;
	return (b);
}

/*
BeastRegistry registry;
Beast* beast = registry.getBeast(BEAST_ABYSSAL_CURRENT);
*/
