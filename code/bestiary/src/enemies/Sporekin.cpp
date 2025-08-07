
#include "Sporekin.hpp"
#include "BeastJsonLoader.hpp"

Sporekin::Sporekin(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

Sporekin::~Sporekin(void) {}

Sporekin::Sporekin(const Sporekin& other) { *this = other; }

Sporekin& Sporekin::operator=(const Sporekin& other)
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

BestiaryID Sporekin::getID(void) const { return BEAST_SPOREKIN; }
const std::string& Sporekin::getName(void) const { return _name; }
const std::string& Sporekin::getDescription(void) const { return _description; }
const std::vector<std::string>& Sporekin::getDrops(void) const { return _drops; }
const std::string& Sporekin::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& Sporekin::getLoreNotes(void) const { return _notes; }

void Sporekin::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	Sporekin::loadFromFile(const std::string& filepath)
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
