// printBeastData.cpp

#include "tests.hpp"

/*
entry->name - [Nickname? (todo)]
[todo] Short description (find name for JSON file section)
lore->quote

lore->flavor_description

---

"Lore Entry"

lore->source

(italic)
lore->field_notes
(reset)

---

"Bestiary Entry"

Name: entry->name
Type: entry->type
Threat Level: entry->threat_level
First Emerged: entry->first_emerged

"Description:"
entry->description

"Hue Interaction:"
entry->hue_interaction

"Behavior:"
entry->behavior

"Known Weaknesses:""
entry->weaknesses

"Notes:"
entry->notes

*/

/* Splits a multi-line JSON string on '\n' and prints each line indented */
static void	printMultiline(const std::string& text, const std::string& indent = "")
{
	std::istringstream	ss(text);
	std::string			line;

	while (std::getline(ss, line))
		std::cout << indent << line << std::endl;
}

/* Fancy Printer */
static void	printBeastDataFancy(Beast* base)
{
	const SimpleBeast*	sb = dynamic_cast<const SimpleBeast*>(base);
	if (!sb)
	{
		std::cout << "Unknown beast type." << std::endl;
		return ;
	}

	const BeastData&	d = sb->getData();

	/* Header */
	std::cout << "\n--- " << BOLD << d.name;
	if (!d.lore_title.empty())
		std::cout << " - " << d.lore_title;
	std::cout << " ---\n" << RESET << std::endl;

	/* [TODO] image path? */
	/* [TODO] short visual description (not in JSON files..)*/

	/* Quote */
	if (!d.lore_quote.empty())
		std::cout << ITALIC << '"' << d.lore_quote << '"' << RESET << "\n\n";

	/* Flavour description bullets */
	for (size_t i = 0; i < d.lore_flavor_description.size(); ++i)
		std::cout << d.lore_flavor_description[i] << '\n';
	std::cout << "\n---\n\n";

	/* Bestiary entry table-ish */
	const int	labelWidth = 15;
	std::cout << BOLD << "Bestiary Entry" << RESET << std::endl;
	std::cout << std::left
			  << std::setw(labelWidth) << "Type: "          << d.type          << '\n'
			  << std::setw(labelWidth) << "Threat Level: "  << d.threat_level  << '\n'
			  << std::setw(labelWidth) << "First Emerged: " << d.first_emerged << '\n'
			  << std::right << std::endl;

	/* Long sections */
	std::cout << BOLD << "Description:\n" << RESET;
	printMultiline(d.description, "  ");

	std::cout << '\n' << BOLD << "Hue Interaction:\n" << RESET;
	printMultiline(d.hue_interaction, "  • ");

	std::cout << '\n' << BOLD << "Behavior:\n" << RESET;
	printMultiline(d.behavior, "  • ");

	std::cout << '\n' << BOLD << "Known Weaknesses:\n" << RESET;
	printMultiline(d.weaknesses, "  • ");

	std::cout << '\n' << BOLD << "Notes:\n" << RESET;
	printMultiline(d.notes, "  ");

	/* Field notes (lore narrative) */
	if (!d.lore_field_notes.empty())
	{
		std::cout << "\n---\n\n"
		          << BOLD << "Lore Entry - " << d.lore_source << RESET << "\n\n";
		for (size_t i = 0; i < d.lore_field_notes.size(); ++i)
			std::cout << GRAYTALIC << '"' << d.lore_field_notes[i] << '"' << RESET << '\n' << std::endl;
	}

	/* Drops */
	if (!d.drops.empty())
	{
		std::cout << "\nDrops:\n";
		for (size_t i = 0; i < d.drops.size(); ++i)
			std::cout << "  • " << d.drops[i] << '\n';
	}
}

/* Basic Printer */
void	printBeastData(Beast* beast, bool fancyPrint = true)
{
	if (fancyPrint)
	{
		printBeastDataFancy(beast);
		return ;
	}

	std::cout << "\n--- " << beast->getName() << " ---\n";

	std::cout << beast->getDescription() << std::endl;
	std::cout << "\nDrops:\n";
	for (size_t i = 0; i < beast->getDrops().size(); ++i)
		std::cout << " • " << beast->getDrops()[i] << std::endl;
	std::cout << "\nQuote: " << beast->getLoreQuote() << std::endl;

	std::cout << "\nField notes:\n";
	for (size_t i = 0; i < beast->getLoreNotes().size(); ++i)
		std::cout << "   - " << beast->getLoreNotes()[i] << std::endl;
}
