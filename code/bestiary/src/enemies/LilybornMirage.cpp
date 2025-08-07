
#include "LilybornMirage.hpp"
#include "BeastJsonLoader.hpp"

LilybornMirage::LilybornMirage(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

LilybornMirage::~LilybornMirage(void) {}

LilybornMirage::LilybornMirage(const LilybornMirage& other) { *this = other; }

LilybornMirage& LilybornMirage::operator=(const LilybornMirage& other)
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

BestiaryID LilybornMirage::getID(void) const { return BEAST_LILYBORN_MIRAGE; }
const std::string& LilybornMirage::getName(void) const { return _name; }
const std::string& LilybornMirage::getDescription(void) const { return _description; }
const std::vector<std::string>& LilybornMirage::getDrops(void) const { return _drops; }
const std::string& LilybornMirage::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& LilybornMirage::getLoreNotes(void) const { return _notes; }

void LilybornMirage::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	LilybornMirage::loadFromFile(const std::string& filepath)
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
