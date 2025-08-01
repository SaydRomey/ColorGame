
#include "ColorlessShape.hpp"
#include "BeastJsonLoader.hpp"

ColorlessShape::ColorlessShape(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

ColorlessShape::~ColorlessShape(void) {}

ColorlessShape::ColorlessShape(const ColorlessShape& other) { *this = other; }

ColorlessShape& ColorlessShape::operator=(const ColorlessShape& other)
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

BestiaryID ColorlessShape::getID(void) const { return BEAST_COLORLESS_SHAPE; }
const std::string& ColorlessShape::getName(void) const { return _name; }
const std::string& ColorlessShape::getDescription(void) const { return _description; }
const std::vector<std::string>& ColorlessShape::getDrops(void) const { return _drops; }
const std::string& ColorlessShape::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& ColorlessShape::getLoreNotes(void) const { return _notes; }

void ColorlessShape::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	ColorlessShape::loadFromFile(const std::string& filepath)
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
