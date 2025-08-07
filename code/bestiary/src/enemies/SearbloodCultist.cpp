
#include "SearbloodCultist.hpp"
#include "BeastJsonLoader.hpp"

SearbloodCultist::SearbloodCultist(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

SearbloodCultist::~SearbloodCultist(void) {}

SearbloodCultist::SearbloodCultist(const SearbloodCultist& other) { *this = other; }

SearbloodCultist& SearbloodCultist::operator=(const SearbloodCultist& other)
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

BestiaryID SearbloodCultist::getID(void) const { return BEAST_SEARBLOOD_CULTIST; }
const std::string& SearbloodCultist::getName(void) const { return _name; }
const std::string& SearbloodCultist::getDescription(void) const { return _description; }
const std::vector<std::string>& SearbloodCultist::getDrops(void) const { return _drops; }
const std::string& SearbloodCultist::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& SearbloodCultist::getLoreNotes(void) const { return _notes; }

void SearbloodCultist::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	SearbloodCultist::loadFromFile(const std::string& filepath)
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
