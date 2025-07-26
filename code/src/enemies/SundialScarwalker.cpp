
#include "SundialScarwalker.hpp"
#include "BeastJsonLoader.hpp"

SundialScarwalker::SundialScarwalker(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

SundialScarwalker::~SundialScarwalker(void) {}

SundialScarwalker::SundialScarwalker(const SundialScarwalker& other) { *this = other; }

SundialScarwalker& SundialScarwalker::operator=(const SundialScarwalker& other)
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

BestiaryID SundialScarwalker::getID(void) const { return BEAST_SUNDIAL_SCARWALKER; }
const std::string& SundialScarwalker::getName(void) const { return _name; }
const std::string& SundialScarwalker::getDescription(void) const { return _description; }
const std::vector<std::string>& SundialScarwalker::getDrops(void) const { return _drops; }
const std::string& SundialScarwalker::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& SundialScarwalker::getLoreNotes(void) const { return _notes; }

void SundialScarwalker::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	SundialScarwalker::loadFromFile(const std::string& filepath)
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
