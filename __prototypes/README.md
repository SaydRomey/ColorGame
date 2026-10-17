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

Download the HTML file and open it in Chrome, Firefox, or Edge. No installation, server, dependencies, or game engine required.

This is a functional browser-based design prototype, not yet a Unity or Godot implementation. The mechanics use placeholder values where your design documents haven't finalized them.

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

This is a standalone browser-based design prototype, not a game-engine implementation. **All NPC encounters and newly written dialogue are examples, not confirmed canon.** Affinity thresholds are also provisional: the design documents specify `X₁`, `X₂`, and `X₃` without final numeric values. The simulator uses example values of 25, 50, and 75 on a 0–100 scale and an experimental rule for blended personalities.

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

The explorer is a browser-based **encounter-design reference and test tool**, not an in-engine combat simulation. Its enemy descriptions and tags are derived from the uploaded bestiary draft. **Undocumented hue interactions remain unspecified** rather than being assigned invented resistances or weaknesses. Numeric combat assumptions are hypothetical.

---

<!-- Links -->

[hud-prototype-html]: ./prototypes/prismwalker_hud_prototype.html
[hud-prototype-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_hud_prototype.html
[personality-prototype-html]: ./prototypes/prismwalker_personality_simulator.html
[personality-prototype-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_personality_simulator.html
[bestiary-prototype-html]: ./prototypes/prismwalker_bestiary_explorer.html
[bestiary-prototype-launch]: https://saydromey.github.io/ColorGame/__prototypes/prototypes/prismwalker_bestiary_explorer.html
