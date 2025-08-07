
#include "SunflareMarionette.hpp"
#include "BeastJsonLoader.hpp"

SunflareMarionette::SunflareMarionette(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

SunflareMarionette::~SunflareMarionette(void) {}

SunflareMarionette::SunflareMarionette(const SunflareMarionette& other) { *this = other; }

SunflareMarionette& SunflareMarionette::operator=(const SunflareMarionette& other)
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

BestiaryID SunflareMarionette::getID(void) const { return BEAST_SUNFLARE_MARIONETTE; }
const std::string& SunflareMarionette::getName(void) const { return _name; }
const std::string& SunflareMarionette::getDescription(void) const { return _description; }
const std::vector<std::string>& SunflareMarionette::getDrops(void) const { return _drops; }
const std::string& SunflareMarionette::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& SunflareMarionette::getLoreNotes(void) const { return _notes; }

void SunflareMarionette::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	SunflareMarionette::loadFromFile(const std::string& filepath)
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
