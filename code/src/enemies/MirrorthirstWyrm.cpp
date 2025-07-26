
#include "MirrorthirstWyrm.hpp"
#include "BeastJsonLoader.hpp"

MirrorthirstWyrm::MirrorthirstWyrm(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

MirrorthirstWyrm::~MirrorthirstWyrm(void) {}

MirrorthirstWyrm::MirrorthirstWyrm(const MirrorthirstWyrm& other) { *this = other; }

MirrorthirstWyrm& MirrorthirstWyrm::operator=(const MirrorthirstWyrm& other)
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

BestiaryID MirrorthirstWyrm::getID(void) const { return BEAST_MIRRORTHIRST_WYRM; }
const std::string& MirrorthirstWyrm::getName(void) const { return _name; }
const std::string& MirrorthirstWyrm::getDescription(void) const { return _description; }
const std::vector<std::string>& MirrorthirstWyrm::getDrops(void) const { return _drops; }
const std::string& MirrorthirstWyrm::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& MirrorthirstWyrm::getLoreNotes(void) const { return _notes; }

void MirrorthirstWyrm::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	MirrorthirstWyrm::loadFromFile(const std::string& filepath)
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
