
#include "PrismCore.hpp"
#include <algorithm>
#include <iostream>

PrismCore::PrismCore() = default;
PrismCore::~PrismCore() = default;

bool	PrismCore::isHueBound(HueType type) const
{
	return (std::any_of(boundHues.begin(), boundHues.end(),
		[type](const Hue& h) { return (h.getType() == type); }));
}

bool	PrismCore::bindHue(const Hue& hue)
{
	if (isHueBound(hue.getType()))
	{
		return (false);
	}

	if (boundHues.size() < MAX_HUES)
	{
		boundHues.push_back(hue);
		return (true);
	}

	return (false);
}

void	PrismCore::replaceHue(int index, const Hue& newHue)
{
	if (index >= 0 && index < static_cast<int>(boundHues.size()))
	{
		boundHues[index] = newHue;
	}
}

void	PrismCore::unbindHue(HueType type)
{
	boundHues.erase(
		std::remove_if(boundHues.begin(), boundHues.end(),
			[type](const Hue& h) { return (h.getType() == type); }),
		boundHues.end());
}

const	std::vector<Hue>& PrismCore::getBoundHues() const
{
	return (boundHues);
}

std::string	PrismCore::describeState() const
{
	std::string result = "Bound Hues: ";
	for (const auto& hue : boundHues)
	{
		result += hue.getName() + " ";
	}
	return (result);
}
