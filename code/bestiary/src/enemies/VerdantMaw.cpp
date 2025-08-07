
#include "VerdantMaw.hpp"
#include "BeastJsonLoader.hpp"

VerdantMaw::VerdantMaw(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

VerdantMaw::~VerdantMaw(void) {}

VerdantMaw::VerdantMaw(const VerdantMaw& other) { *this = other; }

VerdantMaw& VerdantMaw::operator=(const VerdantMaw& other)
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

BestiaryID VerdantMaw::getID(void) const { return BEAST_VERDANT_MAW; }
const std::string& VerdantMaw::getName(void) const { return _name; }
const std::string& VerdantMaw::getDescription(void) const { return _description; }
const std::vector<std::string>& VerdantMaw::getDrops(void) const { return _drops; }
const std::string& VerdantMaw::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& VerdantMaw::getLoreNotes(void) const { return _notes; }

void VerdantMaw::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	VerdantMaw::loadFromFile(const std::string& filepath)
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
