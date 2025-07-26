
#include "VeilshiftMatron.hpp"
#include "BeastJsonLoader.hpp"

VeilshiftMatron::VeilshiftMatron(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

VeilshiftMatron::~VeilshiftMatron(void) {}

VeilshiftMatron::VeilshiftMatron(const VeilshiftMatron& other) { *this = other; }

VeilshiftMatron& VeilshiftMatron::operator=(const VeilshiftMatron& other)
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

BestiaryID VeilshiftMatron::getID(void) const { return BEAST_VEILSHIFT_MATRON; }
const std::string& VeilshiftMatron::getName(void) const { return _name; }
const std::string& VeilshiftMatron::getDescription(void) const { return _description; }
const std::vector<std::string>& VeilshiftMatron::getDrops(void) const { return _drops; }
const std::string& VeilshiftMatron::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& VeilshiftMatron::getLoreNotes(void) const { return _notes; }

void VeilshiftMatron::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	VeilshiftMatron::loadFromFile(const std::string& filepath)
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
