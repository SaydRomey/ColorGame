
#include "CrimsonEcho.hpp"
#include "BeastJsonLoader.hpp"

CrimsonEcho::CrimsonEcho(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

CrimsonEcho::~CrimsonEcho(void) {}

CrimsonEcho::CrimsonEcho(const CrimsonEcho& other) { *this = other; }

CrimsonEcho& CrimsonEcho::operator=(const CrimsonEcho& other)
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

BestiaryID CrimsonEcho::getID(void) const { return BEAST_CRIMSON_ECHO; }
const std::string& CrimsonEcho::getName(void) const { return _name; }
const std::string& CrimsonEcho::getDescription(void) const { return _description; }
const std::vector<std::string>& CrimsonEcho::getDrops(void) const { return _drops; }
const std::string& CrimsonEcho::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& CrimsonEcho::getLoreNotes(void) const { return _notes; }

void CrimsonEcho::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	CrimsonEcho::loadFromFile(const std::string& filepath)
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
