# Hoenn Campaign Progression and Table Completion Plan

Status: working planning map. The main event order follows Emerald story flags/map scripts; detailed side-path reachability and every method still need an in-game pass. Treat this as a living plan, not a locked design spec.

## What is already in place

| Area | Current state | Remaining work |
|---|---|---|
| Roster | 733 National Dex species enabled; roster data describes 346 supported families and 1,011 configured species/forms. | Prove intended families have a valid same-save path, including gifts, evolutions, rods, Rock Smash, Surf, Dive, fossils, trades, and postgame rules. |
| Encounters | src/data/wild_encounters.json is the canonical runtime source. Shiny roll budget, chain context and fishing/DexNav integration exist. | Complete and verify all map/method slices, weights, levels, access gates, duplicates and coverage. |
| Drafted land passes | Routes 101–104, Petalburg Woods, 110, 111, 117, plus Route 112, Fiery Path, 113, 114, Meteor Falls 1F1R and Jagged Pass have been worked on. | These are drafts, not a complete/playtested campaign. Water, fishing, Rock Smash, Surf, Dive, caves, postgame and many remaining maps need auditing. |
| Trainers | Trainer data/pool framework and starter/rival starter hooks are implemented. | Route trainers, rival progression, villain teams, gyms and major bosses are not fully redesigned. Current gym parties are still baseline teams. |
| Level caps | Per-save Off/Soft/Hard modes are implemented in src/caps.c. Current gym-led cap logic includes the Devon Goods Lv24 exception if Brawly is skipped. | Reconcile cap milestones and actual level pacing with story gates and intended Normal challenge. |
| Planning data | Coverage, acquisition, route access, cap, rival and boss CSVs exist. | These are snapshots/proposals; reconcile counts and state against current source before calling them complete. |

A pass is **drafted** when authored. It is **complete** after methods and gates are checked, coverage data agree with runtime, and a playthrough verifies access and progression.

## Main campaign, step by step

R# means route. The table-scope column lists the content to cover; it does not claim that content is already authored.

| Step | Route and events | Battles and gates | Encounter/table scope |
|---|---|---|---|
| 1. Littleroot | Choose a starter; Birch rescue on R101; return to the lab for Pokédex/Poké Balls; go through Oldale. | Starter rival battle on R103. R101 capture access starts after receiving Poké Balls. | Starter/gift, R101 and Oldale. R103 begins as a scripted rival battle. |
| 2. First loop | R102 to Petalburg; meet Norman and Wally; Wally catch tutorial; R104 and Petalburg Woods to Rustboro. | Wally tutorial, route trainers and Woods Aqua grunt. | R102, both R104 sections, Petalburg Woods methods, gifts/tutorial acquisition. Partly covered by early drafts. |
| 3. Rustboro/Devon | Defeat Roxanne; follow Devon employee’s stolen goods into Rusturf Tunnel; rescue Peeko; return goods and deliver letter; meet rival in Rustboro. | Roxanne is badge 1. In normal story flow, her badge unlocks the tunnel/Aqua rescue and Briney trip. | Rustboro gifts/trades, R116 and Rusturf Tunnel. Separate pre-badge R116 from post-badge tunnel access. |
| 4. Dewford | Briney sails to Dewford; deliver Steven’s letter in Granite Cave; challenge Brawly; sail to Slateport. | Brawly badge 2. Old Rod access begins here; Granite Cave depth is its own gate. | R105–109, Dewford, cave floors, Old Rod and gifts. |
| 5. Slateport/Mauville | Oceanic Museum Aqua event; R110, optional Trick House, rival battle; reach Mauville. | Rival on R110; Wally before Wattson; Wattson badge 3. Devon Goods can be delivered at the museum even when Brawly was skipped, setting the Lv24 cap exception. | R110, Trick House trainers/rewards, Slateport gifts, fishing and method access. |
| 6. Mauville/Fallarbor | R111 north and desert boundary; Magma blocks R112 cable car; Fiery Path; R113 ash route to Fallarbor; R114 to Meteor Falls, where Aqua/Magma clash. Return toward Mt. Chimney. | Route trainers and Winstrate family. The cable car is the main story route gate. | R111 (separate desert access), R112, Fiery Path, R113, R114, accessible Meteor Falls floors. Flannery-band draft covers these maps, not necessarily every method. |
| 7. Mt. Chimney/Lavaridge | Jagged Pass to Mt. Chimney; defeat Magma, recover Meteorite; descend to Lavaridge. Go-Goggles later open the desert. | Magma event; Flannery badge 4; rival near the desert return route. | Jagged Pass, Mt. Chimney fixed battles, Lavaridge, desert R111, Mirage Tower/fossils if active. |
| 8. Petalburg/Surf | Return to Petalburg via R112/R111/R110/R103/R102; defeat Norman; Wally’s family gives Surf; optional visit to Wally in Verdanturf. | Norman badge 5 unlocks Surf. It opens important water routes, but not Rock Smash or Dive. | Petalburg gym/gifts; R105–109 and R115 water, R104/R118 edges, water caves, rods and Surf slots. Check method unlock separately from reaching a map. |
| 9. R118–Fortree | Cross R118 and R119; rescue Weather Institute from Aqua; rival battle after the Institute; reach Fortree. Steven’s Devon Scope reveals invisible Kecleon on R120. | Aqua grunts, rival, Winona badge 6. Devon Scope clears R120’s invisible obstacle; Safari Zone access is nearby. | R118–120, Institute, Fortree, Safari Zone, static Kecleon. Separate ledges and subareas. |
| 10. Fortree/Lilycove | R120–121, optional Safari Zone, Lilycove rival battle; climb Mt. Pyre. Aqua steals the Red Orb; in Emerald the player takes the Blue Orb. Use Magma Emblem at Jagged Pass to enter Magma Hideout and recover the stolen orb. | Rival, Mt. Pyre fixed battles, Magma Hideout boss. | R121–123, Safari zones, Mt. Pyre floors/summit, Magma Hideout floors, Lilycove. Emerald orb events are the baseline. |
| 11. Aqua Hideout | Aqua steals Stern’s submarine at Slateport Harbor; follow to Lilycove and clear Aqua Hideout; sub escapes to Seafloor Cavern. | Aqua grunts and Archie. This sets up the late-game sea route. | Aqua Hideout floors and one-time boss/rewards; distinguish fixed battles from wild tables. |
| 12. Mossdeep/Dive | Surf R124–126 to Mossdeep; beat Tate & Liza; receive Dive; Magma attacks Space Center; defeat grunts and Maxie with Steven. | Tate & Liza badge 7; Dive and Space Center event open the Seafloor objective. | R124–128, underwater counterparts, Shoal Cave tides, Mossdeep and Space Center, gifts, Super Rod. Surface, underwater and dive-spot rows are distinct methods. |
| 13. Seafloor/Sootopolis | Dive on R127/128 to Seafloor Cavern; defeat Aqua/Archie; Kyogre wakes. Reach Sootopolis and meet Wallace; find Rayquaza at Sky Pillar and bring it back to stop the clash. | Villain gauntlet and Archie; Rayquaza is a story-timed static. | R127–134 surface/underwater; Seafloor Cavern rooms; Sootopolis; Cave of Origin states; Sky Pillar floors/top; legendary rules. |
| 14. Final badge/League | Wallace leads Sootopolis Gym after the crisis; earn badge 8/Waterfall; cross R128–134 to Ever Grande; Victory Road, Elite Four and Champion. | Wallace badge 8 in Emerald; Wally rematch in Victory Road; Sidney, Phoebe, Glacia, Drake; Champion Wallace. | R128–134 methods, Ever Grande, Victory Road floors and League parties. Verify Waterfall access independently from Surf/Dive. |
| 15. Postgame | Hall of Fame opens Battle Frontier and rematches; revisit routes with HMs/rods and access remaining caves/ruins. | Treat Frontier/rematches as a separate difficulty/reward track unless deliberately tied to badge caps. | Residual Hoenn map/method rows, postgame caves/legendaries, Frontier/Safari scope, gifts/trades. |

## Optional branches and method gates

Include these in acquisition coverage even if they are not required to finish the story:

- Trick House, Winstrate family, Granite Cave deeper floors and Steven’s room.
- Rusturf Tunnel breakable rocks/Strength section; Rock Smash follows Dynamo Badge in current progression.
- R111 desert, Mirage Tower/fossil choice, and Desert Underpass/postgame availability.
- New Mauville (Wattson’s key), Abandoned Ship, Shoal Cave high/low tide.
- Safari Zone areas/expansions; track story access separately from each zone’s methods.
- Sealed Chamber and Regi caves, Desert Ruins, Island Cave, Ancient Tomb, Sky Pillar, Marine/Terra Cave, roaming/one-time legendary rules.
- Old/Good/Super Rod; Rock Smash, Surf, Dive and Waterfall; gifts/eggs, fossils, trades, static encounters and evolution paths. A family can have multiple acquisition routes; wild slots are not the whole Pokédex plan.

## Suggested completion workflow

1. **Name the sources of truth.** Encounters: src/data/wild_encounters.json. Trainers: src/data/trainers.party plus the current trainer-pool data/parser. Shiny odds: existing src/shiny_roll.c, src/pokemon.c, fishing and DexNav integrations. Keep one odds implementation. CSVs are audit/design ledgers and must be reconciled after source edits.
2. **Build one map/method matrix.** For every Hoenn map and method record story band, badge/flag gate, traversal prerequisite, slots/weights, levels, families/forms, encounter type (wild/static/gift/fossil/trade/evolution), first acquisition and repeatability, and audit status. Seed it from wild-encounter-inventory.csv, acquisition-coverage.csv, acquisition-plan.csv, and roster-availability.csv.
3. **Finish gated bands in order.** Opening–Roxanne; Dewford/Slateport–Wattson; Wattson–Flannery; Flannery–Norman; Norman–Winona; Winona–Tate & Liza; Tate & Liza–League; postgame. Per band: enumerate maps/exits/events, author every method and static/gift, align levels to caps, inventory every trainer, verify acquisition coverage, then play through and mark verified.
4. **Design trainer teams by role.** Keep route trainers readable and themed. Give rivals, admins, gym leaders, villain bosses and League coherent roles, coverage, moves, abilities, items and AI appropriate to the chosen difficulty. Use Imperium as a team-design example, then fit ShinyVice’s roster, caps and shunter pacing. Optional powered-up rematches should reward exploration without blocking the main story.
5. **Audit checkpoints.** For every boss, record cap, expected party level, unlocked methods, newly available families and rewards. Check skipped-badge sequences (especially Brawly) for softlocks or unintended jumps. Keep postgame/repeatable activities separate unless the design wants an exception.

## Design choices still open

- Are all 733 intended to be obtainable in one ordinary save, or are some trade/postgame/event-only?
- Do shard/pity rewards change by band or encounter method?
- How much powered-up rematch content belongs in the first complete pass?
- Is Safari Zone, Frontier and postgame legendary coverage in V1?
- What team depth/items define Normal difficulty at each major boss?

## Source pointers

- Systems: normal-implementation-plan.md, normal-cap-milestones.csv, normal-boss-checkpoints.csv, normal-boss-design-pass.csv.
- Encounter/access drafts: encounter-table-research-and-draft.md, flannery-approach-encounter-pass.md, normal-encounter-gate-audit.md, opening-hoenn-access.csv, pre-brawly-encounter-access.csv, wattson-approach-access.csv.
- Coverage/roster: acquisition-coverage.csv, acquisition-plan.csv, wild-encounter-inventory.csv, roster-availability.csv, normal-roster-balance.csv.
- Imperium review: imperium-deep-dive.md, imperium-source-review.md.
- Runtime/maps reviewed: src/caps.c, src/starter_choose.c, src/battle_main.c, src/shiny_roll.c, src/data/wild_encounters.json, src/data/trainers.party, and relevant data/maps/*/scripts.inc and map.json files.

