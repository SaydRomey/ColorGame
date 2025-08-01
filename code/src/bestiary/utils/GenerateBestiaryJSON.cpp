// GenerateBestiaryJSON.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>	// for system()

const char* enumLines[] = {
	"BEAST_ABYSSAL_CURRENT",
	"BEAST_ALCHEMICAL_ECHO",
	"BEAST_AMBERCOIL_ASP",
	"BEAST_ASHWEAVER_RECLUSE",
	"BEAST_ASHWROUGHT_COLOSSUS",
	"BEAST_BANNERBOUND_REVENANT",
	"BEAST_BLOODROOT_EFFIGY",
	"BEAST_BLOOMROT_TITAN",
	"BEAST_BLOOMVEIL_WIDOW",
	"BEAST_BOGLIGHT_MIMIC",
	"BEAST_CAPUT_MARIONETTE",
	"BEAST_CHARTREUSE_HUSK",
	"BEAST_CINNABAR_SCARAB",
	"BEAST_CITRINE_GOLEM",
	"BEAST_CRIMSON_ECHO",
	"BEAST_DOPPELSHADE",
	"BEAST_FANDANCER_FRAGMENT",
	"BEAST_FANGBLOOM_WYRM",
	"BEAST_FEATHERED_NULL",
	"BEAST_FOX_MIRAGE",
	"BEAST_FRACTAL_SHARDLING",
	"BEAST_FUNERAL_DANCER",
	"BEAST_GAMBOGE_DJINNLING",
	"BEAST_GLASSBORNE_ECHO",
	"BEAST_GLASSLASH_SERPENT",
	"BEAST_GLITTERING_GRIMOIRE",
	"BEAST_GROVEBOUND_SENTINEL",
	"BEAST_HELIOTROPIC_LURKER",
	"BEAST_HOLLOW_PROPHET",
	"BEAST_HUE_LEECHES",
	"BEAST_HUEFRACTALS",
	"BEAST_LAVA_FUSED_BEHEMOTH",
	"BEAST_LILYBORN_MIRAGE",
	"BEAST_LIMEROOT_TRICKSTER",
	"BEAST_MEMORY_GRAFTER",
	"BEAST_MEMORY_HUSK",
	"BEAST_MEMORY_LEECH",
	"BEAST_MIRAGE_REVENANT",
	"BEAST_MIRRORWAKE_DUELIST",
	"BEAST_MIRRORTHIRST_WYRM",
	"BEAST_MOSSGRAVE_REVENANT",
	"BEAST_MOTH_WITCH_VERDANT_SPIRAL",
	"BEAST_NULL_ROOT",
	"BEAST_NULLBORN_HUSKS",
	"BEAST_NULLSHADE_ECHO",
	"BEAST_NULLSHADE_REVENANT",
	"BEAST_OCHRE_GOLEM",
	"BEAST_PHYLACTERY_SWARM",
	"BEAST_PRISM_UNFORM",
	"BEAST_RAZZFLARE_IMP",
	"BEAST_RED_WIDOW",
	"BEAST_RUSTWORN_JUDGE",
	"BEAST_SAPBORN_STALKER",
	"BEAST_SEARBLOOD_CULTIST",
	"BEAST_SHATTERGLASS_CHOIR",
	"BEAST_SILENCE_INCARNATE",
	"BEAST_SKYCALL_WRAITH",
	"BEAST_SOOTSHADE_COLLECTOR",
	"BEAST_SORROWWING",
	"BEAST_SPECTRAL_HARVESTER",
	"BEAST_SPOREKIN",
	"BEAST_STORMWRIT_HOUND",
	"BEAST_SUNBURNT_JACKAL",
	"BEAST_SUNDIAL_SCARWALKER",
	"BEAST_SUNFLARE_MARIONETTE",
	"BEAST_TAPESTRY_WATCHER_NULLSHADE",
	"BEAST_TAPESTRY_WATCHER",
	"BEAST_TEMPEST_MARIONETTE",
	"BEAST_THE_BOUND",
	"BEAST_COLORLESS_SHAPE",
	"BEAST_SEVENTH_HUE",
	"BEAST_UNHUED_CHOIR",
	"BEAST_THORNWRITHE_BEAST",
	"BEAST_THULIAN_VOWKEEPER",
	"BEAST_TIDEWORN_APOSTLE",
	"BEAST_TYRIAN_ECHO",
	"BEAST_VEILSHIFT_MATRON",
	"BEAST_VERDANT_MAW",
	"BEAST_WHISPERGLASS_WYRM",
	"BEAST_WICKBONE_LANTERN",
	"BEAST_WICKERBORN",
	"BEAST_WOUND_REMNANT"
};
const int	numLines = sizeof(enumLines) / sizeof(enumLines[0]);

void	writeEntry(const std::string& id)
{
	const std::string	path = "output/" + id + ".json";

	std::ofstream	out(path.c_str());
	if (!out)
	{
		std::cerr << "Cannot open " << path << std::endl;
		return ;
	}

	out << "{\n";
	out << "  \"id\": \"" << id << "\",\n";
	out << "  \"entry\": {\n";
	out << "    \"name\": \"\",\n";
	out << "    \"type\": \"\",\n";
	out << "    \"threat_level\": \"\",\n";
	out << "    \"first_emerged\": \"\",\n";
	out << "    \"description\": \"\",\n";
	out << "    \"hue_interaction\": \"\",\n";
	out << "    \"behavior\": \"\",\n";
	out << "    \"weaknesses\": \"\",\n";
	out << "    \"notes\": \"\"\n";
	out << "  },\n";
	out << "  \"lore\": {\n";
	out << "    \"title\": \"\",\n";
	out << "    \"quote\": \"\",\n";
	out << "    \"flavor_description\": [],\n";
	out << "    \"field_notes\": [],\n";
	out << "    \"source\": \"\"\n";
	out << "  },\n";
	out << "  \"drops\": []\n";
	out << "}\n";
}

/*
Helper to create "output/" if it doesn't exist
*/
static void	ensureOutputDir(void)
{
	system("mkdir -p output");
	// or we could use ::mkdir() from <sys.stat.h> for a pure-C++/POSIX way
}

/*
Helper to generate the JSON files skeleton
*/
int	GenerateBestiaryJSON(void)
{
	// system("mkdir -p output");
	ensureOutputDir();
	
	int	i = 0;
	while (i < numLines)
	{
		std::string id(enumLines[i]);
		writeEntry(id);
		++i;
	}
	std::cout << "Generated " << numLines << " JSON files." << std::endl;
	return (0);
}
