// npc_hue_system.cpp

/* TOCHECK

Making NPCs react to the player's current bound hue(s)
Changing dialogue outcomes based on color affinity
Integrating reputation or hostility systems by hue

*/

#include "npc_hue_system.hpp"

// ---- Utility: Convert HueType to string ----
std::string hueToString(HueType hue)
{
	switch (hue)
	{
		case HueType::Red: return "Red";
		case HueType::Green: return "Green";
		case HueType::Blue: return "Blue";
		case HueType::Yellow: return "Yellow";
		case HueType::Purple: return "Purple";
		case HueType::Brown: return "Brown";
		default: return "None";
	}
}

// ---- Base NPC Implementation ----
NPC::NPC(std::string name, HueType hue) : name(name), hue(hue) {}

void NPC::speak() {
    std::cout << name << " says:\n";
    for (const auto& line : dialogue) {
        std::cout << "  [" << hueToString(line.emotionalTone) << "] " << line.text << "\n";
    }
}

void NPC::speak()
{
	std::cout << name << " says:\n";
	for (const auto& line : dialogue)
	{
		std::cout << "  [" << hueToString(line.emotionalTone) << "] " << line.text << "\n";
	}
}

void NPC::interact()
{
	std::cout << name << " observes your aura...\n";
	std::cout << name << ": 'You walk with the weight of " << hueToString(hue) << ". I know that color well.'\n";
}

void NPC::onDefeat()
{
	std::cout << name << " has fallen.\n";
}

// ---- Combat NPC Implementation ----
CombatNPC::CombatNPC(std::string name, HueType hue, std::string style, int power)
	: NPC(name, hue), combatStyle(style), power(power) {}

void CombatNPC::attack()
{
	std::cout << name << " attacks with " << combatStyle << " dealing " << power << " damage!\n";
}

void CombatNPC::onDefeat()
{
	std::cout << name << " collapses, a shimmer of color fading.\n";
}

// ---- Merchant NPC Implementation ----
MerchantNPC::MerchantNPC(std::string name, HueType hue, std::vector<std::string> wares)
	: NPC(name, hue), wares(wares) {}

void MerchantNPC::trade()
{
	std::cout << name << " shows their wares:\n";
	for (const auto& item : wares)
	{
		std::cout << "  - " << item << "\n";
	}
}

// ---- Example NPC Definitions (by Hue Group) ----
CombatNPC	amaranth("Amaranth the Undying", HueType::Red, "Crimson Bloom Strike", 50);
MerchantNPC	celadon("Celadon Archivist", HueType::Green, {"Spell Shard", "Porcelain Rune"});
CombatNPC	tyrian("Tyrian Purge", HueType::Purple, "Imperial Echo Blade", 70);
MerchantNPC	citrine("Citrine Artisan", HueType::Yellow, {"Gem Lens", "Radiant Chime"});
CombatNPC	zaffre("Zaffre Glasswright", HueType::Blue, "Cobalt Shardstorm", 45);
MerchantNPC	mikado("Mikado Warlord", HueType::Brown, {"Lacquered Katana", "Tyrant’s Sigil"});
