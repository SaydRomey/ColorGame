#ifndef DIALOGUE_SYSTEM_HPP
# define DIALOGUE_SYSTEM_HPP

# include <string>
# include <unordered_map>
# include <vector>

enum class HueType
{
	None,
	Green,
	Red,
	Blue,
	Purple,
	Yellow,
	Brown
};

struct	DialogueNode
{
	int	id;
	std::string npcLine;
	std::vector<std::string> playerChoices;
	std::vector<int> nextNodeIds;
	HueType requiredHue = HueType::None;
	bool endsConversation = false;
};

class Player
{
  public:
	Player(HueType dominantHue);
	HueType getDominantHue() const;

  private:
	HueType dominantHue_;
};

class NPC
{
  public:
	NPC(std::string name, HueType hue, std::vector<DialogueNode> dialogueTree);

	void interact(Player &player);
	std::string getGreeting(HueType playerHue) const;

  private:
	std::string name_;
	HueType hue_;
	std::vector<DialogueNode> dialogueTree_;
};

class DialogueManager
{
  public:
	void startDialogue(NPC &npc, Player &player);

  private:
	void displayNode(const DialogueNode &node, const Player &player);
	void handleChoice(int index, const DialogueNode &node,
			const Player &player);
};

#endif // DIALOGUE_SYSTEM_HPP
