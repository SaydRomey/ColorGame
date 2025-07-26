
#include "MemoryLeech.hpp"
#include "BeastJsonLoader.hpp"

MemoryLeech::MemoryLeech(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

MemoryLeech::~MemoryLeech(void) {}

MemoryLeech::MemoryLeech(const MemoryLeech& other) { *this = other; }

MemoryLeech& MemoryLeech::operator=(const MemoryLeech& other)
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

BestiaryID MemoryLeech::getID(void) const { return BEAST_MEMORY_LEECH; }
const std::string& MemoryLeech::getName(void) const { return _name; }
const std::string& MemoryLeech::getDescription(void) const { return _description; }
const std::vector<std::string>& MemoryLeech::getDrops(void) const { return _drops; }
const std::string& MemoryLeech::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& MemoryLeech::getLoreNotes(void) const { return _notes; }

void MemoryLeech::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	MemoryLeech::loadFromFile(const std::string& filepath)
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
