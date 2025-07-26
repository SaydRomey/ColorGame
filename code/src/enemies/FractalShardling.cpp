
#include "FractalShardling.hpp"
#include "BeastJsonLoader.hpp"

FractalShardling::FractalShardling(void)
	: _name(""), _description(""), _quote(), _notes(), _drops() {}

FractalShardling::~FractalShardling(void) {}

FractalShardling::FractalShardling(const FractalShardling& other) { *this = other; }

FractalShardling& FractalShardling::operator=(const FractalShardling& other)
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

BestiaryID FractalShardling::getID(void) const { return BEAST_FRACTAL_SHARDLING; }
const std::string& FractalShardling::getName(void) const { return _name; }
const std::string& FractalShardling::getDescription(void) const { return _description; }
const std::vector<std::string>& FractalShardling::getDrops(void) const { return _drops; }
const std::string& FractalShardling::getLoreQuote(void) const { return _quote; }
const std::vector<std::string>& FractalShardling::getLoreNotes(void) const { return _notes; }

void FractalShardling::onEncounter(void)
{
	// TODO: Behavior logic
}

bool	FractalShardling::loadFromFile(const std::string& filepath)
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
