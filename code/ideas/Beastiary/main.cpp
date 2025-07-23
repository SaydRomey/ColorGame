// main.cpp

#include "Bestiary.hpp"
#include <iostream>

int main(void)
{
	if (!Bestiary::instance().loadFromFile("data/bestiary_lore.json"))
	{
		std::cerr << "Failed to load bestiary!\n";
		return (1);
	}

	// Example usage:
	const LorePage& page = Bestiary::instance().getLore(BEAST_ABYSSAL_CURRENT);
	std::cout << page.getName() << "\n\n" << page.getDescription() << "\n";

	return (0);
}
