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
	std::map<BestiaryID, Beast*>::iterator	it = _beastCache.begin();

	while (it != _beastCache.end())
	{
		delete it->second;
		++it;
	}
	_beastCache.clear();
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

		BeastMetadata	meta;
		meta.name = entryObj.at("name").get<std::string>();
		meta.type = entryObj.at("type").get<std::string>();
		meta.threat = entryObj.at("threat_level").get<std::string>();
		meta.jsonPath = path;

		_metadata[id] = meta;
	}
	closedir(dp);

	return (true);
}

const BeastMetadata*	BeastRegistry::getMetadata(BestiaryID id) const
{
	std::map<BestiaryID, BeastMetadata>::const_iterator	it = _metadata.find(id);
	if (it != _metadata.end())
		return (&it->second);
	return (NULL);
}

Beast*	BeastRegistry::getBeast(BestiaryID id)
{
	std::map<BestiaryID, Beast*>::iterator	it = _beastCache.find(id);
	if (it != _beastCache.end())
		return (it->second);

	std::map<BestiaryID, BeastMetadata>::iterator	metaIt = _metadata.find(id);
	if (metaIt == _metadata.end())
		return (NULL);

	Beast*	b = BeastFactory::createFromFile(metaIt->second.jsonPath);
	if (b)
		_beastCache[id] = b;
	return (b);
}

/*
BeastRegistry registry;
Beast* beast = registry.getBeast(BEAST_ABYSSAL_CURRENT);
*/
