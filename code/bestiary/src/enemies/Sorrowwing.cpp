
#include "Sorrowwing.hpp"
#include "BeastJsonLoader.hpp"

Sorrowwing::Sorrowwing(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

Sorrowwing::~Sorrowwing(void) {}

Sorrowwing::Sorrowwing(const Sorrowwing& other) { *this = other; }

Sorrowwing& Sorrowwing::operator=(const Sorrowwing& other)
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

BestiaryID Sorrowwing::getID(void) const { return BEAST_SORROWWING; }
const std::string& Sorrowwing::getName(void) const { return _name; }
const std::string& Sorrowwing::getDescription(void) const { return _description; }
const std::vector<std::string>& Sorrowwing::getDrops(void) const { return _drops; }
const std::string& Sorrowwing::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& Sorrowwing::getLoreNotes(void) const { return _notes; }

void Sorrowwing::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	Sorrowwing::loadFromFile(const std::string& filepath)
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
