
#include "ThulianVowkeeper.hpp"
#include "BeastJsonLoader.hpp"

ThulianVowkeeper::ThulianVowkeeper(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

ThulianVowkeeper::~ThulianVowkeeper(void) {}

ThulianVowkeeper::ThulianVowkeeper(const ThulianVowkeeper& other) { *this = other; }

ThulianVowkeeper& ThulianVowkeeper::operator=(const ThulianVowkeeper& other)
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

BestiaryID ThulianVowkeeper::getID(void) const { return BEAST_THULIAN_VOWKEEPER; }
const std::string& ThulianVowkeeper::getName(void) const { return _name; }
const std::string& ThulianVowkeeper::getDescription(void) const { return _description; }
const std::vector<std::string>& ThulianVowkeeper::getDrops(void) const { return _drops; }
const std::string& ThulianVowkeeper::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& ThulianVowkeeper::getLoreNotes(void) const { return _notes; }

void ThulianVowkeeper::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	ThulianVowkeeper::loadFromFile(const std::string& filepath)
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
