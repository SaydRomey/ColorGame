// SimpleBeast.hpp

#ifndef SIMPLE_BEAST_HPP
# define SIMPLE_BEAST_HPP

# include "Beast.hpp"
# include "BeastData.hpp"
# include "BestiaryLookup.hpp"
# include <vector>
# include <string>

class SimpleBeast : public Beast
{
	public:
		explicit		SimpleBeast(const BeastData& data);
						SimpleBeast(const SimpleBeast& other);
		SimpleBeast&	operator=(const SimpleBeast& other);
		virtual			~SimpleBeast(void);

		/* Beast Interface */
		BestiaryID						getID(void) const;
		const std::string&				getName(void) const;
		const std::string&				getDescription(void) const;
		const std::vector<std::string>&	getDrops(void) const;
		const std::string&				getLoreQuote(void) const;
		const std::vector<std::string>&	getLoreNotes(void) const;

		/* Exposes the raw structured record for fancy printing */
		const	BeastData&				getData(void) const;

		void	onEncounter(void); // empty stub
		bool	loadFromFile(const std::string&); // never used (returns false)

	private:
		BeastData	_data;
};

#endif // SIMPLE_BEAST_HPP
