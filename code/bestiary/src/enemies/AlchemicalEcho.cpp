
#include "AlchemicalEcho.hpp"
#include "BeastJsonLoader.hpp"

AlchemicalEcho::AlchemicalEcho(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

AlchemicalEcho::~AlchemicalEcho(void) {}

AlchemicalEcho::AlchemicalEcho(const AlchemicalEcho& other) { *this = other; }

AlchemicalEcho& AlchemicalEcho::operator=(const AlchemicalEcho& other)
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

BestiaryID AlchemicalEcho::getID(void) const { return BEAST_ALCHEMICAL_ECHO; }
const std::string& AlchemicalEcho::getName(void) const { return _name; }
const std::string& AlchemicalEcho::getDescription(void) const { return _description; }
const std::vector<std::string>& AlchemicalEcho::getDrops(void) const { return _drops; }
const std::string& AlchemicalEcho::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& AlchemicalEcho::getLoreNotes(void) const { return _notes; }

void AlchemicalEcho::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	AlchemicalEcho::loadFromFile(const std::string& filepath)
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
