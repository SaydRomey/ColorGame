
#include "LimerootTrickster.hpp"
#include "BeastJsonLoader.hpp"

LimerootTrickster::LimerootTrickster(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

LimerootTrickster::~LimerootTrickster(void) {}

LimerootTrickster::LimerootTrickster(const LimerootTrickster& other) { *this = other; }

LimerootTrickster& LimerootTrickster::operator=(const LimerootTrickster& other)
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

BestiaryID LimerootTrickster::getID(void) const { return BEAST_LIMEROOT_TRICKSTER; }
const std::string& LimerootTrickster::getName(void) const { return _name; }
const std::string& LimerootTrickster::getDescription(void) const { return _description; }
const std::vector<std::string>& LimerootTrickster::getDrops(void) const { return _drops; }
const std::string& LimerootTrickster::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& LimerootTrickster::getLoreNotes(void) const { return _notes; }

void LimerootTrickster::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	LimerootTrickster::loadFromFile(const std::string& filepath)
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
