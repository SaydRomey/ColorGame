// BeastRegistry.hpp

#ifndef BEAST_REGISTRY_HPP
# define BEAST_REGISTRY_HPP

# include "BestiaryIDs.hpp"
# include "Beast.hpp"
# include <map>
# include <string>

struct BeastMetadata
{
	std::string	name;
	std::string	type;
	std::string	threat;
	std::string	jsonPath;
};

class BeastRegistry
{
	public:
		BeastRegistry(void);
		// BeastRegistry(const BeastRegistry& other);
		// BeastRegistry&	operator=(const BeastRegistry& other);
		~BeastRegistry(void);

		bool	loadMetadataDirectory(const std::string& dir);
		const BeastMetadata*	getMetadata(BestiaryID id) const;
		Beast*	getBeast(BestiaryID id); // lazily loads & caches
		void	unloadAll();

	private:
		std::map<BestiaryID, BeastMetadata>	_metadata;
		std::map<BestiaryID, Beast*>		_beastCache;
};


#endif // BEAST_REGISTRY_HPP
