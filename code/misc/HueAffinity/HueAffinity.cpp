// HueAffinity.cpp

#include "HueAffinity.hpp"
#include <cassert>

// Define XP thresholds for NOVICE, ADEPT, MASTER, LEGEND
const int	HueAffinity::XP_THRESHOLD[HueAffinity::TIER_COUNT] = {
	0,     // NOVICE
	1000,  // ADEPT
	5000,  // MASTER
	20000  // LEGEND
};

// ────────────────────────────────────────────────────────────────────────────────

HueAffinity::HueAffinity(void)
{
	int	i = 0;
	while (i < HUE_COUNT)
	{
		_xp[i] = 0;
		_tier[i] = NOVICE;
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
	if(h < 0 || h >= HUE_COUNT || amount <= 0)
		return ;

	_xp[h] += amount;

	// bump tier up as far as XP allows
	while (_tier[h] < LEGEND && _xp[h] >= XP_THRESHOLD[_tier[h] + 1])
	{
		_tier[h] = static_cast<Tier>(_tier[h] + 1);
	}
}

int	HueAffinity::getXp(Hue h) const
{
	if (h < 0 || h >= HUE_COUNT)
		return (0);
	return (_xp[h]);
}

HueAffinity::Tier	HueAffinity::getTier(Hue h) const
{
	if (h < 0 || h >= HUE_COUNT)
		return (NOVICE);
	return (_tier[h]);
}

bool	HueAffinity::meetsTier(Hue h, Tier required) const
{
	if (h < 0 || h >= HUE_COUNT || required < NOVICE || required >= TIER_COUNT)
		return (false);
	return (_tier[h] >= required);
}

// ────────────────────────────────────────────────────────────────────────────────

bool	HueAffinity::save(std::ostream& out) const
{
	// Simple format: one line per hue: “<xp> <tier>\n”
	int	h = 0;
	while (h < HUE_COUNT)
	{
		out << _xp[h] << ' ' << _tier[h] << '\n';
		if (!out)
			return (false);
		++h;
	}
	return (true);
}

bool	HueAffinity::load(std::istream& in)
{
	int	h = 0;
	while (h < HUE_COUNT)
	{
		int	xp, tierInt;

		in >> xp >> tierInt;
		if (!in)
			return (false);

		// Basic validation:
		assert(xp >= 0);
		assert(tierInt >= NOVICE && tierInt < TIER_COUNT);

		_xp[h] = xp;
		_tier[h] = static_cast<Tier>(tierInt);
		++h;
	}
	return (true);
}

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
