# Badge 1 stabilization plan: establish the Lv15 baseline

**Purpose:** reconcile the opening-to-Roxanne work already in Shiny Vice, compare it with vanilla Emerald, Emerald Imperium, and Radical Red, and define what must be settled before the campaign moves to the next badge band.

**Scope:** the required Route 103 starter battle through Roxanne and the Stone Badge. This plan covers Normal, which is intended to be challenging. Hard mode remains a later pass. The player may heal between trainer battles and before Roxanne; balance each fight on its own rather than relying on attrition.

## Current Shiny Vice snapshot

| Area | Current state |
|---|---|
| Cap and access | Lv15 from the opening through Roxanne; badge 1 raises it to 19. The opening rival happens before Poké Balls, so the player has only the chosen starter. Land catches begin after Birch gives five Poké Balls. Surf, fishing, and Rock Smash pools are excluded from this band because their methods are still gated. |
| Land encounter envelope | Six tables: Route 101 (8 families), Route 102 (8), Route 103 (7), shared Route 104 north/south (8), Petalburg Woods (9), and Route 116 (11). The opening access ledger groups these into 38 distinct enabled families, plus the selected starter. These are huntable pool counts, not proof that every route tile or optional trainer is reachable. |
| Encounter customization | All six tables differ from vanilla Emerald in the current source. Route 116 keeps its six familiar families and adds five family macros; Geodude is a 1% slot. Route 104's Taillow/Wingull/Fletchling total is 30%. The 12-slot weights remain the Emerald vector. |
| Required and optional battles | Route 102 teams were expanded; the Woods grunt now has Poochyena and Carvanha; Route 104 trainers were revised; the optional Route 104 rival has authored support sets plus a dynamically assigned counter-starter; all ten Route 116 teams were expanded; Gym trainers now lead from Geodude into Aron, Lileep, and Nosepass. Exact deltas are in the trainer balance pass. |
| Trainer AI | Trainer and rival records included in the current first-badge pass use the three `Basic Trainer` checks (avoid bad moves, seek knockouts, evaluate move viability). Roxanne uses smart switching and smart mon choices without a flat status preference; engine scoring checks caught the status bonus overriding a guaranteed knockout. No included first-badge trainer has omniscient access to the player's unseen moves, ability, or item. The expansion AI guide recommends this three-flag profile for normal trainers. |
| Roxanne | Four Pokémon at Lv13/14/14/15: Geodude (Sturdy, Hard Stone), Aron (Rock Head), Lileep (Storm Drain, Oran Berry), Nosepass (Sturdy, Berry Juice). Moves, nature, IVs, and AI are authored. The party is in runtime data; the remaining work is matchup and play-through validation, not wiring. |
| Recovery and battle rules | Healing between fights and before the leader is allowed. Current Normal rules prohibit Bag use during trainer battles. Do not assume the player has the Rock Tomb TM before the fight; it is Roxanne's reward. |



The eight east-side Route 103 trainer records are not included in the current pass because their pre-badge reachability is unresolved. They still use the older Check Bad Move profile; include them in this chunk only if the map/gate audit proves the player can reach them before Roxanne.

The family totals above are grounded in `opening-hoenn-access.csv`, which consolidates repeated slots and evolution branches by family. Do not use the conflicting 31/32-family totals in older drafts.

## Cross-reference: what to take from each game

| Reference | What it demonstrates | What Shiny Vice should take from it |
|---|---|---|
| Vanilla Emerald | Familiar Hoenn route order and 12 weighted land slots. Its six corresponding tables cover 15 families in total. Its first Roxanne party is Geodude Lv12, Geodude Lv12, and Nosepass Lv15; Gym trainers repeat Geodude, and the Woods Aqua grunt has one Poochyena. | Preserve recognizable locations and the slot system; make every content departure explicit. The current encounter tables and parties are a deliberate Normal redesign, not a claim of vanilla equivalence. Compare each trainer's party, items, moves, AI, and script status against `pret/pokeemerald`, not only the species. |
| Emerald Imperium | Connects encounter methods and gates to trainer progression and boss preparation. Its opening route trainers build toward the boss; its Roxanne source uses four role-based Pokémon, authored moves/items/abilities/stats, and a stronger AI package. The checked release branch and supplied v1.3/v1.3.1 materials do not always agree, so individual teams need a pinned reference snapshot. | Adopt the linked-data workflow, role clarity, and difficulty budget concentrated at major fights. Do not copy its roster, exact cap milestones, or optional Gardenia content. Keep Shiny Vice's Gym-led cap policy and verify its own 27-starter/access envelope. |
| Radical Red v4.1 Normal | The documented Pewter Brock fight has four distinct sets under a Lv15 cap: Geodude-Alola Lv13, Varoom Lv13, Onix Lv14, and Archen Lv12. Their items and abilities have explicit jobs (including Custap/Sturdy, Air Balloon/Filter, and Berry Juice/Sturdy), with mixed coverage and utility. | Use this as a boss-set quality benchmark: every Pokémon should have a useful role, the item/ability/moves should reinforce it, and the player should have multiple answers. Shiny Vice matches the four-member structure and cap, but its Lv15 ace is a higher top level than Brock's Lv14 team. Radical Red's original v4.1 game source was not found in the existing research, so compare documented teams and rules, not hidden AI implementation. |

Radical Red's team data here are the v4.1 Normal reference reproduced by a public tracker and cross-checked against the supplied v4.1 boss workbook; it is not source code. Imperium's public `release` branch moves independently of the supplied files. Pin versions or commits before treating either team's exact sets as fixed references.

## What is already a solid base

- The opening has a specific contract: chosen starter-only opening rival, catches after the Poké Ball gift, Lv15 cap, optional preparation, and recovery between trainer battles.
- The current six-map land union is 38 families, versus 15 in the corresponding vanilla Emerald tables. Route 116 is customized in the current data; its older “vanilla-equivalent” description is stale.
- The trainer pass gives ordinary battles intentional party size and moveset progression, while the required Aqua encounter and optional rival have defined roles.
- Basic move-scoring AI is now consistent across the first-badge trainer slice. Roxanne has stronger but non-omniscient switching/status behavior.
- Roxanne is a runtime four-member boss set rather than an unwired proposal. Her role structure and support levels are already authored.

These are content and implementation foundations, not a claim that the chunk is balanced. The current pass has not been play-through verified.

## Work order to lock the chunk

1. **Make the source snapshot authoritative.** Reconcile the opening access CSV, encounter draft, trainer pass, first-badge inventory, and README. Correct stale totals and label pre-pass party tables as historical. Record the vanilla Emerald revision and Imperium source/docs version used for the comparison; keep Radical Red identified as v4.1 Normal.
2. **Finish the reachability boundary.** Verify Route 103's eastern objects and Route 116 side paths against map connections/collision and scripts. Confirm the shared Route 104 encounter map and the exact pre-badge item/gift access. Keep Route 103's post-rival catch gate, Woods Wally tutorial, optional Route 104 rival, and Route 116 optional fights distinct in the ledger.
3. **Complete the vanilla delta ledger.** For each reachable fight, compare trainer ID and script, party species/count/order/levels, held items, trainer healing items, moves, abilities, IVs/natures, AI, double-battle status, optional/rematch flag, and reward. Mark each field as inherited, changed, or not applicable. Record vanilla party shapes separately from the new Normal proposal.
4. **Tune the route curve and encounter distribution.** Review one fight at a time in story order: opening rival; Route 102; Route 104 south; Woods; optional Route 104 rival; Route 104 north; Route 116; Gym trainers. Confirm an early catch-and-train window, meaningful route identities, and no optional fight becoming a hidden toll. Recheck the 30% bird share on Route 104, 1% Geodude on Route 116, and duplicated Wurmple/Nidoran family aggregation against the intended hunt experience.
5. **Resolve boss-set quality issues.** Audit Roxanne's damage and speed breakpoints against all 27 starter choices and representative teams from the 38-family envelope, using only pre-fight moves/items/evolutions. In particular, decide whether Aron should keep Rock Head with no recoil move, whether three Sturdy users would be better than leaving that ability inactive, and whether Sturdy plus Berry Juice on Nosepass creates an interesting check or excessive extra survival. Keep player healing before the leader in every matchup review.
6. **Verify the authored result in-game.** Confirm party parser behavior, dynamic rival species/moves for all six optional branches and all 27 starters, field reachability, rewards, cap timing, AI choices at low levels/doubles, and actual battle difficulty. Adjust content only after these observations; then mark the chunk locked and start the post-badge/Rusturf-to-Dewford band.

## Lock criteria

Move past Badge 1 only when:

- one current source of truth reports the same encounter-family counts and trainer parties across all planning files;
- the pre-Roxanne access envelope and optional fights are script/map verified;
- every reachable trainer has a complete vanilla delta and an intentional Normal role;
- the 27 starter paths and realistic captured-team options each have plausible counterplay against Roxanne;
- no unused ability, misleading item, illegal move, inaccessible counter, or unintended post-badge content remains in the fight plan;
- an in-game route pass confirms the cap/recovery contract and that the intended challenge comes from each encounter's design, not accumulated damage.

## References

- Vanilla Emerald [wild encounters](https://github.com/pret/pokeemerald/blob/master/src/data/wild_encounters.json), [trainer parties](https://github.com/pret/pokeemerald/blob/master/src/data/trainer_parties.h), and [trainer records](https://github.com/pret/pokeemerald/blob/master/src/data/trainers.h).
- Imperium [release source](https://github.com/iriv24/pokeemerald-expansion/tree/release), [encounter tables](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/wild_encounters.json), and [trainer parties](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party).
- Radical Red v4.1 Normal [Brock set reference](https://radicalredtracker.com/bosses/brock); use the supplied v4.1 boss workbook in `Radical Red Docs-20261022T074330Z-1-001.zip` as the accompanying project reference.
- Shiny Vice current sources: `src/data/wild_encounters.json`, `src/data/trainers.party`, `data/maps`, `docs/design/gameplay-tables/opening-hoenn-access.csv`, and `docs/tutorials/ai_flags.md`.
