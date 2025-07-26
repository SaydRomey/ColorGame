
#include "WickboneLantern.hpp"
#include "BeastJsonLoader.hpp"

WickboneLantern::WickboneLantern(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

WickboneLantern::~WickboneLantern(void) {}

WickboneLantern::WickboneLantern(const WickboneLantern& other) { *this = other; }

WickboneLantern& WickboneLantern::operator=(const WickboneLantern& other)
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

BestiaryID WickboneLantern::getID(void) const { return BEAST_WICKBONE_LANTERN; }
const std::string& WickboneLantern::getName(void) const { return _name; }
const std::string& WickboneLantern::getDescription(void) const { return _description; }
const std::vector<std::string>& WickboneLantern::getDrops(void) const { return _drops; }
const std::string& WickboneLantern::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& WickboneLantern::getLoreNotes(void) const { return _notes; }

void WickboneLantern::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	WickboneLantern::loadFromFile(const std::string& filepath)
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
