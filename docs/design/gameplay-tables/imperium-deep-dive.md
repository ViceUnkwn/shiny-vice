# Emerald Imperium source and design deep dive

**Purpose:** record the useful, source-backed patterns from Emerald Imperium for Shiny Vice's encounter, acquisition, trainer, rival, boss, and Normal-mode design. This is a reference analysis, not a request to copy Imperium's exact teams or route placements.

**Reviewed:** the supplied Imperium documentation ZIP (encounter guide and tracker labeled v1.3, plus changelogs through v1.3.1 and the boss workbook) and the public [`iriv24/pokeemerald-expansion` `release` branch](https://github.com/iriv24/pokeemerald-expansion/tree/release). The live branch can move independently of the supplied files.

## Main conclusions

1. **Imperium's best transferable idea is the connected design loop.** It treats locations, encounter methods, story order, available catches, trainer teams, levels, and boss preparation as related data. Shiny Vice should keep these views linked, while keeping source evidence distinct from proposed design.
2. **The source tables are more useful than copying the docs' individual species choices.** `wild_encounters.json` shows actual method, slot, and level data; `trainers.party` shows actual authored teams and AI. The workbooks are strong player-facing indexes and balance aids, but they are not necessarily the same version as the source branch.
3. **Imperium's route density is a benchmark, not a target.** Its first four routes each use the full 12-slot land table and spread the slots across 11–12 species. Shiny Vice's enabled roster intersects that pool less broadly, and its routes should still feel like Hoenn habitats. Use the slot budget to tune common, uncommon, and rare hunts rather than forcing twelve distinct species everywhere.
4. **Boss difficulty is built from more than level.** Imperium authors move coverage, abilities, held items, nature, IVs/EVs, party roles, battle format, and AI. Shiny Vice should tune those against the player options actually available before each fight.
5. **Keep Shiny Vice's gym-only cap rule.** Imperium's cap ladder also advances after story bosses and rivals. Its ordered checkpoint approach is valuable; its exact milestone policy conflicts with the user's chosen design that only Gym victories raise the cap.

## Version and source caveats

The encounter guide in the ZIP labels itself **Emerald Imperium v1.3**; the tracker is also labeled v1.3, and the ZIP contains v1.3.1 changelog material. The public `release` branch is a separate, moving source snapshot. A concrete mismatch: the supplied Boss Battles workbook gives its first Roxanne team as Rhyhorn, Paldean Wooper, Gligar, and Nosepass. The current public `release` `TRAINER_ROXANNE_1` instead has Geodude, Lileep, Gligar, and Nosepass. The current Shiny Vice source inventory is a third snapshot. So use the source and docs to learn structure and design, but pin a commit or ROM version before treating an individual party as canonical.

The Imperium README describes the intended Normal experience as substantially harder than a mainline game, with competitive trainer teams and custom AI; it calls the stronger optional Gym battles out separately and says Hard Mode is under construction. That makes the shipped Normal party data the relevant benchmark for Shiny Vice Normal, not an unfinished Hard Mode or the workbook's optional challenge teams. [Imperium README](https://github.com/iriv24/pokeemerald-expansion/blob/release/README.md)

## Encounter tables: what the source is doing

### One map entry, separate methods

Imperium's [`src/data/wild_encounters.json`](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/wild_encounters.json) is route/map-first. Each map can define land, Surf, fishing, and Rock Smash independently. Each method has its own encounter-trigger rate and species slots; each slot has a species and minimum/maximum level. The group header supplies the probability weight for each slot. Those are separate controls: `encounter_rate` controls how often that method produces an encounter, while the slot weights control which species is selected once it does.

The standard slot weights in the current source are:

| Method | Slot weights |
|---|---|
| Land, 12 slots | 20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1 |
| Surf, 5 slots | 60, 30, 5, 4, 1 |
| Rock Smash, 5 slots | 60, 30, 5, 4, 1 |
| Fishing, 11 slots | 34, 33, 33, 34, 33, 33, 40, 40, 15, 4, 1; Old Rod slots 0–2, Good Rod 3–5, Super Rod 6–10 |

Repeated species in multiple slots add their weights together. This gives designers a way to make a line common on one method, rare on another, and higher-level at a later rod tier without inventing a new system. The supplied encounter PDF spells out the method and percentage interpretation and color-codes the rod-specific slots.

The source also varies encounter-trigger rates by map and method. For example, the public table uses a land rate of 15 on Route 119 and 10 on Route 124, with separate Surf/fishing rates. Shiny Vice can tune both the overall hunt pace and the distribution among species; they should not be confused with each other.

### What the route examples teach

- **Opening:** Imperium Routes 101–104 use levels 2–6 and the full 12 land slots. Route 101 includes a mix of Hoenn and later-generation lines; Route 102 adds a different mix plus water and fishing data; Route 103 has its own terrestrial and marine mix; Route 104 has a forest/coast composition. The actual first four route tables are in the source and pages 35–36 of the supplied encounter guide.
- **Midgame transitions:** Route 110 uses an electric-leaning selection at levels 19–23, alongside separate water/fishing tables. Route 119 uses a new land pool at levels 25–27 and its own water/fishing entries. These show how a route can introduce fresh families at a meaningful level band rather than just repeat the early-game pool.
- **Late routes:** Route 124 uses a distinct land pool at levels 42–47 in addition to water and fishing. Later routes can introduce evolved or higher-stage forms as their own late-game direct hunts, while the early-stage line remains available earlier for players who want to raise and breed it.
- **Methods form separate hunt loops:** route land, Surf, Old/Good/Super Rod, Rock Smash, and statics/gifts need separate ledger entries. A water entry in a map table does not mean it can be caught immediately: Surf access and fishing-rod possession are method-specific gates. A route can be reachable while one or more of its methods are still unavailable.

### What to copy into Shiny Vice's authoring workflow

- Keep `src/data/wild_encounters.json` as the editable implementation source and review generated encounter headers only as build output.
- For every slot, record map, method, slot index/weight, species/form, level band, and story/method gate in planning data. Keep repeated slots explicit so actual odds stay auditable.
- Review each area as a hunt experience: habitat fit, newly introduced families, available counters before the next required boss, repeatability, and whether its shiny-hunt odds feel intentional.
- Preserve separate method pools. Do not count a Surf or Rod species as early access just because the map can be walked to early.
- Use the current Shiny Vice enabled-species list as a hard inclusion filter. Imperium contains the full expansion roster and some forms that Shiny Vice has not enabled.
- In the opening, balance the combined pre-Roxanne access envelope (Routes 101–104, Petalburg Woods, Route 116, and any actually reachable tunnel sources) rather than judging each route in isolation. The player needs meaningful choices, but a single Gym answer should not dominate every slot or become mandatory.

## Acquisition and shiny-hunt design

The supplied **Pokémon Routes, Gift Mons, and Eggs** guide separates wild tables from static/gift Pokémon, egg encounters, and multiple-choice encounter pools. It includes exact location, level, method, rod tier, and access notes. The Encounter Tracker is a player-facing Nuzlocke checklist organized around named areas; it is useful for checking coverage and first-catch experience, but it is not by itself a one-save acquisition proof or a story-gate audit.

Useful patterns for Shiny Vice:

- Let the route tables carry the repeatable hunt population, then use gifts, eggs, trades, fossils, shops, and postgame events to fill family or branch gaps where they make more sense.
- Treat a random egg pool as an optional bonus or broad novelty source, not the only way to hunt a target that players are expected to obtain. For each species, document whether the source is selectable, random, repeatable, one-time, or breedable.
- Keep direct source access and evolution access separate. One pre-evolution can prove family access, but does not automatically solve branch evolutions, regional forms, item gates, or form-specific shiny behavior.
- For every one-time/static source, record its shiny behavior and reset/repeat rules so Shiny Vice's starter-shiny preview and other hunting guarantees remain predictable.
- Use the tracker idea to create a player-visible checklist/map, but generate it from the same normalized acquisition ledger that proves all 733 enabled Dex entries have a path.

## Trainers, rivals, bosses, and gyms

### Trainer authoring

Imperium uses the expansion's competitive-style [`src/data/trainers.party`](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party) as its readable party source; `src/data/trainers.h` is generated. A trainer record can carry class, battle format, items, and AI flags, while each Pokémon can specify level, nature, ability, held item, IVs, EVs, and moves. This is a strong fit for Shiny Vice's planned table: author the proposed Normal team in the source party file and keep the planning view linked to trainer IDs rather than editing generated data.

The public source shows a useful strength gradient: ordinary trainers may have simple teams and basic AI; major story trainers and bosses use fuller sets and add selected strategy flags. Roxanne's current public team, for example, has four level-14/15 Pokémon, held items, moves, abilities, 31 IVs, and a strategy-oriented AI profile. A regular route trainer does not need the same build budget. Avoid giving every opponent maximum AI, perfect sets, and full teams; concentrate complexity where the player has had a chance to prepare.

### Rivals

The opening rival is a deliberately small, starter-aware encounter. The source has separate Route 103 trainer records for each Hoenn starter choice; each first fight is the opposing starter at level 5. The supplied workbook describes the counter-pick rule. Later Route 110 and Route 119 records are still split by the player's starter, but grow into expanded teams with stronger AI. Shiny Vice's saved region-plus-slot choice means it should keep using its dynamic same-pool counter-pick rather than copy Imperium's three Hoenn starter branches. Preserve that counter-pick identity at every later rival trigger, and validate all 27 enabled starter inputs across every scripted branch.

### Boss order and gym pacing

The Boss Battles workbook's strongest feature is its sequential view: it places required bosses, Gym Leaders, rivals, evil-team fights, optional battles, and the League in the order a player encounters them. It records team paste, level, nature, item, ability, moves, IV/EV context, and a speed calculation. Its Navigation sheet also documents the cap expected before each checkpoint. This makes it possible to see not only “what is Roxanne's team?” but “what has the player plausibly caught and trained before Roxanne?”

Shiny Vice should preserve that ordered index, but attach a separate **pre-fight access envelope** to each row: available species/families, methods, evolution/item access, TMs/tutors, healing/items, and optional preparation. Only then finalize the boss team. Keep main-path bosses and optional challenge battles explicitly distinct. Imperium's optional powered-up Gym battles are a useful way to add harder rematches and rewards without making the main story depend on them.

The public `release` teams show an intentionally steep story-team ramp: Roxanne has four Pokémon at levels 14–15; Brawly has three at level 25; Wattson has five at level 34; Flannery has six at level 47; Norman has six at level 59; Winona has six at level 68; Tate/Liza's teams are around 76; Juan has six at level 82; the Champion team peaks at 85. These line up with the workbook's pre-fight cap notes, but those exact levels are not portable without matching its cap rules and XP pacing. The team identity also comes from a battle plan, not just type: Wattson establishes Electric Terrain and pivot pressure, Flannery layers Sun and Chlorophyll, Norman combines burn-activated Guts and Illusion/Shed Tail-style pressure, and Winona mixes speed, setup, bulky pivoting, and coverage. For Shiny Vice, use that cohesion as a pattern, then check whether the enabling abilities, moves, items, and counters are actually available by the checkpoint.

### AI and encounter intensity

Imperium's parties make AI an explicit trainer property instead of assuming every battle is equally intelligent. For Shiny Vice, a sensible Normal tiering is:

- **Ordinary route trainer:** avoid illegal/bad moves and make basic damage choices.
- **Notable trainer or early rival:** use a small amount of additional tactical behavior when it makes the fight clearer or more memorable.
- **Gym leader, major rival, or story boss:** use reliable basic decision-making plus selected strategies (setup, switching, status, weather, doubles support) that match the authored party.
- **Optional rematch / postgame challenge:** reserve the strongest AI and competitive party structures for players who opt in.

The goal is to make team construction and coverage matter without making routine route battles exhausting or making an omniscient switch into every player action the baseline.

## Level caps and Normal-mode implications

Imperium's cap code is an ordered flag-to-level table, and its current ladder advances on both badge flags and non-Gym story events. It separately configures no/hard/soft cap enforcement, Rare Candy behavior, and below-cap EXP boosts. The supplied boss navigation uses a sequence of pre-fight cap checkpoints too. This shows the benefit of one explicit milestone source and a clear before/after level for each fight.

For Shiny Vice, carry over the data-driven milestone approach but keep the chosen rule: **only Gym wins raise the main-story cap.** Optional rivals and story bosses use the current cap and do not advance it. Track fight ace level separately from active cap; add an explicit League/postgame policy rather than inferring it from Imperium's ladder. Keep Off/Soft/Hard as enforcement choices independent of the milestone list.

For Normal difficulty, the most reusable benchmark is Imperium's authored party quality and fight sequencing, not simply raising levels. Preserve the user's standard IV/EV training and breeding loop. Balance teams against Shiny Vice's actual roster, encounter distribution, move/ability changes, and available TMs/items. If those differ from Imperium, identical parties will not have identical difficulty.

## Recommended Shiny Vice work sequence

1. **Freeze the Imperium reference snapshot:** record branch/commit or identify the exact ROM/doc version for each comparison. Keep the v1.3 guide, v1.3 tracker, v1.3.1 changelog, and live source branch labeled separately.
2. **Finish the map/method inventory:** enumerate every Shiny Vice campaign map and each method's slots, species weights, levels, and actual story/field/rod gate. Add gifts, eggs, trades, shops, fossils, and statics in the same acquisition ledger.
3. **Complete opening-to-Roxanne access proof:** verify Routes 101–104, Petalburg Woods, Route 116, and the Rusturf Tunnel timing. Then choose encounter odds and finalize the first required boss only from that proven pool.
4. **Continue in campaign bands:** lock acquisition and optional access before designing each Gym/major boss team; keep encounter and rival design coupled to those checkpoint options.
5. **Author teams in `trainers.party`:** make trainer tiers, team size, AI, ace level, items, moves, IV/EV assumptions, and optional status explicit. Do not hand-edit generated trainer headers.
6. **Validate in the built game by checkpoint:** confirm method gates, actual species/odds, starter-dependent rival branches, team order, held items/moves, cap display/enforcement, and pre-boss preparation routes. Adjust route weights and team composition together.

## Primary references

- [Imperium public source repository](https://github.com/iriv24/pokeemerald-expansion/tree/release)
- [Wild encounter authoring data](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/wild_encounters.json)
- [Trainer party source](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party)
- [Cap policy and milestone implementation](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/caps.c)
- [Cap configuration](https://github.com/iriv24/pokeemerald-expansion/blob/release/include/config/caps.h)
- [Rematch progression table](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/battle_setup.c)
- Shiny Vice working inputs and plan: [encounter draft](encounter-table-research-and-draft.md), [opening access inventory](opening-hoenn-access.csv), [boss checkpoints](normal-boss-checkpoints.csv), [acquisition plan](acquisition-plan.csv), and [roster source review](imperium-source-review.md).
