
#include "CitrineGolem.hpp"
#include "BeastJsonLoader.hpp"

CitrineGolem::CitrineGolem(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

CitrineGolem::~CitrineGolem(void) {}

CitrineGolem::CitrineGolem(const CitrineGolem& other) { *this = other; }

CitrineGolem& CitrineGolem::operator=(const CitrineGolem& other)
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

BestiaryID CitrineGolem::getID(void) const { return BEAST_CITRINE_GOLEM; }
const std::string& CitrineGolem::getName(void) const { return _name; }
const std::string& CitrineGolem::getDescription(void) const { return _description; }
const std::vector<std::string>& CitrineGolem::getDrops(void) const { return _drops; }
const std::string& CitrineGolem::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& CitrineGolem::getLoreNotes(void) const { return _notes; }

void CitrineGolem::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	CitrineGolem::loadFromFile(const std::string& filepath)
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
