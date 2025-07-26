
#include "SunburntJackal.hpp"
#include "BeastJsonLoader.hpp"

SunburntJackal::SunburntJackal(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

SunburntJackal::~SunburntJackal(void) {}

SunburntJackal::SunburntJackal(const SunburntJackal& other) { *this = other; }

SunburntJackal& SunburntJackal::operator=(const SunburntJackal& other)
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

BestiaryID SunburntJackal::getID(void) const { return BEAST_SUNBURNT_JACKAL; }
const std::string& SunburntJackal::getName(void) const { return _name; }
const std::string& SunburntJackal::getDescription(void) const { return _description; }
const std::vector<std::string>& SunburntJackal::getDrops(void) const { return _drops; }
const std::string& SunburntJackal::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& SunburntJackal::getLoreNotes(void) const { return _notes; }

void SunburntJackal::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	SunburntJackal::loadFromFile(const std::string& filepath)
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
