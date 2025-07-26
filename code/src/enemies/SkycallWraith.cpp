
#include "SkycallWraith.hpp"
#include "BeastJsonLoader.hpp"

SkycallWraith::SkycallWraith(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

SkycallWraith::~SkycallWraith(void) {}

SkycallWraith::SkycallWraith(const SkycallWraith& other) { *this = other; }

SkycallWraith& SkycallWraith::operator=(const SkycallWraith& other)
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

BestiaryID SkycallWraith::getID(void) const { return BEAST_SKYCALL_WRAITH; }
const std::string& SkycallWraith::getName(void) const { return _name; }
const std::string& SkycallWraith::getDescription(void) const { return _description; }
const std::vector<std::string>& SkycallWraith::getDrops(void) const { return _drops; }
const std::string& SkycallWraith::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& SkycallWraith::getLoreNotes(void) const { return _notes; }

void SkycallWraith::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	SkycallWraith::loadFromFile(const std::string& filepath)
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
