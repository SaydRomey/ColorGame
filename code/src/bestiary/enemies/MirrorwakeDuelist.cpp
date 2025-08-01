
#include "MirrorwakeDuelist.hpp"
#include "BeastJsonLoader.hpp"

MirrorwakeDuelist::MirrorwakeDuelist(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

MirrorwakeDuelist::~MirrorwakeDuelist(void) {}

MirrorwakeDuelist::MirrorwakeDuelist(const MirrorwakeDuelist& other) { *this = other; }

MirrorwakeDuelist& MirrorwakeDuelist::operator=(const MirrorwakeDuelist& other)
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

BestiaryID MirrorwakeDuelist::getID(void) const { return BEAST_MIRRORWAKE_DUELIST; }
const std::string& MirrorwakeDuelist::getName(void) const { return _name; }
const std::string& MirrorwakeDuelist::getDescription(void) const { return _description; }
const std::vector<std::string>& MirrorwakeDuelist::getDrops(void) const { return _drops; }
const std::string& MirrorwakeDuelist::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& MirrorwakeDuelist::getLoreNotes(void) const { return _notes; }

void MirrorwakeDuelist::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	MirrorwakeDuelist::loadFromFile(const std::string& filepath)
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
