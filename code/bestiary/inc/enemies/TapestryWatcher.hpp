
#ifndef TAPESTRYWATCHER_HPP
# define TAPESTRYWATCHER_HPP

# include "Beast.hpp"

class TapestryWatcher : public Beast
{
	public:
		TapestryWatcher(void);
		TapestryWatcher(const TapestryWatcher& other);
		TapestryWatcher& operator=(const TapestryWatcher& other);
		~TapestryWatcher(void);

		BestiaryID			getID(void) const;
		const std::string&	getName(void) const;
		const std::string&	getDescription(void) const;
		const std::vector<std::string>&	getDrops(void) const;
		const std::string&	getLoreQuote(void) const;
		const std::vector<std::string>&	getLoreNotes(void) const;

		void	onEncounter(void);
		bool	loadFromFile(const std::string& filepath);

	private:
		std::string					_name;
		std::string					_description;
		std::string					_quote;
		std::vector<std::string>	_notes;
		std::vector<std::string>	_drops;
};

#endif // TAPESTRYWATCHER_HPP
