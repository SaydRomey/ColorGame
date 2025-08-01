
#include "TempestMarionette.hpp"
#include "BeastJsonLoader.hpp"

TempestMarionette::TempestMarionette(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

TempestMarionette::~TempestMarionette(void) {}

TempestMarionette::TempestMarionette(const TempestMarionette& other) { *this = other; }

TempestMarionette& TempestMarionette::operator=(const TempestMarionette& other)
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

BestiaryID TempestMarionette::getID(void) const { return BEAST_TEMPEST_MARIONETTE; }
const std::string& TempestMarionette::getName(void) const { return _name; }
const std::string& TempestMarionette::getDescription(void) const { return _description; }
const std::vector<std::string>& TempestMarionette::getDrops(void) const { return _drops; }
const std::string& TempestMarionette::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& TempestMarionette::getLoreNotes(void) const { return _notes; }

void TempestMarionette::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	TempestMarionette::loadFromFile(const std::string& filepath)
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
