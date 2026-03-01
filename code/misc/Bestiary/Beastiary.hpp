// Bestiary.hpp

#pragma once
#include "BestiaryIDs.hpp"
#include <string>
#include <map>

// ----------------------------------------------------------------
// LorePage
// ----------------------------------------------------------------
class LorePage {
	public:
		LorePage();
		LorePage(const std::string& name, const std::string& desc);
		LorePage(const LorePage& other);
		~LorePage();
		LorePage&	operator=(const LorePage& other);

	const std::string&	getName() const;
	const std::string&	getDescription() const;

	private:
		std::string _name;
		std::string _description;
};

// ----------------------------------------------------------------
// Bestiary manager (singleton style)
// ----------------------------------------------------------------
class Bestiary
{
	public:
		Bestiary();
		Bestiary(const Bestiary& other);
		~Bestiary();
		Bestiary&	operator=(const Bestiary& other);

	static Bestiary&	instance();

	/// Load your JSON lore file; return false on error
	bool	loadFromFile(const std::string& filename);

	/// Retrieve a lore page by enum ID
	const LorePage&	getLore(BestiaryID id) const;

	private:
		std::map<BestiaryID, LorePage>	_entries;
};
