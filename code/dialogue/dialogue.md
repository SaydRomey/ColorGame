
# Dialogue

## 🌿 Dialogue Tree

Like a **flowchart** of speech options:
```text
NPC: “You’re not from around here, are you?”

1) [Calm] “No, I just arrived.”      → (neutral response)
2) [Red]  “Back off. None of your business.” → (hostile response)
3) [Purple] “Does it matter?”        → (cryptic response)
```
Based on what the player chooses, 
or what hue(s) they're aligned with, the conversation shifts paths.

---

## Dialogue System : Basic Overview

<details><summary>C++ Model Example</summary>

### Dialogue Node
```cpp
struct DialogueOption {
    std::string playerLine;
    std::string npcResponse;
    HueType     requiredHue; // Optional: restrict choices based on color
    int         nextNodeId;
};
```

### Dialogue Tree
```cpp
class DialogueTree {
public:
    void addNode(int id, const std::vector<DialogueOption>& options);
    void startDialogue();

private:
    std::unordered_map<int, std::vector<DialogueOption>> nodes_;
    int currentNode_;
};
```
The `startDialogue()` function would present the options at `currentNode_`, 
let the player choose, then jump to the `nextNodeId`.  

</details>

---

## 🧠 Whith Prismwalker Mechanics

- Hue-based affinity could unlock or **restrict options**
- The **dominant** hue could **auto-choose a tone** if player skips
- NPCs might react more warmly or coldly depending on shared or opposing hues

---

## 🔮 Example in the game

**Wisteria Enchantress:**
> “You dream in color. But which one wakes you?”

1. 🌱 “Green. I trust what grows.” (Wisteria smiles gently)
2. 🔥 “Red. I strike before I think.” (Wisteria frowns)
3. 🌌 “Purple. I don’t wake at all.” (Wisteria leans closer)

---

## ➕ Possible Expansions

- Attach **stat changes**, **quest triggers**, or **world state shifts** to certain paths
- Add **conditions**: certain lines appear only if you have a hue or artifact
- Include **emotion tone markers** (e.g. [bold], [mysterious]) for immersive flavor

---

## Dialogue System: Scalable Architecture Overview

### Base C++ Classes
Split responsibilities into manageable systems:

🗂 `DialogueNode`
```cpp
struct	DialogueNode
{
  int	id;
  std::string npcLine;
  std::vector<std::string> playerChoices;
  std::vector<int> nextNodeIds;
  HueType requiredHue = HueType::None; // Optional gating
	bool endsConversation = false;
};
```

👤 `NPC`
```cpp
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
```

🧬 `Player`
```cpp
class Player
{
  public:
	HueType getDominantHue() const;
	void respondToDialogue(int choiceIndex);

	// Other stats: inventory, choices made, etc.
};
```

---

### Dynamic Dialogue Based on Hue
Within the `NPC::getGreeting()` or `interact()` function:

```cpp
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
```

---

### DialogueManager: Runtime Tree Navigation

```cpp
class DialogueManager
{
  public:
	void startDialogue(NPC &npc, Player &player);

  private:
	void displayNode(const DialogueNode &node, const Player &player);
	void handleChoice(int index, const DialogueNode &node);
};
```
This lets us walk the tree based on player choices, hue, 
and whether the player has unlocked special options.

---

## 📁 External Dialogue File Format (Optional)
We could Use JSON, XML, or YAML for each NPC's dialogue tree.  
That allows us to:
- Edit conversations without recompiling
- Store branching dialogue for each NPC in a `dialogues/npc_name.json`
- Include variables like:
  - Hue requirements
  - Quest states
  - Tone variations based on player's hue balance

Example JSON node:
```json
{
  "id": 1,
  "npcLine": "Gardens grow again, even over bones.",
  "playerChoices": [
    "Why did the garden fall?",
    "What lies beneath it?",
    "You speak like it still lives."
  ],
  "nextNodeIds": [2, 3, 4],
  "requiredHue": "Green"
}
```

## NPC Tiers (for scale)

| Type          | Dialogue Complexity                                   | Interactions                |
| ------------- | ----------------------------------------------------- | --------------------------- |
| 🟢 Major NPCs | Full tree, hue-based logic, item-giving, quest-gating | Combat, lore, world choices |
| 🟡 Town NPCs  | 1–3 lines, randomized, tone-based                     | Minor item hints or rumors  |
| 🟣 Vendors    | Greet + sale line + exit line; vary by hue or trust   | Prices, special offers      |
| 🔵 Echoes     | Single echo lines; memory-style interaction           | World-building only         |
