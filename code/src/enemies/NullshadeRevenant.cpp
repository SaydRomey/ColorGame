
#include "NullshadeRevenant.hpp"
#include "BeastJsonLoader.hpp"

NullshadeRevenant::NullshadeRevenant(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

NullshadeRevenant::~NullshadeRevenant(void) {}

NullshadeRevenant::NullshadeRevenant(const NullshadeRevenant& other) { *this = other; }

NullshadeRevenant& NullshadeRevenant::operator=(const NullshadeRevenant& other)
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

BestiaryID NullshadeRevenant::getID(void) const { return BEAST_NULLSHADE_REVENANT; }
const std::string& NullshadeRevenant::getName(void) const { return _name; }
const std::string& NullshadeRevenant::getDescription(void) const { return _description; }
const std::vector<std::string>& NullshadeRevenant::getDrops(void) const { return _drops; }
const std::string& NullshadeRevenant::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& NullshadeRevenant::getLoreNotes(void) const { return _notes; }

void NullshadeRevenant::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	NullshadeRevenant::loadFromFile(const std::string& filepath)
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
