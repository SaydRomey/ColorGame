
#include "HollowProphet.hpp"
#include "BeastJsonLoader.hpp"

HollowProphet::HollowProphet(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

HollowProphet::~HollowProphet(void) {}

HollowProphet::HollowProphet(const HollowProphet& other) { *this = other; }

HollowProphet& HollowProphet::operator=(const HollowProphet& other)
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

BestiaryID HollowProphet::getID(void) const { return BEAST_HOLLOW_PROPHET; }
const std::string& HollowProphet::getName(void) const { return _name; }
const std::string& HollowProphet::getDescription(void) const { return _description; }
const std::vector<std::string>& HollowProphet::getDrops(void) const { return _drops; }
const std::string& HollowProphet::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& HollowProphet::getLoreNotes(void) const { return _notes; }

void HollowProphet::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	HollowProphet::loadFromFile(const std::string& filepath)
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
