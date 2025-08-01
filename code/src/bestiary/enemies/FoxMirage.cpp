
#include "FoxMirage.hpp"
#include "BeastJsonLoader.hpp"

FoxMirage::FoxMirage(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

FoxMirage::~FoxMirage(void) {}

FoxMirage::FoxMirage(const FoxMirage& other) { *this = other; }

FoxMirage& FoxMirage::operator=(const FoxMirage& other)
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

BestiaryID FoxMirage::getID(void) const { return BEAST_FOX_MIRAGE; }
const std::string& FoxMirage::getName(void) const { return _name; }
const std::string& FoxMirage::getDescription(void) const { return _description; }
const std::vector<std::string>& FoxMirage::getDrops(void) const { return _drops; }
const std::string& FoxMirage::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& FoxMirage::getLoreNotes(void) const { return _notes; }

void FoxMirage::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	FoxMirage::loadFromFile(const std::string& filepath)
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
