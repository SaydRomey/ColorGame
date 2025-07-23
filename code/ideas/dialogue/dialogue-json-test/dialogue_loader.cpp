
#include "dialogue_loader.hpp"
#include <fstream>
#include <iostream>
// #include <nlohmann/json.hpp> // https://github.com/nlohmann/json
#include "json.hpp"

using	json = nlohmann::json;

void NPCDialogue::displayDialogue() const
{
	std::cout << name << " (" << hue << "): " << tree.greeting << "\n\n";
	for (size_t i = 0; i < tree.choices.size(); ++i)
	{
		std::cout << i + 1 << ". " << tree.choices[i].prompt << "\n";
	}

	int	choice;
	std::cout << "\nChoose an option: ";
	std::cin >> choice;

	if (choice > 0 && choice <= tree.choices.size())
	{
		std::cout << "\n" << name << ": " << tree.choices[choice - 1].response << "\n";
	}
	else
	{
		std::cout << "Invalid choice.\n";
	}
}

std::vector<NPCDialogue> DialogueLoader::loadFromJSON(const std::string &filepath)
{
	json			data;
	NPCDialogue		npc;
	DialogueChoice	choice;

	std::ifstream file(filepath);
	if (!file)
	{
		std::cerr << "Failed to open JSON file: " << filepath << "\n";
		return ({});
	}
	file >> data;
	std::vector<NPCDialogue> npcs;
	for (const auto &entry : data["npcs"])
	{
		npc.name = entry["name"];
		npc.hue = entry["hue"];
		npc.tree.greeting = entry["dialogue_tree"]["greeting"];
		for (const auto &c : entry["dialogue_tree"]["choices"])
		{
			choice.prompt = c["prompt"];
			choice.response = c["response"];
			choice.next = c.value("next", "");
			npc.tree.choices.push_back(choice);
		}
		npcs.push_back(npc);
	}
	return (npcs);
}

// Usage example
/*
#include "dialogue_loader.hpp"

int	main(void)
{
	auto	npcs;

	npcs = DialogueLoader::loadFromJSON("npc_dialogue.json");
	if (!npcs.empty())
	{
		npcs[0].displayDialogue(); // Test with Viridian Alchemist
	}
	return (0);
}
*/
