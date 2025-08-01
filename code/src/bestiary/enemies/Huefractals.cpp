
#include "Huefractals.hpp"
#include "BeastJsonLoader.hpp"

Huefractals::Huefractals(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

Huefractals::~Huefractals(void) {}

Huefractals::Huefractals(const Huefractals& other) { *this = other; }

Huefractals& Huefractals::operator=(const Huefractals& other)
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

BestiaryID Huefractals::getID(void) const { return BEAST_HUEFRACTALS; }
const std::string& Huefractals::getName(void) const { return _name; }
const std::string& Huefractals::getDescription(void) const { return _description; }
const std::vector<std::string>& Huefractals::getDrops(void) const { return _drops; }
const std::string& Huefractals::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& Huefractals::getLoreNotes(void) const { return _notes; }

void Huefractals::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	Huefractals::loadFromFile(const std::string& filepath)
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
