
#include "PrismUnform.hpp"
#include "BeastJsonLoader.hpp"

PrismUnform::PrismUnform(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

PrismUnform::~PrismUnform(void) {}

PrismUnform::PrismUnform(const PrismUnform& other) { *this = other; }

PrismUnform& PrismUnform::operator=(const PrismUnform& other)
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

BestiaryID PrismUnform::getID(void) const { return BEAST_PRISM_UNFORM; }
const std::string& PrismUnform::getName(void) const { return _name; }
const std::string& PrismUnform::getDescription(void) const { return _description; }
const std::vector<std::string>& PrismUnform::getDrops(void) const { return _drops; }
const std::string& PrismUnform::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& PrismUnform::getLoreNotes(void) const { return _notes; }

void PrismUnform::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	PrismUnform::loadFromFile(const std::string& filepath)
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
