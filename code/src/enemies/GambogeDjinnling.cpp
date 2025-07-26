
#include "GambogeDjinnling.hpp"
#include "BeastJsonLoader.hpp"

GambogeDjinnling::GambogeDjinnling(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

GambogeDjinnling::~GambogeDjinnling(void) {}

GambogeDjinnling::GambogeDjinnling(const GambogeDjinnling& other) { *this = other; }

GambogeDjinnling& GambogeDjinnling::operator=(const GambogeDjinnling& other)
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

BestiaryID GambogeDjinnling::getID(void) const { return BEAST_GAMBOGE_DJINNLING; }
const std::string& GambogeDjinnling::getName(void) const { return _name; }
const std::string& GambogeDjinnling::getDescription(void) const { return _description; }
const std::vector<std::string>& GambogeDjinnling::getDrops(void) const { return _drops; }
const std::string& GambogeDjinnling::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& GambogeDjinnling::getLoreNotes(void) const { return _notes; }

void GambogeDjinnling::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	GambogeDjinnling::loadFromFile(const std::string& filepath)
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
