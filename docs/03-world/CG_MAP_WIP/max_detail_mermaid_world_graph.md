# Max-Detail Mermaid Graph — Geography / NPCs / Enemies / Factions / Landmarks

This file contains a high-detail Mermaid graph that links:

- world structure
- regional geography
- landmarks
- NPCs
- enemies
- factions / groups
- relics / tools
- traversal laws
- Nullshade intrusion logic
- cross-region conceptual parallels

Because this is a large graph, it is designed for Mermaid renderers that support large flowcharts.  
If the graph is too crowded in one renderer, 
split the regional subgraphs into separate files using the section headers.

```mermaid
flowchart TB

%% ============================================================
%% STYLE DEFINITIONS
%% ============================================================

classDef world fill:#ede9fe,stroke:#6d28d9,stroke-width:3px,color:#111827;
classDef region fill:#dbeafe,stroke:#2563eb,stroke-width:2px,color:#111827;
classDef location fill:#fef3c7,stroke:#d97706,stroke-width:1.5px,color:#111827;
classDef sublocation fill:#fff7ed,stroke:#fb923c,stroke-width:1px,color:#111827;
classDef faction fill:#e0f2fe,stroke:#0284c7,stroke-width:1.5px,color:#111827;
classDef npc fill:#dcfce7,stroke:#16a34a,stroke-width:1.5px,color:#111827;
classDef enemy fill:#fee2e2,stroke:#dc2626,stroke-width:1.5px,color:#111827;
classDef boss fill:#fecaca,stroke:#991b1b,stroke-width:2px,color:#111827;
classDef relic fill:#fce7f3,stroke:#db2777,stroke-width:1.5px,color:#111827;
classDef rule fill:#e5e7eb,stroke:#4b5563,stroke-width:1.5px,color:#111827;
classDef gate fill:#cffafe,stroke:#0891b2,stroke-width:1.5px,color:#111827;
classDef cross fill:#f3f4f6,stroke:#6b7280,stroke-dasharray:5 5,color:#111827;

%% ============================================================
%% WORLD CORE
%% ============================================================

Realm["The Realm / Shattered Realm"]:::world
PrismaticCore["Prismatic Core<br/>pre-shattering unity"]:::world
Shattering["Huefall / Shattering<br/>Core breaks; regional laws dominate"]:::world
PrismWound["Prism Wound<br/>shattered center of the world"]:::world
Nullshade["Nullshade<br/>Colorless Core / sealed endgame region"]:::world
NullPhenomenon["Nullshade as Phenomenon<br/>intrusion / exposure / desaturation leaking outward"]:::cross
HueCoherence["Hue Coherence<br/>survivability / readability in deeper Nullshade"]:::rule
MemoryEcho["Memory Echo<br/>truth scene / diegetic replay"]:::rule
Mneme["Mneme / Memory Stability<br/>self-integrity under pressure"]:::rule

Realm --> PrismaticCore --> Shattering --> PrismWound --> Nullshade
Nullshade --> HueCoherence
Nullshade --> MemoryEcho
Nullshade --> Mneme
Nullshade -.-> NullPhenomenon

Gate_H["Huevale Prism Gate"]:::gate
Gate_V["Vireya Prism Gate"]:::gate
Gate_I["Iriseld Prism Gate"]:::gate
Gate_M["Myrrala Prism Gate"]:::gate
Gate_L["Luxeran Prism Gate"]:::gate
Gate_A["Auralith Prism Gate"]:::gate

Nullshade --> Gate_H
Nullshade --> Gate_V
Nullshade --> Gate_I
Nullshade --> Gate_M
Nullshade --> Gate_L
Nullshade --> Gate_A

%% ============================================================
%% HUEVALE
%% ============================================================

subgraph HUEVALE["HUEVALE — Verdant Frontier"]
direction TB

H_Region["Huevale<br/>growth / living memory / adaptive vegetation"]:::region
H_Rule["Rule: vegetation regrows and reacts<br/>paths open or close based on magic, intent, reverence"]:::rule

H_Tinctara["Tinctara<br/>living archive-city"]:::location
H_TinctaraArchives["Tinctara Archives<br/>ceramic memory / grown records"]:::sublocation
H_FloodedVaults["Flooded Archive Vaults"]:::sublocation
H_MemorialGroves["Memorial Groves"]:::sublocation
H_MalachiteGrove["Malachite Grove<br/>dream-poison / prophecy / harmonic-root zone"]:::location
H_SaprootShrine["Saproot Shrine<br/>curse / decay / root cult threshold"]:::location
H_VerdantSpiral["Verdant Spiral<br/>moth-witch / spiral growth / boss arena"]:::location
H_Sporeveil["Sporeveil Hollow"]:::sublocation
H_Mycelial["Mycelial Sanctum"]:::sublocation
H_RootSanctuaries["Root Sanctuaries"]:::sublocation
H_ShrineGardens["Shrine Gardens / Sacred Flower Beds"]:::sublocation
H_DeepGroves["Deep Groves"]:::sublocation
H_MarshRuins["Marsh Ruins / Drowned Monasteries"]:::sublocation

H_VerdantOrder["Verdant Order<br/>druids / alchemists / balance"]:::faction
H_ArchivistsCeladon["Archivists of Celadon<br/>spell-record / ceramic memory"]:::faction
H_RootboundOrders["Rootbound Orders<br/>sacred groves / oath-grown boundaries"]:::faction
H_Thornward["Thornward Circle<br/>defensive grove alliance"]:::faction
H_Sapbound["Sapbound Covenant<br/>swamp cult / earth-blood color doctrine"]:::faction
H_Rootwake["Rootwake Communion<br/>ancient plants / fungal minds"]:::faction
H_Mycofen["The Mycofen<br/>spore cult"]:::faction

H_CeladonArchivist["Celadon Archivist"]:::npc
H_ViridianAlchemist["Viridian Alchemist"]:::npc
H_MalachiteOracle["Malachite Oracle"]:::npc
H_XanaduWarden["Xanadu Warden"]:::npc
H_LimerickDruid["Limerick Druid"]:::npc
H_SkobeloffDiver["Skobeloff Diver"]:::npc
H_SmaragdineKnight["Smaragdine Knight"]:::npc
H_ChartreuseInitiate["Chartreuse Initiate"]:::npc
H_FeldgrauVeteran["Feldgrau Veteran"]:::npc
H_HarlequinTrickblade["Harlequin Trickblade"]:::npc
H_SaprootCultist["Saproot Cultist"]:::npc
H_Thalera["Thalera the Rootborn"]:::npc

H_CeladonShards["Celadon Shards<br/>record spell images"]:::relic
H_ViridianInk["Viridian Ink<br/>permanent enchanted glyphs"]:::relic
H_MalachiteFang["Malachite Fang<br/>poison / transformation / dream weapon"]:::relic
H_XanaduStone["Xanadu Stone<br/>moonlight visions"]:::relic
H_LimerickFlute["Limerick Flute<br/>summons forest spirits / charm bypass"]:::relic
H_SkobeloffLens["Skobeloff Lens<br/>reveals illusions / traps"]:::relic
H_SmaragdineCirclet["Smaragdine Circlet<br/>nature attunement / calm beasts"]:::relic
H_ChartreuseTonic["Chartreuse Tonic<br/>stamina restoration"]:::relic
H_FeldgrauCloak["Feldgrau Cloak<br/>stealth in forests and ruins"]:::relic
H_HarlequinMask["Harlequin Mask<br/>mimic voices / dodge fate"]:::relic
H_SaprootIdol["Saproot Idol<br/>protects from decay / curses"]:::relic

H_SapbornStalker["Sapborn Stalker<br/>root-burrow ambusher"]:::enemy
H_BoglightMimic["Boglight Mimic<br/>lure-light predator"]:::enemy
H_VerdantMaw["Verdant Maw<br/>flower predator"]:::enemy
H_Sporekin["Sporekin<br/>spore / confusion hazard"]:::enemy
H_Thornwrithe["Thornwrithe Beast<br/>bramble predator"]:::enemy
H_LimerootTrickster["Limeroot Trickster<br/>plantlife misdirection"]:::enemy
H_ChartreuseHusk["Chartreuse Husk<br/>alchemical corruption"]:::enemy
H_GroveboundSentinel["Grovebound Sentinel<br/>shrine / archive guardian"]:::enemy
H_FangbloomWyrm["Fangbloom Wyrm<br/>hidden flower-bed constrictor"]:::enemy
H_MossgraveRevenant["Mossgrave Revenant<br/>dream-poison knight specter"]:::enemy
H_MothWitch["Moth-Witch of the Verdant Spiral<br/>boss / mini-boss"]:::boss
H_HueLeeches["Hue Leeches<br/>Color Charge / memory drain"]:::enemy

H_Region --> H_Rule
H_Region --> H_Tinctara
H_Tinctara --> H_TinctaraArchives
H_Tinctara --> H_FloodedVaults
H_Tinctara --> H_MemorialGroves
H_Region --> H_MalachiteGrove
H_Region --> H_SaprootShrine
H_Region --> H_VerdantSpiral
H_Region --> H_Sporeveil
H_Region --> H_Mycelial
H_Region --> H_RootSanctuaries
H_Region --> H_ShrineGardens
H_Region --> H_DeepGroves
H_Region --> H_MarshRuins
H_Region --> Gate_H

H_Region --> H_VerdantOrder
H_VerdantOrder --> H_RootboundOrders
H_VerdantOrder --> H_ArchivistsCeladon
H_VerdantOrder --> H_Thornward
H_VerdantOrder --> H_Sapbound
H_VerdantOrder --> H_Rootwake
H_VerdantOrder --> H_Mycofen

H_ArchivistsCeladon --> H_CeladonArchivist --> H_CeladonShards
H_CeladonArchivist --> H_TinctaraArchives
H_ViridianAlchemist --> H_ViridianInk
H_ViridianAlchemist --> H_Tinctara
H_MalachiteOracle --> H_MalachiteFang
H_MalachiteOracle --> H_MalachiteGrove
H_XanaduWarden --> H_XanaduStone
H_XanaduWarden --> H_DeepGroves
H_LimerickDruid --> H_LimerickFlute
H_LimerickDruid --> H_RootSanctuaries
H_SkobeloffDiver --> H_SkobeloffLens
H_SkobeloffDiver --> H_FloodedVaults
H_SmaragdineKnight --> H_SmaragdineCirclet
H_SmaragdineKnight --> H_ShrineGardens
H_ChartreuseInitiate --> H_ChartreuseTonic
H_ChartreuseInitiate --> H_Tinctara
H_FeldgrauVeteran --> H_FeldgrauCloak
H_FeldgrauVeteran --> H_MarshRuins
H_HarlequinTrickblade --> H_HarlequinMask
H_HarlequinTrickblade --> H_DeepGroves
H_SaprootCultist --> H_SaprootIdol
H_SaprootCultist --> H_SaprootShrine
H_Thalera --> H_RootSanctuaries
H_Thalera --> Gate_H

H_Sporeveil --> H_Sporekin
H_Sporeveil --> H_BoglightMimic
H_Mycelial --> H_Sporekin
H_RootSanctuaries --> H_SapbornStalker
H_RootSanctuaries --> H_GroveboundSentinel
H_ShrineGardens --> H_VerdantMaw
H_ShrineGardens --> H_FangbloomWyrm
H_MalachiteGrove --> H_MossgraveRevenant
H_MalachiteGrove --> H_MothWitch
H_VerdantSpiral --> H_MothWitch
H_MarshRuins --> H_BoglightMimic
H_MarshRuins --> H_ChartreuseHusk
H_DeepGroves --> H_LimerootTrickster
H_DeepGroves --> H_Thornwrithe
H_TinctaraArchives --> H_GroveboundSentinel
H_TinctaraArchives --> H_HueLeeches

H_SkobeloffLens -. "reveals" .-> H_FangbloomWyrm
H_SkobeloffLens -. "detects" .-> H_BoglightMimic
H_LimerickFlute -. "charm / bypass" .-> H_VerdantMaw
H_SmaragdineCirclet -. "calms beasts" .-> H_Thornwrithe
H_SaprootIdol -. "resists decay" .-> H_ChartreuseHusk
H_CeladonShards -. "records spells / memory" .-> MemoryEcho

end

%% ============================================================
%% VIREYA
%% ============================================================

subgraph VIREYA["VIREYA — Ember Expanse"]
direction TB

V_Region["Vireya<br/>war-memory / heat / oath / blood"]:::region
V_Rule["Rule: heat, blood, and battle awaken dormant forces"]:::rule

V_CrimsonBastion["Crimson Bastion<br/>fortress-city / martial heart"]:::location
V_DuelPit["Duelist's Pit"]:::location
V_FoxMirage["Fox Mirage<br/>illusion-haunted volcanic valley"]:::location
V_Scoria["Scoria's Throne"]:::sublocation
V_Crucible["Crucible Spires"]:::sublocation
V_Emberglass["Emberglass Forge"]:::sublocation
V_TrialPits["Trial Pits"]:::sublocation
V_BannerRoads["Banner Roads / Shattered Battlements"]:::sublocation
V_Amaroth["Amaroth Vale<br/>martyr-heroes buried and rising"]:::sublocation
V_GlassedCraters["Glassed Craters / Obsidian Fields"]:::sublocation
V_AltarFields["Altar-Fields / Oath Shrines"]:::sublocation

V_CrimsonOrder["Crimson Order<br/>action / sacrifice / fury / courage"]:::faction
V_BannerHouses["Banner Houses"]:::faction
V_RebelCircles["Rebel Circles"]:::faction
V_Embersaints["Embersaints / Flame-Priests"]:::faction
V_DuelLineages["Duel Lineages"]:::faction
V_BloodrootCult["Blood-root / Martyr Cult Remnants"]:::faction

V_VermilionDuelist["Vermilion Duelist"]:::npc
V_Amaranth["Amaranth the Undying"]:::npc
V_Alizarin["Alizarin the Crimson Weaver"]:::npc
V_Nacarat["Nacarat the Fox"]:::npc
V_Falu["Falu Homesteader"]:::npc
V_Coquelicot["Coquelicot Banner"]:::npc
V_CinnabarMaskNPC["Cinnabar Mask"]:::npc
V_SanguineQuartermaster["Sanguine Quartermaster"]:::npc
V_RustbannerChild["Rustbanner Child"]:::npc

V_CinnabarSeal["Cinnabar Seal<br/>symbolic binding / trickster counter"]:::relic
V_SanguineLedger["Sanguine Ledger<br/>blood debts / burial obligations"]:::relic
V_CoquelicotStandard["Coquelicot Standard<br/>banner memory"]:::relic
V_VermilionBlade["Vermilion Duel Blade<br/>duel lineage token"]:::relic
V_NacaratToken["Nacarat Token<br/>fox-mirage clue"]:::relic

V_Ashwrought["Ashwrought Colossus<br/>molten siege construct"]:::enemy
V_CrimsonEcho["Crimson Echo<br/>duel-loop ghost"]:::enemy
V_LavaBehemot["Lava-Fused Behemot"]:::enemy
V_GlasslashSerpent["Glasslash Serpent<br/>volcanic betrayal glass"]:::enemy
V_Bannerbound["Bannerbound Revenant<br/>standard-tethered revenant"]:::enemy
V_Searblood["Searblood Cultist"]:::enemy
V_FuneralDancer["Funeral Dancer<br/>ritual death combat"]:::enemy
V_BloodrootEffigy["Bloodroot Effigy<br/>martyr-bone golem"]:::enemy
V_RedWidow["Red Widow"]:::enemy
V_Wickerborn["Wickerborn<br/>pyre effigy"]:::enemy
V_TyrianEcho["Tyrian Echo<br/>mixed-hue war echo"]:::enemy
V_RustwornJudge["Rustworn Judge<br/>old verdict / execution memory"]:::enemy

V_Region --> V_Rule
V_Region --> V_CrimsonBastion
V_Region --> V_DuelPit
V_Region --> V_FoxMirage
V_Region --> V_Scoria
V_Region --> V_Crucible
V_Region --> V_Emberglass
V_Region --> V_TrialPits
V_Region --> V_BannerRoads
V_Region --> V_Amaroth
V_Region --> V_GlassedCraters
V_Region --> V_AltarFields
V_Region --> Gate_V

V_Region --> V_CrimsonOrder
V_CrimsonOrder --> V_BannerHouses
V_CrimsonOrder --> V_RebelCircles
V_CrimsonOrder --> V_Embersaints
V_CrimsonOrder --> V_DuelLineages
V_CrimsonOrder --> V_BloodrootCult

V_DuelLineages --> V_VermilionDuelist --> V_VermilionBlade
V_VermilionDuelist --> V_DuelPit
V_BannerHouses --> V_Coquelicot --> V_CoquelicotStandard
V_Coquelicot --> V_BannerRoads
V_BloodrootCult --> V_Amaranth
V_Amaranth --> V_Amaroth
V_Alizarin --> V_CrimsonBastion
V_Nacarat --> V_NacaratToken
V_Nacarat --> V_FoxMirage
V_Falu --> V_BannerRoads
V_CinnabarMaskNPC --> V_CinnabarSeal
V_CinnabarMaskNPC --> V_AltarFields
V_SanguineQuartermaster --> V_SanguineLedger
V_SanguineQuartermaster --> V_CrimsonBastion
V_RustbannerChild --> V_BannerRoads

V_Crucible --> V_Ashwrought
V_Crucible --> V_LavaBehemot
V_Emberglass --> V_GlasslashSerpent
V_GlassedCraters --> V_GlasslashSerpent
V_DuelPit --> V_CrimsonEcho
V_DuelPit --> V_FuneralDancer
V_BannerRoads --> V_Bannerbound
V_BannerRoads --> V_RedWidow
V_BannerRoads --> V_Wickerborn
V_AltarFields --> V_Searblood
V_AltarFields --> V_BloodrootEffigy
V_Amaroth --> V_BloodrootEffigy
V_CrimsonBastion --> V_RustwornJudge
V_BannerRoads --> V_TyrianEcho

V_CinnabarSeal -. "binds / exposes" .-> V_Nacarat
V_CinnabarSeal -. "counters trickster logic" .-> V_GlasslashSerpent
V_SanguineLedger -. "reveals unpaid blood" .-> V_Bannerbound
V_SanguineLedger -. "reveals burial debt" .-> V_CrimsonEcho
V_CoquelicotStandard -. "anchors" .-> V_Bannerbound
V_Rule -. "combat awakens" .-> V_CrimsonEcho
V_Rule -. "blood wakes" .-> V_BloodrootEffigy

end

%% ============================================================
%% IRISELD
%% ============================================================

subgraph IRISELD["IRISELD — Tidespire Reach"]
direction TB

I_Region["Iriseld<br/>storm-memory / sound / reflection / grief"]:::region
I_Rule["Rule: wind and gravity alter access; memory rides weather"]:::rule

I_Zaffran["Zaffran Port<br/>harbor / glasswright culture"]:::location
I_WhisperingBay["Whispering Bay<br/>drowned pages / sea-memory"]:::location
I_Skyglass["Skyglass Pillars<br/>vertical traversal / storm glass"]:::location
I_Mirrorwake["The Mirrorwake<br/>reflective duel / grief exposure"]:::location
I_Tidemirror["Tidemirror Reach"]:::sublocation
I_Shipwake["Shipwake Cross"]:::sublocation
I_Glassmoor["Glassmoor Caverns"]:::sublocation
I_Moonwake["Moonwake Docks"]:::sublocation
I_Glasvale["Glasvale<br/>glass valley where winds whisper truths"]:::sublocation
I_Stormirth["Stormirth<br/>weather genesis / observatory"]:::sublocation
I_FloatingCliffs["Floating Cliffs / Sky Islands"]:::sublocation

I_CobaltOrder["Cobalt Order<br/>clarity / memory / storm logic"]:::faction
I_Glasswrights["Glasswrights"]:::faction
I_Skydancers["Skydancers"]:::faction
I_StormSeers["Storm Seers"]:::faction
I_ReflectiveExiles["Reflective Exiles"]:::faction

I_ZaffreGlasswright["Zaffre Glasswright"]:::npc
I_CeruleanSkydancer["Cerulean Skydancer"]:::npc
I_GlaucousWing["Glaucous Wing"]:::npc
I_PaynesShade["Payne's Shade"]:::npc
I_Eigengrau["Eigengrau the Unseeing"]:::npc

I_ZaffreVial["Zaffre Vial<br/>banish memory-water / reveal hidden passage"]:::relic
I_CeruleanCloak["Cerulean Cloak<br/>storm / aerial survival"]:::relic
I_PaynesBrush["Payne's Brush<br/>forces invisible/reflected targets into legibility"]:::relic
I_GlaucousFeather["Glaucous Feather<br/>aerial passage / wing-sign"]:::relic
I_EigengrauBlindfold["Eigengrau Blindfold<br/>truth through unseeing"]:::relic

I_GlassborneEcho["Glassborne Echo<br/>mirrors movement with delay"]:::enemy
I_SkycallWraith["Skycall Wraith<br/>glide denial / aerial shriek"]:::enemy
I_StormwritHound["Stormwrit Hound<br/>lightning traversal hunter"]:::enemy
I_TidewornApostle["Tideworn Apostle<br/>drowned knowledge / ink storm"]:::enemy
I_MirrorwakeDuelist["Mirrorwake Duelist<br/>reflective combat logic"]:::enemy
I_FeatheredNull["Feathered Null<br/>Nullshade-tainted aerial form"]:::enemy
I_AbyssalCurrent["Abyssal Current<br/>submerged force / undertow"]:::enemy
I_TempestMarionette["Tempest Marionette<br/>storm puppet / movement disruption"]:::enemy
I_Sorrowwing["Sorrowwing<br/>grief / aerial predator"]:::enemy

I_Region --> I_Rule
I_Region --> I_Zaffran
I_Region --> I_WhisperingBay
I_Region --> I_Skyglass
I_Region --> I_Mirrorwake
I_Region --> I_Tidemirror
I_Region --> I_Shipwake
I_Region --> I_Glassmoor
I_Region --> I_Moonwake
I_Region --> I_Glasvale
I_Region --> I_Stormirth
I_Region --> I_FloatingCliffs
I_Region --> Gate_I

I_Region --> I_CobaltOrder
I_CobaltOrder --> I_Glasswrights
I_CobaltOrder --> I_Skydancers
I_CobaltOrder --> I_StormSeers
I_CobaltOrder --> I_ReflectiveExiles

I_Glasswrights --> I_ZaffreGlasswright --> I_ZaffreVial
I_ZaffreGlasswright --> I_Zaffran
I_ZaffreGlasswright --> I_Skyglass
I_Skydancers --> I_CeruleanSkydancer --> I_CeruleanCloak
I_CeruleanSkydancer --> I_Skyglass
I_CeruleanSkydancer --> I_FloatingCliffs
I_GlaucousWing --> I_GlaucousFeather
I_GlaucousWing --> I_FloatingCliffs
I_PaynesShade --> I_PaynesBrush
I_PaynesShade --> I_Mirrorwake
I_Eigengrau --> I_EigengrauBlindfold
I_Eigengrau --> I_Glasvale
I_Eigengrau --> I_Stormirth

I_Skyglass --> I_GlassborneEcho
I_Skyglass --> I_TempestMarionette
I_FloatingCliffs --> I_SkycallWraith
I_FloatingCliffs --> I_StormwritHound
I_FloatingCliffs --> I_Sorrowwing
I_WhisperingBay --> I_TidewornApostle
I_WhisperingBay --> I_AbyssalCurrent
I_Mirrorwake --> I_MirrorwakeDuelist
I_FloatingCliffs --> I_FeatheredNull

I_ZaffreVial -. "temporary answer to memory-water" .-> I_AbyssalCurrent
I_PaynesBrush -. "reveals / stabilizes" .-> I_MirrorwakeDuelist
I_PaynesBrush -. "forces legibility" .-> I_GlassborneEcho
I_CeruleanCloak -. "aerial survival" .-> I_SkycallWraith
I_Rule -. "wind alters access" .-> I_Skyglass
I_Rule -. "storm replays grief" .-> I_Sorrowwing

end

%% ============================================================
%% MYRRALA
%% ============================================================

subgraph MYRRALA["MYRRALA — Blooming Veil"]
direction TB

M_Region["Myrrala<br/>identity distortion / glamour / dream logic"]:::region
M_Rule["Rule: loadout changes the landscape"]:::rule

M_LiseranShrine["Liseran Shrine<br/>healing / dream-root threshold"]:::location
M_ThulianCourt["Thulian Court<br/>glamour / public self / court authority"]:::location
M_Veilgrove["Veilgrove<br/>dream garden / glamour ecology"]:::location
M_Dreamroot["Dreamroot Loom<br/>authored magic / woven identity"]:::sublocation
M_ThulianGate["Thulian Gate<br/>truth gate / vow threshold"]:::sublocation
M_BloomingMirror["Blooming Mirror"]:::sublocation
M_WovenSteps["Woven Memory Steps"]:::sublocation
M_ThulianGrove["Thulian Grove"]:::sublocation
M_Heliobloom["Heliobloom<br/>prophetic twilight flowers"]:::sublocation
M_LiseranHollow["Liseran Hollow"]:::sublocation
M_PetalLabyrinth["The Petal Labyrinth"]:::sublocation

M_VioletOrder["Violet Order / Thulian Court<br/>identity / glamour / dream authorship"]:::faction
M_ThulianCourtFaction["Thulian Court Faction"]:::faction
M_LiseranCaretakers["Liseran Caretakers"]:::faction
M_Dreamweavers["Dreamroot Weavers"]:::faction
M_Performers["Fandango / Razzmatazz Performers"]:::faction

M_LiseranCaretaker["Liseran Caretaker"]:::npc
M_ThulianEmissary["Thulian Emissary"]:::npc
M_FandangoDuelstar["Fandango Duelstar"]:::npc
M_RazzmatazzSprite["Razzmatazz Sprite"]:::npc
M_PeriwinkleSiren["Periwinkle Siren"]:::npc
M_QuinacridoneBlade["Quinacridone Blade"]:::npc
M_HeliotropeDevotee["Heliotrope Devotee"]:::npc
M_WisteriaEnchantress["Wisteria Enchantress"]:::npc
M_MauveineSpark["Mauveine Spark"]:::npc
M_PompChancellor["Pomp & Power Chancellor"]:::npc

M_LiseranLily["Liseran Lily<br/>healing aura on break"]:::relic
M_ThulianMirror["Thulian Mirror<br/>truth, but incompletely"]:::relic
M_FandangoDagger["Fandango Dagger<br/>duel-linked singing blade"]:::relic
M_RazzmatazzDrum["Razzmatazz Drum<br/>awakens slumbering artifacts"]:::relic
M_QuinacridoneCodex["Quinacridone Codex<br/>battle-paint / authored magic"]:::relic
M_PompMantle["Pomp and Power Mantle<br/>temporary command over nobles / weak minds"]:::relic

M_Doppelshade["Doppelshade<br/>player clone / input prediction"]:::enemy
M_LilybornMirage["Lilyborn Mirage<br/>lily-mist memory loop"]:::enemy
M_BloomveilWidow["Bloomveil Widow<br/>glamour predator"]:::enemy
M_GlitteringGrimoire["Glittering Grimoire<br/>spell-history mimicry"]:::enemy
M_ChronopollenSprite["Chronopollen Sprite<br/>time-pollen distortion"]:::enemy
M_FandancerFragment["Fandancer Fragment<br/>rhythm / performance enemy"]:::enemy
M_VeilshiftMatron["Veilshift Matron<br/>identity boss"]:::boss
M_ThulianVowkeep["Thulian Vowkeep<br/>promise / vow logic"]:::enemy
M_RazzflareImp["Razzflare Imp<br/>unstable artifact trickster"]:::enemy

M_Region --> M_Rule
M_Region --> M_LiseranShrine
M_Region --> M_ThulianCourt
M_Region --> M_Veilgrove
M_Region --> M_Dreamroot
M_Region --> M_ThulianGate
M_Region --> M_BloomingMirror
M_Region --> M_WovenSteps
M_Region --> M_ThulianGrove
M_Region --> M_Heliobloom
M_Region --> M_LiseranHollow
M_Region --> M_PetalLabyrinth
M_Region --> Gate_M

M_Region --> M_VioletOrder
M_VioletOrder --> M_ThulianCourtFaction
M_VioletOrder --> M_LiseranCaretakers
M_VioletOrder --> M_Dreamweavers
M_VioletOrder --> M_Performers

M_LiseranCaretakers --> M_LiseranCaretaker --> M_LiseranLily
M_LiseranCaretaker --> M_LiseranShrine
M_LiseranCaretaker --> M_LiseranHollow

M_ThulianCourtFaction --> M_ThulianEmissary --> M_ThulianMirror
M_ThulianEmissary --> M_ThulianCourt
M_ThulianEmissary --> M_ThulianGate

M_Performers --> M_FandangoDuelstar --> M_FandangoDagger
M_FandangoDuelstar --> M_ThulianCourt
M_Performers --> M_RazzmatazzSprite --> M_RazzmatazzDrum
M_RazzmatazzSprite --> M_Dreamroot
M_RazzmatazzSprite --> M_Veilgrove

M_PeriwinkleSiren --> M_LiseranShrine
M_QuinacridoneBlade --> M_QuinacridoneCodex
M_QuinacridoneBlade --> M_Dreamroot
M_HeliotropeDevotee --> M_Heliobloom
M_WisteriaEnchantress --> M_Veilgrove
M_MauveineSpark --> M_Dreamroot
M_PompChancellor --> M_PompMantle
M_PompChancellor --> M_ThulianCourt

M_ThulianCourt --> M_Doppelshade
M_LiseranShrine --> M_LilybornMirage
M_Veilgrove --> M_BloomveilWidow
M_Dreamroot --> M_GlitteringGrimoire
M_Heliobloom --> M_ChronopollenSprite
M_ThulianCourt --> M_FandancerFragment
M_Veilgrove --> M_VeilshiftMatron
M_ThulianGate --> M_ThulianVowkeep
M_Dreamroot --> M_RazzflareImp

M_ThulianMirror -. "reveals incomplete truth" .-> M_Doppelshade
M_ThulianMirror -. "glamour break" .-> M_VeilshiftMatron
M_RazzmatazzDrum -. "rhythm / artifact awakening" .-> M_GlitteringGrimoire
M_RazzmatazzDrum -. "rhythm counter" .-> M_FandancerFragment
M_QuinacridoneCodex -. "authored magic" .-> M_GlitteringGrimoire
M_PompMantle -. "command logic" .-> M_ThulianVowkeep
M_Rule -. "loadout changes routes" .-> M_PetalLabyrinth
M_Rule -. "identity pressure" .-> M_Doppelshade

end

%% ============================================================
%% LUXERAN
%% ============================================================

subgraph LUXERAN["LUXERAN — Gilded Expanse"]
direction TB

L_Region["Luxeran<br/>radiance / mirage / legitimacy / judgment"]:::region
L_Rule["Rule: mirages falsify the map"]:::rule

L_Eburnea["Eburnea<br/>gilded hub / legitimacy economy"]:::location
L_GambogeVault["Gamboge Vault"]:::location
L_AureolinTemple["Aureolin Temple"]:::location
L_GildedHollow["Gilded Hollow"]:::sublocation
L_SundialTemple["Sundial Temple"]:::sublocation
L_CitrineCorridor["Citrine Corridor"]:::sublocation
L_GlassMirageVaults["Glass Mirage Vaults"]:::sublocation
L_Gildora["Gildora<br/>market city gilded in permanent light"]:::sublocation
L_Aurenza["Aurenza<br/>solar monastery"]:::sublocation
L_DuneRoads["Dune Roads / False Trade Routes"]:::sublocation

L_AurelianOrder["Aurelian Order<br/>light / trade / judgment / surface truth"]:::faction
L_EburneanPriesthood["Eburnean Priesthood"]:::faction
L_GambogeMonks["Gamboge Monks"]:::faction
L_CitrineArtisans["Citrine Artisans"]:::faction
L_DesertCouriers["Desert Couriers"]:::faction
L_SunHunters["Sun Hunters"]:::faction

L_EburneanPriestess["Eburnean Priestess"]:::npc
L_CitrineArtisan["Citrine Artisan"]:::npc
L_GambogeMonk["Gamboge Monk"]:::npc
L_FulvousHunter["Fulvous Hunter"]:::npc
L_OrangepeelCourier["Orangepeel Courier"]:::npc
L_AureolinFlame["Aureolin Flame"]:::npc

L_EburneanDice["Eburnean Dice<br/>fate-break / ritual counter"]:::relic
L_CitrineTool["Citrine Artisan Tool<br/>lightcraft / market legitimacy"]:::relic
L_GambogeCharm["Gamboge Charm<br/>vault rite / monk token"]:::relic
L_OrangepeelSatchel["Orangepeel Satchel<br/>route / courier map"]:::relic
L_AureolinFlameRelic["Aureolin Flame<br/>solar devotion / temple rite"]:::relic

L_SunburntJackal["Sunburnt Jackal<br/>heat/scent predator"]:::enemy
L_MirageRevenant["Mirage Revenant<br/>fake NPC / chest mimic"]:::enemy
L_CinnabarScarab["Cinnabar Scarab<br/>gleaming dust predator"]:::enemy
L_AmbercoilAsp["Ambercoil Asp<br/>desert coil hazard"]:::enemy
L_GambogeDjinnling["Gamboge Djinnling<br/>mirage spirit"]:::enemy
L_HollowProphet["Hollow Prophet<br/>light-judgment caster"]:::enemy
L_CitrineGolem["Citrine Golem<br/>radiant construct"]:::enemy
L_SunflareMarionette["Sunflare Marionette<br/>beam rhythm puppet"]:::enemy
L_HeliotropicLurker["Heliotropic Lurker<br/>sun-following ambusher"]:::enemy

L_Region --> L_Rule
L_Region --> L_Eburnea
L_Region --> L_GambogeVault
L_Region --> L_AureolinTemple
L_Region --> L_GildedHollow
L_Region --> L_SundialTemple
L_Region --> L_CitrineCorridor
L_Region --> L_GlassMirageVaults
L_Region --> L_Gildora
L_Region --> L_Aurenza
L_Region --> L_DuneRoads
L_Region --> Gate_L

L_Region --> L_AurelianOrder
L_AurelianOrder --> L_EburneanPriesthood
L_AurelianOrder --> L_GambogeMonks
L_AurelianOrder --> L_CitrineArtisans
L_AurelianOrder --> L_DesertCouriers
L_AurelianOrder --> L_SunHunters

L_EburneanPriesthood --> L_EburneanPriestess --> L_EburneanDice
L_EburneanPriestess --> L_Eburnea
L_EburneanPriestess --> L_AureolinTemple

L_CitrineArtisans --> L_CitrineArtisan --> L_CitrineTool
L_CitrineArtisan --> L_CitrineCorridor
L_CitrineArtisan --> L_Eburnea

L_GambogeMonks --> L_GambogeMonk --> L_GambogeCharm
L_GambogeMonk --> L_GambogeVault
L_GambogeMonk --> L_Aurenza

L_SunHunters --> L_FulvousHunter
L_FulvousHunter --> L_DuneRoads
L_DesertCouriers --> L_OrangepeelCourier --> L_OrangepeelSatchel
L_OrangepeelCourier --> L_DuneRoads
L_AureolinFlame --> L_AureolinFlameRelic
L_AureolinFlame --> L_AureolinTemple

L_DuneRoads --> L_SunburntJackal
L_GlassMirageVaults --> L_MirageRevenant
L_CitrineCorridor --> L_CinnabarScarab
L_DuneRoads --> L_AmbercoilAsp
L_GambogeVault --> L_GambogeDjinnling
L_AureolinTemple --> L_HollowProphet
L_CitrineCorridor --> L_CitrineGolem
L_SundialTemple --> L_SunflareMarionette
L_GildedHollow --> L_HeliotropicLurker

L_EburneanDice -. "fate-break / ritual counter" .-> L_HollowProphet
L_EburneanDice -. "trial counter" .-> L_MirageRevenant
L_CitrineTool -. "lightcraft stabilizes" .-> L_CitrineGolem
L_GambogeCharm -. "vault rite" .-> L_GambogeDjinnling
L_Rule -. "false map" .-> L_MirageRevenant
L_Rule -. "visibility hazard" .-> L_SunburntJackal

end

%% ============================================================
%% AURALITH
%% ============================================================

subgraph AURALITH["AURALITH — Dimming Hollow"]
direction TB

A_Region["Auralith<br/>residue / ruin / soul-binding / fossil memory"]:::region
A_Rule["Rule: player action leaves ghosts behind"]:::rule

A_MortuumHold["Mortuum Hold"]:::location
A_IsabellineCatacombs["Isabelline Catacombs"]:::location
A_PhylacteryVault["Phylactery Vault"]:::location
A_RustcladArchive["Rustclad Archive"]:::sublocation
A_GolmFields["Golm Burial Fields"]:::sublocation
A_Dustmere["Dustmere<br/>dead lake / sunken memory vault"]:::sublocation
A_FossilLabs["Fossilized Alchemical Labs"]:::sublocation
A_Soulfields["Soulfields"]:::sublocation
A_AshPlains["Ash Plains"]:::sublocation

A_EarthenOrder["Earthen Order<br/>transmutation / endings / residue"]:::faction
A_MortumicCircle["Mortumic Circle<br/>death refined, not prevented"]:::faction
A_Ochranthium["The Ochranthium<br/>truth in clay / dust / amber"]:::faction
A_BoundFlame["Order of the Bound Flame<br/>fire as memory"]:::faction
A_TenebricScribes["Tenebric Scribes<br/>chronicle erased things"]:::faction

A_CaputAscetic["Caput Mortuum Ascetic"]:::npc
A_BistreArchivist["Bistre Archivist"]:::npc
A_IsabellineWidow["Isabelline Widow"]:::npc
A_BurntSiennaSculptor["Burnt Sienna Sculptor"]:::npc
A_MikadoWarlord["Mikado Warlord"]:::npc

A_CaputPhylactery["Caput Mortuum Phylactery<br/>stabilizes death-adjacent states"]:::relic
A_BistreLantern["Bistre Lantern<br/>reveals prior events / residue entities"]:::relic
A_IsabellineVeil["Isabelline Veil<br/>mourning / catacomb rite"]:::relic
A_SiennaChisel["Burnt Sienna Chisel<br/>fossil memory sculpting"]:::relic
A_MikadoSeal["Mikado Seal<br/>old authority / ruin command"]:::relic

A_MemoryHusk["Memory Husk<br/>past-self shell"]:::enemy
A_SootshadeCollector["Sootshade Collector<br/>ash-and-parchment trauma fog"]:::enemy
A_AlchemicalEcho["Alchemical Echo<br/>failed alchemy residue"]:::enemy
A_WickbornLantern["Wickborn Lantern<br/>soulfield guide-or-threat"]:::enemy
A_OchreGolem["Ochre Golem<br/>fossilized memory-ore guardian"]:::enemy
A_CaputMarionette["Caput Marionette<br/>death puppet"]:::enemy
A_RustwornJudge_A["Rustworn Judge<br/>old verdict / ruin judgment"]:::enemy
A_TapestryWatcher["Tapestry Watcher<br/>prior-truth overwrite entity"]:::enemy

A_Region --> A_Rule
A_Region --> A_MortuumHold
A_Region --> A_IsabellineCatacombs
A_Region --> A_PhylacteryVault
A_Region --> A_RustcladArchive
A_Region --> A_GolmFields
A_Region --> A_Dustmere
A_Region --> A_FossilLabs
A_Region --> A_Soulfields
A_Region --> A_AshPlains
A_Region --> Gate_A

A_Region --> A_EarthenOrder
A_EarthenOrder --> A_MortumicCircle
A_EarthenOrder --> A_Ochranthium
A_EarthenOrder --> A_BoundFlame
A_EarthenOrder --> A_TenebricScribes

A_MortumicCircle --> A_CaputAscetic --> A_CaputPhylactery
A_CaputAscetic --> A_MortuumHold
A_CaputAscetic --> A_PhylacteryVault
A_Ochranthium --> A_BistreArchivist --> A_BistreLantern
A_BistreArchivist --> A_RustcladArchive
A_IsabellineWidow --> A_IsabellineVeil
A_IsabellineWidow --> A_IsabellineCatacombs
A_BurntSiennaSculptor --> A_SiennaChisel
A_BurntSiennaSculptor --> A_FossilLabs
A_MikadoWarlord --> A_MikadoSeal
A_MikadoWarlord --> A_MortuumHold
A_MikadoWarlord --> A_GolmFields

A_RustcladArchive --> A_MemoryHusk
A_AshPlains --> A_SootshadeCollector
A_FossilLabs --> A_AlchemicalEcho
A_Soulfields --> A_WickbornLantern
A_GolmFields --> A_OchreGolem
A_PhylacteryVault --> A_CaputMarionette
A_MortuumHold --> A_RustwornJudge_A
A_RustcladArchive --> A_TapestryWatcher
A_Dustmere --> A_MemoryHusk

A_BistreLantern -. "reveals prior events" .-> A_SootshadeCollector
A_BistreLantern -. "reveals residue entity" .-> A_MemoryHusk
A_CaputPhylactery -. "stabilizes death state" .-> A_CaputMarionette
A_CaputPhylactery -. "alchemical stabilization" .-> A_AlchemicalEcho
A_SiennaChisel -. "fossil memory manipulation" .-> A_OchreGolem
A_Rule -. "actions leave ghosts" .-> A_MemoryHusk
A_Rule -. "guilt mechanics" .-> A_TapestryWatcher

end

%% ============================================================
%% NULLSHADE
%% ============================================================

subgraph NULLSHADE_GRAPH["NULLSHADE — Colorless Core / Prism Wound"]
direction TB

N_Region["Nullshade<br/>absence / contradiction / return"]:::region
N_Rule["Rule: truth is spatially and mnemonically sealed"]:::rule
N_HueCoherenceReq["Requires Hue Coherence<br/>otherwise player zeros out / becomes Bound"]:::rule

N_PrismWound["Prism Wound<br/>true center / birthplace / wound"]:::location
N_NullRuins["Nullshade Ruins"]:::location
N_Shatterglass["Shatterglass Pools"]:::location
N_Monoliths["Collapsed Monoliths"]:::sublocation
N_BoundGrove["The Bound / Bound Grove"]:::location
N_MemoryGates["Memory Gate Circles"]:::location
N_SilenceZones["Silence Zones / Absence Fields"]:::sublocation
N_BrokenGeometry["Broken Geometry / Slow-Time Tiles / Void Ravines"]:::sublocation

N_OrderMask["The Mask<br/>Order-imposed sealed story"]:::faction
N_Prismara["Prismara / Primal Harmony Remnants"]:::faction
N_BoundWitnesses["The Bound<br/>witnesses frozen by Mask or failed coherence"]:::faction
N_WoundImmune["Wound Immune Responses"]:::faction

N_PrismUnform["Prism Unform<br/>glitching spectral hue-shifter"]:::enemy
N_TheBound["The Bound<br/>awakened stone figures"]:::enemy
N_NullshadeEcho["Nullshade Echo<br/>reflection without mercy"]:::enemy
N_NullRoot["Null-Root<br/>failed void-growth"]:::enemy
N_SilenceIncarnate["Silence Incarnate<br/>unblinking judgment"]:::boss
N_FractalShardling["Fractal Shardling<br/>broken geometry shard"]:::enemy
N_WoundRemnant["Wound Remnant<br/>shattering residue"]:::enemy
N_NullshadeRevenant["Nullshade Revenant"]:::enemy
N_UnhuedChoir["The Unhued Choir<br/>song that removes color"]:::enemy
N_SeventhHue["The Seventh Hue<br/>optional mythic contradiction"]:::boss
N_ColorlessShape["The Colorless Shape<br/>distorted build / loadout mirror"]:::boss
N_MemoryLeech["Memory Leech<br/>HUD / control parasite"]:::enemy
N_TapestryNull["Tapestry Watcher — Nullshade Variant<br/>prior-truth fracture"]:::enemy
N_SpectralHarvester["Spectral Harvester"]:::enemy
N_MemoryGrafter["Memory Grafter"]:::enemy
N_NullbornHusks["Nullborn Husks<br/>early intrusion immune responses"]:::enemy

N_Region --> N_Rule
N_Region --> N_HueCoherenceReq
N_Region --> N_PrismWound
N_Region --> N_NullRuins
N_Region --> N_Shatterglass
N_Region --> N_Monoliths
N_Region --> N_BoundGrove
N_Region --> N_MemoryGates
N_Region --> N_SilenceZones
N_Region --> N_BrokenGeometry

N_Region --> N_OrderMask
N_Region --> N_Prismara
N_Region --> N_BoundWitnesses
N_Region --> N_WoundImmune

N_PrismWound --> N_PrismUnform
N_PrismWound --> N_WoundRemnant
N_PrismWound --> N_SeventhHue
N_PrismWound --> N_ColorlessShape
N_PrismWound --> N_MemoryGrafter

N_NullRuins --> N_NullshadeRevenant
N_NullRuins --> N_SpectralHarvester
N_Shatterglass --> N_NullshadeEcho
N_Shatterglass --> N_UnhuedChoir
N_BrokenGeometry --> N_NullRoot
N_BrokenGeometry --> N_FractalShardling
N_SilenceZones --> N_SilenceIncarnate
N_BoundGrove --> N_TheBound
N_MemoryGates --> N_MemoryLeech
N_MemoryGates --> N_TapestryNull
N_WoundImmune --> N_NullbornHusks

N_OrderMask -. "sealed story creates" .-> N_BoundWitnesses
N_BoundWitnesses -. "manifest as" .-> N_TheBound
N_Prismara -. "origin mystery" .-> PrismWound
N_HueCoherenceReq -. "gates access to" .-> N_PrismWound
N_Rule -. "memory collapse creates" .-> N_MemoryLeech
N_Rule -. "contradiction creates" .-> N_SeventhHue

end

%% ============================================================
%% GLOBAL NULLSHADE INTRUSION LINKS
%% ============================================================

NullPhenomenon -. "gray leaves / roots refuse player" .-> H_Region
NullPhenomenon -. "cold flame / insignia-less banners" .-> V_Region
NullPhenomenon -. "reflections with no source" .-> I_Region
NullPhenomenon -. "mirrors refuse reflection" .-> M_Region
NullPhenomenon -. "false legitimacy collapses" .-> L_Region
NullPhenomenon -. "shadows point nowhere / signatures erased" .-> A_Region

N_NullbornHusks -. "early intrusion encounters" .-> H_HueLeeches
N_MemoryLeech -. "memory-drain kinship" .-> H_HueLeeches
N_MemoryLeech -. "memory-heavy zone variant" .-> A_MemoryHusk
N_TapestryNull -. "Nullshade variant of" .-> A_TapestryWatcher
N_SeventhHue -. "secret contradiction thread" .-> A_TapestryWatcher
N_ColorlessShape -. "anti-self mirror" .-> M_Doppelshade
N_NullshadeEcho -. "self-reflection cousin" .-> I_GlassborneEcho
N_UnhuedChoir -. "song / unmaking parallel" .-> I_TidewornApostle
N_NullRoot -. "failed growth inversion" .-> H_VerdantMaw
N_FractalShardling -. "broken glass / shard logic" .-> I_GlassborneEcho

%% ============================================================
%% CROSS-REGION MECHANICAL / PHILOSOPHICAL LINKS
%% ============================================================

H_Rule -. "matter remembers" .-> A_Rule
A_Rule -. "residue remembers action" .-> H_Rule

I_Rule -. "reveals / stabilizes illusion" .-> M_Rule
M_Rule -. "rewrites / performs illusion" .-> I_Rule

L_Rule -. "public truth / legitimacy" .-> M_ThulianCourt
M_ThulianCourt -. "performed identity" .-> L_Eburnea

V_Rule -. "violence leaves material consequence" .-> A_Rule
A_Rule -. "consequences become ghosts" .-> V_CrimsonEcho

H_SkobeloffLens -. "reveal technology parallel" .-> I_PaynesBrush
I_PaynesBrush -. "truth through seeing" .-> M_ThulianMirror
M_ThulianMirror -. "incomplete truth" .-> L_EburneanDice
L_EburneanDice -. "fate-break trial logic" .-> A_CaputPhylactery
A_BistreLantern -. "reveals prior event" .-> MemoryEcho

V_TyrianEcho -. "Color War / mixed-hue history" .-> PrismWound
V_TyrianEcho -. "betrayal echo can surface in Huevale scenes" .-> H_Thalera
V_TyrianEcho -. "historical wound thread" .-> A_RustcladArchive

%% ============================================================
%% GATE ROUTES
%% ============================================================

H_Thalera --> Gate_H
H_RootSanctuaries --> Gate_H
V_AltarFields --> Gate_V
V_DuelPit --> Gate_V
I_Skyglass --> Gate_I
I_Mirrorwake --> Gate_I
M_ThulianGate --> Gate_M
M_PetalLabyrinth --> Gate_M
L_AureolinTemple --> Gate_L
L_GlassMirageVaults --> Gate_L
A_PhylacteryVault --> Gate_A
A_IsabellineCatacombs --> Gate_A

Gate_H --> N_MemoryGates
Gate_V --> N_MemoryGates
Gate_I --> N_MemoryGates
Gate_M --> N_MemoryGates
Gate_L --> N_MemoryGates
Gate_A --> N_MemoryGates

N_MemoryGates --> N_PrismWound
```

---

## Suggested usage

This graph is intentionally dense. For production use, split it into these files:

1. `world-core.mmd`
2. `huevale-region.mmd`
3. `vireya-region.mmd`
4. `iriseld-region.mmd`
5. `myrrala-region.mmd`
6. `luxeran-region.mmd`
7. `auralith-region.mmd`
8. `nullshade-region.mmd`
9. `cross-region-links.mmd`

The full version is useful as a master design map. The split versions are better for day-to-day writing, level design, and issue tracking.
