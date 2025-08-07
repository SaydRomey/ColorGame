// test_interactive.cpp

#include "tests.hpp"

static void showMenu(const std::vector<BestiaryID>& ids, const BeastRegistry& reg)
{
	std::cout << "\n=== Bestiary Tester ===\n";

	size_t	idx = 0;
	while (idx < ids.size())
	{
		const BeastMetadata* m = reg.getMetadata(ids[idx]);
		if (m)
		{
			std::cout << " [" << idx << "] " 
					  << m->name 
					  << " (" << m->type << ")\n";
		}
		++idx;
	}
	std::cout << " [q] Quit\n";
	// std::cout << "Choose monster index > " << std::flush;
	std::cout << "> " << std::flush;
}

void runInteractiveTester(void)
{
	BeastRegistry	reg;
	if (!reg.loadMetadataDirectory(BESTIARY_PATH))
	{
		// std::cerr << "Failed to read JSON directory at: " << BESTIARY_PATH << std::endl;
		std::cerr << "Cannot read JSON directory." << std::endl;
		return ;
	}

	std::vector<BestiaryID>	ids;
	int	i = 0;
	while (i < BESTIARY_ID_COUNT)
	{
		if (reg.getMetadata(static_cast<BestiaryID>(i)))
			ids.push_back(static_cast<BestiaryID>(i));
		++i;
	}

	std::string	choice;
	while (true)
	{
		showMenu(ids, reg);
		if (!std::getline(std::cin, choice))
			break ;
		if (choice == "q" || choice == "Q")
			break ;

		// Parse integer input
		std::istringstream	ss(choice);
		int	sel; // = -1; // ?needed?
		if (!(ss >> sel) || sel < 0 || sel >= static_cast<int>(ids.size()))
		{
			std::cout << "Bad input." << std::endl;
			continue ;
		}

		// Lazy-load selected beast
		Beast*	beast = reg.getBeast(ids[sel]);
		if (!beast)
		{
			// std::cout << "Failed to load beast data." << std::endl;
			std::cout << "Load error." << std::endl;
			continue ;
		}

		// Print beast data
		system("clear");
		printBeastData(beast, true);

		std::cout << "\nPress <enter> to return to the list…";
		std::getline(std::cin, choice);
	}
	std::cout << "Good-bye!" << std::endl;
}
