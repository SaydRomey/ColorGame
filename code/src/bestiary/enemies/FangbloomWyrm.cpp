
#include "FangbloomWyrm.hpp"
#include "BeastJsonLoader.hpp"

FangbloomWyrm::FangbloomWyrm(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

FangbloomWyrm::~FangbloomWyrm(void) {}

FangbloomWyrm::FangbloomWyrm(const FangbloomWyrm& other) { *this = other; }

FangbloomWyrm& FangbloomWyrm::operator=(const FangbloomWyrm& other)
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

BestiaryID FangbloomWyrm::getID(void) const { return BEAST_FANGBLOOM_WYRM; }
const std::string& FangbloomWyrm::getName(void) const { return _name; }
const std::string& FangbloomWyrm::getDescription(void) const { return _description; }
const std::vector<std::string>& FangbloomWyrm::getDrops(void) const { return _drops; }
const std::string& FangbloomWyrm::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& FangbloomWyrm::getLoreNotes(void) const { return _notes; }

void FangbloomWyrm::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	FangbloomWyrm::loadFromFile(const std::string& filepath)
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
