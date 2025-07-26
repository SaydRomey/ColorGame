
#include "FuneralDancer.hpp"
#include "BeastJsonLoader.hpp"

FuneralDancer::FuneralDancer(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

FuneralDancer::~FuneralDancer(void) {}

FuneralDancer::FuneralDancer(const FuneralDancer& other) { *this = other; }

FuneralDancer& FuneralDancer::operator=(const FuneralDancer& other)
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

BestiaryID FuneralDancer::getID(void) const { return BEAST_FUNERAL_DANCER; }
const std::string& FuneralDancer::getName(void) const { return _name; }
const std::string& FuneralDancer::getDescription(void) const { return _description; }
const std::vector<std::string>& FuneralDancer::getDrops(void) const { return _drops; }
const std::string& FuneralDancer::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& FuneralDancer::getLoreNotes(void) const { return _notes; }

void FuneralDancer::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	FuneralDancer::loadFromFile(const std::string& filepath)
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
