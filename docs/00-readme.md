

# Restructuring
> Changing to a more conventional folder taxonomy so i can scale without losing my mind...

## TODO:
- understand and use frontmatters
- write a **Terminology** doc that defines: 
  Hue, Region, Order, Mneme, Memory Echo, Prism Gate, Shard, Affinity Tier naming, etc.
- Lock the **Hue key names** (`CRIMSON/COBALT/VERDANT/VIOLET/AURELIAN/EARTHEN`) 
  and use then everywhere (docs + code).
- 

```
```

---

## the layout

```perl
docs/
├ 00-readme.md                      # how to navigate these docs
├ 01-design/                        # GDD + gameplay rules
│  ├ gdd.md                         # from gdd-draft.md (polish/keep)
│  ├ pillars.md                     # the high-level vision (optional)
│  └ systems/                       # "how it plays"
│     ├ overview.md                 # from core-systems.md
│     ├ hue-affinity.md             # (move from gameplay/)
│     ├ hue-binding.md              # (move from gameplay/)
│     ├ personality-system.md
│     └ personality-system-notes.md # from personality-system-mixed.md
├ 02-content/                       # the “content bible”
│  ├ characters/
│  │  ├ player/
│  │  │  └ prismwalker.md      # merge main-character.md + prismwalker.md maybe
│  │  └ npcs/
│  │     ├ index.md            # from NPCs/npcs-overview.md
│  │     └ entries/
│  │        └ <npc-slug>.md
│  ├ bestiary/
│  │  ├ index.md               # from bestiary/bestiary.md or enemies.md (pick one)
│  │  └ entries/               # all creature pages live here
│  │     └ <beast-slug>.md           # move every file from docs/enemies/*.md here
│  ├ items/
│  │  ├ index.md               # from items.md
│  │  └ entries/
│  │     └ <item-slug>.md
│  └ artifacts/                # (optional, if i split items later)
│  │  └ entries/
│  │     └ <artifact-slug>.md
│  └ factions/                 # (optional)
├ 03-world/
│  ├ overview.md               # from world.md
│  ├ timeline.md
│  ├ myths-and-omens.md
│  └ regions/
│     ├ index.md
│     ├ auralith.md
│     ├ huevale.md
│     ├ iriseld.md
│     ├ luxeran.md
│     ├ myrrala.md
│     ├ nullshade.md
│     └ vireya.md
├ 04-narrative/
│  ├ scenes/
│  │  ├ endgame.md
│  │  ├ scene-ashes-remember.md
│  │  ├ scene-ashes-whisper.md
│  │  ├ scene-echoes.md
│  │  ├ scene-examples.md
│  │  ├ scene-greenwood.md
│  │  ├ scene-mirages.md
│  │  ├ scene-petals-lie.md
│  │  ├ scene-petals.md
│  │  ├ scene-skyglass.md
│  │  └ scene-the-song.md
│  └ structure.md              # (optional: acts/beats overview)
├ 05-ux/
│  ├ ui.md
│  ├ ui-crystal-shard.md
│  ├ ui-pixel-art.md
│  └ wireframe.md
├ 06-art/
│  ├ art-bible.md              # create: moodboard, palette rules, rendering targets
│  ├ palette.md                # if colors.md is about art palette, maybe move it here
│  ├ in-game-visuals.md
│  └ asset-style-guide.md      # from assets/textual-tools.md
├ 07-audio/                    # (placeholder)
│  └ audio-bible.md
├ 08-engineering/
│  ├ data-pipeline.md          # how JSON ↔ Godot ↔ docs connect
│  ├ schemas/                  # (later: bestiary.schema.json)
│  └ tooling.md                # notes on Makefile, scripts, etc.
├ 09-production/
│  ├ roadmap.md
│  ├ backlog.md
│  ├ changelog.md
│  └ playtest-notes.md
└ _shared/
   ├ templates/
   │  ├ bestiary-entry.md
   │  └ scene.md
   ├ media/                    # optional: doc-only figures
   └ meta/                     # canon policy, naming, term glossary, cross-cutting lists..
      ├ glossary.md
      ├ tags.md
      └ naming-conventions.md
```

> [!WARNING]  
> Keep the art and sprites where they already live at repo root; 
> link to them from docs via relative paths. 
> Don’t duplicate assets inside docs/.

---

## Minimal front-matter (to auto-index later)

```yaml
---
id: BEAST_BOGLIGHT_MIMIC          # or a slug like "boglight-mimic" for non-data pages
type: beast                       # beast | item | npc | region | scene | system | doc
title: Boglight Mimic
status: draft                     # draft | review | approved | cut
owner: sayd
tags: [region:huevale, hue:chartreuse, tier:2, family:mimic]
links:
  json: ../../game/data/bestiary/BEAST_BOGLIGHT_MIMIC.json
  sprite: ../../assets/sprites/enemies/huevale/boglight-mimic.png
  concept: ../../assets/npc-sketches/huevale/chartreuse.png
  header: ../../code/bestiary/inc/enemies/BoglightMimic.hpp
updated: 2025-08-27
---
```

---

## Sections to maybe standardize for beasts:
- **Fantasy** (one-paragraph elevator pitch)
- **Behavior** (AI hooks, encounter notes)
- **Abilities** (cooldowns, ranges, damage types)
- **Stats** (link to JSON; keep numbers in JSON, not here)
- **Lore** (1–3 short beats + drops)
- **Placement & Tuning** (where, why, difficulty notes)
- **Assets** (inline image links)

---

## Conventions that keep things tidy
- **kebab-case** filenames; one thing per file.
- **one canonical index per folder** (`index.md`) with a short TL;DR and auto-generated tables (see below).
- single source of truth for numbers: JSON in `game/data/bestiary/*.json` (already true!); docs reference with `links.json`.
- keep “notes/mixed” pages (like `personality-system-mixed.md`) but suffix with `-notes.md` so they never masquerade as specs.

---

## quick win: auto-generate indexes (no site generator required)
Add a tiny script later that reads YAML front-matter and builds tables.

With my Makefile setup, a target like:
```bash
make docs:index
```
…can scan `docs/02-content/bestiary/entries/*.md` 
and update `docs/02-content/bestiary/index.md` with a table grouped by `tags.region` and `tags.tier`.

## optional buckets to maybe add over time
- **08-engineering/schemas/** — JSON schemas for `BEAST_*.json`
- **09-production/** — roadmap, playtest notes, checklists
- **_shared/templates/** — drop a template for “bestiary entry” and “scene”

---

## Enemy/NPC metadata
Add a tiny font-matter block to each file so cross-refs are trivial:
```yaml
---
slug: enemies/abyssal-current
region: Iriseld
hues: [Blue]
type: Elemental
level_range: 8–12
inflicts: [Memory Drain, Slow]
counters: [Zaffre Vial, Mind Echo]
loot: [Stormglass Scale]
ui_effects: [HUD Distortion]
quests: [The Azure Tithes]
---
```

---