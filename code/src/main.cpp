
#include "BeastRegistry.hpp"
#include <iostream>

// int	GenerateBestiaryJSON(void);
void	runInteractiveTesterOld(void);
void	runInteractiveTester(void);

int	testBestiary(void)
{
	BeastRegistry	registry;
	if (!registry.loadMetadataDirectory("data/bestiary"))
	{
		std::cerr << "Failed to load metadata.\n";
		return (1);
	}

	// Show UI names
	int	i = 0;
	while (i < BESTIARY_ID_COUNT)
	{
		const BeastMetadata*	meta = registry.getMetadata(static_cast<BestiaryID>(i));
		if (!meta)
		{
			++i;
			continue;
		}
		std::cout << " - " << meta->name << " (" << meta->type << ")\n";
		++i;
	}

	// Lazy load full beast
	Beast*	abyss = registry.getBeast(BEAST_ABYSSAL_CURRENT);
	if (abyss)
	{
		std::cout << "\n" << abyss->getName() << ": " << abyss->getDescription() << "\n";
	}

	return (0);
}


int	main(void)
{
	std::cout << "Color Game (W.I.P.)\n" << std::endl;
	
	// GenerateBestiaryJSON();

	// testBestiary();

	runInteractiveTester();

	return (0);
}
