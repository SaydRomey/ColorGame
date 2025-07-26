
#include "GlitteringGrimoire.hpp"
#include "BeastJsonLoader.hpp"

GlitteringGrimoire::GlitteringGrimoire(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

GlitteringGrimoire::~GlitteringGrimoire(void) {}

GlitteringGrimoire::GlitteringGrimoire(const GlitteringGrimoire& other) { *this = other; }

GlitteringGrimoire& GlitteringGrimoire::operator=(const GlitteringGrimoire& other)
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

BestiaryID GlitteringGrimoire::getID(void) const { return BEAST_GLITTERING_GRIMOIRE; }
const std::string& GlitteringGrimoire::getName(void) const { return _name; }
const std::string& GlitteringGrimoire::getDescription(void) const { return _description; }
const std::vector<std::string>& GlitteringGrimoire::getDrops(void) const { return _drops; }
const std::string& GlitteringGrimoire::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& GlitteringGrimoire::getLoreNotes(void) const { return _notes; }

void GlitteringGrimoire::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	GlitteringGrimoire::loadFromFile(const std::string& filepath)
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
