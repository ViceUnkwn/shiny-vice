# Shiny Vice acquisition and roster balance — first pass

**Status:** design/planning artifact. No encounter or trainer data has been changed.

## Working roster and coverage snapshot

Treat the enabled species config as the curated roster. It represents **733 distinct National Pokédex entries across 346 supported enabled family blocks**; the extra true `P_FAMILY_SINISTCHA` config macro has no separate family data block.

`acquisition-plan.csv` is a first source-by-source ledger modeled on Imperium's route/method tables. It contains 1,055 rows covering all 346 supported enabled families. Its family National Dex counts have now been recomputed from the enabled species data and total 733 distinct entries. The initial type/BST cues were defective for 22 families; they have now been rebuilt from the current enabled species/form source inventory. Use `normal-roster-inputs-733.csv` and `normal-roster-inputs-by-form.csv` for the source-level detail, with macro-backed blanks treated as unresolved.

- 811 current wild-data family/map/method records on Hoenn campaign maps, including level ranges, encounter rates, slot order, and slot weights.
- 22 gift/egg/static script records from Hoenn maps, covering 16 families. These are script matches; story conditions and repeatability still need checking.
- 222 family-level design-gap records: 151 families with no direct path found in the audited wild/script data, 47 found only on other expansion maps, and 24 whose only known source is the selected starter option.

The counts describe different things: there are Hoenn wild paths for 111 families; 22 script path records cover 16 families and overlap some wild families; and 222 families still lack a verified Hoenn campaign path. A “source found” means data or a script reference exists; it does **not** guarantee the player can reach it at that point. The source uses story-window estimates, not verified map gates.

The ledger's `family_national_dex_entries` values are roster counts. Its `max_normal_form_bst` and `family_types` columns have been recomputed from the current form inventory; battle-only Mega, Gmax, Tera, Ultra, Primal, Eternamax, and fusion forms are excluded from the normal BST maximum. BST is a screening signal, not a rule that every member of that family must be delayed: a low-level pre-evolution can be a fair early encounter even if its final evolution is strong. Review exceptional forms and any unresolved macro data before locking placement.

## Full-roster acquisition contract

`acquisition-coverage.csv` is the one-row-per-family checklist for the user's 733-species enabled roster. It turns “all obtainable” into a single-save completion requirement. Current source evidence is not being mistaken for the finished plan: the 222 families without an audited Hoenn campaign source still need deliberate placement, and all other candidates need reachability and repeatability checks.

For Normal, the intended rule is that every enabled National Dex species can be obtained in one save by a campaign path, either directly or through a supported in-game evolution. Use these checks when converting the coverage rows into final route, gift, shop, fossil, trade, and postgame tables:

- **First acquisition:** Every family has at least one in-game first-access source. Breeding and evolution can complete a line but cannot be its only first-access source if no parent is obtainable.
- **Whole line and branches:** Track base species, split evolutions, baby Pokémon, cross-generation evolutions, regional variants, and evolution items separately. An evolution method must be possible in the same save; link trade cannot be the sole way through a line.
- **Forms:** Regional and special forms may share one National Dex number. Track their source and form-change unlock separately from the 733 Dex-species count. Mega, Gigantamax, Tera, fusion, and other battle forms need an explicit unlock method where those mechanics are enabled.
- **Starter pools:** The player chooses one region at New Game, but the other eight regions' starter families still need later campaign paths so one save can collect the full roster. The rival's counter-pick is determined from the selected trio and does not consume an acquisition slot.
- **Breeding:** Keep IVs, EVs, egg moves, and breeding relevant. Provide parents and daycare access in the campaign; include Ditto, genderless or single-gender families, baby-item requirements, and form inheritance in the audit. Eggs are a strong alternate hunt path, not a substitute for acquiring the first parent.
- **Special acquisition:** Fossil lines need every intended fossil/revival choice over a single save; trade evolutions need an in-game alternative; shop lines need a clear currency and unlock; legendary, mythical, paradox, and other rare species can be late/postgame quest or static encounters. No enabled species should depend solely on an external distribution or another player's save.
- **Shiny-hunt support:** For each gift/static/event source, record whether it can be reset, repeated, or hunted through a second method, and whether it is shiny-locked. Avoid making a one-time, shiny-locked event the only path to a family.
- **Boss gates:** A planned acquisition only counts before a boss if its map, story flag, method, level, and required items are reachable before that fight. Boss teams and cap milestones must be balanced against that reachable roster.

## Use Imperium's good data shape

Imperium's encounter authoring table is map-first: it names encounter methods, encounter rates, level ranges, ordered slots, and rod groups. The source also uses repeated species slots to express their combined encounter weight. Shiny Vice's plan keeps the same information instead of flattening all access into “species is on route.” Apply that format to each Hoenn map and keep these distinct:

1. **Current source evidence:** species, map/event, method, levels, slot weight, and source reference.
2. **Campaign access:** the story flag/map connection/field-move gate that proves the player can reach it.
3. **Design placement:** the intended first access window and any later alternate hunt or breeding path.

This is why a map ID on its own is not enough. The current source contains expansion maps outside the Hoenn campaign, and map scripts can make an encounter conditional or one-time.

## First-pass encounter balance rules

Use these as review checks while assigning species to route tables:

- **Theme each area.** Choose species that fit the place (forest, early roads, caves, desert, volcanic routes, coast, deep water, ruins, or late-game sky routes), but mix generations within that habitat. Imperium's Route 104 demonstrates a dense, multi-generation low-level route while retaining slot weights and method separation; use the density idea, not its exact roster.
- **Balance roles before typing alone.** Before each boss, check that the accessible roster offers plausible answers and team-building options: safe switch-ins, status control, physical and special damage, and more than one counter to a boss gimmick. Avoid making a single exact species mandatory.
- **Pace evolutions and move access.** Review the species' base form, evolution level/item/trade method, level-up moves, and availability of TMs/tutors. High final-form BST can be acceptable early if only a weak base form is available and the evolution timing is fair.
- **Treat high-power species deliberately.** Keep legendaries, mythicals, paradox species, pseudo-legendaries, and powerful forms on an explicit story/event plan. Do not accidentally put an unevolved line's final-stage stats on the route as if that were its catch power. Place late forms, stones, and evolution items at intentional milestones.
- **Preserve different hunt styles.** Give families planned repeatable wild sources where possible; use gifts/statics, fishing/surf, fossils, eggs, and evolution as distinct acquisition methods rather than treating them as interchangeable. Note one-time/resettable behavior and shiny status for every static.
- **Support the full roster across a save.** The menu offers one starter trio from one of nine regions. The selected trio and rival counter-pick are clear; other starter lines still need a later wild, gift, or egg path if a player is expected to obtain the entire roster in one save.
- **Keep breeding relevant.** Normal keeps IVs, EVs, and breeding. Starter and rare-family availability should give breeders a realistic way to obtain parents and pass down the traits/moves the game supports; Minimal Grinding remains deferred.

## Draft first-access windows for uncovered families

These broad windows populate `draft_first_access_band` in the ledger. They are starting hypotheses for campaign planning, not approved locations or hard stat gates.

| Roster signal | Draft first-access window | Review before locking |
|---|---|---|
| Low BST / utility / early-stage family | Opening through Badges 1–3 | Early moves, status/speed tricks, starter matchup, and encounter share |
| Standard final-stage family | Badges 2–5 | Base-form catch level, evolution timing, and counterplay before the next boss |
| High BST final stage | Badges 4–6 | Consider earlier base-form access only when level/evolution pacing supports it |
| Very high BST / pseudo-legendary candidate | Badge 6 through League for the line's pre-evolution | Gate final evolution fairly; don't confuse line potential with caught-form strength |
| Legendary / Mythical / Paradox / special event | Late-game or postgame quest/static | State whether it can be shiny, reset, repeated, or hunted by another method |
| Starter family | New Game for the chosen regional pool | Add another path for unchosen regions if full-roster completion is intended |

Habitat and exact map choice still take priority within a window. Revisit the windows against actual team compositions, route pace, boss caps, and the candidate's moves/abilities.

## What the first pass shows

Current Hoenn wild data already place 111 families somewhere in the campaign map tables, but only 23 have a source in the opening-to-Roxanne window. The current table contains many more mid/late placements; the map windows are heuristic and overlap, so those counts are a snapshot, not final route allocations. The 151 no-direct-source families include a broad strength spread (low utility through legendary/paradox), so they should not all be solved with the same rare encounter or postgame bucket.

The next focused design pass should assign exact **Hoenn habitat + method + story window** to all 222 families lacking a verified Hoenn campaign source, then audit the other 124 candidate families for map gates, line branches, shiny behavior, and same-save completion. Start with Routes 101–104 and Petalburg Woods: those determine early team diversity, available answers to Roxanne, and how many of the 733-entry roster the player can actually hunt before the first cap.

## Related artifacts

- `acquisition-plan.csv` — source paths, gap rows, and draft access windows for every supported enabled family.
- `acquisition-coverage.csv` — corrected 733-entry roster accounting and one explicit full-save coverage obligation per supported enabled family.
- `normal-roster-balance.md` — Normal-mode balance framework covering the complete curated roster, boss access envelopes, evolution pacing, and cap design.
- `normal-roster-balance.csv` — one review row for each of the 733 National Dex species, linked to its family/forms and current family-level acquisition evidence.
- `normal-roster-inputs-733.csv` / `normal-roster-inputs-by-form.csv` — rebuilt balance inputs for all 733 Dex entries and 1,011 configured species/forms.
- `roster-availability.csv` — original wide audit with current map and script evidence.
- `normal-boss-checkpoints.csv` — story order, configured parties, and draft cap anchors.
- `starters-and-rival.md` — region starter pools and rival counter-pick rule.
- `imperium-source-review.md` — source-code review and adaptation recommendations.
