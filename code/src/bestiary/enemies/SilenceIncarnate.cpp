
#include "SilenceIncarnate.hpp"
#include "BeastJsonLoader.hpp"

SilenceIncarnate::SilenceIncarnate(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

SilenceIncarnate::~SilenceIncarnate(void) {}

SilenceIncarnate::SilenceIncarnate(const SilenceIncarnate& other) { *this = other; }

SilenceIncarnate& SilenceIncarnate::operator=(const SilenceIncarnate& other)
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

BestiaryID SilenceIncarnate::getID(void) const { return BEAST_SILENCE_INCARNATE; }
const std::string& SilenceIncarnate::getName(void) const { return _name; }
const std::string& SilenceIncarnate::getDescription(void) const { return _description; }
const std::vector<std::string>& SilenceIncarnate::getDrops(void) const { return _drops; }
const std::string& SilenceIncarnate::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& SilenceIncarnate::getLoreNotes(void) const { return _notes; }

void SilenceIncarnate::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	SilenceIncarnate::loadFromFile(const std::string& filepath)
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
