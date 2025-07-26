
#include "NullbornHusks.hpp"
#include "BeastJsonLoader.hpp"

NullbornHusks::NullbornHusks(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

NullbornHusks::~NullbornHusks(void) {}

NullbornHusks::NullbornHusks(const NullbornHusks& other) { *this = other; }

NullbornHusks& NullbornHusks::operator=(const NullbornHusks& other)
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

BestiaryID NullbornHusks::getID(void) const { return BEAST_NULLBORN_HUSKS; }
const std::string& NullbornHusks::getName(void) const { return _name; }
const std::string& NullbornHusks::getDescription(void) const { return _description; }
const std::vector<std::string>& NullbornHusks::getDrops(void) const { return _drops; }
const std::string& NullbornHusks::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& NullbornHusks::getLoreNotes(void) const { return _notes; }

void NullbornHusks::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	NullbornHusks::loadFromFile(const std::string& filepath)
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
