// HueTestUtils.cpp

#include "HueTestUtils.hpp"
#include <iostream>
#include <sstream>

const char*	hueName(HueAffinity::Hue h)
{
	switch (h)
	{
		case HueAffinity::VERDANT: return "VERDANT";
		case HueAffinity::CRIMSON: return "CRIMSON";
		case HueAffinity::COBALT:  return "COBALT";
		case HueAffinity::VIOLET:  return "VIOLET";
		case HueAffinity::GOLDEN:  return "GOLDEN";
		case HueAffinity::EARTHEN: return "EARTHEN";
		default: return "???";
	}
}

const char*	tierName(HueAffinity::Tier t)
{
	switch (t)
	{
		case HueAffinity::INITIATE: return "INITIATE";
		case HueAffinity::ADEPT:    return "ADEPT";
		case HueAffinity::EXPERT:   return "EXPERT";
		case HueAffinity::MASTER:   return "MASTER";
		default: return "???";
	}
}

void	dump(const HueAffinity& a, const char* label)
{
	std::cout << "\n== " << label << " ==\n";

	int	h = 0;
	while (h < HueAffinity::HUE_COUNT)
	{
		HueAffinity::Hue hue = static_cast<HueAffinity::Hue>(h);
		std::cout
			<< hueName(hue)
			<< " xp=" << a.getXp(hue)
			<< " tier=" << tierName(a.getTier(hue))
			<< "\n";
		++h;
	}
}

bool	equals(const HueAffinity& a, const HueAffinity& b)
{
	int	h = 0;

	while (h < HueAffinity::HUE_COUNT)
	{
		HueAffinity::Hue hue = static_cast<HueAffinity::Hue>(h);

		if (a.getXp(hue) != b.getXp(hue))
			return (false);
		if (a.getTier(hue) != b.getTier(hue))
			return (false);

		++h;
	}
	return (true);
}

int	fail(const char* msg)
{
	std::cout << "[FAIL] " << msg << "\n";
	return (1);
}

int	pass(const char* msg)
{
	std::cout << "[ OK ] " << msg << "\n";
	return (0);
}

bool	saveToString(const HueAffinity& a, std::string& out)
{
	std::ostringstream oss;

	if (!a.save(oss))
		return (false);

	out = oss.str();
	return (true);
}

bool	loadFromString(HueAffinity& a, const std::string& in)
{
	std::istringstream iss(in);
	return (a.load(iss));
}

static int	deriveTierIntFromXp(int xp)
{
	// Must match HueAffinity thresholds: 0, 1000, 5000, 20000
	if (xp >= 20000) return 3;
	if (xp >= 5000)  return 2;
	if (xp >= 1000)  return 1;
	return 0;
}

bool	validateSavedTierColumn(const std::string& saved)
{
	std::istringstream iss(saved);
	std::string header;

	if (!(iss >> header))
		return (false);
	if (header != "HUEAFFINITY_V1")
		return (false);

	int h = 0;
	while (h < HueAffinity::HUE_COUNT)
	{
		int xp = 0;
		int tierInt = 0;

		if (!(iss >> xp >> tierInt))
			return (false);
		if (xp < 0)
			return (false);

		if (tierInt != deriveTierIntFromXp(xp))
			return (false);

		++h;
	}
	return (true);
}
