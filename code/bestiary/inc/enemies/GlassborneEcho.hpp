
#ifndef GLASSBORNEECHO_HPP
# define GLASSBORNEECHO_HPP

# include "Beast.hpp"

class GlassborneEcho : public Beast
{
	public:
		GlassborneEcho(void);
		GlassborneEcho(const GlassborneEcho& other);
		GlassborneEcho& operator=(const GlassborneEcho& other);
		~GlassborneEcho(void);

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

#endif // GLASSBORNEECHO_HPP
