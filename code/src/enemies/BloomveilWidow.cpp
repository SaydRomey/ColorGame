
#include "BloomveilWidow.hpp"
#include "BeastJsonLoader.hpp"

BloomveilWidow::BloomveilWidow(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

BloomveilWidow::~BloomveilWidow(void) {}

BloomveilWidow::BloomveilWidow(const BloomveilWidow& other) { *this = other; }

BloomveilWidow& BloomveilWidow::operator=(const BloomveilWidow& other)
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

BestiaryID BloomveilWidow::getID(void) const { return BEAST_BLOOMVEIL_WIDOW; }
const std::string& BloomveilWidow::getName(void) const { return _name; }
const std::string& BloomveilWidow::getDescription(void) const { return _description; }
const std::vector<std::string>& BloomveilWidow::getDrops(void) const { return _drops; }
const std::string& BloomveilWidow::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& BloomveilWidow::getLoreNotes(void) const { return _notes; }

void BloomveilWidow::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	BloomveilWidow::loadFromFile(const std::string& filepath)
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
