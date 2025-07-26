
#include "BloodrootEffigy.hpp"
#include "BeastJsonLoader.hpp"

BloodrootEffigy::BloodrootEffigy(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

BloodrootEffigy::~BloodrootEffigy(void) {}

BloodrootEffigy::BloodrootEffigy(const BloodrootEffigy& other) { *this = other; }

BloodrootEffigy& BloodrootEffigy::operator=(const BloodrootEffigy& other)
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

BestiaryID BloodrootEffigy::getID(void) const { return BEAST_BLOODROOT_EFFIGY; }
const std::string& BloodrootEffigy::getName(void) const { return _name; }
const std::string& BloodrootEffigy::getDescription(void) const { return _description; }
const std::vector<std::string>& BloodrootEffigy::getDrops(void) const { return _drops; }
const std::string& BloodrootEffigy::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& BloodrootEffigy::getLoreNotes(void) const { return _notes; }

void BloodrootEffigy::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	BloodrootEffigy::loadFromFile(const std::string& filepath)
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
