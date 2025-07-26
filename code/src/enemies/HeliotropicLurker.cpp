
#include "HeliotropicLurker.hpp"
#include "BeastJsonLoader.hpp"

HeliotropicLurker::HeliotropicLurker(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

HeliotropicLurker::~HeliotropicLurker(void) {}

HeliotropicLurker::HeliotropicLurker(const HeliotropicLurker& other) { *this = other; }

HeliotropicLurker& HeliotropicLurker::operator=(const HeliotropicLurker& other)
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

BestiaryID HeliotropicLurker::getID(void) const { return BEAST_HELIOTROPIC_LURKER; }
const std::string& HeliotropicLurker::getName(void) const { return _name; }
const std::string& HeliotropicLurker::getDescription(void) const { return _description; }
const std::vector<std::string>& HeliotropicLurker::getDrops(void) const { return _drops; }
const std::string& HeliotropicLurker::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& HeliotropicLurker::getLoreNotes(void) const { return _notes; }

void HeliotropicLurker::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	HeliotropicLurker::loadFromFile(const std::string& filepath)
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
