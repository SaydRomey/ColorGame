// tests.hpp

#ifndef TESTS_HPP
# define TESTS_HPP

# define BESTIARY_PATH	"data/bestiary"

# include "ansi.hpp"		// ansi escape sequences
# include "BeastRegistry.hpp"
# include "SimpleBeast.hpp"	// for down-cast

# include <cstdlib>			// for system()
# include <iomanip>			// std::setw
# include <iostream>
# include <sstream>
# include <vector>

void	printBeastData(Beast* beast, bool fancyPrint);
void	runInteractiveTester(void);

#endif // TESTS_HPP
