
#include "AbyssalCurrent.hpp"
#include "BeastJsonLoader.hpp"

AbyssalCurrent::AbyssalCurrent(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

AbyssalCurrent::~AbyssalCurrent(void) {}

AbyssalCurrent::AbyssalCurrent(const AbyssalCurrent& other) { *this = other; }

AbyssalCurrent& AbyssalCurrent::operator=(const AbyssalCurrent& other)
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

BestiaryID AbyssalCurrent::getID(void) const { return BEAST_ABYSSAL_CURRENT; }
const std::string& AbyssalCurrent::getName(void) const { return _name; }
const std::string& AbyssalCurrent::getDescription(void) const { return _description; }
const std::vector<std::string>& AbyssalCurrent::getDrops(void) const { return _drops; }
const std::string& AbyssalCurrent::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& AbyssalCurrent::getLoreNotes(void) const { return _notes; }

void AbyssalCurrent::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	AbyssalCurrent::loadFromFile(const std::string& filepath)
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
