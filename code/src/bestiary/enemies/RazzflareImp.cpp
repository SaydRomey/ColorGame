
#include "RazzflareImp.hpp"
#include "BeastJsonLoader.hpp"

RazzflareImp::RazzflareImp(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

RazzflareImp::~RazzflareImp(void) {}

RazzflareImp::RazzflareImp(const RazzflareImp& other) { *this = other; }

RazzflareImp& RazzflareImp::operator=(const RazzflareImp& other)
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

BestiaryID RazzflareImp::getID(void) const { return BEAST_RAZZFLARE_IMP; }
const std::string& RazzflareImp::getName(void) const { return _name; }
const std::string& RazzflareImp::getDescription(void) const { return _description; }
const std::vector<std::string>& RazzflareImp::getDrops(void) const { return _drops; }
const std::string& RazzflareImp::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& RazzflareImp::getLoreNotes(void) const { return _notes; }

void RazzflareImp::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	RazzflareImp::loadFromFile(const std::string& filepath)
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
