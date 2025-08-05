
<div align="right">

[◄ Go back to Gameplay Mechanics Reference](../core-systems.md)

</div>

# 🎨 Hue-Binding System

Below is a high-level breakdown of the **Hue-Binding** system, 
how players pick up, manage and use "colors" in the world.  

> [Check Hue-Affinity Logic ►](./hue-affinity.md)

---

## What Is a Hue?

- **Hue** = an elemental/magical alignment (Green, Red, Blue, Purple, Yellow, Brown)

- Each Hue grants **passive** benefits (buffs, traversal tweaks) and **active** powers (spells/skills) that consume a shared resource ("Charge").

- Hues interact with **enemies**, **puzzles** and *terrain* in predictable ways - 
  some foes are drawn to, weakened by or immune to particular colors.

---

## Acquiring & Binding Hues

- **Finding a Hue Shard** in the world unlocks that color permanently.

- The player can **bind** up to **N** active Hues at once (e.g. 3-slot wheel).

- Binding is done at safe zones / shrines / menu - 
  swapping Hues *outside* of combat or puzzle sequences.

---

## Charges & Recharge

- All bound Hues draw from a **common "Hue Bar"** with **X** total charges.

- Using an active Hue ability deducts a certain number of charges.

- The bar refills via: resting at Hue shrines, picking up hue pick-ups, special relics or pausing in safe rooms.

- Some relics modify recharge behaviour (e.g. faster regen if you avoid damage, or slow drip while moving).

---

## Activating & Cycling

- **Quick-cast**: hold a Hue’s button for its basic ability (e.g. Crimson: burst of flame).

- **Charged**: tap + another input for a stronger effect (e.g. Crimson: conflagration orb).

- You can **cycle** between bound Hues on the fly, but only one aura/overlay is shown at a time.

- Visual/UI: each bound Hue has an overlay icon + charge-cost marker.

---

## Core Hues & Their Roles

| Hue                   | Role                  | Passive                               | Active Example                     | Nemesis Mechanics                                       |
| --------------------- | --------------------- | ------------------------------------- | ---------------------------------- | ------------------------------------------------------- |
| **Crimson** (Red)     | Offense & flame       | +Damage vs. flesh/constructs          | Fireburst, flame dash              | Empowers Searblood Cultists; immune to fire-based roots |
| **Cobalt** (Blue)     | Disruption & defense  | +Shield regen; reduced cooldowns      | Mind Echo pulse; Static Dash       | Drains Stormwrit Hounds’ charge; reveals illusions      |
| **Verdant** (Green)   | Control & traversal   | +Movement speed in foliage            | Skygrowth Seed; vine snare         | Pacifies Sapborn Stalkers; roots Feathered Null         |
| **Golden** (Yellow)   | Light & utility       | +Ambient light regen; waypoint reveal | Radiant Echo flash; blinding flare | Powers Sunflare Marionettes; shatters glass constructs  |
| **Violet** (Purple)   | Illusion & mind-magic | +Illusion strength; stealth boost     | Glamour Pulse; Illusion Clone      | Counters Doppelshade, Tapestry Watchers                 |
| **Brown** (Earth)     | Memory & Echo-magic   | +Passive memory regen; lore detect    | Earthen Echo; Decay Grasp          | Stuns Memory Leeches; anchors Wound Remnants            |

> *"Nemesis Mechanics"* shows which creatures heavily react to that Hue.

---

## Inter-Hue Synergies & Counters

- **Combo**: casting two different Hues in quick succession triggers a small bonus (e.g. Crimson→Cobalt = ember-shard stun).

- **Counter-casting**: using a Hue that your enemy is weak to deals bonus damage or interrupts its special behavior.

- **Conflict**: casting a Hue the mob "feeds on" (e.g. Verdant vs. Bloomrot Titan) empowers the foe.

---

## Environmental & Puzzle Integration

- Certain shrines or puzzles **only** respond to a given Hue (e.g. a Verdant seed to grow a path, or a Violet pulse to reveal hidden glyphs).

- World zones can have **Aura Fields** - 
  e.g. Feathered Null zone suppresses all Hue flight abilities; 
  Shatterglass Choir field drains color on a timer.

- Binding/unbinding Hues at special pedestals can **toggle** parts of the map, open doors or reset traps.

---

## NPC & Bestiary Reactions

- Friendly NPCs may grant **side-quests** to unlock new Hue powers or upgrades 
  (e.g. a Thulian Mage who deepens your Violet ability).

- Beasts and constructs each have **tags** based on which Hues they’re drawn to, repelled by or require to be unmasked ([see "Nemesis Mechanics" above]()).

- Some world events (e.g. solar eclipses, mist cycles) temporarily alter Hue behavior - 
  enemies shift weaknesses or aura fields invert.

---

## Next Steps (TODO)

- Decide on **how many Hues** a player can bind at once and how large the central Hue Bar is.

- Flesh out **combo rules** 
  (e.g. Crimson→Verdant synergy, Cobalt→Violet feedback loops).

- Map out each major zone’s **aura fields** and which puzzles/NPCs require Hue interaction.

---
