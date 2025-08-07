// Beast.hpp

#ifndef BEAST_HPP
# define BEAST_HPP

# include "BestiaryIDs.hpp"
// # include "picojson.h"
# include <string>
# include <vector>

class Beast
{
	public:
		virtual	~Beast(void) {}

		virtual BestiaryID						getID(void) const = 0;
		virtual const std::string&				getName(void) const = 0;
		virtual const std::string&				getDescription(void) const = 0;
		virtual const std::vector<std::string>&	getDrops(void) const = 0;
		virtual const std::string&				getLoreQuote(void) const = 0;
		virtual const std::vector<std::string>&	getLoreNotes(void) const = 0;

		virtual void	onEncounter(void) = 0; // gameplay hook
		virtual bool	loadFromFile(const std::string& filepath) = 0; // populate from JSON
};

#endif // BEAST_HPP
