// BeastJsonLoader.hpp

#ifndef BEAST_JSON_LOADER_HPP
# define BEAST_JSON_LOADER_HPP

# include "BeastData.hpp"
# include <string>

namespace BeastJsonLoader
{
	bool	loadFromFile(const std::string& path, BeastData& data);
}

#endif // BEAST_JSON_LOADER_HPP
