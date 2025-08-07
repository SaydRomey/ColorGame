
#include "SapbornStalker.hpp"
#include "BeastJsonLoader.hpp"

SapbornStalker::SapbornStalker(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

SapbornStalker::~SapbornStalker(void) {}

SapbornStalker::SapbornStalker(const SapbornStalker& other) { *this = other; }

SapbornStalker& SapbornStalker::operator=(const SapbornStalker& other)
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

BestiaryID SapbornStalker::getID(void) const { return BEAST_SAPBORN_STALKER; }
const std::string& SapbornStalker::getName(void) const { return _name; }
const std::string& SapbornStalker::getDescription(void) const { return _description; }
const std::vector<std::string>& SapbornStalker::getDrops(void) const { return _drops; }
const std::string& SapbornStalker::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& SapbornStalker::getLoreNotes(void) const { return _notes; }

void SapbornStalker::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	SapbornStalker::loadFromFile(const std::string& filepath)
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
