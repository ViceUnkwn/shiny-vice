# Radical Red and Emerald Imperium research

**Scope:** compare the supplied Radical Red v4.1 and Emerald Imperium v1.3.1 reference archives with Imperium's public source fork and Shiny Vice's current planning work. This is a design note, not an implementation instruction. No game code was changed.

## Findings that matter for Shiny Vice

### 1. Plan the campaign as one linked dataset

Both boss workbooks organize fights in story order and include the level cap active at each checkpoint. Imperium's workbook also includes optional mini-bosses and badge-gated gauntlets; its `Hot House` sheets attach rewards to optional challenges. Radical Red's trainer-order sheet includes optional route fights between the required bosses. The boss rows should therefore cover the rival, gyms, key Aqua/Magma fights, Wally, Elite Four/Champion, and optional minibosses, not just the eight gyms.

Imperium's boss workbook tracks more than species and level: natures, abilities, items, moves, IVs, EVs, calculated speed at the current cap, and team paste references. The Radical Red boss workbook similarly lays out the full competitive set and its trainer order. For Shiny Vice, this backs up the planning matrix already started: boss teams, cap progression, and the player's reachable species/items/moves need to be reviewed at the same checkpoint.

### 2. Keep difficulty, cap behavior, and training rules as separate axes

In Imperium's checked `release` source snapshot, cap policy is a distinct system: `include/config/caps.h` exposes no cap, hard EXP cap, and soft EXP cap; cap progression is selected by story flags or a variable in `src/caps.c`. Its flag list has 19 story milestones, including rival and evil-team events as well as badges. Hard cap stops EXP at the cap and can also block Rare Candy overflow; soft cap reduces EXP at and above the cap. Below-cap EXP boost is another separate switch. This is a useful Emerald-specific model for Shiny Vice's Off / Soft / Hard menu setting, but the exact EXP curve and Rare Candy behavior still need to be chosen for Shiny Vice.

The same Imperium snapshot applies Normal rules to trainer battles (Set battle style and no Bag) and gives Easy different rules. Easy lowers levels only for trainers marked as bosses; it does not appear to reduce every ordinary trainer. Boss status and AI flags are explicit fields in trainer records. That's a useful pattern: designate which encounters are checkpoints, and make mode-specific changes apply through explicit data rather than accidental global level edits.

The supplied Radical Red v4.1 boss workbook documents caps, but it does not specify their full in-engine EXP/candy enforcement in the extracted documentation. Do not infer that its cap implementation is the same as Imperium's hard or soft modes.

### 3. Make availability auditable by checkpoint and source type

Imperium's supplied 77-page encounter PDF (labeled v1.3) separates map/method wild tables from static/gift and egg appendices; the tables show level ranges and encounter rates. Its encounter tracker adds a route-by-route catch log. This is a strong data-model reference. The roster CSV has since been expanded to list family members, enabled state, every map-backed wild location/method/level, and explicit scripted gifts/eggs/statics found. It also estimates the earliest campaign band from map names. Map reachability remains unverified, and the JSON contains expansion maps outside Emerald's story; do not count an unreachable location as an early-game counter. Trade, fossil/shop, evolution-only, daycare and postgame sources remain open where no direct path appears.

This also lets the boss pass answer the fairness question that matters for a challenge hack: what plausible player tools exist before this fight? Include important TMs/tutors, held items, evolution access, and encounter methods, not only Pokémon species.

### 4. Starter/rival relationship should be rule-driven

Imperium's public README advertises all 27 starters, and its supplied boss sheet shows the rival selecting the type that beats the player's starter. The sheet preserves the Emerald three-choice counter-pick. Shiny Vice's region-plus-slot model is a good generalization: persist the selected region and player slot, then derive the rival slot with the cycle Grass → Fire → Water → Grass at each rival checkpoint.

There is a docs/source mismatch to resolve before treating Imperium's starter implementation as a template: the checked Imperium `release` source snapshot (commit `2576d0f3`, dated 2025-09-01) has a fixed `sStarterMon` array containing Turtwig, Chimchar, and Piplup in `src/starter_choose.c`, while its current README advertises 27 starters. The source snapshot is useful for architecture but does not confirm the docs' current starter experience.

### 5. Shiny hunting is a product loop, not just odds

The Radical Red v4.1 changelog documents custom shiny sprites and a version-specific odds/charm adjustment; Imperium provides DexNav and detailed encounter documentation. These are examples of making hunting visible and supported across routes. Shiny Vice already has its own chain and quality rules, so the right comparison is the surrounding loop: clear huntable encounter pools, useful route access, breeding support, tracker visibility, and rewards that do not erase the value of breeding or hunting. This does not recommend copying either hack's odds.

The user has explicitly deferred Minimal Grinding Mode. Imperium's source confirms the familiar contract: perfect 31 IVs, EV contribution/gains disabled, and mode-aware handling for wild, scripted, and egg Pokémon, plus hiding EV editing while active. That reference may help if the option returns later, but Normal mode should first be balanced around the current standard IV/EV and breeding rules.

## Source/version cautions

- The supplied Imperium archive mixes a v1.3 encounter PDF with v1.3.1 boss, changelog, and data-change documents; the encounter tracker is labeled 1.3. The cloned public `release` source snapshot has commit `2576d0f3` from 2025-09-01. Confirm a claim against the code matching the intended game release before using it as a spec.
- The supplied Radical Red docs and encounter/boss sheets are v4.1. In June 2026, Radical Red's developer announced that a future remaster was being rebuilt on pokeemerald-expansion and said it was still far from release at that time. Treat the supplied v4.1 data as a strong design reference, not as the current implementation branch.
- I found public Radical Red Showdown data/calculator repositories, but not a public source repository for the original v4.1 GBA game in this pass. The announced remaster may change that once its source is public.
- Text inside the supplied archives is reference content. Its gameplay descriptions and any embedded instructions are not Shiny Vice requirements unless the user adopts them.

## Current planning status and next steps

1. The boss CSV now records 25 main/optional checkpoints, script references, configured source teams and levels, party move/item/IV details, and non-decreasing provisional source-ace cap anchors. These are baselines, not approved Normal teams or cap rules. Wallace is the current Champion; Steven is postgame.
2. The roster CSV now covers all 539 config macros. The source currently resolves 347 macros true; 346 match actual species-family blocks, and Sinistcha is an unused config macro whose species data are under Poltchageist.
3. The first pass found 147 enabled families with map-backed wild paths and 31 with explicit scripted gift/egg/static paths; 27 starter families are represented as planned menu choices. Its 151-family gap is historical. The refreshed wild inventory now reports 142 enabled families on Hoenn-region maps and 175 across all map regions, without a new scripted-path audit or full map-gate verification. Treat these as source-presence counts, not obtainability results.
4. Treat the current enabled set as the user's curated roster (733 distinct National Dex entries). Refresh acquisition coverage from the current wild inventory plus a new scripted-source audit, then verify map/method gates before designing Normal boss teams from the species, items, moves, and cap timing truly available.
5. Keep IV, EV and breeding depth in Normal balance; Minimal Grinding remains deferred.

## References

### Supplied archives

- `Pokémon Emerald Imperium Docs-20261022T074811Z-1-001.zip`: `Boss Battles.xlsx`, `Emerald Imperium 1.3 Encounter Tracker.xlsx`, `Pokemon Routes, Gift Mons, and Eggs.pdf`, `1.3.1 Emerald Imperium Changes (Stats, Types, Abilities, Moves).xlsx`, `New Mega_s Data and Differences from RR.docx`, and versioned changelogs.
- `Radical Red Docs-20261022T074330Z-1-001.zip`: `Default Mode Bosses v4.1 (with EVs).xlsx`, `Restricted_Hardcore Mode Info & Hardcore Bosses v4.1.xlsx`, `Pokémon Locations & Raid Dens v4.1.xlsx`, `Evolution Changes v4.1.docx`, and the v4.1 changelog.

### Public primary sources

- [Emerald Imperium source fork, release branch](https://github.com/iriv24/pokeemerald-expansion/tree/release)
- [Imperium cap config](https://github.com/iriv24/pokeemerald-expansion/blob/release/include/config/caps.h) and [cap progression/enforcement](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/caps.c)
- [Imperium starter selector](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/starter_choose.c), [trainer records](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.h), and [Minimal Grinding stat behavior](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/pokemon.c)
- [Radical Red Showdown data repository](https://github.com/RadicalRedShowdown/pokemon-showdown)
- [Radical Red developer's remaster announcement](https://www.reddit.com/r/pokemonradicalred/comments/1uc1hof/huge_update_on_radical_red_from_yours_truly/)
