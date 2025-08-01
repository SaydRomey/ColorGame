// BeastFactory.cpp

#include "BeastFactory.hpp"
#include "BeastJsonLoader.hpp"
// #include "BestiaryLookup.hpp"
// #include "BeastsHeaders.hpp"
#include "SimpleBeast.hpp"
#include <fstream>
// #include "picojson.h"


Beast*	BeastFactory::createFromFile(const std::string& filepath)
{
	BeastData	data;

	if (!BeastJsonLoader::loadFromFile(filepath, data))
		return (NULL);

	return (new SimpleBeast(data));
}

/*
Beast* BeastFactory::createFromFile(const std::string& filepath)
{
	std::ifstream in(filepath.c_str());
	if (!in)
		return (NULL);

	picojson::value root;
	in >> root;
	if (!root.is<picojson::object>())
		return (NULL);

	const picojson::object& obj = root.get<picojson::object>();
	if (!obj.count("id") || !obj.at("id").is<std::string>())
		return (NULL);

	std::string idStr = obj.at("id").get<std::string>();

	BestiaryID	id;
	try
	{
		id = toBestiaryID(idStr);
	}
	catch (...)
	{
		return (NULL);
	}

	Beast* beast = NULL;

	switch (id)
	{
		case BEAST_ABYSSAL_CURRENT:
			beast = new AbyssalCurrent();
			break;
		case BEAST_ALCHEMICAL_ECHO:
			beast = new AlchemicalEcho();
			break;
		case BEAST_AMBERCOIL_ASP:
			beast = new AmbercoilAsp();
			break;
		case BEAST_ASHWEAVER_RECLUSE:
			beast = new AshweaverRecluse();
			break;
		case BEAST_ASHWROUGHT_COLOSSUS:
			beast = new AshwroughtColossus();
			break;
		case BEAST_BANNERBOUND_REVENANT:
			beast = new BannerboundRevenant();
			break;
		case BEAST_BLOODROOT_EFFIGY:
			beast = new BloodrootEffigy();
			break;
		case BEAST_BLOOMROT_TITAN:
			beast = new BloomrotTitan();
			break;
		case BEAST_BLOOMVEIL_WIDOW:
			beast = new BloomveilWidow();
			break;
		case BEAST_BOGLIGHT_MIMIC:
			beast = new BoglightMimic();
			break;
		case BEAST_CAPUT_MARIONETTE:
			beast = new CaputMarionette();
			break;
		case BEAST_CHARTREUSE_HUSK:
			beast = new ChartreuseHusk();
			break;
		case BEAST_CINNABAR_SCARAB:
			beast = new CinnabarScarab();
			break;
		case BEAST_CITRINE_GOLEM:
			beast = new CitrineGolem();
			break;
		case BEAST_CRIMSON_ECHO:
			beast = new CrimsonEcho();
			break;
		case BEAST_DOPPELSHADE:
			beast = new Doppelshade();
			break;
		case BEAST_FANDANCER_FRAGMENT:
			beast = new FandancerFragment();
			break;
		case BEAST_FANGBLOOM_WYRM:
			beast = new FangbloomWyrm();
			break;
		case BEAST_FEATHERED_NULL:
			beast = new FeatheredNull();
			break;
		case BEAST_FOX_MIRAGE:
			beast = new FoxMirage();
			break;
		case BEAST_FRACTAL_SHARDLING:
			beast = new FractalShardling();
			break;
		case BEAST_FUNERAL_DANCER:
			beast = new FuneralDancer();
			break;
		case BEAST_GAMBOGE_DJINNLING:
			beast = new GambogeDjinnling();
			break;
		case BEAST_GLASSBORNE_ECHO:
			beast = new GlassborneEcho();
			break;
		case BEAST_GLASSLASH_SERPENT:
			beast = new GlasslashSerpent();
			break;
		case BEAST_GLITTERING_GRIMOIRE:
			beast = new GlitteringGrimoire();
			break;
		case BEAST_GROVEBOUND_SENTINEL:
			beast = new GroveboundSentinel();
			break;
		case BEAST_HELIOTROPIC_LURKER:
			beast = new HeliotropicLurker();
			break;
		case BEAST_HOLLOW_PROPHET:
			beast = new HollowProphet();
			break;
		case BEAST_HUE_LEECHES:
			beast = new HueLeeches();
			break;
		case BEAST_HUEFRACTALS:
			beast = new Huefractals();
			break;
		case BEAST_LAVA_FUSED_BEHEMOTH:
			beast = new LavaFusedBehemoth();
			break;
		case BEAST_LILYBORN_MIRAGE:
			beast = new LilybornMirage();
			break;
		case BEAST_LIMEROOT_TRICKSTER:
			beast = new LimerootTrickster();
			break;
		case BEAST_MEMORY_GRAFTER:
			beast = new MemoryGrafter();
			break;
		case BEAST_MEMORY_HUSK:
			beast = new MemoryHusk();
			break;
		case BEAST_MEMORY_LEECH:
			beast = new MemoryLeech();
			break;
		case BEAST_MIRAGE_REVENANT:
			beast = new MirageRevenant();
			break;
		case BEAST_MIRRORWAKE_DUELIST:
			beast = new MirrorwakeDuelist();
			break;
		case BEAST_MIRRORTHIRST_WYRM:
			beast = new MirrorthirstWyrm();
			break;
		case BEAST_MOSSGRAVE_REVENANT:
			beast = new MossgraveRevenant();
			break;
		case BEAST_MOTH_WITCH_VERDANT_SPIRAL:
			beast = new MothWitchVerdantSpiral();
			break;
		case BEAST_NULL_ROOT:
			beast = new NullRoot();
			break;
		case BEAST_NULLBORN_HUSKS:
			beast = new NullbornHusks();
			break;
		case BEAST_NULLSHADE_ECHO:
			beast = new NullshadeEcho();
			break;
		case BEAST_NULLSHADE_REVENANT:
			beast = new NullshadeRevenant();
			break;
		case BEAST_OCHRE_GOLEM:
			beast = new OchreGolem();
			break;
		case BEAST_PHYLACTERY_SWARM:
			beast = new PhylacterySwarm();
			break;
		case BEAST_PRISM_UNFORM:
			beast = new PrismUnform();
			break;
		case BEAST_RAZZFLARE_IMP:
			beast = new RazzflareImp();
			break;
		case BEAST_RED_WIDOW:
			beast = new RedWidow();
			break;
		case BEAST_RUSTWORN_JUDGE:
			beast = new RustwornJudge();
			break;
		case BEAST_SAPBORN_STALKER:
			beast = new SapbornStalker();
			break;
		case BEAST_SEARBLOOD_CULTIST:
			beast = new SearbloodCultist();
			break;
		case BEAST_SHATTERGLASS_CHOIR:
			beast = new ShatterglassChoir();
			break;
		case BEAST_SILENCE_INCARNATE:
			beast = new SilenceIncarnate();
			break;
		case BEAST_SKYCALL_WRAITH:
			beast = new SkycallWraith();
			break;
		case BEAST_SOOTSHADE_COLLECTOR:
			beast = new SootshadeCollector();
			break;
		case BEAST_SORROWWING:
			beast = new Sorrowwing();
			break;
		case BEAST_SPECTRAL_HARVESTER:
			beast = new SpectralHarvester();
			break;
		case BEAST_SPOREKIN:
			beast = new Sporekin();
			break;
		case BEAST_STORMWRIT_HOUND:
			beast = new StormwritHound();
			break;
		case BEAST_SUNBURNT_JACKAL:
			beast = new SunburntJackal();
			break;
		case BEAST_SUNDIAL_SCARWALKER:
			beast = new SundialScarwalker();
			break;
		case BEAST_SUNFLARE_MARIONETTE:
			beast = new SunflareMarionette();
			break;
		case BEAST_TAPESTRY_WATCHER_NULLSHADE:
			beast = new TapestryWatcherNullshade();
			break;
		case BEAST_TAPESTRY_WATCHER:
			beast = new TapestryWatcher();
			break;
		case BEAST_TEMPEST_MARIONETTE:
			beast = new TempestMarionette();
			break;
		case BEAST_THE_BOUND:
			beast = new TheBound();
			break;
		case BEAST_COLORLESS_SHAPE:
			beast = new ColorlessShape();
			break;
		case BEAST_SEVENTH_HUE:
			beast = new SeventhHue();
			break;
		case BEAST_UNHUED_CHOIR:
			beast = new UnhuedChoir();
			break;
		case BEAST_THORNWRITHE_BEAST:
			beast = new ThornwritheBeast();
			break;
		case BEAST_THULIAN_VOWKEEPER:
			beast = new ThulianVowkeeper();
			break;
		case BEAST_TIDEWORN_APOSTLE:
			beast = new TidewornApostle();
			break;
		case BEAST_TYRIAN_ECHO:
			beast = new TyrianEcho();
			break;
		case BEAST_VEILSHIFT_MATRON:
			beast = new VeilshiftMatron();
			break;
		case BEAST_VERDANT_MAW:
			beast = new VerdantMaw();
			break;
		case BEAST_WHISPERGLASS_WYRM:
			beast = new WhisperglassWyrm();
			break;
		case BEAST_WICKBONE_LANTERN:
			beast = new WickboneLantern();
			break;
		case BEAST_WICKERBORN:
			beast = new Wickerborn();
			break;
		case BEAST_WOUND_REMNANT:
			beast = new WoundRemnant();
			break;

		default:
			return (NULL);
	}

	if (beast && beast->loadFromFile(filepath))
		return (beast);

	delete beast;

	// if (idStr == "BEAST_ABYSSAL_CURRENT") {
	// 	AbyssalCurrent* b = new AbyssalCurrent();
	// 	if (b->loadFromFile(filepath)) return b;
	// 	delete b;
	// }
	// else if (idStr == "BEAST_ALCHEMICAL_ECHO") {
	// 	AlchemicalEcho* b = new AlchemicalEcho();
	// 	if (b->loadFromFile(filepath)) return b;
	// 	delete b;
	// }

	return (NULL);
}
*/

/*
Beast*	BeastFactory::createFromID(BestiaryID id)
{
	std::string	path = getBeastJsonPath(id);
	if (path.empty())
		return (NULL);
	return (createFromFile(path));
}
*/

/*
Beast* BeastFactory::createFromID(BestiaryID id)
{
	std::string path = "data/bestiary/";
	switch (id)
	{
		case BEAST_ABYSSAL_CURRENT: path += "BEAST_ABYSSAL_CURRENT.json"; break;
		case BEAST_ALCHEMICAL_ECHO: path += "BEAST_ALCHEMICAL_ECHO.json"; break;
		case BEAST_AMBERCOIL_ASP: path += "BEAST_AMBERCOIL_ASP.json"; break;
		case BEAST_ASHWEAVER_RECLUSE: path += "BEAST_ASHWEAVER_RECLUSE.json"; break;
		case BEAST_ASHWROUGHT_COLOSSUS: path += "BEAST_ASHWROUGHT_COLOSSUS.json"; break;
		case BEAST_BANNERBOUND_REVENANT: path += "BEAST_BANNERBOUND_REVENANT.json"; break;
		case BEAST_BLOODROOT_EFFIGY: path += "BEAST_BLOODROOT_EFFIGY.json"; break;
		case BEAST_BLOOMROT_TITAN: path += "BEAST_BLOOMROT_TITAN.json"; break;
		case BEAST_BLOOMVEIL_WIDOW: path += "BEAST_BLOOMVEIL_WIDOW.json"; break;
		case BEAST_BOGLIGHT_MIMIC: path += "BEAST_BOGLIGHT_MIMIC.json"; break;
		case BEAST_CAPUT_MARIONETTE: path += "BEAST_CAPUT_MARIONETTE.json"; break;
		case BEAST_CHARTREUSE_HUSK: path += "BEAST_CHARTREUSE_HUSK.json"; break;
		case BEAST_CINNABAR_SCARAB: path += "BEAST_CINNABAR_SCARAB.json"; break;
		case BEAST_CITRINE_GOLEM: path += "BEAST_CITRINE_GOLEM.json"; break;
		case BEAST_CRIMSON_ECHO: path += "BEAST_CRIMSON_ECHO.json"; break;
		case BEAST_DOPPELSHADE: path += "BEAST_DOPPELSHADE.json"; break;
		case BEAST_FANDANCER_FRAGMENT: path += "BEAST_FANDANCER_FRAGMENT.json"; break;
		case BEAST_FANGBLOOM_WYRM: path += "BEAST_FANGBLOOM_WYRM.json"; break;
		case BEAST_FEATHERED_NULL: path += "BEAST_FEATHERED_NULL.json"; break;
		case BEAST_FOX_MIRAGE: path += "BEAST_FOX_MIRAGE.json"; break;
		case BEAST_FRACTAL_SHARDLING: path += "BEAST_FRACTAL_SHARDLING.json"; break;
		case BEAST_FUNERAL_DANCER: path += "BEAST_FUNERAL_DANCER.json"; break;
		case BEAST_GAMBOGE_DJINNLING: path += "BEAST_GAMBOGE_DJINNLING.json"; break;
		case BEAST_GLASSBORNE_ECHO: path += "BEAST_GLASSBORNE_ECHO.json"; break;
		case BEAST_GLASSLASH_SERPENT: path += "BEAST_GLASSLASH_SERPENT.json"; break;
		case BEAST_GLITTERING_GRIMOIRE: path += "BEAST_GLITTERING_GRIMOIRE.json"; break;
		case BEAST_GROVEBOUND_SENTINEL: path += "BEAST_GROVEBOUND_SENTINEL.json"; break;
		case BEAST_HELIOTROPIC_LURKER: path += "BEAST_HELIOTROPIC_LURKER.json"; break;
		case BEAST_HOLLOW_PROPHET: path += "BEAST_HOLLOW_PROPHET.json"; break;
		case BEAST_HUE_LEECHES: path += "BEAST_HUE_LEECHES.json"; break;
		case BEAST_HUEFRACTALS: path += "BEAST_HUEFRACTALS.json"; break;
		case BEAST_LAVA_FUSED_BEHEMOTH: path += "BEAST_LAVA_FUSED_BEHEMOTH.json"; break;
		case BEAST_LILYBORN_MIRAGE: path += "BEAST_LILYBORN_MIRAGE.json"; break;
		case BEAST_LIMEROOT_TRICKSTER: path += "BEAST_LIMEROOT_TRICKSTER.json"; break;
		case BEAST_MEMORY_GRAFTER: path += "BEAST_MEMORY_GRAFTER.json"; break;
		case BEAST_MEMORY_HUSK: path += "BEAST_MEMORY_HUSK.json"; break;
		case BEAST_MEMORY_LEECH: path += "BEAST_MEMORY_LEECH.json"; break;
		case BEAST_MIRAGE_REVENANT: path += "BEAST_MIRAGE_REVENANT.json"; break;
		case BEAST_MIRRORWAKE_DUELIST: path += "BEAST_MIRRORWAKE_DUELIST.json"; break;
		case BEAST_MIRRORTHIRST_WYRM: path += "BEAST_MIRRORTHIRST_WYRM.json"; break;
		case BEAST_MOSSGRAVE_REVENANT: path += "BEAST_MOSSGRAVE_REVENANT.json"; break;
		case BEAST_MOTH_WITCH_VERDANT_SPIRAL: path += "BEAST_MOTH_WITCH_VERDANT_SPIRAL.json"; break;
		case BEAST_NULL_ROOT: path += "BEAST_NULL_ROOT.json"; break;
		case BEAST_NULLBORN_HUSKS: path += "BEAST_NULLBORN_HUSKS.json"; break;
		case BEAST_NULLSHADE_ECHO: path += "BEAST_NULLSHADE_ECHO.json"; break;
		case BEAST_NULLSHADE_REVENANT: path += "BEAST_NULLSHADE_REVENANT.json"; break;
		case BEAST_OCHRE_GOLEM: path += "BEAST_OCHRE_GOLEM.json"; break;
		case BEAST_PHYLACTERY_SWARM: path += "BEAST_PHYLACTERY_SWARM.json"; break;
		case BEAST_PRISM_UNFORM: path += "BEAST_PRISM_UNFORM.json"; break;
		case BEAST_RAZZFLARE_IMP: path += "BEAST_RAZZFLARE_IMP.json"; break;
		case BEAST_RED_WIDOW: path += "BEAST_RED_WIDOW.json"; break;
		case BEAST_RUSTWORN_JUDGE: path += "BEAST_RUSTWORN_JUDGE.json"; break;
		case BEAST_SAPBORN_STALKER: path += "BEAST_SAPBORN_STALKER.json"; break;
		case BEAST_SEARBLOOD_CULTIST: path += "BEAST_SEARBLOOD_CULTIST.json"; break;
		case BEAST_SHATTERGLASS_CHOIR: path += "BEAST_SHATTERGLASS_CHOIR.json"; break;
		case BEAST_SILENCE_INCARNATE: path += "BEAST_SILENCE_INCARNATE.json"; break;
		case BEAST_SKYCALL_WRAITH: path += "BEAST_SKYCALL_WRAITH.json"; break;
		case BEAST_SOOTSHADE_COLLECTOR: path += "BEAST_SOOTSHADE_COLLECTOR.json"; break;
		case BEAST_SORROWWING: path += "BEAST_SORROWWING.json"; break;
		case BEAST_SPECTRAL_HARVESTER: path += "BEAST_SPECTRAL_HARVESTER.json"; break;
		case BEAST_SPOREKIN: path += "BEAST_SPOREKIN.json"; break;
		case BEAST_STORMWRIT_HOUND: path += "BEAST_STORMWRIT_HOUND.json"; break;
		case BEAST_SUNBURNT_JACKAL: path += "BEAST_SUNBURNT_JACKAL.json"; break;
		case BEAST_SUNDIAL_SCARWALKER: path += "BEAST_SUNDIAL_SCARWALKER.json"; break;
		case BEAST_SUNFLARE_MARIONETTE: path += "BEAST_SUNFLARE_MARIONETTE.json"; break;
		case BEAST_TAPESTRY_WATCHER_NULLSHADE: path += "BEAST_TAPESTRY_WATCHER_NULLSHADE.json"; break;
		case BEAST_TAPESTRY_WATCHER: path += "BEAST_TAPESTRY_WATCHER.json"; break;
		case BEAST_TEMPEST_MARIONETTE: path += "BEAST_TEMPEST_MARIONETTE.json"; break;
		case BEAST_THE_BOUND: path += "BEAST_THE_BOUND.json"; break;
		case BEAST_COLORLESS_SHAPE: path += "BEAST_COLORLESS_SHAPE.json"; break;
		case BEAST_SEVENTH_HUE: path += "BEAST_SEVENTH_HUE.json"; break;
		case BEAST_UNHUED_CHOIR: path += "BEAST_UNHUED_CHOIR.json"; break;
		case BEAST_THORNWRITHE_BEAST: path += "BEAST_THORNWRITHE_BEAST.json"; break;
		case BEAST_THULIAN_VOWKEEPER: path += "BEAST_THULIAN_VOWKEEPER.json"; break;
		case BEAST_TIDEWORN_APOSTLE: path += "BEAST_TIDEWORN_APOSTLE.json"; break;
		case BEAST_TYRIAN_ECHO: path += "BEAST_TYRIAN_ECHO.json"; break;
		case BEAST_VEILSHIFT_MATRON: path += "BEAST_VEILSHIFT_MATRON.json"; break;
		case BEAST_VERDANT_MAW: path += "BEAST_VERDANT_MAW.json"; break;
		case BEAST_WHISPERGLASS_WYRM: path += "BEAST_WHISPERGLASS_WYRM.json"; break;
		case BEAST_WICKBONE_LANTERN: path += "BEAST_WICKBONE_LANTERN.json"; break;
		case BEAST_WICKERBORN: path += "BEAST_WICKERBORN.json"; break;
		case BEAST_WOUND_REMNANT: path += "BEAST_WOUND_REMNANT.json"; break;
		default: return NULL;
	}
	return createFromFile(path);
}
*/
