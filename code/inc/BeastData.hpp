
#ifndef BEAST_DATA_HPP
# define BEAST_DATA_HPP

# include <string>
# include <vector>

struct BeastData
{
	std::string id;

	// Entry section
	std::string name;
	std::string type;
	std::string threat_level;
	std::string first_emerged;
	std::string description;
	std::string hue_interaction;
	std::string behavior;
	std::string weaknesses;
	std::string notes;

	// Lore section
	std::string lore_title;
	std::string lore_quote;
	std::vector<std::string> lore_flavor_description;
	std::vector<std::string> lore_field_notes;
	std::string lore_source;

	// Drops
	std::vector<std::string> drops;
};

#endif // BEAST_DATA_HPP
