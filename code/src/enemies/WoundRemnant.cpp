
#include "WoundRemnant.hpp"
#include "BeastJsonLoader.hpp"

WoundRemnant::WoundRemnant(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

WoundRemnant::~WoundRemnant(void) {}

WoundRemnant::WoundRemnant(const WoundRemnant& other) { *this = other; }

WoundRemnant& WoundRemnant::operator=(const WoundRemnant& other)
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

BestiaryID WoundRemnant::getID(void) const { return BEAST_WOUND_REMNANT; }
const std::string& WoundRemnant::getName(void) const { return _name; }
const std::string& WoundRemnant::getDescription(void) const { return _description; }
const std::vector<std::string>& WoundRemnant::getDrops(void) const { return _drops; }
const std::string& WoundRemnant::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& WoundRemnant::getLoreNotes(void) const { return _notes; }

void WoundRemnant::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	WoundRemnant::loadFromFile(const std::string& filepath)
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
