
#include "ChartreuseHusk.hpp"
#include "BeastJsonLoader.hpp"

ChartreuseHusk::ChartreuseHusk(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

ChartreuseHusk::~ChartreuseHusk(void) {}

ChartreuseHusk::ChartreuseHusk(const ChartreuseHusk& other) { *this = other; }

ChartreuseHusk& ChartreuseHusk::operator=(const ChartreuseHusk& other)
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

BestiaryID ChartreuseHusk::getID(void) const { return BEAST_CHARTREUSE_HUSK; }
const std::string& ChartreuseHusk::getName(void) const { return _name; }
const std::string& ChartreuseHusk::getDescription(void) const { return _description; }
const std::vector<std::string>& ChartreuseHusk::getDrops(void) const { return _drops; }
const std::string& ChartreuseHusk::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& ChartreuseHusk::getLoreNotes(void) const { return _notes; }

void ChartreuseHusk::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	ChartreuseHusk::loadFromFile(const std::string& filepath)
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
