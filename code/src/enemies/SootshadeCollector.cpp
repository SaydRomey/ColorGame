
#include "SootshadeCollector.hpp"
#include "BeastJsonLoader.hpp"

SootshadeCollector::SootshadeCollector(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

SootshadeCollector::~SootshadeCollector(void) {}

SootshadeCollector::SootshadeCollector(const SootshadeCollector& other) { *this = other; }

SootshadeCollector& SootshadeCollector::operator=(const SootshadeCollector& other)
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

BestiaryID SootshadeCollector::getID(void) const { return BEAST_SOOTSHADE_COLLECTOR; }
const std::string& SootshadeCollector::getName(void) const { return _name; }
const std::string& SootshadeCollector::getDescription(void) const { return _description; }
const std::vector<std::string>& SootshadeCollector::getDrops(void) const { return _drops; }
const std::string& SootshadeCollector::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& SootshadeCollector::getLoreNotes(void) const { return _notes; }

void SootshadeCollector::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	SootshadeCollector::loadFromFile(const std::string& filepath)
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
