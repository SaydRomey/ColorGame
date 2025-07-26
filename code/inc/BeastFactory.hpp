// BeastFactory.hpp

#ifndef BEAST_FACTORY_HPP
# define BEAST_FACTORY_HPP

# include "Beast.hpp"
# include "BestiaryIDs.hpp"

class BeastFactory
{
	public:
		// Create a full beast instance from JSON file
		static Beast*	createFromFile(const std::string& filepath);
		// static Beast*	createFromID(BestiaryID id);  // resolves path internally
};

#endif // BEAST_FACTORY_HPP
