
#ifndef BOGLIGHTMIMIC_HPP
# define BOGLIGHTMIMIC_HPP

# include "Beast.hpp"

class BoglightMimic : public Beast
{
	public:
		BoglightMimic(void);
		BoglightMimic(const BoglightMimic& other);
		BoglightMimic& operator=(const BoglightMimic& other);
		~BoglightMimic(void);

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

#endif // BOGLIGHTMIMIC_HPP
