// HueAffinity.cpp

#include "HueAffinity.hpp"
#include <climits>			// INT_MAX
#include <string>

// Define XP thresholds for INITIATE, ADEPT, EXPERT, MASTER
const int	HueAffinity::XP_THRESHOLD[HueAffinity::TIER_COUNT] = {
	0,     // INITIATE
	1000,  // ADEPT
	5000,  // EXPERT
	20000  // MASTER
};

bool	HueAffinity::isValidHue(Hue h) {return (h >= VERDANT && h < HUE_COUNT);}

HueAffinity::Tier	HueAffinity::deriveTierFromXp(int xp)
{
	Tier	t = INITIATE;

	if (xp < 0)
		return (INITIATE);

	while (t < MASTER && xp >= XP_THRESHOLD[t + 1])
		t = static_cast<Tier>(t + 1);

	return (t);
}

// ────────────────────────────────────────────────────────────────────────────────

HueAffinity::HueAffinity(void)
{
	int	i = 0;
	while (i < HUE_COUNT)
	{
		_xp[i] = 0;
		_tier[i] = INITIATE;
		++i;
	}
}

HueAffinity::HueAffinity(const HueAffinity& other)
{
	int	i = 0;
	while (i < HUE_COUNT)
	{
		_xp[i] = other._xp[i];
		_tier[i] = other._tier[i];
		++i;
	}
}

HueAffinity&	HueAffinity::operator=(const HueAffinity& other)
{
	int	i = 0;
	if (this != &other)
	{
		while (i < HUE_COUNT)
		{
			_xp[i] = other._xp[i];
			_tier[i] = other._tier[i];
			++i;
		}
	}
	return (*this);
}

HueAffinity::~HueAffinity(void) {}

// ────────────────────────────────────────────────────────────────────────────────

void	HueAffinity::addXp(Hue h, int amount)
{
	if(!isValidHue(h) || amount <= 0)
		return ;

	if (_xp[h] > INT_MAX - amount)
		_xp[h] = INT_MAX;
	else
		_xp[h] += amount;

	_tier[h] = deriveTierFromXp(_xp[h]);
}

int	HueAffinity::getXp(Hue h) const
{
	if (!isValidHue(h))
		return (0);
	return (_xp[h]);
}

HueAffinity::Tier	HueAffinity::getTier(Hue h) const
{
	if (!isValidHue(h))
		return (INITIATE);
	return (_tier[h]);
}

bool	HueAffinity::meetsTier(Hue h, Tier required) const
{
	if (!isValidHue(h) || required < INITIATE || required >= TIER_COUNT)
		return (false);
	return (_tier[h] >= required);
}

// ────────────────────────────────────────────────────────────────────────────────

bool	HueAffinity::save(std::ostream& out) const
{
	out << "HUEAFFINITY_V1\n";
	if (!out)
		return (false);

	int	h = 0;
	while (h < HUE_COUNT)
	{
		// Human-readable: save derived tier from XP (keeps file consistent)
		Tier t = deriveTierFromXp(_xp[h]);
		out << _xp[h] << ' ' << static_cast<int>(t) << "\n";
		// out << _xp[h] << "\n";
		if (!out)
			return (false);
		++h;
	}
	return (true);
}

bool	HueAffinity::load(std::istream& in)
{
	std::string header;

	if (!(in >> header))
		return (false);
	if (header != "HUEAFFINITY_V1")
		return (false);

	int	h = 0;
	while (h < HUE_COUNT)
	{
		int	xp = 0;
		int tierInt = 0;

		if (!(in >> xp >> tierInt))
			return (false);
		if (xp < 0)
			return (false);

		_xp[h] = xp;

		// ignore tierInt, always derive from XP
		_tier[h] = deriveTierFromXp(xp);

		// // Optional STRICT debug check (off by default)
		// // If we want it later, compile with -DHUEAFFINITY_STRICT_SAVE
		// #ifdef HUEAFFINITY_STRICT_SAVE
		// if (tierInt != static_cast<int>(_tier[h]))
		// 	return (false);
		// #else
		// (void)tierInt;
		// #endif

		++h;
	}

	// Reject trailing non-whitespace garbage (optional)
	// If we want to allow concatenated chunks in a bigger save file, remove this.
	// (optional; remove if integrating into a bigger save blob)
	std::string extra;
	if (in >> extra)
		return (false);

	return (true);
}

// #include <sstream>
// #include <string>

// bool HueAffinity::save(std::ostream& out) const
// {
// 	out << "HUEAFFINITY_V1\n";
// 	if (!out)
// 		return (false);

// 	for (int h = 0; h < HUE_COUNT; ++h)
// 	{
// 		out << _xp[h] << ' ' << static_cast<int>(_tier[h]) << '\n';
// 		if (!out)
// 			return (false);
// 	}
// 	return (true);
// }

// /*
// // corruption detection (after we derive _tier[h] from _xp[h])
// int derivedTierInt = static_cast<int>(_tier[h]);
// if (tierInt != derivedTierInt)
// 	return (false);
// */
// bool HueAffinity::load(std::istream& in)
// {
// 	// Read first token: either header or first xp
// 	std::string first;
// 	if (!(in >> first))
// 		return (false);

// 	bool hasHeader = (first == "HUEAFFINITY_V1");

// 	int startHue = 0;
// 	int firstXp = 0;
// 	int firstTierInt = 0;

// 	if (!hasHeader)
// 	{
// 		// Legacy format: first token was xp
// 		std::istringstream iss(first);
// 		if (!(iss >> firstXp))
// 			return (false);

// 		if (!(in >> firstTierInt))
// 			return (false);

// 		if (firstXp < 0 || !isValidTierInt(firstTierInt))
// 			return (false);

// 		_xp[0] = firstXp;
// 		_tier[0] = INITIATE;
// 		while (_tier[0] < MASTER && _xp[0] >= XP_THRESHOLD[_tier[0] + 1])
// 			_tier[0] = static_cast<Tier>(_tier[0] + 1);

// 		startHue = 1;
// 	}

// 	for (int h = startHue; h < HUE_COUNT; ++h)
// 	{
// 		int xp = 0;
// 		int tierInt = 0;

// 		in >> xp >> tierInt;
// 		if (!in)
// 			return (false);

// 		if (xp < 0 || !isValidTierInt(tierInt))
// 			return (false);

// 		_xp[h] = xp;
// 		_tier[h] = INITIATE;
// 		while (_tier[h] < MASTER && _xp[h] >= XP_THRESHOLD[_tier[h] + 1])
// 			_tier[h] = static_cast<Tier>(_tier[h] + 1);
// 	}

// 	return (true);
// }


/*
// usage example:

#include <fstream>

// … somewhere in our save routine …
HueAffinity	affinities;
// (player has built some XP…)
std::ofstream	file("save.txt");
if(!affinities.save(file))
{
	// handle error
}

// … somewhere in your load routine …
HueAffinity	loaded;
std::ifstream	in("save.txt");
if(!loaded.load(in))
{
	// handle corrupt/missing data
}
*/
