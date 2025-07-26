
#include "OchreGolem.hpp"
#include "BeastJsonLoader.hpp"

OchreGolem::OchreGolem(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

OchreGolem::~OchreGolem(void) {}

OchreGolem::OchreGolem(const OchreGolem& other) { *this = other; }

OchreGolem& OchreGolem::operator=(const OchreGolem& other)
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

BestiaryID OchreGolem::getID(void) const { return BEAST_OCHRE_GOLEM; }
const std::string& OchreGolem::getName(void) const { return _name; }
const std::string& OchreGolem::getDescription(void) const { return _description; }
const std::vector<std::string>& OchreGolem::getDrops(void) const { return _drops; }
const std::string& OchreGolem::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& OchreGolem::getLoreNotes(void) const { return _notes; }

void OchreGolem::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	OchreGolem::loadFromFile(const std::string& filepath)
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
