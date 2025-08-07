
#include "GlassborneEcho.hpp"
#include "BeastJsonLoader.hpp"

GlassborneEcho::GlassborneEcho(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

GlassborneEcho::~GlassborneEcho(void) {}

GlassborneEcho::GlassborneEcho(const GlassborneEcho& other) { *this = other; }

GlassborneEcho& GlassborneEcho::operator=(const GlassborneEcho& other)
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

BestiaryID GlassborneEcho::getID(void) const { return BEAST_GLASSBORNE_ECHO; }
const std::string& GlassborneEcho::getName(void) const { return _name; }
const std::string& GlassborneEcho::getDescription(void) const { return _description; }
const std::vector<std::string>& GlassborneEcho::getDrops(void) const { return _drops; }
const std::string& GlassborneEcho::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& GlassborneEcho::getLoreNotes(void) const { return _notes; }

void GlassborneEcho::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	GlassborneEcho::loadFromFile(const std::string& filepath)
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
