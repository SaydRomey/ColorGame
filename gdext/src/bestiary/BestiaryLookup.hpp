// BestiaryLookup.hpp

#ifndef BESTIARY_LOOKUP_HPP
# define BESTIARY_LOOKUP_HPP

# include "BestiaryIDs.hpp"
# include <string>
# include <map>
# include <stdexcept>

/* ---------------------------------------- */
/* helper : builds a singleton lookup-table */
/* -----------------------------------------*/
inline const std::map<std::string, BestiaryID>& beastLookupTable(void)
{
	typedef std::map<std::string, BestiaryID>	map_t;
	static map_t*	tbl = 0;
	if (!tbl)
	{
		tbl = new map_t;

#define ADD(ID) (*tbl)["BEAST_" #ID] = BEAST_##ID
		ADD(ABYSSAL_CURRENT);          ADD(ALCHEMICAL_ECHO);
		ADD(AMBERCOIL_ASP);            ADD(ASHWEAVER_RECLUSE);
		ADD(ASHWROUGHT_COLOSSUS);      ADD(BANNERBOUND_REVENANT);
		ADD(BLOODROOT_EFFIGY);         ADD(BLOOMROT_TITAN);
		ADD(BLOOMVEIL_WIDOW);          ADD(BOGLIGHT_MIMIC);
		ADD(CAPUT_MARIONETTE);         ADD(CHARTREUSE_HUSK);
		ADD(CINNABAR_SCARAB);          ADD(CITRINE_GOLEM);
		ADD(CRIMSON_ECHO);             ADD(DOPPELSHADE);
		ADD(FANDANCER_FRAGMENT);       ADD(FANGBLOOM_WYRM);
		ADD(FEATHERED_NULL);           ADD(FOX_MIRAGE);
		ADD(FRACTAL_SHARDLING);        ADD(FUNERAL_DANCER);
		ADD(GAMBOGE_DJINNLING);        ADD(GLASSBORNE_ECHO);
		ADD(GLASSLASH_SERPENT);        ADD(GLITTERING_GRIMOIRE);
		ADD(GROVEBOUND_SENTINEL);      ADD(HELIOTROPIC_LURKER);
		ADD(HOLLOW_PROPHET);           ADD(HUE_LEECHES);
		ADD(HUEFRACTALS);              ADD(LAVA_FUSED_BEHEMOTH);
		ADD(LILYBORN_MIRAGE);          ADD(LIMEROOT_TRICKSTER);
		ADD(MEMORY_GRAFTER);           ADD(MEMORY_HUSK);
		ADD(MEMORY_LEECH);             ADD(MIRAGE_REVENANT);
		ADD(MIRRORWAKE_DUELIST);       ADD(MIRRORTHIRST_WYRM);
		ADD(MOSSGRAVE_REVENANT);       ADD(MOTH_WITCH_VERDANT_SPIRAL);
		ADD(NULL_ROOT);                ADD(NULLBORN_HUSKS);
		ADD(NULLSHADE_ECHO);           ADD(NULLSHADE_REVENANT);
		ADD(OCHRE_GOLEM);              ADD(PHYLACTERY_SWARM);
		ADD(PRISM_UNFORM);             ADD(RAZZFLARE_IMP);
		ADD(RED_WIDOW);                ADD(RUSTWORN_JUDGE);
		ADD(SAPBORN_STALKER);          ADD(SEARBLOOD_CULTIST);
		ADD(SHATTERGLASS_CHOIR);       ADD(SILENCE_INCARNATE);
		ADD(SKYCALL_WRAITH);           ADD(SOOTSHADE_COLLECTOR);
		ADD(SORROWWING);               ADD(SPECTRAL_HARVESTER);
		ADD(SPOREKIN);                 ADD(STORMWRIT_HOUND);
		ADD(SUNBURNT_JACKAL);          ADD(SUNDIAL_SCARWALKER);
		ADD(SUNFLARE_MARIONETTE);      ADD(TAPESTRY_WATCHER_NULLSHADE);
		ADD(TAPESTRY_WATCHER);         ADD(TEMPEST_MARIONETTE);
		ADD(THE_BOUND);                ADD(COLORLESS_SHAPE);
		ADD(SEVENTH_HUE);              ADD(UNHUED_CHOIR);
		ADD(THORNWRITHE_BEAST);        ADD(THULIAN_VOWKEEPER);
		ADD(TIDEWORN_APOSTLE);         ADD(TYRIAN_ECHO);
		ADD(VEILSHIFT_MATRON);         ADD(VERDANT_MAW);
		ADD(WHISPERGLASS_WYRM);        ADD(WICKBONE_LANTERN);
		ADD(WICKERBORN);               ADD(WOUND_REMNANT);
#undef ADD
	}
	return (*tbl);
}

/* ------------------------------------------------------------------ */
// Non-throwing lookup
inline bool	try_toBestiaryID(const std::string& s, BestiaryID& out)
{
	const std::map<std::string, BestiaryID>&	t = beastLookupTable();

	std::map<std::string, BestiaryID>::const_iterator	it = t.find(s);
	if (it == t.end())
		return (false);
	out = it->second;
	return (true);
}

/* ------------------------------------------------------------------ */
inline BestiaryID	toBestiaryID(const std::string& s)
{
	const std::map<std::string, BestiaryID>&	t = beastLookupTable();

	std::map<std::string, BestiaryID>::const_iterator	it = t.find(s);
	if (it == t.end())
		throw (std::runtime_error("Unknown BestiaryID: " + s));

	return (it->second);
}

#endif // BESTIARY_LOOKUP_HPP
