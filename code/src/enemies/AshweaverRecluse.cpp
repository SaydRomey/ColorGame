
#include "AshweaverRecluse.hpp"
#include "BeastJsonLoader.hpp"

AshweaverRecluse::AshweaverRecluse(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

AshweaverRecluse::~AshweaverRecluse(void) {}

AshweaverRecluse::AshweaverRecluse(const AshweaverRecluse& other) { *this = other; }

AshweaverRecluse& AshweaverRecluse::operator=(const AshweaverRecluse& other)
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

BestiaryID AshweaverRecluse::getID(void) const { return BEAST_ASHWEAVER_RECLUSE; }
const std::string& AshweaverRecluse::getName(void) const { return _name; }
const std::string& AshweaverRecluse::getDescription(void) const { return _description; }
const std::vector<std::string>& AshweaverRecluse::getDrops(void) const { return _drops; }
const std::string& AshweaverRecluse::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& AshweaverRecluse::getLoreNotes(void) const { return _notes; }

void AshweaverRecluse::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	AshweaverRecluse::loadFromFile(const std::string& filepath)
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
