
#include "AmbercoilAsp.hpp"
#include "BeastJsonLoader.hpp"

AmbercoilAsp::AmbercoilAsp(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

AmbercoilAsp::~AmbercoilAsp(void) {}

AmbercoilAsp::AmbercoilAsp(const AmbercoilAsp& other) { *this = other; }

AmbercoilAsp& AmbercoilAsp::operator=(const AmbercoilAsp& other)
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

BestiaryID AmbercoilAsp::getID(void) const { return BEAST_AMBERCOIL_ASP; }
const std::string& AmbercoilAsp::getName(void) const { return _name; }
const std::string& AmbercoilAsp::getDescription(void) const { return _description; }
const std::vector<std::string>& AmbercoilAsp::getDrops(void) const { return _drops; }
const std::string& AmbercoilAsp::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& AmbercoilAsp::getLoreNotes(void) const { return _notes; }

void AmbercoilAsp::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	AmbercoilAsp::loadFromFile(const std::string& filepath)
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
