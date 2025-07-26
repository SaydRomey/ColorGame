
#include "BannerboundRevenant.hpp"
#include "BeastJsonLoader.hpp"

BannerboundRevenant::BannerboundRevenant(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

BannerboundRevenant::~BannerboundRevenant(void) {}

BannerboundRevenant::BannerboundRevenant(const BannerboundRevenant& other) { *this = other; }

BannerboundRevenant& BannerboundRevenant::operator=(const BannerboundRevenant& other)
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

BestiaryID BannerboundRevenant::getID(void) const { return BEAST_BANNERBOUND_REVENANT; }
const std::string& BannerboundRevenant::getName(void) const { return _name; }
const std::string& BannerboundRevenant::getDescription(void) const { return _description; }
const std::vector<std::string>& BannerboundRevenant::getDrops(void) const { return _drops; }
const std::string& BannerboundRevenant::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& BannerboundRevenant::getLoreNotes(void) const { return _notes; }

void BannerboundRevenant::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	BannerboundRevenant::loadFromFile(const std::string& filepath)
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
