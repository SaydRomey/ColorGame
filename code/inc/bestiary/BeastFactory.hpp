// BeastFactory.hpp

#ifndef BEAST_FACTORY_HPP
# define BEAST_FACTORY_HPP

# include "Beast.hpp"
// # include "BestiaryIDs.hpp"

class BeastFactory
{
	public:
		/* create a SimpleBeast from any JSON file */
		static Beast*	createFromFile(const std::string& filepath);
};

#endif // BEAST_FACTORY_HPP
