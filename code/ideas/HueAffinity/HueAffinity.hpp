// HueAffinity.hpp

#ifndef HUE_AFFINITY_HPP
# define HUE_AFFINITY_HPP

# include <ostream>
# include <istream>

class HueAffinity {
	public:
		// The six possible hues
		enum Hue {
			VERDANT = 0,
			CRIMSON,
			COBALT,
			VIOLET,
			GOLDEN,
			EARTHEN,
			HUE_COUNT
		};

		// Affinity tiers
		enum Tier {
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

