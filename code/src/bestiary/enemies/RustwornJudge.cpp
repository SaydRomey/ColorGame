
#include "RustwornJudge.hpp"
#include "BeastJsonLoader.hpp"

RustwornJudge::RustwornJudge(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

RustwornJudge::~RustwornJudge(void) {}

RustwornJudge::RustwornJudge(const RustwornJudge& other) { *this = other; }

RustwornJudge& RustwornJudge::operator=(const RustwornJudge& other)
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

BestiaryID RustwornJudge::getID(void) const { return BEAST_RUSTWORN_JUDGE; }
const std::string& RustwornJudge::getName(void) const { return _name; }
const std::string& RustwornJudge::getDescription(void) const { return _description; }
const std::vector<std::string>& RustwornJudge::getDrops(void) const { return _drops; }
const std::string& RustwornJudge::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& RustwornJudge::getLoreNotes(void) const { return _notes; }

void RustwornJudge::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	RustwornJudge::loadFromFile(const std::string& filepath)
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
