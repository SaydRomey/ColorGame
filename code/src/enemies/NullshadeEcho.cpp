
#include "NullshadeEcho.hpp"
#include "BeastJsonLoader.hpp"

NullshadeEcho::NullshadeEcho(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

NullshadeEcho::~NullshadeEcho(void) {}

NullshadeEcho::NullshadeEcho(const NullshadeEcho& other) { *this = other; }

NullshadeEcho& NullshadeEcho::operator=(const NullshadeEcho& other)
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

BestiaryID NullshadeEcho::getID(void) const { return BEAST_NULLSHADE_ECHO; }
const std::string& NullshadeEcho::getName(void) const { return _name; }
const std::string& NullshadeEcho::getDescription(void) const { return _description; }
const std::vector<std::string>& NullshadeEcho::getDrops(void) const { return _drops; }
const std::string& NullshadeEcho::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& NullshadeEcho::getLoreNotes(void) const { return _notes; }

void NullshadeEcho::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	NullshadeEcho::loadFromFile(const std::string& filepath)
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
