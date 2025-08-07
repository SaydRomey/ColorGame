
#include "TheBound.hpp"
#include "BeastJsonLoader.hpp"

TheBound::TheBound(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

TheBound::~TheBound(void) {}

TheBound::TheBound(const TheBound& other) { *this = other; }

TheBound& TheBound::operator=(const TheBound& other)
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

BestiaryID TheBound::getID(void) const { return BEAST_THE_BOUND; }
const std::string& TheBound::getName(void) const { return _name; }
const std::string& TheBound::getDescription(void) const { return _description; }
const std::vector<std::string>& TheBound::getDrops(void) const { return _drops; }
const std::string& TheBound::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& TheBound::getLoreNotes(void) const { return _notes; }

void TheBound::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	TheBound::loadFromFile(const std::string& filepath)
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
