
#include "LavaFusedBehemoth.hpp"
#include "BeastJsonLoader.hpp"

LavaFusedBehemoth::LavaFusedBehemoth(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

LavaFusedBehemoth::~LavaFusedBehemoth(void) {}

LavaFusedBehemoth::LavaFusedBehemoth(const LavaFusedBehemoth& other) { *this = other; }

LavaFusedBehemoth& LavaFusedBehemoth::operator=(const LavaFusedBehemoth& other)
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

BestiaryID LavaFusedBehemoth::getID(void) const { return BEAST_LAVA_FUSED_BEHEMOTH; }
const std::string& LavaFusedBehemoth::getName(void) const { return _name; }
const std::string& LavaFusedBehemoth::getDescription(void) const { return _description; }
const std::vector<std::string>& LavaFusedBehemoth::getDrops(void) const { return _drops; }
const std::string& LavaFusedBehemoth::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& LavaFusedBehemoth::getLoreNotes(void) const { return _notes; }

void LavaFusedBehemoth::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	LavaFusedBehemoth::loadFromFile(const std::string& filepath)
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
