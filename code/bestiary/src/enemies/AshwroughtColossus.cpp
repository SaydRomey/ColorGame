
#include "AshwroughtColossus.hpp"
#include "BeastJsonLoader.hpp"

AshwroughtColossus::AshwroughtColossus(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

AshwroughtColossus::~AshwroughtColossus(void) {}

AshwroughtColossus::AshwroughtColossus(const AshwroughtColossus& other) { *this = other; }

AshwroughtColossus& AshwroughtColossus::operator=(const AshwroughtColossus& other)
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

BestiaryID AshwroughtColossus::getID(void) const { return BEAST_ASHWROUGHT_COLOSSUS; }
const std::string& AshwroughtColossus::getName(void) const { return _name; }
const std::string& AshwroughtColossus::getDescription(void) const { return _description; }
const std::vector<std::string>& AshwroughtColossus::getDrops(void) const { return _drops; }
const std::string& AshwroughtColossus::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& AshwroughtColossus::getLoreNotes(void) const { return _notes; }

void AshwroughtColossus::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	AshwroughtColossus::loadFromFile(const std::string& filepath)
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
