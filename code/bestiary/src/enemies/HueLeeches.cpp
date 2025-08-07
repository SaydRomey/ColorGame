
#include "HueLeeches.hpp"
#include "BeastJsonLoader.hpp"

HueLeeches::HueLeeches(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

HueLeeches::~HueLeeches(void) {}

HueLeeches::HueLeeches(const HueLeeches& other) { *this = other; }

HueLeeches& HueLeeches::operator=(const HueLeeches& other)
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

BestiaryID HueLeeches::getID(void) const { return BEAST_HUE_LEECHES; }
const std::string& HueLeeches::getName(void) const { return _name; }
const std::string& HueLeeches::getDescription(void) const { return _description; }
const std::vector<std::string>& HueLeeches::getDrops(void) const { return _drops; }
const std::string& HueLeeches::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& HueLeeches::getLoreNotes(void) const { return _notes; }

void HueLeeches::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	HueLeeches::loadFromFile(const std::string& filepath)
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
