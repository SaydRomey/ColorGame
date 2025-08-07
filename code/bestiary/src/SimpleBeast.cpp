// SimpleBeast.cpp

#include "SimpleBeast.hpp"

SimpleBeast::SimpleBeast(const BeastData& data) : _data(data) {}
SimpleBeast::SimpleBeast(const SimpleBeast& other) : _data(other._data) {}

SimpleBeast&	SimpleBeast::operator=(const SimpleBeast& other)
{
	if (this != &other)
		_data = other._data;
	return (*this);
}

SimpleBeast::~SimpleBeast(void) {}


BestiaryID						SimpleBeast::getID(void) const { return (toBestiaryID(_data.id)); }
const std::string&				SimpleBeast::getName(void) const { return (_data.name); }
const std::string&				SimpleBeast::getDescription(void) const { return (_data.description); }
const std::vector<std::string>& SimpleBeast::getDrops(void) const { return (_data.drops); }
const std::string&				SimpleBeast::getLoreQuote(void) const { return (_data.lore_quote); }
const std::vector<std::string>& SimpleBeast::getLoreNotes(void) const {	return (_data.lore_field_notes); }
const BeastData&				SimpleBeast::getData(void) const { return (_data); }



void	SimpleBeast::onEncounter(void) { /* stub for now */ }

bool	SimpleBeast::loadFromFile(const std::string&) { return (false); }
