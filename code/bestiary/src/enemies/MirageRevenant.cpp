
#include "MirageRevenant.hpp"
#include "BeastJsonLoader.hpp"

MirageRevenant::MirageRevenant(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

MirageRevenant::~MirageRevenant(void) {}

MirageRevenant::MirageRevenant(const MirageRevenant& other) { *this = other; }

MirageRevenant& MirageRevenant::operator=(const MirageRevenant& other)
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

BestiaryID MirageRevenant::getID(void) const { return BEAST_MIRAGE_REVENANT; }
const std::string& MirageRevenant::getName(void) const { return _name; }
const std::string& MirageRevenant::getDescription(void) const { return _description; }
const std::vector<std::string>& MirageRevenant::getDrops(void) const { return _drops; }
const std::string& MirageRevenant::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& MirageRevenant::getLoreNotes(void) const { return _notes; }

void MirageRevenant::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	MirageRevenant::loadFromFile(const std::string& filepath)
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
