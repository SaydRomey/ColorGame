

class Prismwalker
{
	public:
		std::string			name;
		std::vector<Color>	boundHues;
		Inventory			inventory;
		Stats				stats;
		PrismCore			core;
	
		void bindHue(Color hue);
		void activateHueAbility();
		void speak(const DialogueContext& context);
};

// Hue system

enum class HueType { Red, Green, Blue, Yellow, Purple, Brown };

class Color
{
	public:
    	HueType			type;
    	std::string		description;
    	PassiveEffect	passive;
    	ActiveSkill		active;
};

// Personality and dialogue

class DialogueOption
{
	public:
		std::string				text;
		HueType					affinityRequirement;
		std::function<void()>	effect;
};
	
class DialogueTree
{
	std::vector<DialogueOption>	options;
	void displayOptions(const Prismwalker& player);
};

// Region and biomes

class Region
{
	public:
		std::string			name;
		HueType				dominantHue;
		std::vector<NPC>	inhabitants;
		std::vector<Quest>	availableQuests;
		Terrain				terrain;
	};

// Combat system

class Skill
{
	public:
		std::string	name;
		HueType		hueType;
		int			damage;
		void execute(Target& enemy);
	};

// Artefact and item system

class Artifact
{
	public:
		std::string	name;
		HueType		hue;
		std::string	lore;
		void activate(Prismwalker& player);
	};

// NPC

// Base class NPC
class NPC
{
	public:
		std::string					name;
		HueType						hue;
		Region*						homeRegion;
		PersonalityType				personality;
		std::vector<DialogueLine>	dialogue;
		Artifact					signatureItem;
	
		virtual void	speak();
		virtual void	interact(Prismwalker& player);
		virtual void	onDefeat();
};

// Derived classes by personality or role

class CombatNPC : public NPC
{
	public:
		Skill	combatStyle;
		void	attack(Prismwalker& player);
};
	
class MerchantNPC : public NPC
{
	public:
		std::vector<Item>	wares;
		void	trade(Prismwalker& player);
};
	
class QuestGiverNPC : public NPC
{
	public:
		std::vector<Quest>	quests;
		void	offerQuest(Prismwalker& player);
};

// Sample implementation of AmaranthTheUndying
class AmaranthTheUndying : public CombatNPC
{
	public:
		AmaranthTheUndying()
		{
			name = "Amaranth the Undying";
			hue = HueType::Red;
			personality = PersonalityType::Martyr;
			signatureItem = Artifact("Amaranth Rose", HueType::Red);
			dialogue = {
				{"Rebirth is a mercy. I've done it too many times."},
				{"The bloom is beautiful... just before it drinks."}
			};
			combatStyle = Skill("Crimson Bloom Strike", HueType::Red, 50);
		}
	
		void onDefeat() override
		{
			std::cout << name << " falls... but the rose remains upright.\n";
			// Perhaps triggers a resurrection mechanic or artifact event
		}
	};

// Dialogue system

struct DialogueLine
{
    std::string	text;
    HueType		emotionalTone;
};

void NPC::speak()
{
    for (const auto& line : dialogue)
	{
        std::cout << name << " says: " << line.text << "\n";
    }
}

// Hue-based behavior example

// NPCs react to Prismwalker’s bound hue
void NPC::interact(Prismwalker& player)
{
    if (player.hasBoundHue(HueType::Red) && hue == HueType::Blue)
	{
        std::cout << name << " narrows their eyes at your fiery aura.\n";
    }
}

