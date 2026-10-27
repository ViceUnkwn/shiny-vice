# First Badge Content Plan: Lv15 Opening Through Roxanne

Status: historical planning inventory. Runtime encounter and trainer-party edits have since been applied; use [badge-1-opening-chunk-draft.md](badge-1-opening-chunk-draft.md) and [badge-1-trainer-balance-pass.md](badge-1-trainer-balance-pass.md) for the current design and source-party snapshot.

## Goal and boundary

Complete the player's full Lv15 content envelope from the opening through Roxanne's first badge. Include every reachable map/method, one-time story event, optional rival battle, route trainer, gym trainer, and the Roxanne fight itself. The Stone Badge ends this slice; Devon/Briney, Rusturf Tunnel's Aqua rescue, and the Rustboro rival event are post-checkpoint content in this checkout.

Opening level cap is already wired at Lv15. Keep it at Lv15 through the first badge. Cap advancement to Lv19 occurs after Roxanne grants badge 1. Don't add another story cap to this band.

## Reference comparison: Emerald Imperium

The release branch is a good source for content design patterns and is structurally close enough to compare at the same map IDs:

- Its opening land maps still use the familiar 12 weighted encounter slots. ShinyVice uses that same table shape. The value is in how a curated roster is distributed across the available map ecology, not importing a new encounter engine.
- Its route choices fit the locations: Route 101 has a simple low-level spread; the woods and later Route 116 introduce different families/roles. In this checkout, Imperium's exact species are a different roster and should not be copied.
- Imperium has an optional Gardenia challenge in Petalburg Woods, in addition to regular Bug Catchers and the required Aqua grunt. The event has a rematch/upgraded variant after Wattson and gives several valuable rewards (including ten Leaf Stones). The useful idea is clearly labeled optional challenge content with a rematch state. The team/rewards are far beyond the needs of the ShinyVice opening and should not transfer unchanged.
- Its regular opening trainer parties use multiple species and rising levels, even when the team is simple. Its Roxanne has four Lv14–15 Pokémon, role-specific moves and abilities, held berries/items, natures, high IVs, and a more capable AI profile. ShinyVice already has a four-member Normal Roxanne party at Lv13–15; compare the current party details in the vanilla-delta audit below. The remaining first-badge work is to validate it against the actual Lv15 access envelope and systematically classify ordinary trainers and rivals.
- Imperium's Gym leader designs show the value of team identity and an ace with a job. ShinyVice's current Normal Roxanne is already runtime-custom: Geodude Lv13, Aron Lv14, Lileep Lv14, and Nosepass Lv15, with custom moves, abilities, held items, IVs, and advanced AI. That party needs balance/playthrough validation; the ordinary opening trainers and rival branches still need their own systematic vanilla-delta audit.
- Imperium's cap code uses additional story milestones after Roxanne. ShinyVice already correctly starts at Lv15 and increments after badges; the first band needs no extra cap milestones.

Sources checked: Imperium release's early map encounter entries, Route/woods trainer scripts, Petalburg Woods optional Gardenia event, trainer parties and caps; ShinyVice map scripts, live encounters, trainer parties, cap code, opening access audit, boss checkpoint/design CSVs.

## Source-backed progression and scope

| Order | Map/event | What belongs in this pass |
|---|---|---|
| 1 | Littleroot and Route 101 | Starter choice; Birch rescue/tutorial encounter. Route 101 land table is present, but capture starts only after the Route 103 battle and Poké Ball gift. Include any starter gift/rules and item/gift sources that affect opening balance. |
| 2 | Route 103 first crossing | Required rival counter-pick battle at Lv5, before Poké Balls; it must remain starter-only. After getting Poké Balls, the player can backtrack and catch the reachable Route 103 land encounters. The other Route 103 trainer objects are east of the water crossing; their pre-gym access is not established, so do not include them in the opening battle curve pending tile-path verification. |
| 3 | Oldale, Route 102 | All four initial trainer battles (Calvin, Rick, Tiana, Allen), Route 102 land table, town services/items/gifts. No rod/Surf source is usable yet. |
| 4 | Petalburg City | Norman story introduction; Wally catches Ralts using the player's loaned Zigzagoon. This is a tutorial/event, not a trainer battle against Wally. Record the catch event and its acquisition rules. |
| 5 | Route 104 south | Route 104 land table, accessible trainers/items/berries, and route-side gifts. This is the southern half of the same map/table as the northern section. |
| 6 | Petalburg Woods | Required Aqua grunt story battle; optional Lyle and James trainer fights; land encounters and pickups. Do not count the after-badge Devon/Rusturf event here. |
| 7 | Route 104 north and Briney's Cottage | Same Route 104 land table as the south half; accessible regular trainers and gifts; optional same-pool rival battle (yes/no, own defeat flag) is pre-Roxanne content. Audit its three starter branches and party levels. |
| 8 | Rustboro City | City buildings, gifts/trades/items, Devon Corp access and Gym. Route 116 is an optional dead-end reachable from the city before the Gym. The Rustboro rival event is not in this pre-badge pass; current script turns it on through Roxanne's Devon Goods sequence. |
| 9 | Route 116 | Land encounters and all ten trainer fights: Joey, Jose, Jerry, Clark, Janice, Karen, Sarah, Dawson, Devan and Johnson. Include items/berries and verify the route's inaccessible east exit at Rusturf Tunnel before badge 1. |
| 10 | Rustboro Gym | Puzzle and all three Gym trainers (Josh, Tommy, Marc), then Roxanne. Review gym trainer-to-leader cumulative difficulty and healing/item access. |
| 11 | Badge event | Stone Badge, TM Rock Tomb, defeated-gym flag, cap moves to 19. The Devon Goods coordinate scene/Rusturf Tunnel Aqua battle start after this milestone, so list those in the next band. |

### Encounter methods in the Lv15 window

**Author/review as live:** land on Route 101, 102, 103, 104 (shared north/south table), Petalburg Woods, and Route 116.

**Record as present but locked:** fishing/water pools on routes that need a rod or Surf; Surf pools; Rock Smash pools. The Old Rod is received in Dewford, Surf is usable after Norman, and Rock Smash is usable after Wattson, all outside this slice. The method matrix should retain these source rows but mark them unavailable before Roxanne.

For each live land table, validate: all 12 slots and encounter weights; level range; species/family aggregation; repeat-family and evolution-line odds; story reachability; catch/move/evolution pacing under Lv15; and early-saver usability. Route 104 must be audited as one shared table because both map halves share the encounter map ID. Petalburg Woods has multiple species slots from Wurmple branch evolutions, so report both slot species and unique families.
### Vanilla Emerald delta: opening land tables

Compared the current `src/data/wild_encounters.json` against the pre-design encounter data and the pret/pokeemerald Emerald source. This distinguishes edits to the encounter content from the 12-slot format and weights inherited from Emerald. The land-slot weight vector is unchanged; the species, repeated-slot distribution, and in some cases level ranges are customized as follows:

| Map | Vanilla Emerald land pool | Current Shiny Vice land pool | Delta status |
|---|---|---|---|
| Route 101 | Poochyena, Wurmple, Zigzagoon (Lv2–3) | Those plus Pidgey, Caterpie, Rattata, Sentret, Weedle (Lv2–3) | **Custom**: adds five families and redistributes slots; levels broadened within the same band. |
| Route 102 | Poochyena, Wurmple, Lotad, Zigzagoon, Ralts, Seedot (Lv3–4) | Same six plus Mareep and Hoppip (Lv3–4) | **Custom**: adds two families and redistributes slots. |
| Route 103 | Poochyena, Wingull, Zigzagoon (Lv2–4) | Those plus Shinx, Starly, Pawmi, Rookidee (Lv2–4) | **Custom**: adds four families and redistributes slots. |
| Route 104 | Poochyena, Wurmple, Marill, Taillow, Wingull (Lv3–5) | Wurmple, Taillow, Marill, Wingull, Fletchling, Hoppip (Lv4–5) | **Custom**: removes Poochyena, adds two families, redistributes slots, and raises the minimum level. |
| Petalburg Woods | Poochyena, Wurmple line, Shroomish, Taillow, Slakoth (Lv5–6) | Those plus Oddish, Paras, Spinarak, Ledyba (Lv5–6) | **Custom**: adds four families and redistributes slots. The Woods were changed; they are not vanilla in the current source. |
| Route 116 | Poochyena, Whismur, Nincada, Abra, Taillow, Skitty (Lv6–8) | Those six plus Budew, Nidoran♀, Nidoran♂, Drowzee, Magby, Geodude; 12 slots at Lv6–8. | **Custom:** keeps the six familiar species and adds five family macros (Nidoran♀/♂ share a family); Geodude is a 1% hunt. |

The current land pool contains **38 families** across the six maps; the corresponding six vanilla land tables contain **15 families** in their union. “Custom” here means the runtime land table differs from Emerald's source data. It does not mean the table has passed playtesting or that the resulting family has a verified capture opportunity on every route section. Route 116 is now a custom addition; its current data should be counted in the opening pool. Water and fishing are separate methods and remain locked in the pre-Roxanne window; their current method-slot layout also has a project-wide fishing-layout edit, so audit those independently when the story unlocks them.



### Trainer and rival delta status

The opening trainer party inventory is a current-source snapshot, not yet a vanilla comparison. Roxanne is already a runtime customization: current Normal uses Geodude Lv13, Aron Lv14, Lileep Lv14, and Nosepass Lv15; vanilla Emerald uses two Geodude at Lv12 and Nosepass at Lv15. The trainer's moves, AI, held items, and IVs also differ. Do not treat the proposed Roxanne party as unwired. The next audit should compare each reachable Route 102/104/Woods/Route 116 trainer and both pre-gym rival branches against Emerald, then record each party field that differs before proposing more edits.
Baseline sources: [pret/pokeemerald wild encounter data](https://github.com/pret/pokeemerald/blob/master/src/data/wild_encounters.json) and [pret/pokeemerald trainer definitions](https://github.com/pret/pokeemerald/blob/master/src/data/trainers.h). The current project history records the opening table rewrite in commit `b290c35` (“Adopt Imperium fishing slot layout”); that edit also changed the global fishing slot groups. The pre-design data in this repository is the source snapshot immediately before that commit.

## Battle ledger to author and balance

This is the complete first-pass list of trainer encounters surfaced by the current opening map scripts. Retain optional and double battles as such, and count each battle instance once when two script approaches lead to the same fight.

| Area | Battle entries |
|---|---|
| Route 103 | Required starter rival (three counter-pick branches). The reachable west-side land table becomes catchable after the Poké Ball gift. Daisy, Amy & Liv, Andrew, Miguel, Marcos, Rhett, Pete and Isabelle are east-side map objects; hold those battles out of the pre-gym ledger until the water-crossing gate is confirmed. |
| Route 102 | Calvin, Rick, Tiana, Allen. |
| Petalburg Woods | Lyle, James, required Aqua grunt. |
| Route 104 | Optional rival (three starter branches); Ivan, Billy, Haley, Winston, Cindy, Gina & Mia double battle, Darian. |
| Route 116 | Joey, Jose, Jerry, Clark, Janice, Karen, Sarah, Dawson, Devan, Johnson. |
| Rustboro Gym | Josh, Tommy, Marc, Roxanne. |

The script inventory and current party snapshot below are source evidence, not proof that every object is reachable before Roxanne. Track trainer IDs, trigger, optional status, rematch state, party, items, AI and access gate separately. Rustboro rival and the post-Roxanne Aqua grunt are outside this band.


## Historical trainer party snapshot before the Normal party pass

| Area / encounter | Current authored party | Access and source notes |
|---|---|---|
| Birch rescue | Scripted wild Zigzagoon Lv2; player chooses a starter from the bag. | This is a fixed opening battle, before standard route encounters. The starter chooser hands over the selected Pokémon; the route tutorial is not a trainer battle. |
| Route 103 opening rival | One opposing starter at Lv5; six Brendan/May and player-slot records. | Required before Poké Balls. The selected starter-region pool now supplies the rival counter-pick at runtime. All six opening rival records now use the same basic move-scoring profile; the selected counter species and generated moves remain source-driven. |
| Route 102 | Calvin: Poochyena Lv5. Rick: two Wurmple Lv4. Tiana: Zigzagoon and Shroomish Lv4. Allen: Zigzagoon Lv4 and Taillow Lv3. | Four ordinary single battles on the open route. The original records used Check Bad Move and mostly relied on level-up moves; the current Normal pass adds explicit moves and Basic Trainer scoring. |
| Route 104 optional rival | Two Pokémon, ace Lv15. Treecko player: Lotad Lv13 + counter starter Lv15. Torchic player: Slugma or Torkoal Lv13 + Mudkip Lv15. Mudkip player: Wingull Lv13 + Treecko Lv15. | Yes/no challenge near Briney's Cottage; can be declined and uses `FLAG_DEFEATED_RIVAL_ROUTE_104`. The six optional rival records now share the three basic move-scoring checks. Slugma/Torkoal are not in the current six-map opening land pool, so review rival acquisition/story logic and intended fairness. |
| Route 104 regular trainers | Ivan: three Magikarp Lv5/6/7; Billy: Zigzagoon Lv5 + Seedot Lv7; Haley: Lotad + Shroomish Lv6; Winston/Cindy: Zigzagoon Lv7 each with Full Restore; Gina & Mia: Seedot + Lotad Lv6 double battle; Darian: Magikarp Lv9. | Eight battle setups, including one shared twins double battle. Full Restores on the Lv7 single-Pokémon Winston/Cindy fights also appear in vanilla Emerald; change them only as an explicit Normal redesign decision. |
| Petalburg Woods | Lyle: four Wurmple Lv3; James: two Nincada Lv6; required Aqua grunt: Poochyena Lv9. | Lyle and James are optional trainer battles; the Devon researcher scene forces the Aqua battle from either approach. Victory gives a Great Ball. Wally's earlier catch tutorial is separate and restores the player's party afterward; it does not give the loaned Zigzagoon or Ralts to the player. |
| Route 116 | Joey: Machop Lv9; Jose: Wurmple + Nincada Lv8; Jerry: Ralts Lv9; Clark: Geodude Lv8; Janice: Marill Lv9; Karen: Shroomish Lv9; Sarah: Lotad + Zigzagoon Lv8; Dawson: Zigzagoon + Poochyena Lv8; Devan: two Geodude Lv8; Johnson: Shroomish + Lotad Lv8. | Ten ordinary trainer scripts lie along the Rustboro-side route. Verify the side paths around Cut trees before counting every trainer as unavoidable. Route 116 land encounters are Lv6–8. The Devon employee's Repeat Ball is hidden until the post-badge story sequence. |
| Rustboro Gym | Josh: Geodude Lv10; Tommy: two Geodude Lv8; Marc: two Geodude Lv8; Roxanne: Geodude Lv13, Aron Lv14, Lileep Lv14, Nosepass Lv15. | Three trainer records are near-duplicates with no deliberate role variation; only Josh has an explicit move (Tackle). Roxanne is now authored as the Normal boss draft. TM Rock Tomb is a post-victory reward, not a player-access assumption for the fight. |
| Route 103 eastern trainer group (deferred) | Daisy: Shroomish + Roselia Lv14; Amy & Liv: Plusle + Minun Lv15; Andrew: Magikarp Lv5/10/15; Miguel: Skitty Lv15; Marcos: Voltorb Lv15; Rhett: Makuhita Lv15; Pete: Tentacool Lv15; Isabelle: Marill Lv15. | Trainer objects are at x=36–71 on the east side of the Route 103 map; several are water-side/swimmer objects. Their script presence does not prove pre-Roxanne access. Keep them out of the Lv15 opening plan until the map crossing is verified. |

The current opening land tables contain **38 distinct wild families** across the six maps (8/8/7/8/9/11 per map, with overlap), plus the selected starter. These counts are consolidated by family in `opening-hoenn-access.csv`; the Route 116 additions are included. Land slots are usable after Birch's five-Poké-Ball gift; Route 102/103/104 water and fishing rows are present in JSON but not available here: Surf is badge-gated later and the first rod is received in Dewford after Roxanne. The Roxanne envelope therefore uses the six land tables and the selected starter only.

## Pre-gym items and scripted gifts that affect preparation

| Source | Pre-Roxanne availability / balance effect |
|---|---|
| Birch's lab | Gives the selected starter first; after the Lv5 Route 103 rival, Birch grants the Pokédex and five Poké Balls. This is the first point where route catches can join the team. |
| Route 102 | Potion item ball on the open route. |
| Route 104 | Chesto Berry gift; Bullet Seed TM gift; Potion, Poké Ball, X Accuracy and PP Up item balls; berry trees and hidden pickups. White Herb delivery is hidden until `FLAG_BADGE03_GET`, so it is not in the first-Gym envelope. |
| Petalburg Woods | Ether, X Attack and Paralyze Heal item balls; Miracle Seed gift; the mandatory Aqua battle rewards a Great Ball. |
| Rustboro | Pokémon School gives Quick Claw; Cutter's House gives HM Cut (field use is badge-gated); a house gives Premier Ball; Mart sells Poké Balls and healing items. Pokémon Center is available for field healing between battles. |
| Route 116 | Ether, Repel, Potion and X Special item balls, plus a hidden Super Potion. HP Up/Black Glasses on the far east and the Devon employee's Repeat Ball are outside or gated from the pre-badge story path; verify tile access before counting them. |
| Route 103 east | Guard Spec and PP Up item balls are with the deferred east-side object group; don't count them in pre-gym prep until that crossing is verified. |
| Post-badge rewards | Roxanne gives TM Rock Tomb and the Stone Badge; do not assume the player has that TM during her battle. Badge 1 advances the level cap from 15 to 19 and opens the Devon/Rusturf sequence. |
## Recommended work order

1. **Freeze the Lv15 reachability envelope.** Use map connections, event flags and method/badge gates to verify which tile areas, NPCs, gifts and land encounters are available before Roxanne. Add Route 103 backtracking, both Route 104 halves, Route 116 dead-end access, and pre-badge exclusions to the existing opening audit.
2. **Reconcile encounter sources.** Compare the six live land maps against wild_encounter_inventory.csv and opening-hoenn-access.csv. Rebuild any stale acquisition-plan and roster-availability rows from current runtime data. Write down intended first-seen and repeat-hunt roles for each family, including rare targets and starters.
3. **Set the Lv15 encounter curve.** Adjust levels and slot shares only after the current family pool is evaluated together. Avoid piling the same role (especially birds and early Grass/Water answers) onto every early route. Make starter region choice not determine access to Roxanne counterplay. Keep Shroomish's Woods presence and timing deliberate.
4. **Build every regular trainer team across the route order.** Give ordinary trainers compact, readable roles and increasing party size/levels so healing and captures make sense. Don't let optional Route 104 rival or late Route 116 trainers accidentally overtake Roxanne as the difficulty peak.
5. **Design scripted fights.** Preserve the Lv5 starter-only Route 103 battle. Design the optional Route 104 rival for the actual caught pool and cap 15. Keep the Woods Aqua grunt as a short story bridge. Add no unrequested optional super-boss in the Woods in this first pass; Gardenia can be considered later as a discrete side challenge with its own unlock and reward budget.
6. **Design Roxanne from the actual envelope.** The current Normal draft uses four members with a Lv15 ace, following Imperium team size while keeping Shiny Vice cap. Aron is selected; tune coverage, defensive tools, AI, and held items against all 27 starter choices and the reachable roster.
7. **Close progression around the badge.** Verify rewards, Stone Badge field moves, TM Rock Tomb, cap transition 15→19, Devon Goods story setup, Rusturf Tunnel enemy activation and the post-badge rival trigger. No event in the next band should accidentally be required to finish this one.
8. **Update records and mark status.** Update boss checkpoint/design rows; reconcile encounter/acquisition CSVs; use Drafted, Source-verified, and Playthrough-verified separately. Once content exists, play the slice with Soft and Hard cap policies and across starter-region choices before calling it complete.

## Decisions for this content pass

- Roxanne draft: four Pokémon at a Lv15 ace; Aron selected, matchup validation pending.
- Whether to rebalance every ordinary trainer party or preserve vanilla team size while improving moves and level curve.
- Target encounter density for each family and how prominently 733-roster families rotate into the opening.
- How route-trainer AI/items/IVs/EVs should progress toward the authored Normal boss baseline.
- Whether optional Gardenia-style challenge content belongs after the core badge slice, with separate reward and rematch design.

## Existing source and planning records

- Source gates and method exclusions: normal-encounter-gate-audit.md.
- Current family pools/gates: opening-hoenn-access.csv; live map inventory: wild-encounter-inventory.csv; per-family acquisition checklist: acquisition-coverage.csv; source-by-source plans: acquisition-plan.csv; family window inventory: roster-availability.csv.
- Battle party inventory: normal-boss-checkpoints.csv; proposed Normal checkpoints: normal-boss-design-pass.csv; cap policy: normal-cap-milestones.csv.
- Runtime: src/data/wild_encounters.json; src/data/trainers.party; src/caps.c; data/maps/Route103/scripts.inc; Route102/scripts.inc; Route104/scripts.inc; PetalburgWoods/scripts.inc; Route116/scripts.inc; RustboroCity/scripts.inc; RustboroCity_Gym/scripts.inc.

