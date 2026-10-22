# Emerald Imperium source review for Shiny Vice

**Purpose:** use Emerald Imperium's source and supplied design documents to guide Shiny Vice's roster acquisition, boss progression, and Normal-mode balance. This is a design pass only; it does not change game behavior.

## Source scope and version cautions

Reviewed the public `iriv24/pokeemerald-expansion` repository's `release` branch, especially `src/data/wild_encounters.json`, `src/data/trainers.party`, `src/data/trainers.h`, `src/caps.c`, `include/config/caps.h`, `src/starter_choose.c`, and `src/pokemon.c`. Also compared those structures with the supplied Imperium encounter tracker, encounter PDF, and boss workbook.

The branch is moving, and the supplied docs mix Imperium v1.3 and v1.3.1. The current public branch's starter selector still has a hard-coded three-species `sStarterMon` array (Turtwig, Chimchar, Piplup), even though Imperium's README advertises 27 starters. Do not treat that code snapshot as proof that the shipped game exposes 27 starters; the docs and source appear out of sync or the implementation may live elsewhere. Recheck a pinned commit or matching ROM release before copying a specific mechanic.

## What Imperium's data model does well

### Encounters are authored as map-level tables

`src/data/wild_encounters.json` is the source table. Each map entry identifies a map and encounter group, then records each method's encounter rate and ordered slots. Slots carry species and minimum/maximum level; fishing has separate old/good/super rod slot groups. Repeated species slots are meaningful because their position contributes to encounter weighting. For example, Imperium's Route 104 land table mixes several generations at levels 4–6, while water and fishing are separately defined.

The useful pattern is route-first and method-aware data, then species availability can be derived from it. A flattened "family has a location" cell loses encounter odds, method, levels, and timing. A map row alone still does not say when the route can actually be reached; route/event scripts and progression gates supply that context.

### Trainer source is a rich, readable authoring format

`src/data/trainers.party` keeps trainer identity and battle policy beside the party: class, sprite, music, battle type, AI flags, and each Pokémon's level, nature, ability, held item, IVs, moves, and other supported overrides. `src/data/trainers.h` is the generated/compiled representation; source edits belong in the authoring table, not the generated header.

The supplied Imperium boss workbook adds useful planning views: trainer order and cap, team paste, and calculated speed checks. The source party file remains the implementation source of truth. The current public party table contains repeated competitive-style variants for story leaders and late/postgame fights, but a suffix such as `_1` should not be assumed to mean a particular difficulty without checking the script that invokes it. The supplied workbook and source can also differ by version.

AI flags are explicit per trainer, so an easy route trainer need not inherit the boss AI profile. For Shiny Vice, model battle intensity per encounter (ordinary, notable, boss, optional challenge) and assign AI and team complexity deliberately, rather than making every trainer maximally competitive.

### Caps are progression milestones, separate from fight levels

`include/config/caps.h` separates cap policy (none, hard, soft), milestone selection (first-unset story-flag list or event variable), Rare Candy handling, and below-cap EXP boost. `src/caps.c` maps story flags to level thresholds and calculates EXP. In this snapshot, the cap ladder includes rival and evil-team story events as well as badges; it is not just eight badge values. The soft-cap EXP reduction is graduated by distance over the cap, while under-cap EXP boost is a separately configurable behavior.

This is a good architecture for Shiny Vice: store a single ordered milestone table; keep Off/Soft/Hard as enforcement policy; and distinguish each boss's ace level from the cap active before/after the fight. Define candy behavior and below-cap catch-up independently. The current planning CSV's monotonic source-ace cap anchors are provisional and should not be used as final rules until the milestone timing and cap semantics are selected.

### The encounter/boss workbook is valuable because it joins context

The encounter materials organize wild tables separately from gifts, eggs, and statics. The boss workbook orders the story and records team details and cap context, plus optional challenges. The transferable lesson is not to put every fact into one gigantic spreadsheet; it is to keep clear source tables and give each boss/checkpoint a linked view of the player's options before the fight.

## What Shiny Vice should adopt

1. **Keep a normalized acquisition ledger.** One record per acquisition source/event, not one overloaded cell per family. Include species/family, source kind, map/NPC/item/trade, encounter method and slot/rate, level range, repeatability, prerequisites/story flag, first available checkpoint, source file/line, and confidence. Derive a species/family summary view from those records.
2. **Represent every intended path.** Distinguish repeatable wild hunting, one-time gifts/statics, eggs and breeding, evolution-only access, fossils, shops, trades, conditional events, and postgame. A pre-evolution path is a valid family acquisition path, but should be labeled so forms and evolution timing are not mistaken for a direct wild encounter.
3. **Verify campaign reachability.** The 151 enabled families without a direct match in the already-audited wild/scripted data are audit work items, not proof of unobtainability. For each candidate path, check map connections, HM/field-move gates, story flags, NPC script conditions, and whether the source is actually active in the intended build. Expansion maps and battle facilities must not be counted as campaign availability by themselves.
4. **Make each enabled family huntable on purpose.** For a shiny-hunting game, record at least one intended player-facing acquisition route and its method/rate/requirements. Preserve different hunt styles where practical: ordinary encounters, fishing/surf, gifts/statics, outbreaks/DexNav or other Shiny Vice mechanics, and breeding. Do not let a single incidental or postgame route silently satisfy availability.
5. **Link boss rows to player tools.** For every required and optional checkpoint, link the species, abilities, moves, items, evolution access, TMs/tutors, healing/resource access, and encounter paths available before it. Then choose a team that challenges a reasonable party built from those options, not from the whole enabled dex.
6. **Keep battle design auditable in one authoring source.** Use trainer records for party data and explicit AI/boss classification. Track proposed Normal team separately from current source inventory until approved. Include natures, abilities, IVs, EV assumptions, item, moves, ace, AI profile, and the cap at that checkpoint.

## What to adapt rather than copy

- **Starter system:** Shiny Vice has a real region-plus-slot choice and rival counter-pick requirement. Imperium's current public source array does not implement the advertised 27-choice scope in the inspected file. Use our starter-region table as the canonical mapping, persist the region and slot, derive the rival counter-pick deterministically, and ensure alternate rival party branches preserve the chosen rival starter at every encounter.
- **Roster breadth:** Imperium's broad Gen 1–9 route tables demonstrate how to spread species through Hoenn, but its specific slots, levels, and route density are not automatically right for Shiny Vice. Our configured roster is 733 distinct National Dex entries; every route needs a themed, progression-appropriate subset, not indiscriminate species saturation.
- **Difficulty:** Imperium's Normal mode is a substantial baseline with prepared teams and capable AI; its source also includes radically stronger postgame/optional parties. Shiny Vice should aim for the user's Radical Red-like Normal challenge, but expose a coherent baseline rather than copying Imperium's largest teams or assuming a trainer suffix is a mode. Decide Set/Switch, Bag, AI tiers, trainer item use, team size, EV/IV expectations, and cap behavior as separate rules.
- **Minimal Grinding:** keep it deferred as requested. Preserve ordinary IVs, EV training, and breeding in Normal. If brought back later, present it as an optional convenience ruleset with a clear name and exact contract; it should not silently erase the hunt/breeding loop.

## Recommended next planning sequence

1. Treat the user's current enabled config as the curated roster unless they choose to revise it. Record the verified 733 National Dex count separately from the 346 supported enabled family-block count; the orphan Sinistcha macro does not add a family.
2. Finish acquisition-path coverage and story-gate verification, keeping source evidence and confidence. Prioritize the earliest campaign bands first so roster composition can be balanced from actual player options.
3. Lock the Normal rules contract: battle style, bag/item rules, AI profile tiers, trainer items, IV/EV assumptions, EXP curve, and cap Off/Soft/Hard definitions (including Rare Candy and under-cap EXP behavior).
4. Rebuild the campaign checkpoint ladder from actual Hoenn script order. Mark each boss's before/after cap, required/optional status, source trainer IDs, and player acquisition/tool envelope.
5. Propose Normal teams and route trainer distributions from that ladder, then run playtests and adjust roster density, encounter levels/rates, boss teams, and caps together.

## Reference source files

- [Imperium release source](https://github.com/iriv24/pokeemerald-expansion/tree/release)
- [Wild encounter authoring table](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/wild_encounters.json)
- [Trainer party authoring table](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party)
- [Generated trainer records](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.h)
- [Cap configuration](https://github.com/iriv24/pokeemerald-expansion/blob/release/include/config/caps.h)
- [Cap progression and EXP policy](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/caps.c)
- [Starter selector](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/starter_choose.c)
- [Imperium README and advertised features](https://github.com/iriv24/pokeemerald-expansion)

Shiny Vice's current working tables are in `README.md`, `starters-and-rival.md`, `roster-availability.csv`, and `normal-boss-checkpoints.csv` in this directory. Their acquisition timing and Normal proposals remain provisional until the audits above are complete.
