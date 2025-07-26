
#include "MossgraveRevenant.hpp"
#include "BeastJsonLoader.hpp"

MossgraveRevenant::MossgraveRevenant(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

MossgraveRevenant::~MossgraveRevenant(void) {}

MossgraveRevenant::MossgraveRevenant(const MossgraveRevenant& other) { *this = other; }

MossgraveRevenant& MossgraveRevenant::operator=(const MossgraveRevenant& other)
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

BestiaryID MossgraveRevenant::getID(void) const { return BEAST_MOSSGRAVE_REVENANT; }
const std::string& MossgraveRevenant::getName(void) const { return _name; }
const std::string& MossgraveRevenant::getDescription(void) const { return _description; }
const std::vector<std::string>& MossgraveRevenant::getDrops(void) const { return _drops; }
const std::string& MossgraveRevenant::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& MossgraveRevenant::getLoreNotes(void) const { return _notes; }

void MossgraveRevenant::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	MossgraveRevenant::loadFromFile(const std::string& filepath)
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
