
<div align="right">

[◄ Go back to Hue-Binding](./hue-binding.md)

</div>

# Hue Affinity Tiers

Each Hue has its own Affinity meter. 
Hitting certain thresholds unlocks new powers, dialogue, relic-effects 
and even alternate scene branches.


| Tier         | Affinity Range | Core Unlocks                                                                                                         |
| ------------ | -------------- | -------------------------------------------------------------------------------------------------------------------- |
| **Initiate** | 0 – X₁         | • Basic Hue Abilities<br>• Entry-level dialogue choices<br>• Can equip Hue relics at reduced potency                 |
| **Adept**    | X₁ – X₂        | • Mid-tier Abilities & upgrades<br>• New dialogue branches<br>• Unlock full base power of Hue relics                 |
| **Expert**   | X₂ – X₃        | • Advanced/combo Hue skills<br>• Secret or lore-only dialogue<br>• Relic bonus effects (extra charges, damage, etc.) |
| **Master**   | X₃+            | • Ultimate Hue powers (endgame spells)<br>• Exclusive narrative branches/endings<br>• Overcharged relic effects      |

(X₁, X₂, X₃ to be defined later.)

---

## Affinity XP Sources

Players earn Hue-Affinity XP in each color through:
  - **Ability Usage** (casting spells, using Hue skills)
  - **Time Bound** (how long that Hue is actively equipped)
  - **Region Exposure** (time spent in areas tied to that Hue)
  - **Lore Discovery** (reading field notes, bestiary entries, dialogue)
  - **Item Interaction** (using or equipping relics/tomes linked to a Hue)

---

## Dialogue & Scene Gates

Certain choices or ending scenes only appear if your Hue is at a given Tier:
  - **Initiate**: basic “flavor” lines—NPCs greet you in that color.
  - **Adept**: persuasion/bribe options, hue-specific lore reveals.
  - **Expert**: secret quest triggers, hidden NPC confidences.
  - **Master**: alternate endings or epilogues unlocked (e.g. you “speak the true name” at the final Prism pool).

---

## Relic/Item Scaling by Hue Tier

Every Hue-linked item carries a **Required Tier** and a **Bonus Tier**:
  - **Below Required Tier** → item is inert or weak (e.g. 50% effect or unusable).
  - **At Required Tier** → item works at base power.
  - **At or Above Bonus Tier** → item grants extra effects (extra charges, cooldown reduction, enhanced potency).

---

## Inter-Hue Synergies & Counters (Reminder)

- **Combo Bonus**: quickly switch A→B for small burst effects.
- **Counter-Cast**: hitting an enemy’s weakness Hue stuns or deals bonus.
- **Conflict**: using the Hue an enemy “feeds on” can actually buff them.

---

## Next Steps (TODO)

1. **Define X₁/X₂/X₃** thresholds (and whether they’re uniform across all Hues).

2. **List the major relics & scene-triggers** alongside their Required/Bonus Hue Tiers.

3. **Map key NPC dialogues or endings** to the Tier gates above.

---

## Code

### HueAffinity.hpp
```cpp
// HueAffinity.hpp

#ifndef HUE_AFFINITY_HPP
# define HUE_AFFINITY_HPP

# include <ostream>
# include <istream>

class HueAffinity
{
	public:
		// The six possible hues
		enum Hue
		{
			VERDANT = 0,
			CRIMSON,
			COBALT,
			VIOLET,
			GOLDEN,
			EARTHEN,
			HUE_COUNT
		};

		// Affinity tiers
		enum Tier
		{
			NOVICE = 0,
			ADEPT,
			MASTER,
			LEGEND,
			TIER_COUNT
		};

	private:
		int		_xp[HUE_COUNT];
		Tier	_tier[HUE_COUNT];

		// XP required to reach each tier (NOVICE starts at 0)
		static const int	XP_THRESHOLD[TIER_COUNT];

	public:
		HueAffinity(void);
		HueAffinity(const HueAffinity& other);
		HueAffinity&	operator=(const HueAffinity& other);
		~HueAffinity(void);

		void	addXp(Hue h, int amount);
		int		getXp(Hue h) const;
		Tier	getTier(Hue h) const;
		bool	meetsTier(Hue h, Tier required) const;

		// ─── Serialization helpers ─────────────────────────────────────────────
	    /// Writes out each hue’s XP and tier as plain text:
    	bool	save(std::ostream& out) const;
    	/// Reads the same format the save() wrote:
    	bool	load(std::istream& in);
    // ────────────────────────────────────────────────────────────────────────────

};

#endif // HUE_AFFINITY_HPP
```

### HueAffinity.cpp
```cpp
// HueAffinity.cpp

#include "HueAffinity.hpp"
#include <cassert>

// Define XP thresholds for NOVICE, ADEPT, MASTER, LEGEND
const int	HueAffinity::XP_THRESHOLD[HueAffinity::TIER_COUNT] = {
	0,     // NOVICE
	1000,  // ADEPT
	5000,  // MASTER
	20000  // LEGEND
};

// ────────────────────────────────────────────────────────────────────────────────

HueAffinity::HueAffinity(void)
{
	int	i = 0;
	while (i < HUE_COUNT)
	{
		_xp[i] = 0;
		_tier[i] = NOVICE;
		++i;
	}
}

HueAffinity::HueAffinity(const HueAffinity& other)
{
	int	i = 0;
	while (i < HUE_COUNT)
	{
		_xp[i] = other._xp[i];
		_tier[i] = other._tier[i];
		++i;
	}
}

HueAffinity&	HueAffinity::operator=(const HueAffinity& other)
{
	if (this != &other)
	{
		while (i < HUE_COUNT)
		{
			_xp[i] = other._xp[i];
			_tier[i] = other._tier[i];
			++i;
		}
	}
	return (*this);
}

HueAffinity::~HueAffinity(void) {}

// ────────────────────────────────────────────────────────────────────────────────

void	HueAffinity::addXp(Hue h, int amount)
{
	if(h < 0 || h >= HUE_COUNT || amount <= 0)
		return ;

	_xp[h] += amount;

	// bump tier up as far as XP allows
	while (_tier[h] < LEGEND && _xp[h] >= XP_THRESHOLD[_tier[h] + 1])
	{
		_tier[h] = static_cast<Tier>(_tier[h] + 1);
	}
}

int	HueAffinity::getXp(Hue h) const
{
	if (h < 0 || h >= HUE_COUNT)
		return (0);
	return (_xp[h]);
}

HueAffinity::Tier	HueAffinity::getTier(Hue h) const
{
	if (h < 0 || h >= HUE_COUNT)
		return (NOVICE);
	return (_tier[h]);
}

bool	HueAffinity::meetsTier(Hue h, Tier required) const
{
	if (h < 0 || h >= HUE_COUNT || required < NOVICE || required >= TIER_COUNT)
		return (false);
	return (_tier[h] >= required);
}

// ────────────────────────────────────────────────────────────────────────────────

bool	HueAffinity::save(std::ostream& out) const
{
	// Simple format: one line per hue: “<xp> <tier>\n”
	int	h = 0;
	while (h < HUE_COUNT)
	{
		out << _xp[h] << ' ' << _tier[h] << '\n';
		if (!out)
			return (false);
		++h;
	}
	return (true);
}

bool	HueAffinity::load(std::istream& in)
{
	int	h = 0;
	while (h < HUE_COUNT)
	{
		int	xp, tierInt;

		in >> xp >> tierInt;
		if (!in)
			return (false);

		// Basic validation:
		assert(xp >= 0);
		assert(tierInt >= NOVICE && tierInt < TIER_COUNT);

		_xp[h] = xp;
		_tier[h] = static_cast<Tier>(tierInt);
		++h;
	}
	return (true);
}
```

### Usage Example
```cpp
// usage example:

#include <fstream>

// … somewhere in our save routine …
HueAffinity	affinities;

// (player has built some XP…)
std::ofstream	file("save.txt");
if(!affinities.save(file))
{
	// handle error
}

// … somewhere in your load routine …
HueAffinity	loaded;

std::ifstream	in("save.txt");
if(!loaded.load(in))
{
	// handle corrupt/missing data
}
```

---