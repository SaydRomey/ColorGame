
#include "FandancerFragment.hpp"
#include "BeastJsonLoader.hpp"

FandancerFragment::FandancerFragment(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

FandancerFragment::~FandancerFragment(void) {}

FandancerFragment::FandancerFragment(const FandancerFragment& other) { *this = other; }

FandancerFragment& FandancerFragment::operator=(const FandancerFragment& other)
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

BestiaryID FandancerFragment::getID(void) const { return BEAST_FANDANCER_FRAGMENT; }
const std::string& FandancerFragment::getName(void) const { return _name; }
const std::string& FandancerFragment::getDescription(void) const { return _description; }
const std::vector<std::string>& FandancerFragment::getDrops(void) const { return _drops; }
const std::string& FandancerFragment::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& FandancerFragment::getLoreNotes(void) const { return _notes; }

void FandancerFragment::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	FandancerFragment::loadFromFile(const std::string& filepath)
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
