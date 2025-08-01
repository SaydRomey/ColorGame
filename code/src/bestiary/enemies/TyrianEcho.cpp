
#include "TyrianEcho.hpp"
#include "BeastJsonLoader.hpp"

TyrianEcho::TyrianEcho(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

TyrianEcho::~TyrianEcho(void) {}

TyrianEcho::TyrianEcho(const TyrianEcho& other) { *this = other; }

TyrianEcho& TyrianEcho::operator=(const TyrianEcho& other)
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

BestiaryID TyrianEcho::getID(void) const { return BEAST_TYRIAN_ECHO; }
const std::string& TyrianEcho::getName(void) const { return _name; }
const std::string& TyrianEcho::getDescription(void) const { return _description; }
const std::vector<std::string>& TyrianEcho::getDrops(void) const { return _drops; }
const std::string& TyrianEcho::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& TyrianEcho::getLoreNotes(void) const { return _notes; }

void TyrianEcho::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	TyrianEcho::loadFromFile(const std::string& filepath)
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
