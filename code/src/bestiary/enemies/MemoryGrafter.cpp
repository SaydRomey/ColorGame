
#include "MemoryGrafter.hpp"
#include "BeastJsonLoader.hpp"

MemoryGrafter::MemoryGrafter(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

MemoryGrafter::~MemoryGrafter(void) {}

MemoryGrafter::MemoryGrafter(const MemoryGrafter& other) { *this = other; }

MemoryGrafter& MemoryGrafter::operator=(const MemoryGrafter& other)
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

BestiaryID MemoryGrafter::getID(void) const { return BEAST_MEMORY_GRAFTER; }
const std::string& MemoryGrafter::getName(void) const { return _name; }
const std::string& MemoryGrafter::getDescription(void) const { return _description; }
const std::vector<std::string>& MemoryGrafter::getDrops(void) const { return _drops; }
const std::string& MemoryGrafter::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& MemoryGrafter::getLoreNotes(void) const { return _notes; }

void MemoryGrafter::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	MemoryGrafter::loadFromFile(const std::string& filepath)
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
