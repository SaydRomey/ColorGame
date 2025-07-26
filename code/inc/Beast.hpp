// Beast.hpp

#ifndef BEAST_HPP
# define BEAST_HPP

# include "BestiaryIDs.hpp"
# include "picojson.h"
# include <string>
# include <vector>

class Beast
{
	public:
		virtual	~Beast() {}

		virtual BestiaryID	getID() const = 0;
		virtual const std::string&	getName() const = 0;
		virtual const std::string&	getDescription() const = 0;
		virtual const std::vector<std::string>&	getDrops() const = 0;
		virtual const std::string&	getLoreQuote() const = 0;
		virtual const std::vector<std::string>&	getLoreNotes() const = 0;

		virtual void	onEncounter() = 0;

		// Optional: load from JSON
		virtual bool	loadFromFile(const std::string& filepath) = 0;
};

#endif // BEAST_HPP
