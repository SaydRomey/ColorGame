
#include "GlasslashSerpent.hpp"
#include "BeastJsonLoader.hpp"

GlasslashSerpent::GlasslashSerpent(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

GlasslashSerpent::~GlasslashSerpent(void) {}

GlasslashSerpent::GlasslashSerpent(const GlasslashSerpent& other) { *this = other; }

GlasslashSerpent& GlasslashSerpent::operator=(const GlasslashSerpent& other)
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

BestiaryID GlasslashSerpent::getID(void) const { return BEAST_GLASSLASH_SERPENT; }
const std::string& GlasslashSerpent::getName(void) const { return _name; }
const std::string& GlasslashSerpent::getDescription(void) const { return _description; }
const std::vector<std::string>& GlasslashSerpent::getDrops(void) const { return _drops; }
const std::string& GlasslashSerpent::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& GlasslashSerpent::getLoreNotes(void) const { return _notes; }

void GlasslashSerpent::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	GlasslashSerpent::loadFromFile(const std::string& filepath)
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
