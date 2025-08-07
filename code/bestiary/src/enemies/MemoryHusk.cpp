
#include "MemoryHusk.hpp"
#include "BeastJsonLoader.hpp"

MemoryHusk::MemoryHusk(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

MemoryHusk::~MemoryHusk(void) {}

MemoryHusk::MemoryHusk(const MemoryHusk& other) { *this = other; }

MemoryHusk& MemoryHusk::operator=(const MemoryHusk& other)
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

BestiaryID MemoryHusk::getID(void) const { return BEAST_MEMORY_HUSK; }
const std::string& MemoryHusk::getName(void) const { return _name; }
const std::string& MemoryHusk::getDescription(void) const { return _description; }
const std::vector<std::string>& MemoryHusk::getDrops(void) const { return _drops; }
const std::string& MemoryHusk::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& MemoryHusk::getLoreNotes(void) const { return _notes; }

void MemoryHusk::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	MemoryHusk::loadFromFile(const std::string& filepath)
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
