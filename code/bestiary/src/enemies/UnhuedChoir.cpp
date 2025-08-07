
#include "UnhuedChoir.hpp"
#include "BeastJsonLoader.hpp"

UnhuedChoir::UnhuedChoir(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

UnhuedChoir::~UnhuedChoir(void) {}

UnhuedChoir::UnhuedChoir(const UnhuedChoir& other) { *this = other; }

UnhuedChoir& UnhuedChoir::operator=(const UnhuedChoir& other)
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

BestiaryID UnhuedChoir::getID(void) const { return BEAST_UNHUED_CHOIR; }
const std::string& UnhuedChoir::getName(void) const { return _name; }
const std::string& UnhuedChoir::getDescription(void) const { return _description; }
const std::vector<std::string>& UnhuedChoir::getDrops(void) const { return _drops; }
const std::string& UnhuedChoir::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& UnhuedChoir::getLoreNotes(void) const { return _notes; }

void UnhuedChoir::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	UnhuedChoir::loadFromFile(const std::string& filepath)
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
