# Shiny Vice encounter table research and draft

**Status:** Route 101–104 land tables are drafted, and the Route 110/117 land tables now form the next midgame pass in `src/data/wild_encounters.json`. The new levels and family mix are source-validated but not yet playtested; other method tables, Petalburg Woods, campaign-wide acquisition, and boss-team review remain open.

## What the enabled roster contains

The source-backed roster inputs resolve to **733 distinct National Dex species in 346 supported enabled families**. Species distribution by generation is:

| Generation | Species |
|---|---:|
| Gen 1 | 188 |
| Gen 2 | 101 |
| Gen 3 | 141 |
| Gen 4 | 50 |
| Gen 5 | 71 |
| Gen 6 | 45 |
| Gen 7 | 39 |
| Gen 8 | 44 |
| Gen 9 | 54 |

Types are broad rather than evenly represented: Water (118 species), Grass (80), Flying (74), Normal (72), Fire (67), Poison and Psychic (66 each), Ground (62), Dragon (58), Fighting and Rock (56 each), Bug (54), Dark (53), Ghost (51), Electric (49), Steel (44), Ice (39), and Fairy (28). Counts overlap for dual types. Do not use a type count as a route quota; use it to catch omissions and over-concentration.

The roster CSV includes provisional strength and access cues, but some form-backed stats and types are blank in the flat NatDex input. Blank BST is unresolved source data, not zero strength. Resolve macro/generated stat records from `normal-roster-inputs-by-form.csv` and species source before using BST alone to decide a family’s first-access tier. Prefer the caught stage, evolution level/item, learnset, ability, and available TMs alongside power.

## How the current decomp tables work

Shiny Vice’s encounter source is `src/data/wild_encounters.json`; the map-level records are compiled into the C header data used by `src/wild_encounter.c`. Each map can have separate land, water, Rock Smash, and fishing tables. A method record has an `encounter_rate` and an ordered list of level/species slots. Fishing slots are partitioned into Old, Good, and Super Rod groups.

The slot index is weighted. In the current Shiny Vice land schema the 12 weights are `20,20,10,10,10,10,5,5,4,4,1,1`; water and Rock Smash use five slots weighted `60,30,5,4,1`. Fishing now follows Imperium’s 11-slot grouping: Old Rod `34,33,33`; Good Rod `34,33,33`; Super Rod `40,40,15,4,1`. Repeating a species in several slots increases its combined chance. The method `encounter_rate` controls the chance of triggering a wild battle; it is separate from the species’ share of slots.

`WE_VANILLA_RANDOM TRUE` in `include/config/wild_encounter.h` means encounters trigger through random steps on encounter tiles. It is not a species randomizer and does not pull from every enabled species. `WE_OW_ENCOUNTERS FALSE` leaves generated overworld encounters off by default. Enabling a species in the National Dex therefore does not create an encounter for it.

Before this draft, the early Shiny Vice land tables were largely vanilla. This pass authors mixed-roster placements on Routes 101–104; Petalburg Woods remains on its existing Hoenn list and still needs its own pass. This is why the custom roster needs a campaign-wide acquisition ledger rather than isolated route additions.

## What Imperium contributes

The public `iriv24/pokeemerald-expansion` `release` branch is a fork of `rh-hideout/pokeemerald-expansion`. Its `src/data/wild_encounters.json` uses the same map-first table model and expands the species in those map records. The useful pattern is to plan by Hoenn area and method, retaining encounter levels, slot order, and duplicate weights; there is no need for Shiny Vice to invent a new runtime encounter system for ordinary route additions.

Examples from the public Imperium table:

| Area | Imperium placement pattern | Lesson for Shiny Vice |
|---|---|---|
| Route 101 | Twelve species in level 2–5 land slots, mixing Hoenn staples with lines such as Shinx, Pidgey, Blipbug, Bunnelby, Rolycoly, Fomantis, Sewaddle, Vulpix, and Growlithe. | A small early route can introduce several generations while keeping caught levels low. Preserve rarity weights; do not make every new family equally common. |
| Route 104 | Twelve species around level 4–6, mixing Starly, Lotad, Teddiursa, Seedot, Galarian Farfetch’d, Nickit, Smoliv, Gossifleur, Galarian Ponyta, Lechonk, and others. | Related nearby routes can have distinct but overlapping habitat identities. |
| Route 110 | A level 19–23 mixture with electric lines (Plusle/Minun, Pawmi, Shinx, Toxel, Electrike) alongside Ponyta, Inkay, Fletchling, Flabébé, and Axew. | Use the route’s theme while offering varied team roles; a rare low-level pseudo line can be catchable without making its final evolution early. |
| Route 111 | Desert/rock/ground choices include Trapinch, Cacnea, Rockruff, Stunfisk, Golett, Helioptile, Klawf, Baltoy, and Orthworm. | A strong habitat identity makes broad roster inclusion feel intentional. |
| Route 119 | Twelve varied lines at level 25–27, including Capsakid, Hisuian Growlithe, Hawlucha, Durant, Combee, Stonjourner, Cutiefly, Silicobra, and Falinks. | Mid-game routes can widen type coverage and introduce stronger pre-evolutions at a new level band. |
| Route 123 | Forested route options include Toedscool, Pangoro, Turtonator, Parasect, Arboliva, Tangrowth, Roselia, Druddigon, Ribombee, Komala, and both Sliggoo forms. | Late evolution stages can be placed by habitat and access window, but must be checked against local boss caps and move availability. |
| Victory Road | The public file includes level 60–65 late-stage and rare species. | Treat its levels and legendary density as a comparison point only. Shiny Vice must check actual Emerald story access and the Champion cap; copying the table can put over-cap Pokémon in a pre-League area. |

The fishing runtime and source data now use the same 3/3/5 slot grouping as Imperium, with Imperium’s 34/33/33 weights for the first two rods. This migration added a copy of each table’s common Old Rod slot as the third Old Rod entry, preserving the existing species pool while moving its common/rare split from 70/30 to 67/33. These repeated slots are a structural bridge, not a finished fishing roster: route-by-route non-land balancing should replace them with curated species after method gates, levels, and story access are audited. Surfing and Rock Smash still need their own species-balance pass.

The public branch and supplied Imperium docs can differ by release. This review treats the `release` source branch as a structural and design reference, not proof that every row matches the latest shipped ROM. Its table is a baseline for composition, not a target to copy: Imperium’s roster, battle teams, routes, level curve, and density are not automatically balanced for Shiny Vice’s 733 curated species, shiny odds, or cap rules.

## Current Shiny Vice access evidence

The existing acquisition inventory is useful but not final availability proof:

- `acquisition-plan.csv` is an older snapshot with 811 wild map/method records and 111 distinct Hoenn-map families. The refreshed generated `wild-encounter-inventory.csv` currently reports 118 distinct Hoenn-map families and 158 across all map regions. It includes unverified story gates, so neither count means “obtainable in the campaign.”
- Script matching found 22 gift/egg/static records across 16 families; NPC conditions, repeatability, and shiny behavior still need verification.
- The 151/47/24 split is a legacy snapshot from the earlier wild/script audit. Refresh the scripted-acquisition ledger before using it as a current gap count. These figures were design/audit obligations, not evidence that those Pokémon were impossible to obtain.

## Route 110 and Route 117 pass

The second land-table pass uses the newly confirmed Lv24 milestone: Brawly's badge or completing the Oceanic Museum story event. Route 110's existing Lv12–13 land table was under-level for the Lv20 rival and Lv24 Wattson; it is now Lv18–20. Its 12 weighted slots cover Electrike, Ponyta, Shinx, Minun, Gulpin, Oddish, Pawmi, Toxel, Inkay, Wingull, Plusle, and a 1% Axew hunt. The Electric families together occupy 51% of the slots, keeping Route 110's electric identity while offering other types and a very rare pseudo line.

Route 117's existing Lv13–14 land table was similarly under-level for the next Gym. It is now Lv19–21 and places Oddish, Marill, Machop, Illumise, Volbeat, Cutiefly, Swirlix, Skitty, Dunsparce, Seedot, Eevee, and Hoppip. This area adds bug, fairy, fighting, and breeding-friendly options near the Day Care while keeping early Eevee rare (1%). Both changes preserve the standard 12-slot weight vector and leave water/fishing tables unchanged.

The Route 110/111/117 availability audit keeps their land and Old Rod pools separate from Surf, Rock Smash, and later rod tiers. Route 111 land gives the player several Ground answers before Wattson; his final team should pressure those answers with measured coverage rather than canceling Ground immunity outright. See `wattson-approach-access.csv` for every method row and its gate.
- The acquisition coverage file has one obligation per supported family, but all rows remain planning-only. Each family needs a first in-game source, and each NatDex member/evolution branch needs a same-save completion path.

### Timing and balance audit flags

The current first-access bands are useful sorting cues, not yet safe map assignments. In particular, “Opening–Roxanne” must be split by actual method access: a species present in a Route 102/103 water table is not obtainable before Surf; a fishing entry is not obtainable before the player has a rod; and an expansion map entry is not a Hoenn story path. This matters for Tentacool, Goldeen, Magikarp, Carvanha, Wailmer, and Corphish among the current early-window candidates. Route 103 is also an optional rival encounter before the Pokédex/Poké Ball handoff, so those wild slots do not expand the pre-fight party.

The 31-family “Opening–Badges 1–3” bucket also spans multiple materially different access windows. Split it into pre-Roxanne, after Roxanne/before Brawly, and later before Wattson. Likewise, a family-level maximum BST can make an early base-form line look overpowered: e.g. Slakoth is an early-stage catch while Slaking is a high-stat final form. Review catchable species, evolution level, move access, and cap together; do not assign rarity solely from the maximum BST of the whole family.

## Draft campaign layout

This is the initial shape for the encounter table. The bands follow Emerald’s Hoenn campaign, not a region-selection mode. Exact reachable flags, side paths, and field-move gates must be checked before a row is considered available.

| Story band | Candidate Hoenn maps/methods | Encounter role and balancing direction |
|---|---|---|
| Opening to Roxanne | Routes 101–104, Petalburg Woods; land first, with only methods actually usable at that point | Keep the Route 103 rival fight’s starter-only envelope intact. After Poké Balls are received, spread early base forms across grass/forest/road habitats. Offer more than one useful answer to Roxanne, but avoid placing multiple early final forms or requiring a rare slot as the only counter. |
| Roxanne to Brawly/Wattson | Route 116, Rusturf Tunnel, Granite Cave, Routes 109–110 and nearby accessible water/fishing | Add cave rock/ground/fighting/steel lines and coastal/water/electric options as each map opens. Keep cave and water methods separate; do not count Surf/Rod access before it exists. |
| Mauville to Lavaridge/Fallarbor | Routes 111–115, desert, Fiery Path, Route 112, Route 113/114, and accessible cave maps | Give the desert and volcanic areas clear ground/rock/fire themes. Use common slots for suitable basic forms and low-weight slots for rare or unusually strong lines. Check Devon/Magma/Aqua story gates and the Badge 3–4 bosses. |
| Petalburg/Fortree approach | Routes 117–120, Route 118/119/120, Weather Institute and relevant forest/river maps | Broaden grass, bug, poison, flying, electric, and water choices. Place strong lines as catchable pre-evolutions when their evolution timing keeps the power curve fair. |
| Fortree to Sootopolis | Routes 121–123, Mt. Pyre, Lilycove/Mossdeep coasts, Shoal Cave, underwater routes | Use forest, coast, cave, ice, and deep-water identities. Gate methods and areas to Surf/Dive/story progression. Reserve rare powerful species for low-weight slots or scripted hunts, not a large flat pool. |
| Sootopolis to League | Seafloor Cavern, Sky Pillar, Victory Road, Ever Grande and remaining story maps | Complete late families, dragons, pseudo-legendaries, and high-power lines through a mix of pre-evolution catches and late stages. Keep wild levels inside the active badge cap unless a deliberately optional/postgame source is intended. |
| Postgame and special acquisitions | Battle Frontier/optional areas, repeatable statics, gifts, eggs, fossils, shops, trades with in-game alternatives, and quests | Finish all remaining families/forms and starter lines not selected at New Game. Protect shiny-hunt routes: a one-time shiny-locked static should not be the only way to get a family. Battle facilities or Expansion-only maps do not count as campaign access by themselves. |

### Slot-density draft

Use the existing 12 land slots as weighted positions, not a mandate for 12 different families on every route. For a typical route, start with roughly 8–10 distinct families, use duplicate slots for the intended common encounters, and reserve the 1% positions for intentionally rare hunts. Small/early routes can use fewer distinct families; major mid/late routes can use more if their encounter identity and player access support it. Review each line’s total share across nearby maps so that “available” does not mean prohibitively rare to shunt.

For each row in the eventual authored table, retain: map, method, species/form, level range, slot weight, story gate, repeatability, and source evidence. Add a derived audit view for each family showing first access, later alternate hunt paths, and all required evolution branches. Gifts, eggs, fossils, and quests complement the route tables; they should not be flattened into wild encounter entries.

## First land-table pass: Routes 101–104

The player's supplied story order gives these timing constraints:

- Routes 101–103 can be explored immediately. The Route 103 rival battle occurs before the Pokédex/Poké Ball handoff, so wild-table additions do not put extra Pokémon in the party for that fight.
- Route 104 opens after the Petalburg City conversation with Norman. Its south and north halves use the same `MAP_ROUTE104` encounter header, so one land table applies to both.
- Route 102–103 water and fishing rows are deliberately unchanged here. Their map records are not proof of early access: Surf and rod methods unlock later.
- Route 116 and the new mid-game sequence begin after Rustboro, so they are outside this first slice.

The opening tables retain recognizable Hoenn anchors but do not preserve every native species on every adjacent route. Poochyena is concentrated on Routes 101–103 and removed from Route 104; Lotad and Seedot anchor Route 102; Route 103 shifts toward Wingull and its regional additions; Route 104 emphasizes its forest/coastal mix. Per-map encounter trigger rates and early level bands stay unchanged. Duplicate slots control combined rarity using the existing expansion weight vector. Percentages below are conditional on a land encounter triggering.

| Map | Land level band | Combined slot shares | Design reason |
|---|---:|---|---|
| Route 101 | 2–3 | Poochyena 24%, Wurmple 20%, Pidgey 14%, Zigzagoon 11%, Caterpie 10%, Rattata 10%, Sentret 6%, Weedle 5% | A familiar opening core with distinct low-level bird, rodent, and bug choices; Poochyena no longer crowds out every other species. |
| Route 102 | 3–4 | Lotad 21%, Seedot 20%, Ralts 14%, Mareep 14%, Hoppip 11%, Zigzagoon 10%, Poochyena 5%, Wurmple 5% | The early meadow/pond route: preserves multiple Hoenn options for Roxanne, adds Electric and Grass/Flying lines, and reduces carry-over species from Route 101. |
| Route 103 | 2–4 | Wingull 24%, Shinx 24%, Starly 11%, Pawmi 11%, Poochyena 10%, Rookidee 10%, Zigzagoon 10% | A distinct open/coastal mix. Hoppip moves to Routes 102 and 104; the Route 103 rival's starter-only team remains a separate script rule. |
| Route 104 | 4–5 | Taillow 25%, Wurmple 24%, Marill 15%, Wingull 14%, Fletchling 11%, Hoppip 11% | Forest/coast transition with no Poochyena; retains useful native Water/Flying choices and adds two early-stage lines. Both Route 104 sections share this map table. |

The tables are rebalanced in `src/data/wild_encounters.json` for playtesting, not final Normal balance. Ralts has a 14% combined Route 102 share (up from the old 4% slot) so it remains huntable while still sharing that meadow with Lotad, Seedot, Mareep, and Hoppip. The pre-Roxanne Grass/Water pool is meaningful through Lotad, Seedot, Hoppip, and Marill, so review their available moves and the planned Roxanne team together before adding more direct counters.

Petalburg Woods sits between Route 104 south and north in the supplied progression. It remains a separate table for the next adjacent pass; the current table still has its vanilla Hoenn species. Reviewing Routes 101–104 in isolation should not mark the opening map band complete until the Woods table and its gates are included.

## Decisions for the next table pass

1. Use `normal-roster-inputs-733.csv` and `acquisition-coverage.csv` as the roster checklist; use `wild_encounters.json` and scripts as current source evidence.
2. Resolve macro-backed stats/types before final rarity assignments. Do not interpret missing numeric fields as low strength.
3. Draft exact first-access maps for the opening through Roxanne, including all currently available methods and the Route 103 starter-only timing. Cross-check every placement with the planned Roxanne team and cap.
4. Once that opening band is coherent, continue sequentially through badge bands. Add late/powerful lines only when their stage, level, and location fit the boss envelope.
5. Only after the campaign acquisition ledger is reviewed should approved encounter rows be copied into `src/data/wild_encounters.json`.

## Sources

- Shiny Vice: `src/data/wild_encounters.json`, `include/config/wild_encounter.h`, `src/wild_encounter.c`, `docs/design/gameplay-tables/normal-roster-inputs-733.csv`, `normal-roster-inputs-by-form.csv`, `acquisition-plan.csv`, `acquisition-coverage.csv`.
- [Emerald Expansion overworld encounter tutorial](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/docs/tutorials/how_to_overworld_wild_encounters.md).
- [Imperium `release` encounter data](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/wild_encounters.json).
- [Imperium Route 101 raw data](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L79-L148), [Route 104](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L467-L530), [Route 110](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L721-L787), [Route 111](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L880-L933), [Route 119](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L3683-L3748), [Route 123](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L4319-L4384), and [Victory Road](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L2287-L2352).
