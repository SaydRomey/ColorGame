
#include "TidewornApostle.hpp"
#include "BeastJsonLoader.hpp"

TidewornApostle::TidewornApostle(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

TidewornApostle::~TidewornApostle(void) {}

TidewornApostle::TidewornApostle(const TidewornApostle& other) { *this = other; }

TidewornApostle& TidewornApostle::operator=(const TidewornApostle& other)
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

BestiaryID TidewornApostle::getID(void) const { return BEAST_TIDEWORN_APOSTLE; }
const std::string& TidewornApostle::getName(void) const { return _name; }
const std::string& TidewornApostle::getDescription(void) const { return _description; }
const std::vector<std::string>& TidewornApostle::getDrops(void) const { return _drops; }
const std::string& TidewornApostle::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& TidewornApostle::getLoreNotes(void) const { return _notes; }

void TidewornApostle::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	TidewornApostle::loadFromFile(const std::string& filepath)
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
