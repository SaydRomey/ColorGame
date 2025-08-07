
#include "CaputMarionette.hpp"
#include "BeastJsonLoader.hpp"

CaputMarionette::CaputMarionette(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

CaputMarionette::~CaputMarionette(void) {}

CaputMarionette::CaputMarionette(const CaputMarionette& other) { *this = other; }

CaputMarionette& CaputMarionette::operator=(const CaputMarionette& other)
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

BestiaryID CaputMarionette::getID(void) const { return BEAST_CAPUT_MARIONETTE; }
const std::string& CaputMarionette::getName(void) const { return _name; }
const std::string& CaputMarionette::getDescription(void) const { return _description; }
const std::vector<std::string>& CaputMarionette::getDrops(void) const { return _drops; }
const std::string& CaputMarionette::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& CaputMarionette::getLoreNotes(void) const { return _notes; }

void CaputMarionette::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	CaputMarionette::loadFromFile(const std::string& filepath)
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
