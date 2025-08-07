// prismwalker.cpp

#include "prismwalker.hpp"
#include <iostream>
#include <algorithm> //?

// Default constructor
Prismwalker::Prismwalker()
	: name_("Unnamed"), maxBoundHues_(3), prismaticUnlocked_(false) {}

// Copy constructor
Prismwalker::Prismwalker(const Prismwalker& other)
	: name_(other.name_),
	  boundHues_(other.boundHues_),
	  hueAbilities_(other.hueAbilities_),
	  artifacts_(other.artifacts_),
	  maxBoundHues_(other.maxBoundHues_),
	  prismaticUnlocked_(other.prismaticUnlocked_) {}

// Assignment operator
Prismwalker& Prismwalker::operator=(const Prismwalker& other)
{
	if (this != &other)
	{
		name_ = other.name_;
		boundHues_ = other.boundHues_;
		hueAbilities_ = other.hueAbilities_;
		artifacts_ = other.artifacts_;
		maxBoundHues_ = other.maxBoundHues_;
		prismaticUnlocked_ = other.prismaticUnlocked_;
	}
	return (*this);
}

// Destructor
Prismwalker::~Prismwalker() {}

// 

// Mechanics
void Prismwalker::bindHue(const HueType& hue) {
    if (boundHues_.size() >= maxBoundHues_) {
        std::cout << "Maximum hues bound.\n";
        return;
    }
    if (!hasBoundHue(hue)) {
        boundHues_.push_back(hue);
        hueAbilities_[hue] = Skill(hue);  // Assume Skill has a constructor by hue
        std::cout << "Bound hue: " << static_cast<int>(hue) << "\n";
    }

    if (boundHues_.size() == 6 && !prismaticUnlocked_) {
        unlockPrismaticBurst();
    }
}

void Prismwalker::unbindHue(const HueType& hue) {
    boundHues_.erase(
        std::remove(boundHues_.begin(), boundHues_.end(), hue),
        boundHues_.end()
    );
    hueAbilities_.erase(hue);
}

bool Prismwalker::hasBoundHue(HueType hue) const {
    return std::find(boundHues_.begin(), boundHues_.end(), hue) != boundHues_.end();
}


void Prismwalker::activateHueAbility() {
    for (const auto& hue : boundHues_) {
        std::cout << "Activating ability: ";
        hueAbilities_[hue].activate();
    }
}

void Prismwalker::useUltimate() {
    if (prismaticUnlocked_) {
        std::cout << "Releasing Prismatic Burst!\n";
        // Insert ultimate effect logic here
    } else {
        std::cout << "Prismatic Burst not unlocked yet.\n";
    }
}


void Prismwalker::speakDialogue() {
    for (auto hue : boundHues_) {
        switch (hue) {
            case HueType::Red: std::cout << "[Bold tone] Let's act now.\n"; break;
            case HueType::Green: std::cout << "[Calm tone] Everything grows in time.\n"; break;
            case HueType::Blue: std::cout << "[Logical tone] Consider the consequences.\n"; break;
            case HueType::Purple: std::cout << "[Mysterious tone] I feel... echoes.\n"; break;
            case HueType::Yellow: std::cout << "[Witty tone] Light always finds a crack.\n"; break;
            case HueType::Brown: std::cout << "[Grim tone] The earth takes all.\n"; break;
        }
    }
}

void Prismwalker::absorbArtifact(const Artifact& artifact) {
    artifacts_.push_back(artifact);
    std::cout << "Absorbed artifact: " << artifact.getName() << "\n";
}

void Prismwalker::displayStatus() const {
    std::cout << "Current Hues:\n";
    for (const auto& hue : boundHues_) {
        std::cout << "- " << static_cast<int>(hue) << "\n";
    }
}

void Prismwalker::unlockPrismaticBurst() {
    prismaticUnlocked_ = true;
    std::cout << "Prismatic Burst Unlocked!\n";
}

// ?

void	Prismwalker::swapHue(HueType oldHue, HueType newHue)
{
	auto	it = std::find(boundHues.begin(), boundHues.end(), oldHue);
	if (it != boundHues.end())
	{
		*it = newHue;
		std::cout << "Swapped " << hueToString(oldHue) << " with " << hueToString(newHue) << "\n";
	}
}

void	Prismwalker::displayHueState() const
{
	std::cout << "Current bound hues: ";
	for (auto hue : boundHues)
	{
		std::cout << hueToString(hue) << " ";
	}
	std::cout << "\n";
}

void	Prismwalker::usePassiveEffects()
{
	std::cout << name << " gains passive effects from hues.\n";
}

void	Prismwalker::activateHueAbility(HueType hue)
{
	std::cout << name << " activates " << hueToString(hue) << " ability!\n";
	stamina -= 10;
}

void	Prismwalker::prismaticBurst()
{
	if (boundHues.size() == 6)
	{
		std::cout << name << " unleashes a PRISMATIC BURST!\n";
		stamina = 0;
	}
	else
	{
		std::cout << "Not enough hues bound to unleash burst.\n";
	}
}

void	Prismwalker::takeDamage(int amount)
{
	health -= amount;
	std::cout << name << " takes " << amount << " damage! Health now at " << health << ".\n";
}

void	Prismwalker::heal(int amount)
{
	health += amount;
	std::cout << name << " heals " << amount << ". Health now at " << health << ".\n";
}

void	Prismwalker::speakTo(NPC& npc)
{
	std::cout << name << " approaches " << npc.name << ".\n";
	npc.interact();
	npc.speak();
}

std::string	Prismwalker::getName() const { return name; }
int	Prismwalker::getHealth() const { return health; }
std::vector<HueType>	Prismwalker::getBoundHues() const { return boundHues; }
