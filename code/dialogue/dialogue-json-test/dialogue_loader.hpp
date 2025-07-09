
#pragma once
#include <map>
#include <string>
#include <vector>

struct	DialogueChoice
{
	std::string prompt;
	std::string response;
	std::string next; // For future branching
};

struct	DialogueTree
{
	std::string greeting;
	std::vector<DialogueChoice> choices;
};

class NPCDialogue
{
  public:
	std::string name;
	std::string hue;
	DialogueTree tree;

	void displayDialogue() const;
};

class DialogueLoader
{
  public:
	static std::vector<NPCDialogue> loadFromJSON(const std::string &filepath);
};
