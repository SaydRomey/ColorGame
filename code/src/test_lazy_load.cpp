
#include "BeastRegistry.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void	runInteractiveTester(void)
{
    bool LOOP = true;

    BeastRegistry	registry;
    if (!registry.loadMetadataDirectory("data/bestiary"))
	{
        std::cerr << "Failed to load metadata.\n";
        return ;
    }

    // Build a list of all valid BestiaryIDs in order
    std::vector<BestiaryID>	ids;
	int	i = 0;
    while (i < BESTIARY_ID_COUNT)
	{
        BestiaryID	id = static_cast<BestiaryID>(i);
        if (registry.getMetadata(id))
		{
            ids.push_back(id);
        }
		++i;
    }

    while (LOOP)
	{
        // Print menu
        std::cout << "\n=== Bestiary Tester ===\n";

		size_t idx = 0;
        while (idx < ids.size())
		{
            const BeastMetadata*	meta = registry.getMetadata(ids[idx]);
            std::cout << " [" << idx << "] " << meta->name 
                      << " (" << meta->type << ")\n";
			++idx;
        }
        std::cout << " [q] Quit\n";
        std::cout << "Choose monster index> " << std::flush;

        std::string	choice;
        if (!std::getline(std::cin, choice))
			break ;
        if (choice == "q" || choice == "Q")
		{
            break ;
        }

        std::cout << "HERE" << std::endl;

		// parse integer
        std::istringstream	ss(choice);
        int	sel = -1;
        if (!(ss >> sel) || sel < 0 || sel >= static_cast<int>(ids.size()))
		{
            std::cout << "Invalid selection.\n";
            continue ;
        }

        // Lazy‑load the beast
        Beast*	beast = registry.getBeast(ids[sel]);
        if (!beast)
		{
            std::cout << "Failed to load beast data.\n";
            continue ;
        }

        // Print all data
        std::cout << "\n--- [" << sel << "] " 
                  << beast->getName() << " ---\n";
        std::cout << "ID:           " << beast->getID() << "\n";
        std::cout << "Name:         " << beast->getName() << "\n";
        std::cout << "Description:  " << beast->getDescription() << "\n";

		const std::vector<std::string>&	drops = beast->getDrops();
        std::cout << "Drops:\n";
		size_t di = 0;
        while (di < drops.size()) 
		{
            std::cout << "  - " << drops[di] << "\n";
			++di;
        }

        std::cout << "Lore Quote:   " << beast->getLoreQuote() << "\n";
        const std::vector<std::string>& notes = beast->getLoreNotes();
        std::cout << "Lore Notes:\n";
		size_t ni = 0;
		while (ni < notes.size())
        {
            std::cout << "  * " << notes[ni] << "\n";
			++ni;
		}

        LOOP = false;
    }

    std::cout << "Exiting tester.\n";
}
