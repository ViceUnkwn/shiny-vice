# Normal-mode balance plan for the 733-species roster

**Status:** design framework. This does not change species, encounter, trainer, or cap data.

## Goal

Make the enabled roster feel broad, huntable, and strategically useful across one Hoenn campaign save while giving Normal a prepared, Radical Red-inspired boss challenge. Do not try to make 733 species appear equally often or make their final forms equally strong. Balance access, evolution timing, encounter weight, move access, and boss preparation together.

The source of truth is the enabled-family data in `include/config/species_enabled.h` and `src/data/pokemon/species_info/`. It resolves to 733 distinct National Dex species in 346 supported families, plus 1,011 species constants when alternate and battle forms are counted. Forms that share a National Dex number still need their own acquisition or unlock review.

## What the source currently tells us

- `src/data/pokemon/species_info/` uses `P_UPDATED_STATS GEN_LATEST`; roster strength review should use those current stats, not old generation stats.
- `include/config/caps.h` currently selects `LEVEL_CAP_NONE` and `EXP_CAP_NONE`; Rare Candy caps are disabled. The menu's cap choices are not yet an active campaign cap policy.
- `src/caps.c` reads the selected per-save cap policy and the Gym-led ladder, including the Lv24 Oceanic Museum story milestone for a Brawly bypass; it no longer depends on compile-time cap configuration. The Trainer Card displays the active mode and level for the local save.
- `normal-boss-checkpoints.csv` has 24 provisional story and optional checkpoints. Its source ace levels are useful sequencing evidence, but its draft caps and player-access notes are not approved balance decisions.
- The refreshed wild inventory contains Hoenn-map source candidates for 118 families. Older scripted-source and gap totals are not current: regenerate the scripted audit before measuring full coverage. Wild map rows include unverified story gates, so this is source evidence, not final availability.
- The rebuilt `normal-roster-inputs-733.csv` covers all 733 Dex entries; `normal-roster-inputs-by-form.csv` covers all 1,011 configured species/form IDs. The form input has explicit stats for 950 rows and explicit initializer locations for 965. Remaining macro-backed data are flagged for source/preprocessor review.
- Inputs use the source configuration's latest stats, types, abilities, egg groups, and Gen 9 level-up learnsets. `acquisition-plan.csv` refreshes family type and normal-form BST cues from the configured form inventory; the existing `balance_class` values remain provisional. Some form records still need C-macro or generated-record resolution, so check the source location and parse status before treating an individual blank as meaningful.

## Balance levers

Use these levers in this order. Leave species base stats alone unless a deliberate species rebalance is separately approved.

| Lever | What it controls | Balance question |
|---|---|---|
| First access | Where and when a family enters a save | Does the player have enough options by this checkpoint, and is this species meant to be common, unusual, or a chase? |
| Encounter weight | How often each wild species is found | Does the route make this a practical hunt without drowning out its habitat neighbors? |
| Caught level and evolution | How close the catch is to its next evolution and moves | Is a strong family fair because only its early form is available, or is a final-stage catch too early? |
| Evolution items and conditions | Whether a branch or form is reachable in the same save | Can the player finish the line without an external trade, distribution, or mutually exclusive choice? |
| Move and ability access | What the species can do at its availability point | Does it get its key coverage, setup, recovery, priority, or defensive ability before the next boss? |
| Boss party and AI | The pressure and tactical demands of required fights | Does each boss ask for team-building and play decisions without requiring one exact counter? |
| Level-cap milestone | The level ceiling around required fights | Does the cap make the boss a deliberate challenge while letting players catch up afterward? |

The strength review should be a **profile**, not a single BST cutoff. For every species or form, record: current base stats and distribution, typing, abilities, level-up moves by checkpoint, evolution level and method, key item/TM/tutor access, catch level and rate, and the earliest reachable boss after its first access. A 500 BST first-stage Pokémon with early setup or a powerful ability may be a bigger early threat than a higher-BST species caught unevolved with a weak moveset.

## Campaign bands

Use the existing story order as the skeleton. Assign first access and boss caps to milestones only after script order and map gates are verified.

| Campaign band | Intended roster role | Placement rule |
|---|---|---|
| Opening to Roxanne | Readable basics and team identity | Keep the selected starter meaningful; give several non-starter answers to Rock, status, and setup. Avoid early full evolutions and dominant abilities at high encounter weight. |
| Badges 2–3 | Team-building choices widen | Add reliable answers to the next boss themes, early branch evolutions, and a few uncommon high-utility hunts. |
| Badges 4–5 | Broad role coverage | Introduce more evolved forms, held-item and weather strategies, and stronger alternatives. Keep route tables habitat-led and vary hunt methods. |
| Badges 6–8 | Strong lines and late evolution access | Make powerful evolutions, rare families, and more specialized team roles available at fair levels. Check that required field access does not silently gate key counters. |
| League | Full six-member builds | The full campaign roster should offer multiple viable styles and answers to each Elite Four specialist, without making every family equally common. |
| Postgame | Rare and collection-focused access | Put late legendaries, mythicals, paradox families, special forms, and optional bosses behind explicit quests or statics; preserve a shiny-huntable route. |

The current caps 5, 15, 19, 24, and onward are **source-ace anchors only**. Do not lock first-access bands, evolution items, or boss teams to these numbers until one shared milestone table defines which cap is active before and after each fight.

## Distribution rules for the 733 species

1. **Every family gets a first-access plan.** Use repeatable wild access as the normal case. Choose gifts, eggs, trades, shops, fossils, or postgame events when that method fits the family or gives the hunt a distinct identity. No family is counted as covered solely because it is in a different expansion region or in one unchosen starter pool.
2. **Every branch is reachable in one save.** Record evolution edges from species data and assign items, friendship, time, location, or NPC alternatives. Trade evolutions need an in-game solo-save path. Do not make link trading the only completion route.
3. **Use evolution pacing before delaying whole families.** If a family has an early base form and late evolution, place the base form where it supports team-building and gate its stronger form through normal evolution timing. Put direct final-stage encounters later or at low weights.
4. **Spread strong families by access context.** Consider current stats, move quality, typing, abilities, and evolution timing together. Keep pseudos, legendaries, mythicals, paradoxes, and unusual forms on named milestones rather than applying one blanket BST rule.
5. **Mix generations within habitats.** Give each Hoenn area a clear ecology and mix curated generations inside it. Keep method tables separate for land, water, fishing, rock smash, hidden/special encounters, and scripted sources. Preserve slot order, rates, and levels so hunt odds can be reviewed.
6. **Keep shiny hunts intentional.** Each family should have a player-facing hunt path. For gifts and statics, record whether they reset, repeat, and can be shiny; if a one-time event is shiny-locked, provide another hunt path. Keep breeding as a meaningful alternative by placing parents, Ditto, daycare, baby items, and form inheritance deliberately.
7. **Track forms separately from Dex completion.** The 733 count is National Dex species, not every `SPECIES_*` form. Regional forms need distinct access; Mega, Gigantamax, Tera, fusion, and other enabled battle forms need explicit unlock rules.

## Boss balance contract for Normal

Normal should make required bosses feel prepared without making every route trainer a boss. Assign intensity by encounter role:

- **Ordinary trainers:** small, coherent teams; simple plans; lower AI complexity and modest items. They provide pacing and EXP, not a gauntlet of perfect coverage.
- **Rivals and story bosses:** teams reflect their character and the current campaign band. Add coverage, abilities, held items, and stronger AI in steps. The rival's starter and counter-pick remain tied to the selected regional trio.
- **Gyms and Elite Four:** clear battle identity, complementary roles, and a recognizable ace. Use strong movesets and appropriate held items; introduce hazards, setup, weather, speed control, and switching gradually. League teams can assume the player can build a full party from the full campaign access pool.
- **Optional/postgame bosses:** may demand deeper optimization and more complete teams than the Normal story ladder.

For each required boss, make a pre-fight **player access envelope** containing available species, evolutions, moves, abilities, items, healing, and cap. Check that at least three different team-building approaches can plausibly prepare for the fight. Bosses may punish an unprepared team, but should not demand one specific species or hidden route. Put optional high-difficulty rematches outside the mandatory Normal ladder.

Normal preserves ordinary IVs, EV training, and breeding as requested. Use Set battle style and disable Bag use in trainer battles for the Normal challenge contract, while retaining field healing between fights. Explain those rules before game start. Put no-EV guarantees on every player Pokémon only in a separately defined convenience ruleset if that option is brought back later. For Normal bosses, assign IVs and EVs deliberately by milestone rather than granting every trainer maximum competitive spreads. This keeps boss preparation meaningful without turning ordinary trainers into stat-checks.

## Cap behavior to design before implementation

Treat cap value and cap policy as separate settings:

- **Milestone value:** the ace level of the next required story boss, with optional bosses on their own ladder.
- **Off:** no cap restriction.
- **Soft:** keep the milestone as the maximum level, but award the existing graduated reduced EXP at/above the cap and retain progress toward later levels. The current `TryIncrementMonLevel` already prevents levels above `GetCurrentLevelCap()` in Soft.
- **Hard:** keep the same maximum level and award no EXP at/above the milestone. Block Rare Candy at cap too; the current compile-time Candy gate is not sufficient for per-save settings.
- **Rare Candy and Day Care:** neither may advance a Pokémon beyond the active cap in a capped mode. Rare Candy must report failure before consuming an item. Day Care already clamps to `GetCurrentLevelCap()`.
- **After a required boss:** advance the active cap at the script/event that marks victory, not merely by entering a map.
- **Catch-up:** define below-cap EXP separately; do not let catch-up erase the challenge or force excessive grinding after a loss.

This makes the menu's Off/Soft/Hard choice understandable and leaves a single ordered milestone source for all three policies. The proposed source-ace ladder and existing story flags are recorded in `normal-cap-milestones.csv`; the full implementation contract is in `normal-implementation-plan.md`. The flag chain follows mandatory main-path victories. Optional rivals do not advance it.

## Data and implementation sequence

1. Lock the source-backed baseline: 733 NatDex rows, 346 family rows, 1,011 configured form rows, all 27 starter choices, source boss order, cap activation draft, and the acquisition/boss planning schemas.
2. Implement the starter/rival slice against the 27-choice pool and 135 checkpoint progression rows.
3. Lock per-save Normal/cap behavior and implement Set/no-Bag trainer rules with the independently selected Off/Soft/Hard cap policy.
4. Fill and approve acquisition rows by campaign band; verify Hoenn map/story gates and one-save branch completion for each band before implementing that band's sources.
5. Draft each band's Normal boss parties from its verified pre-fight access envelope; preserve player IV/EV/breeding progression.
6. Review each required checkpoint with a basic untrained party and a trained/bred party; revise access, teams, moves, caps, and encounter weights together.

## Deliverables for the next balance pass

- Rebuilt species/form strength and progression inputs for all 733 Dex entries and 1,011 configured species/form IDs (available in `normal-roster-inputs-733.csv` and `normal-roster-inputs-by-form.csv`). 950 forms currently have complete explicit numeric stats parsed; 61 need macro/generated-record resolution or explicit form classification before final strength analysis.
- One balance-review row per species and an attached form list, linked to family, evolutionary edges, moves, and current acquisition evidence.
- One first-access and line-completion record per enabled family, with all current sources distinguished from designed sources.
- Hoenn map/method cohort tables with explicit encounter weights, levels, and gates.
- Normal team proposals and a player-access envelope for every required boss in `normal-boss-checkpoints.csv`.
- An ordered cap milestone table whose Soft/Hard/Off behavior is clear and independent of boss ace data.
- A staged implementation contract with source files, runtime behavior, data owners, and completion gates (`normal-implementation-plan.md`).

The next work item is source-level review of the macro-backed rows, then converting the 733 species/form profiles into power and access bands. Route tiers and boss counterplay should use the rebuilt inputs, not the known-bad historical type/BST cues.
