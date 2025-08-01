
#include "TapestryWatcherNullshade.hpp"
#include "BeastJsonLoader.hpp"

TapestryWatcherNullshade::TapestryWatcherNullshade(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

TapestryWatcherNullshade::~TapestryWatcherNullshade(void) {}

TapestryWatcherNullshade::TapestryWatcherNullshade(const TapestryWatcherNullshade& other) { *this = other; }

TapestryWatcherNullshade& TapestryWatcherNullshade::operator=(const TapestryWatcherNullshade& other)
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

BestiaryID TapestryWatcherNullshade::getID(void) const { return BEAST_TAPESTRY_WATCHER_NULLSHADE; }
const std::string& TapestryWatcherNullshade::getName(void) const { return _name; }
const std::string& TapestryWatcherNullshade::getDescription(void) const { return _description; }
const std::vector<std::string>& TapestryWatcherNullshade::getDrops(void) const { return _drops; }
const std::string& TapestryWatcherNullshade::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& TapestryWatcherNullshade::getLoreNotes(void) const { return _notes; }

void TapestryWatcherNullshade::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	TapestryWatcherNullshade::loadFromFile(const std::string& filepath)
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
