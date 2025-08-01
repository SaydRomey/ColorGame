
#include "NullRoot.hpp"
#include "BeastJsonLoader.hpp"

NullRoot::NullRoot(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

NullRoot::~NullRoot(void) {}

NullRoot::NullRoot(const NullRoot& other) { *this = other; }

NullRoot& NullRoot::operator=(const NullRoot& other)
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

BestiaryID NullRoot::getID(void) const { return BEAST_NULL_ROOT; }
const std::string& NullRoot::getName(void) const { return _name; }
const std::string& NullRoot::getDescription(void) const { return _description; }
const std::vector<std::string>& NullRoot::getDrops(void) const { return _drops; }
const std::string& NullRoot::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& NullRoot::getLoreNotes(void) const { return _notes; }

void NullRoot::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	NullRoot::loadFromFile(const std::string& filepath)
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
