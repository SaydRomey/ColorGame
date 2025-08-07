
#ifndef MEMORYLEECH_HPP
# define MEMORYLEECH_HPP

# include "Beast.hpp"

class MemoryLeech : public Beast
{
	public:
		MemoryLeech(void);
		MemoryLeech(const MemoryLeech& other);
		MemoryLeech& operator=(const MemoryLeech& other);
		~MemoryLeech(void);

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

#endif // MEMORYLEECH_HPP
