#include "dialogue_system.hpp"
#include <iostream>

Player::Player(HueType dominantHue) : dominantHue_(dominantHue) {}

HueType Player::getDominantHue() const { return (dominantHue_); }

NPC::NPC(std::string name, HueType hue, std::vector<DialogueNode> dialogueTree)
	: name_(std::move(name)), hue_(hue), dialogueTree_(std::move(dialogueTree))
{
}

std::string NPC::getGreeting(HueType playerHue) const
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

void NPC::interact(Player &player)
{
	DialogueManager	manager;

	manager.startDialogue(*this, player);
}

void DialogueManager::startDialogue(NPC &npc, Player &player)
{
	std::cout << npc.getGreeting(player.getDominantHue()) << "\n\n";
	if (npc.dialogueTree_.empty())
		return ;
	displayNode(npc.dialogueTree_[0], player);
}

void DialogueManager::displayNode(const DialogueNode &node,
		const Player &player)
{
	int	choice;
	int	nextId;

	if (node.requiredHue != HueType::None
		&& node.requiredHue != player.getDominantHue())
	{
		std::cout << "[You sense this conversation is closed to your hue.]" << std::endl;
		return ;
	}
	std::cout << "NPC: " << node.npcLine << "\n";
	for (size_t i = 0; i < node.playerChoices.size(); ++i)
	{
		std::cout << i + 1 << ". " << node.playerChoices[i] << "\n";
	}
	if (node.endsConversation)
	{
		std::cout << "[The conversation ends.]" << std::endl;
		return ;
	}
	std::cout << "Choose: ";
	std::cin >> choice;
	if (choice > 0 && choice <= static_cast<int>(node.nextNodeIds.size()))
	{
		nextId = node.nextNodeIds[choice - 1];
		displayNode({nextId, "Placeholder follow-up line", {}, {},
				HueType::None, true}, player); // Simplified
	}
	else
	{
		std::cout << "[Invalid choice]" << std::endl;
	}
}
