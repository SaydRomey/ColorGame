
#include "PhylacterySwarm.hpp"
#include "BeastJsonLoader.hpp"

PhylacterySwarm::PhylacterySwarm(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

PhylacterySwarm::~PhylacterySwarm(void) {}

PhylacterySwarm::PhylacterySwarm(const PhylacterySwarm& other) { *this = other; }

PhylacterySwarm& PhylacterySwarm::operator=(const PhylacterySwarm& other)
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

BestiaryID PhylacterySwarm::getID(void) const { return BEAST_PHYLACTERY_SWARM; }
const std::string& PhylacterySwarm::getName(void) const { return _name; }
const std::string& PhylacterySwarm::getDescription(void) const { return _description; }
const std::vector<std::string>& PhylacterySwarm::getDrops(void) const { return _drops; }
const std::string& PhylacterySwarm::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& PhylacterySwarm::getLoreNotes(void) const { return _notes; }

void PhylacterySwarm::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	PhylacterySwarm::loadFromFile(const std::string& filepath)
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
