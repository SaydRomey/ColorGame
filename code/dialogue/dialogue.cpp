
struct	DialogueNode
{
	int	id;
	std::string npcLine;
	std::vector<std::string> playerChoices;
	std::vector<int> nextNodeIds;
	HueType requiredHue = HueType::None; // Optional gating
	bool endsConversation = false;
};

// NPC
class NPC
{
  public:
	NPC(std::string name, HueType hue, std::vector<DialogueNode> dialogueTree);

	virtual void interact(Player &player);              // Triggers dialogue
	virtual std::string getGreeting(HueType playerHue); // Hue-dynamic lines

  protected:
	std::string name_;
	HueType hue_;
	std::vector<DialogueNode> dialogueTree_;
};

// Player
class Player
{
  public:
	HueType getDominantHue() const;
	void respondToDialogue(int choiceIndex);

	// Other stats: inventory, choices made, etc.
};

// Dynamic dialogue based on hue
std::string NPC::getGreeting(HueType playerHue)
{
	if (playerHue == hue_)
	{
		return ("Ah... I see you carry our color. Welcome, friend.");
	}
	else if (playerHue == HueType::None)
	{
		return ("A colorless one? Curious. Dangerous, maybe.");
	}
	else
	{
		return ("You shine in another hue. Let's hope you listen better than your kind.");
	}
}

// DialogueManager, runtime tree navigation
class DialogueManager
{
  public:
	void startDialogue(NPC &npc, Player &player);

  private:
	void displayNode(const DialogueNode &node, const Player &player);
	void handleChoice(int index, const DialogueNode &node);
};
