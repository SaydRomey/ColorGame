
# ColorGame — GDD v0.2 (Consolidated + Fixes)

A single, tidy pass that unifies terminology, resolves contradictions, and adds a small amount of concrete tuning so we can build a focused vertical slice. Everything here is designed to sit *on top* of your originals (kept as source/reference). Edits are marked as **\[Unified]** (naming), **\[Refined]** (design), or **\[New]** (fresh addition).

---

## 0) Executive Summary

* **Core Fantasy**: You are the **Prismwalker**, a colorless being who absorbs hues to shape the world, self, and story. Explore six chromatic regions and a colorless wound at the world’s heart; recover artifacts to reforge the Prismatic Core or pick a fate more… complicated.
* **Loop**: Explore → bind hues → solve echo/puzzle gates → fight color-reactive enemies → recover lore/relics → rebind/upgrade → unlock story branches.
* **Loadout**: **3 bound hues** at a time (switchable in combat); actives share a single charge pool. **Affinity** grows per hue with usage/exposure, unlocking powers, dialogue, and endings.

---

## 1) Canonical Terminology & Naming

**\[Unified] Hues (canonical → common synonyms)**

* **CRIMSON** → (Red) — Region: **Vireya** — Order: Crimson Order
* **COBALT** → (Blue) — Region: **Iriseld** — Order: Cobalt Order
* **VERDANT** → (Green) — Region: **Huevale** — Order: Verdant Order
* **VIOLET** → (Purple) — Region: **Myrrala** — Order: Violet Order / Thulian Court
* **AURELIAN** → (Yellow/Gold) — Region: **Luxeran** — Order: Aurelian Order
* **EARTHEN** → (Brown) — Region: **Auralith** — Order: Earthen Order
* **NULLSHADE** → (Void/Colorless) — Center zone / antagonistic force (not a player hue)

> Use these canonical names in systems/code/UI. Color words (red/blue/….) are fine in prose but keep mechanics keyed to the canonical forms above.

**\[Unified] Resource Names**

* **Color Charge (CC)** — the shared, spendable energy used by all bound hue actives (**formerly** “Hue Bar” / “memory charges”).
* **Memory Stability (MS)** — a status that represents the Prismwalker’s intact self/UI. Certain enemies drain CC; if they push you to **CC ≤ 0**, they begin corrupting **MS**, causing UI lockouts and “echo glitches” until repaired.

**\[Unified] Affinity Tiers**

* **INITIATE → ADEPT → EXPERT → MASTER** (replaces mixed usage of Novice/Legend, etc.)

---

## 2) Core Systems

### 2.1 Hue Binding

**\[Refined]**

* Discover **Hue Shards** to unlock a hue permanently.
* Bind up to **3** hues at any time; switching in combat is allowed but incurs a **Global Swap Cooldown** (GSC) of **0.75s** (tunable).
* Bound hues expose **passives** (always on) and **actives** (CC-costed skills). A small, on-hit **“microcharge”** trickle (0.5 CC/sec) occurs out of combat.

### 2.2 Color Charge (CC) & Memory Stability (MS)

**\[Unified+Refined]**

* **Base CC Max**: **100** (tunable). Actives cost **10–30 CC**.
* **Recharge**: Shrines (full); pickups (10–25 CC); certain relics (e.g., slow regen while unhurt).
* **Drain**: Memory-Drainers reduce **CC first**. If **CC ≤ 0**, subsequent drains **tick MS** and trigger **UI corruption**:

  * Randomly hidden HUD elements (e.g., hue icons gray out)
  * Input inversion on a small per-action chance
  * “Echo latch” debuff that requires a **Memory Echo** interaction to clear
* **Repair MS** via: Memory Shrines, Echo puzzles, or certain relics (Caput Mortuum, Bistre Lantern).

> This merges your earlier “memory charges” and “Hue Bar” into a clear two-layer model: **CC** (for casting) atop **MS** (self/integrity).

### 2.3 Affinity (Per-Hue Progression)

**\[Unified]**

* **Tier thresholds (default)**: INITIATE **0** → ADEPT **1,000** → EXPERT **5,000** → MASTER **20,000** Affinity XP
* XP Sources: casting, time bound, region exposure, lore intake, relic use.
* Unlocks: dialogue, passives, combo upgrades, relic potency, and endgame branches.

### 2.4 Interactions & Combos

**\[Refined]**

* **Combo Window**: cast **Hue A → Hue B** within **0.8s** to proc a small synergy.
* **Counter-Cast**: hitting an enemy with its **Nemesis Hue** applies a brief **Interrupt** (0.4s) or **Expose** (10% more damage for 4s).
* **Conflict Casting**: using a Hue that the enemy **feeds on** buffs it (e.g., Verdant on Bloomrot Titan adds regen stacks).

### 2.5 Echo Puzzles (Memory)

**\[Refined]**

* “Echo Segments” spawn near lore sites and after MS corruption.
* Solve micro-puzzles (reorder lines, truth-choice, rhythm recall) to **restore MS**, purge latches, and sometimes grant a **CC overshield** (+25 temporary CC).

---

## 3) Combat & Hues (Tuning Pass v0)

| Hue          | Role            | Passive                     | Core Actives (v0 costs)                                                             | Nemesis & Notes                           |
| ------------ | --------------- | --------------------------- | ----------------------------------------------------------------------------------- | ----------------------------------------- |
| **CRIMSON**  | Offense/Flame   | +8% vs Flesh/Constructs     | **Fireburst** (15 CC, cone); **Flame Dash** (20 CC, i-frames)                       | Overheats constructs; bad vs. fire-immune |
| **COBALT**   | Disrupt/Defense | +1.5%/s shield trickle      | **Mind Echo** (15 CC, reveal/invis ping); **Static Dash** (20 CC, short stun)       | Reveals illusions; chills golems          |
| **VERDANT**  | Control/Travel  | +10% move in foliage        | **Skygrowth Seed** (15 CC, creates climb/vine snare); **Root Bind** (20 CC)         | Pacifies Sapborn; feeds Bloomrot          |
| **AURELIAN** | Light/Utility   | Waypoint reveal radius +30% | **Radiant Flash** (15 CC, blind); **Shatter Note** (25 CC, brittle on glass)        | Empowers Marionettes; shatters glass      |
| **VIOLET**   | Illusion/Mind   | Stealth dampens 15% farther | **Glamour Pulse** (20 CC, dispel/reflect mirage); **Illusion Clone** (25 CC, decoy) | Counters Doppelshade                      |
| **EARTHEN**  | Memory/Decay    | +0.5 MS/s passive repair    | **Earthen Echo** (15 CC, restore MS/pulse); **Decay Grasp** (20 CC, rot DoT)        | Stuns Memory Leeches                      |

**Synergy Examples (v0)**

* **Crimson → Cobalt**: Ember-Shock — adds a 0.5s mini-stun
* **Violet → Aurelian**: Prism Snap — illusions shatter, 100% crit on the next hit
* **Earthen → Verdant**: Compost Surge — root/snare duration +50%

---

## 4) World & Regions (Canonical Set)

* **Huevale (Verdant)** — growth/stealth/overgrowth puzzles. City: **Tinctara**.
* **Vireya (Crimson)** — volcanic warlands, rituals, duel schools.
* **Iriseld (Cobalt)** — stormed coasts, glass ruins, mirror lakes.
* **Myrrala (Violet)** — dream veils, glamours, time-bent courts.
* **Luxeran (Aurelian)** — desert trade, mirage vaults, oath-magic.
* **Auralith (Earthen)** — catacombs, archives, decay alchemy.
* **Nullshade (Void)** — Prism Wound, Shatterglass pools; late-game.

**Endings (kept, lightly clarified)**

* **Harmony** (Reforged Prism) / **Monochrome** (one hue ascendant) / **No Color** (Eigengrau ascends) / **Spectrum War** (perpetual conflict). Affinity at **MASTER** in ≥2 hues unlocks unique epilogues across these.

---

## 5) UI Direction (Locked for Vertical Slice)

* **Diegetic-minimal** HUD: crystal shard health, orbiting hue shards, segmented CC bar.
* **Accessibility**: glyphs for each hue (leaf/flame/wave/spiral/sunburst/root), colorblind-friendly contrasts.
* **Combat cues**: weak-to-hue shimmer; swap pulses; ultimate kaleidoscope ripple.

---

## 6) Vertical Slice Plan (4–6 weeks of content scope, engine-agnostic)

**Goal**: 1 region loop (**Huevale**) showcasing exploration, one shrine puzzle, 3 enemy types, 1 mini-boss, 3 hues (Verdant + Cobalt + Violet), CC/MS loop, and a dialogue check using Affinity.

**Content**

1. **Space**: Huevale Approach → Tinctara Outskirts → Saproot Shrine (bind Verdant) → Boglight Caves (illusion counter) → Malachite Grove (mini-boss).
2. **Enemies**: Hue Leeches (memory), Boglight Mimic (illusion), Sapborn Stalker (control).
3. **Mini-Boss**: **Moth-Witch of the Verdant Spiral** (arena riddles + illusion layers; counter with Violet + Cobalt).
4. **Relics**: Bistre Lantern (MS repair burst), Zaffre Vial (banish memory-water for 10s), Chartreuse Tonic (stam buff).
5. **Systems**: Bind Verdant at shrine; pick up Cobalt shard in caves; earn Violet via quest-Echo at grove. Demonstrate synergy **Violet→Aurelian** via a one-use story artifact.
6. **Narrative**: 3 short scenes including **Color Dialogue** checks and **Affinity** bump to ADEPT in Verdant.

**Success Criteria**

* Player experiences CC drain → MS corruption → Echo repair loop at least once.
* Player uses **2+ hue swaps in combat** and triggers **1 combo**.
* One **Illusion** reveal and one **Traversal** unlock (vines).

---

## 7) Content Backlog (Prioritized)

1. **Aura Fields** per region (suppression/drain/inversion rules).
2. Finish **Bestiary tags** (Nemesis/Feeds-On/Immune) in a single CSV for designers.
3. **Relic gating** list (Required Tier, Bonus Tier) mapped to zones and quests.
4. **Combo library**: 15–20 pair synergies w/ names, tiny effects, 0.8s window.
5. **Dialogue kit**: per-hue personality lines + mixed archetypes (already drafted) plugged into a branching template.

---

## 8) Code — Hue Affinity (Corrected & Aligned)

**Why the change?**

* Fixes a bug in `operator=` (undeclared loop var), aligns tier names with the GDD, and adds helpers for thresholds. Also makes load/save resilient instead of `assert`-only.

### HueAffinity.hpp (v0.2)

```cpp
#ifndef HUE_AFFINITY_HPP
#define HUE_AFFINITY_HPP

#include <ostream>
#include <istream>
#include <cstddef>

class HueAffinity {
public:
    enum Hue {
        VERDANT = 0,
        CRIMSON,
        COBALT,
        VIOLET,
        AURELIAN,
        EARTHEN,
        HUE_COUNT
    };

    enum Tier {
        INITIATE = 0,
        ADEPT,
        EXPERT,
        MASTER,
        TIER_COUNT
    };

private:
    int  _xp[HUE_COUNT];
    Tier _tier[HUE_COUNT];

    // XP required to reach each tier (INITIATE starts at 0)
    static const int XP_THRESHOLD[TIER_COUNT];

    static Tier tierForXp(int xp);

public:
    HueAffinity();
    HueAffinity(const HueAffinity& other);
    HueAffinity& operator=(const HueAffinity& other);

    void addXp(Hue h, int amount);
    int  getXp(Hue h) const;
    Tier getTier(Hue h) const;
    bool meetsTier(Hue h, Tier required) const;

    // Convenience
    int  nextTierXp(Hue h) const;   // XP required for next tier, or -1 if MASTER

    // Serialization
    bool save(std::ostream& out) const; // one line per hue: "<xp> <tier>\n"
    bool load(std::istream& in);        // robust read with bounds checks
};

#endif // HUE_AFFINITY_HPP
```

### HueAffinity.cpp (v0.2)

```cpp
#include "HueAffinity.hpp"
#include <limits>

// INITIATE, ADEPT, EXPERT, MASTER
const int HueAffinity::XP_THRESHOLD[HueAffinity::TIER_COUNT] = {
    0,      // INITIATE
    1000,   // ADEPT
    5000,   // EXPERT
    20000   // MASTER
};

static inline HueAffinity::Tier clampTier(HueAffinity::Tier t) {
    if (t < HueAffinity::INITIATE) return HueAffinity::INITIATE;
    if (t > HueAffinity::MASTER)   return HueAffinity::MASTER;
    return t;
}

HueAffinity::Tier HueAffinity::tierForXp(int xp) {
    if (xp < XP_THRESHOLD[ADEPT])  return INITIATE;
    if (xp < XP_THRESHOLD[EXPERT]) return ADEPT;
    if (xp < XP_THRESHOLD[MASTER]) return EXPERT;
    return MASTER;
}

HueAffinity::HueAffinity() {
    for (int i = 0; i < HUE_COUNT; ++i) {
        _xp[i] = 0;
        _tier[i] = INITIATE;
    }
}

HueAffinity::HueAffinity(const HueAffinity& other) {
    for (int i = 0; i < HUE_COUNT; ++i) {
        _xp[i] = other._xp[i];
        _tier[i] = other._tier[i];
    }
}

HueAffinity& HueAffinity::operator=(const HueAffinity& other) {
    if (this != &other) {
        for (int i = 0; i < HUE_COUNT; ++i) {
            _xp[i]   = other._xp[i];
            _tier[i] = other._tier[i];
        }
    }
    return *this;
}

void HueAffinity::addXp(Hue h, int amount) {
    if (h < 0 || h >= HUE_COUNT || amount <= 0) return;

    // Prevent overflow in absurd saves
    if (_xp[h] > std::numeric_limits<int>::max() - amount)
        _xp[h] = std::numeric_limits<int>::max();
    else
        _xp[h] += amount;

    _tier[h] = tierForXp(_xp[h]);
}

int HueAffinity::getXp(Hue h) const {
    if (h < 0 || h >= HUE_COUNT) return 0;
    return _xp[h];
}

HueAffinity::Tier HueAffinity::getTier(Hue h) const {
    if (h < 0 || h >= HUE_COUNT) return INITIATE;
    return _tier[h];
}

bool HueAffinity::meetsTier(Hue h, Tier required) const {
    if (h < 0 || h >= HUE_COUNT) return false;
    required = clampTier(required);
    return _tier[h] >= required;
}

int HueAffinity::nextTierXp(Hue h) const {
    if (h < 0 || h >= HUE_COUNT) return -1;
    Tier t = _tier[h];
    if (t >= MASTER) return -1;
    return XP_THRESHOLD[t + 1];
}

bool HueAffinity::save(std::ostream& out) const {
    for (int h = 0; h < HUE_COUNT; ++h) {
        out << _xp[h] << ' ' << static_cast<int>(_tier[h]) << '\n';
        if (!out) return false;
    }
    return true;
}

bool HueAffinity::load(std::istream& in) {
    for (int h = 0; h < HUE_COUNT; ++h) {
        int xp = 0, tierInt = 0;
        in >> xp >> tierInt;
        if (!in) return false;

        if (xp < 0) xp = 0;
        if (tierInt < INITIATE) tierInt = INITIATE;
        if (tierInt >= TIER_COUNT) tierInt = MASTER;

        _xp[h]   = xp;
        _tier[h] = clampTier(static_cast<Tier>(tierInt));

        // Reconcile tier from XP (trust XP as source of truth)
        _tier[h] = tierForXp(_xp[h]);
    }
    return true;
}
```

---

## 9) Data & Tools (Designer-Facing)

**Backbone CSVs** (for balancing & clarity)

* `hues.csv` — canonical names, synonyms, UI glyph id, base passives, actives (cost, cooldown, tags)
* `enemies.csv` — region, tags (Memory-Drainer/Illusion/etc.), NemesisHue, FeedsOnHue
* `relics.csv` — RequiredTier, BonusTier, effects, gating notes
* `combos.csv` — (A,B) → effect name, micro-effect description, duration

---

## 10) Open Questions (Non-blocking)

1. Keep **GSC 0.75s** or let specific relics shorten hue swap time?
2. Do we want **Aurelian** to tilt more into **truth-binding** (dialogue oaths) vs. raw light?
3. Should **Nullshade** have unique “anti-hue” mechanics that *invert* combos?
4. Are **tier thresholds** too large for early game? (Consider 0/500/2500/10000 for faster ramp.)
5. HUD: show **MS** as a subtle rim around the shard, or only surface when corrupted?

> We can test these inside the vertical slice; they don’t block content creation now.

---

*End v0.2.*
