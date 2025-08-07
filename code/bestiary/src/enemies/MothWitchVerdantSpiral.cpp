
#include "MothWitchVerdantSpiral.hpp"
#include "BeastJsonLoader.hpp"

MothWitchVerdantSpiral::MothWitchVerdantSpiral(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

MothWitchVerdantSpiral::~MothWitchVerdantSpiral(void) {}

MothWitchVerdantSpiral::MothWitchVerdantSpiral(const MothWitchVerdantSpiral& other) { *this = other; }

MothWitchVerdantSpiral& MothWitchVerdantSpiral::operator=(const MothWitchVerdantSpiral& other)
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

BestiaryID MothWitchVerdantSpiral::getID(void) const { return BEAST_MOTH_WITCH_VERDANT_SPIRAL; }
const std::string& MothWitchVerdantSpiral::getName(void) const { return _name; }
const std::string& MothWitchVerdantSpiral::getDescription(void) const { return _description; }
const std::vector<std::string>& MothWitchVerdantSpiral::getDrops(void) const { return _drops; }
const std::string& MothWitchVerdantSpiral::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& MothWitchVerdantSpiral::getLoreNotes(void) const { return _notes; }

void MothWitchVerdantSpiral::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	MothWitchVerdantSpiral::loadFromFile(const std::string& filepath)
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
