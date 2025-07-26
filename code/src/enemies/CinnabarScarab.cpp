
#include "CinnabarScarab.hpp"
#include "BeastJsonLoader.hpp"

CinnabarScarab::CinnabarScarab(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

CinnabarScarab::~CinnabarScarab(void) {}

CinnabarScarab::CinnabarScarab(const CinnabarScarab& other) { *this = other; }

CinnabarScarab& CinnabarScarab::operator=(const CinnabarScarab& other)
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

BestiaryID CinnabarScarab::getID(void) const { return BEAST_CINNABAR_SCARAB; }
const std::string& CinnabarScarab::getName(void) const { return _name; }
const std::string& CinnabarScarab::getDescription(void) const { return _description; }
const std::vector<std::string>& CinnabarScarab::getDrops(void) const { return _drops; }
const std::string& CinnabarScarab::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& CinnabarScarab::getLoreNotes(void) const { return _notes; }

void CinnabarScarab::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	CinnabarScarab::loadFromFile(const std::string& filepath)
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
