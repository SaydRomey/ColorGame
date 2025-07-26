
#include "TapestryWatcher.hpp"
#include "BeastJsonLoader.hpp"

TapestryWatcher::TapestryWatcher(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

TapestryWatcher::~TapestryWatcher(void) {}

TapestryWatcher::TapestryWatcher(const TapestryWatcher& other) { *this = other; }

TapestryWatcher& TapestryWatcher::operator=(const TapestryWatcher& other)
{
	if (this != &other)
	{
		_name = other._name;
		_description = other._description;
		_quote = other._quote;
		_notes = other._notes;
		_drops = other._drops;
	}
	return (*this);
}

BestiaryID TapestryWatcher::getID(void) const { return BEAST_TAPESTRY_WATCHER; }
const std::string& TapestryWatcher::getName(void) const { return _name; }
const std::string& TapestryWatcher::getDescription(void) const { return _description; }
const std::vector<std::string>& TapestryWatcher::getDrops(void) const { return _drops; }
const std::string& TapestryWatcher::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& TapestryWatcher::getLoreNotes(void) const { return _notes; }

void TapestryWatcher::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	TapestryWatcher::loadFromFile(const std::string& filepath)
{
	BeastData	data;
	if (!BeastJsonLoader::loadFromFile(filepath, data))
		return (false);

	_name = data.name;
	_description = data.description;
	_quote = data.lore_quote;
	_notes = data.lore_field_notes;
	_drops = data.drops;

	return (true);
}
