# Gameplay planning tables

Design inventories and phase plans. The first New Game slice now wires starter-set selection, Birch's starter previews/gifts, and the Hoenn rival's same-pool counter-pick in source. Acquisition placements, Normal boss teams, and cap milestones remain planning proposals.

- Starters and rival: starter-set/slot model, Birch's three-ball bag flow, exact shiny-preview-to-gift identity, Hoenn rival counter-pick rule, and configured rival inventory. The starter-set choice does not change the Hoenn region or story.
- `starter-region-pools.csv`: canonical, code-ordered mapping for all 27 player starters and their rival counter-picks.
- `rival-starter-progression.csv`: all 135 region/slot/checkpoint combinations for the five current rival checkpoints, including the rival species after source-defined level evolutions. Movesets remain an authored Normal team decision.
- Roster availability: one row per configured family macro, including family member species IDs, current enable state, map-backed encounter locations/methods/levels, scripted gifts/eggs/statics, and estimated first campaign band.
- Acquisition plan: source-by-source Hoenn wild paths with slot weights and levels, Hoenn script sources, design-gap rows, and draft first-access windows. Dex counts and family type/BST cues have been rebuilt from the configured roster; balance classes and map reachability remain under review.
- Acquisition coverage: one row per supported enabled family, with corrected distinct National Dex species, all enabled `SPECIES_*` IDs (including forms), current Hoenn evidence, and a full-roster acquisition requirement. This is the canonical family checklist for ensuring every enabled family can be acquired in a single save.
- Acquisition balance: first-pass roster distribution principles, coverage snapshot, and proposed timing rules informed by Emerald Imperium.
- Normal roster balance: Normal-mode design framework for balancing all 733 enabled Dex species through access, encounter weight, evolution pacing, move/item access, boss teams, and cap milestones. It is planning guidance, not a set of approved numerical placements.
- `normal-roster-balance.csv`: one row for each of the 733 National Dex species, linked to its enabled family and forms, current family-level acquisition evidence, and pending review fields for strength, roles, evolution timing, boss access, and shiny-hunt support.
- `normal-roster-inputs-733.csv`: rebuilt one-row-per-Dex balance input with current source stats, types, abilities, egg groups, explicit evolution/move references, configured form counts, family-level acquisition evidence, and open boss-access checks.
- `normal-roster-inputs-by-form.csv`: source inventory for all 1,011 configured species/form IDs in those 346 families. Includes explicit base stats, types, abilities, egg groups, evolution edges, and selected Gen 9 level-up learnset summary when source initializers expose them. Blank cells indicate source/macro review is needed, not zero or unavailable.
- `tools/gameplay_tables/build_roster_inputs.py`: reproducible extractor that rebuilds the per-Dex and per-form inputs, refreshes `normal-roster-balance.csv` and `acquisition-plan.csv`, and derives `rival-starter-progression.csv`; validates the 733 species, 346 families, 1,011 species/form IDs, and 27 starter choices.
- Normal boss checkpoints: story order, source trainer IDs and script references, configured source party details, and explicitly provisional cap anchors.
- `opening-hoenn-access.csv`: source-backed land encounter families and levels available before Roxanne, with the Route 103 Poké Ball gate and hunt/balance checks. Fishing and Surf sources are excluded from the opening roster.
- The opening rows in `normal-boss-checkpoints.csv` distinguish the optional Route 104 and Rustboro rival events (separate flags), include the required Petalburg Woods Aqua fight, and mark Rusturf Tunnel order/cap as unresolved until map blockers are checked.
- Normal implementation plan: phased development roadmap for the New Game menu, Birch's bag and shiny starters, same-pool Hoenn rival, Normal rules, per-save caps, banded 733-species acquisition, forms/postgame, balance/release checks, and deferred QoL options.
- Normal cap milestones: proposed active ace-level caps and the main-path victory flags that advance them; optional rivals do not advance the cap ladder.
- Radical Red and Imperium research: version-scoped reference findings.
- Imperium source review: acquisition, trainer-party authoring, AI, starter, cap, and balancing patterns with recommendations for Shiny Vice.

## Source interpretation

include/config/species_enabled.h is the roster switchboard. At this snapshot, all nine generation switches are TRUE, but 192 family macros are individually FALSE. Of 539 config macros, 347 resolve to TRUE; 346 correspond to supported species-family blocks. The user confirms this enabled set is the curated roster. Counting distinct `.natDexNum` values in enabled family blocks in `src/data/pokemon/species_info/` confirms 733 National Pokédex species. P_FAMILY_SINISTCHA is an unused extra macro; Sinistcha data are included under P_FAMILY_POLTCHAGEIST.

src/data/wild_encounters.json supplies map-backed encounter paths for any species in a family. The table retains the prior root-species match for comparison. Map IDs do not prove that a location is reachable at the estimated story band. Battle Frontier facility tables are omitted from campaign acquisition paths.

Scripted sources extract explicit givemon, giveegg, and static-battle species commands from map .inc scripts. This does not prove each event is reachable or repeatable. Breeding, evolution-only access, trades, shops/fossils, conditional events, postgame, and distributions still need separate audits where no direct source appears. A source match is evidence only; it is not a full-roster acquisition guarantee.

The first `acquisition-plan.csv` pass had a parser defect: it reported zero National Dex entries and zero type/BST for 22 families, including Goldeen and Seaking. The family National Dex counts are now recomputed from enabled `.natDexNum` data and sum to 733 distinct species. Family type and max-normal-form-BST cues are rebuilt from the configured form inventory, excluding battle-only Mega, Gmax, Tera, Ultra, Primal, Eternamax, and fusion forms from the normal BST maximum. Existing `balance_class` values remain provisional pending review against these refreshed metrics and boss access. Use the per-Dex and per-form inputs for detailed review. The latter currently parses complete explicit stats for 950 of 1,011 species/form IDs and finds direct initializers for 965. C macro-backed or generated rows remain blank and require source/preprocessor review; blanks are not zero values. Both inputs use the repo's GEN_LATEST stats/types/abilities/egg-group settings and the Gen 9 level-up learnset selected by `P_LVL_UP_LEARNSETS`.

Boss parties come from src/data/trainers.party; script references come from data/maps. Current source teams are inventory, not Normal proposals. Draft caps are non-decreasing source-ace anchors; optional fights stay off the main ladder and E4/Champion share one provisional cap. All cap values and team edits remain open pending Normal rules, curated roster, and accessibility audit.

Design PDFs are reference material, not binding requirements. The concept calls numerical odds/caps placeholders and leaves story direction open. The v4 system spec's limited roster direction conflicts with the user's current Gen 1-9 curated-roster direction and source config; reconcile project decisions before changing config. Current availability reflects source only.

## Coverage limits and next decisions

1. Current config enables 346 supported family blocks and 733 distinct National Pokédex entries; this is the authoritative roster for acquisition planning.
2. Wild locations are enumerated, but map/event story gates and cross-generation route reachability are not verified.
3. Direct gifts, eggs and static encounters are recorded; trade, fossil/shop, evolution-only, daycare, conditional and postgame paths remain incomplete. The new coverage table makes these explicit design obligations for all 346 families.
4. Verify boss script timing marked open, then design teams from actually reachable species/items/moves.
5. Use the proposed Normal contract (Set battle style, no Bag during trainer battles, staged AI/items/IV/EVs, and independently selected Off/Soft/Hard cap semantics), then replace provisional cap anchors with approved milestones.
6. Preserve IVs, EVs and breeding depth in this pass; Minimal Grinding remains deferred.

Campaign bands are heuristics based on map names, not acquisition guarantees.
