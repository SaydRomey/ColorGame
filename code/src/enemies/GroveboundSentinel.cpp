
#include "GroveboundSentinel.hpp"
#include "BeastJsonLoader.hpp"

GroveboundSentinel::GroveboundSentinel(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

GroveboundSentinel::~GroveboundSentinel(void) {}

GroveboundSentinel::GroveboundSentinel(const GroveboundSentinel& other) { *this = other; }

GroveboundSentinel& GroveboundSentinel::operator=(const GroveboundSentinel& other)
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

BestiaryID GroveboundSentinel::getID(void) const { return BEAST_GROVEBOUND_SENTINEL; }
const std::string& GroveboundSentinel::getName(void) const { return _name; }
const std::string& GroveboundSentinel::getDescription(void) const { return _description; }
const std::vector<std::string>& GroveboundSentinel::getDrops(void) const { return _drops; }
const std::string& GroveboundSentinel::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& GroveboundSentinel::getLoreNotes(void) const { return _notes; }

void GroveboundSentinel::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	GroveboundSentinel::loadFromFile(const std::string& filepath)
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
