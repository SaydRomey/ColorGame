
#include "Wickerborn.hpp"
#include "BeastJsonLoader.hpp"

Wickerborn::Wickerborn(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

Wickerborn::~Wickerborn(void) {}

Wickerborn::Wickerborn(const Wickerborn& other) { *this = other; }

Wickerborn& Wickerborn::operator=(const Wickerborn& other)
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

BestiaryID Wickerborn::getID(void) const { return BEAST_WICKERBORN; }
const std::string& Wickerborn::getName(void) const { return _name; }
const std::string& Wickerborn::getDescription(void) const { return _description; }
const std::vector<std::string>& Wickerborn::getDrops(void) const { return _drops; }
const std::string& Wickerborn::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& Wickerborn::getLoreNotes(void) const { return _notes; }

void Wickerborn::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	Wickerborn::loadFromFile(const std::string& filepath)
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
