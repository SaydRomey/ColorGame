
#include "ThornwritheBeast.hpp"
#include "BeastJsonLoader.hpp"

ThornwritheBeast::ThornwritheBeast(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

ThornwritheBeast::~ThornwritheBeast(void) {}

ThornwritheBeast::ThornwritheBeast(const ThornwritheBeast& other) { *this = other; }

ThornwritheBeast& ThornwritheBeast::operator=(const ThornwritheBeast& other)
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

BestiaryID ThornwritheBeast::getID(void) const { return BEAST_THORNWRITHE_BEAST; }
const std::string& ThornwritheBeast::getName(void) const { return _name; }
const std::string& ThornwritheBeast::getDescription(void) const { return _description; }
const std::vector<std::string>& ThornwritheBeast::getDrops(void) const { return _drops; }
const std::string& ThornwritheBeast::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& ThornwritheBeast::getLoreNotes(void) const { return _notes; }

void ThornwritheBeast::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	ThornwritheBeast::loadFromFile(const std::string& filepath)
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
