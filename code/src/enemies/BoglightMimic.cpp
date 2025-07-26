
#include "BoglightMimic.hpp"
#include "BeastJsonLoader.hpp"

BoglightMimic::BoglightMimic(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

BoglightMimic::~BoglightMimic(void) {}

BoglightMimic::BoglightMimic(const BoglightMimic& other) { *this = other; }

BoglightMimic& BoglightMimic::operator=(const BoglightMimic& other)
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

BestiaryID BoglightMimic::getID(void) const { return BEAST_BOGLIGHT_MIMIC; }
const std::string& BoglightMimic::getName(void) const { return _name; }
const std::string& BoglightMimic::getDescription(void) const { return _description; }
const std::vector<std::string>& BoglightMimic::getDrops(void) const { return _drops; }
const std::string& BoglightMimic::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& BoglightMimic::getLoreNotes(void) const { return _notes; }

void BoglightMimic::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	BoglightMimic::loadFromFile(const std::string& filepath)
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
