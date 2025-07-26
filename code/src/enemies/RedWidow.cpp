
#include "RedWidow.hpp"
#include "BeastJsonLoader.hpp"

RedWidow::RedWidow(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

RedWidow::~RedWidow(void) {}

RedWidow::RedWidow(const RedWidow& other) { *this = other; }

RedWidow& RedWidow::operator=(const RedWidow& other)
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

BestiaryID RedWidow::getID(void) const { return BEAST_RED_WIDOW; }
const std::string& RedWidow::getName(void) const { return _name; }
const std::string& RedWidow::getDescription(void) const { return _description; }
const std::vector<std::string>& RedWidow::getDrops(void) const { return _drops; }
const std::string& RedWidow::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& RedWidow::getLoreNotes(void) const { return _notes; }

void RedWidow::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	RedWidow::loadFromFile(const std::string& filepath)
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
