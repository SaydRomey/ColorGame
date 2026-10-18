# Prototypes

---

## [Prismwalker — Diegetic HUD Prototype][hud-prototype-html]

- [Launch the HUD prototype][hud-prototype-launch]

### What's included

- **Cracked health prism:** Damage increases visible fractures; critical health triggers flickering.
- **Three bound hue slots:** Switch between active hues and experiment with all six.
- **Segmented Mneme bar:** Cast abilities to consume charges and refill at a shrine.
- **Nullshade mode:** Simulates desaturation, distortion, and HUD instability.
- **Minimal / Ornate modes:** Compare interface treatments.
- **Keyboard controls:** Keys `1–3` switch hues; `Space` casts.

### How to run it

Download the HTML file and open it in Chrome, Firefox, or Edge.  
No installation, server, dependencies, or game engine required.

This is a functional browser-based design prototype, not yet a Unity or Godot implementation.  
The mechanics use placeholder values where your design documents haven't finalized them.

---

## [Prismwalker — Personality & Dialogue Simulator][personality-prototype-html]

- [Launch the Personality & Dialogue Simulator][personality-prototype-launch]

### What's included

- **Six affinity sliders:** Adjust Verdant, Crimson, Cobalt, Violet, Aurelian, and Earthen alignment independently.
- **Dominant and blended personality:** Preview the Prismwalker's personality profile based on the strongest hues.
- **Four affinity tiers:** Initiate, Adept, Expert, and EXPERT, with editable example thresholds.
- **NPC dialogue variations:** Test illustrative encounters in Huevale, Vireya, and Myrrala.
- **Affinity-locked dialogue:** Preview available and locked dialogue choices as affinity changes.
- **Preset builds and dialogue log:** Experiment with contrasting profiles and copy a session's dialogue.

### How to run it

Download the HTML file and open it in Chrome, Firefox, or Edge. No installation, server, dependencies, or game engine required.

This is a standalone browser-based design prototype, not a game-engine implementation.  
**All NPC encounters and newly written dialogue are examples, not confirmed canon.**  
Affinity thresholds are also provisional: the design documents specify `X₁`, `X₂`, and `X₃` without final numeric values.  
The simulator uses example values of 25, 50, and 75 on a 0–100 scale and an experimental rule for blended personalities.

---

## [Prismwalker — Bestiary & Encounter Design Explorer][bestiary-prototype-html]

- [Launch the Bestiary & Encounter Design Explorer][bestiary-prototype-launch]

### What's included

- **Searchable bestiary:** Browse 83 enemy entries extracted from `bestiary-draft.pdf`.
- **Regional filters:** Explore Huevale, Vireya, Iriseld, Myrrala, Luxeran, Auralith, Nullshade, and Unbound creatures.
- **Archetype and encounter tags:** Filter by the documented tags, including `DRAINER`, `ILLUSIONIST`, `CONSTRUCT`, `REVENANT`, `TRAPPER`, `REFLECTION`, and `META`.
- **Enemy detail panels:** View each entry's documented role, visual identity, behavior, counterplay, and notes.
- **Artifact references:** Review artifact/tool names identified in enemy counterplay and notes; references are not proof of a universal interaction.
- **Hue-versus-enemy tester:** Inspect explicitly documented interactions, enemy-specific counters, and general hue countermeasure guidance while distinguishing unspecified interactions.
- **Hypothetical combat balancer:** Experiment with example enemy HP and player DPS. These values are **non-canonical** and should not be interpreted as design specifications.

### How to run it

Download the HTML file and open it in Chrome, Firefox, or Edge. No installation, server, dependencies, or game engine required.

The explorer is a browser-based **encounter-design reference and test tool**, not an in-engine combat simulation.  
Its enemy descriptions and tags are derived from the uploaded bestiary draft.  
**Undocumented hue interactions remain unspecified** rather than being assigned invented resistances or weaknesses.  
Numeric combat assumptions are hypothetical.

---

## [Prismwalker — Regional Mechanics Lab][regional-lab-html]

- [Launch Prismwalker — Regional Mechanics Lab][regional-lab-launch]

### What's included

- **Seven regional room experiments:** Huevale, Vireya, Iriseld, Myrrala, Luxeran, Auralith, and Nullshade.
- **World-law demonstrations:** Simulate each region's environmental or metaphysical rule using clickable actions and changing room states.
- **Source versus proposal labels:** Distinguish established regional principles from example puzzle interactions.
- **Session tools:** Room resets, interaction history, and JSON export.

### How to run it

Open `prismwalker_regional_mechanics_sandbox.html` in a modern browser. 

This is a simplified room-state mechanics lab, not an in-engine level. 

Interactive outcomes labeled proposed are non-canonical.

---

## [Prismwalker — Hue Affinity Balancing Lab][affinity-lab-html]

- [Launch Prismwalker — Hue Affinity Balancing Lab][affinity-lab-launch]

### What's included

- **Six XP curves:** Crimson, Cobalt, Verdant, Aurelian, Violet, and Earthen.
- **Editable tier thresholds:** Initiate, Adept, Expert, and EXPERT progression through configurable `X₁`, `X₂`, and `X₃`.
- **Five XP sources:** Ability usage, time bound, region exposure, lore discovery, and item interactions.
- **Pacing tools:** Adjustable campaign playtime, example playstyle distributions, milestone table, and point-in-time tier inspection.
- **Export:** Save modeled progression assumptions and curves as JSON.

### How to run it

Open `prismwalker_hue_affinity_balancing_lab.html` in a modern browser. 

**All numeric XP thresholds, XP rates, playstyle distributions, and linear accumulation curves are hypothetical.** 

The source specifies XP categories and unlock classes, not final numerical balance.

---

## [Prismwalker — Hue Binding & Combat Sandbox][combat-lab-html]

- [Launch Prismwalker — Hue Binding & Combat Sandbox][combat-lab-launch]

### What's included

- **Three bound slots and six hues:** Change equipped hues at the shrine and switch the active hue in combat.
- **Shared 12-charge bar (WIP):** Three spell cost levels (1, 2, 3), proposed spell effects, and charging limitations.
- **Documented enemy reactions:** Selected bestiary and hue-binding interactions, with unspecified pairs clearly identified.
- **Combo experiment:** Test consecutive casts of different hues and a proposed numeric combo bonus.
- **Encounter loop and logs:** Example HP and damage, simulated enemy turns, reset, and JSON session export.

### How to run it

Open `prismwalker_hue_binding_combat_sandbox.html` in a modern browser. 

**Enemy HP, damage, combat turn loop, and combo bonus values are hypothetical;** 
this prototype is a mechanics test, not the finalized combat specification.

---

## [Prismwalker — Page-Turning Bestiary][bestiary-book-html]

[Launch the page-turning bestiary][bestiary-book-launch]

### What's included
- A two-page, animated field-journal layout with page-turn transitions.
- **83 creature entries** across Huevale, Vireya, Iriseld, Myrrala, Luxeran, Auralith, Nullshade, and Unbound.
- Original creature names, flavor quotes, and field observations drawn from `Bestiary_Index.docx`.
- Regional encounter themes drawn from `Bestiary_Reference.docx`.
- Region filters, full-text search, clickable creature index, bookmarks, page navigation, and keyboard controls.
- Decorative archive seals to reserve space for future creature illustrations. **These are not canonical creature art.**

### How to run it
Download the HTML file and open it in a modern browser.  
Use **← / →** to turn pages, **/** to search, and **B** to save a bookmark.  
The prototype works offline; 
the font falls back to local serif/sans-serif fonts without network access.

This is a browser-based reading prototype, not a game-engine UI.  
It preserves WIP gaps and carries no invented statistics.

---

<!-- Links -->
[hud-prototype-html]: ./prototypes/prismwalker_hud_prototype.html
[hud-prototype-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_hud_prototype.html
[personality-prototype-html]: ./prototypes/prismwalker_personality_simulator.html
[personality-prototype-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_personality_simulator.html
[bestiary-prototype-html]: ./prototypes/prismwalker_bestiary_explorer.html
[bestiary-prototype-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_bestiary_explorer.html
[regional-lab-html]: ./prototypes/prismwalker_regional_mechanics_sandbox.html
[regional-lab-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_regional_mechanics_sandbox.html
[affinity-lab-html]: ./prototypes/prismwalker_hue_affinity_balancing_lab.html
[affinity-lab-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_hue_affinity_balancing_lab.html
[combat-lab-html]: ./prototypes/prismwalker_hue_binding_combat_sandbox.html
[combat-lab-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_hue_binding_combat_sandbox.html
[bestiary-book-html]: ./prototypes/prismwalker_page_turning_bestiary.html
[bestiary-book-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_page_turning_bestiary.html
