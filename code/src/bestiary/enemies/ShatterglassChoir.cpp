
#include "ShatterglassChoir.hpp"
#include "BeastJsonLoader.hpp"

ShatterglassChoir::ShatterglassChoir(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

ShatterglassChoir::~ShatterglassChoir(void) {}

ShatterglassChoir::ShatterglassChoir(const ShatterglassChoir& other) { *this = other; }

ShatterglassChoir& ShatterglassChoir::operator=(const ShatterglassChoir& other)
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

BestiaryID ShatterglassChoir::getID(void) const { return BEAST_SHATTERGLASS_CHOIR; }
const std::string& ShatterglassChoir::getName(void) const { return _name; }
const std::string& ShatterglassChoir::getDescription(void) const { return _description; }
const std::vector<std::string>& ShatterglassChoir::getDrops(void) const { return _drops; }
const std::string& ShatterglassChoir::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& ShatterglassChoir::getLoreNotes(void) const { return _notes; }

void ShatterglassChoir::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	ShatterglassChoir::loadFromFile(const std::string& filepath)
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
