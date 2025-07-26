
#include "FeatheredNull.hpp"
#include "BeastJsonLoader.hpp"

FeatheredNull::FeatheredNull(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

FeatheredNull::~FeatheredNull(void) {}

FeatheredNull::FeatheredNull(const FeatheredNull& other) { *this = other; }

FeatheredNull& FeatheredNull::operator=(const FeatheredNull& other)
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

BestiaryID FeatheredNull::getID(void) const { return BEAST_FEATHERED_NULL; }
const std::string& FeatheredNull::getName(void) const { return _name; }
const std::string& FeatheredNull::getDescription(void) const { return _description; }
const std::vector<std::string>& FeatheredNull::getDrops(void) const { return _drops; }
const std::string& FeatheredNull::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& FeatheredNull::getLoreNotes(void) const { return _notes; }

void FeatheredNull::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	FeatheredNull::loadFromFile(const std::string& filepath)
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
