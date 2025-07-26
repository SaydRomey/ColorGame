
#ifndef VERDANTMAW_HPP
# define VERDANTMAW_HPP

# include "Beast.hpp"

class VerdantMaw : public Beast
{
	public:
		VerdantMaw(void);
		VerdantMaw(const VerdantMaw& other);
		VerdantMaw& operator=(const VerdantMaw& other);
		~VerdantMaw(void);

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

#endif // VERDANTMAW_HPP
