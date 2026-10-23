# Normal encounter gates and boss access envelope

This is the source audit for building Shiny Vice's Normal encounter pool and boss progression. It treats three questions separately: whether a method exists in `src/data/wild_encounters.json`, whether the map can be reached in the story, and whether the player has the item/badge needed to use that method. A species appearing in encounter data alone does not make it catchable at that point.

## Findings that affect the design

- Route 101's encounter table is live from the opening, but the player cannot catch its encounters until Birch grants Poké Balls after the Route 103 rival battle. Route 103 is also traversable in the opening, but the first rival battle occurs before the Poké Ball grant. Keep that rival starter-only.
- Routes 101–104 currently have custom land tables. The Route 102, 103, and 104 water/fishing entries are separate method pools; they do not become available just because the land route is open.
- `opening-hoenn-access.csv` has now been refreshed from those live land slots through Route 116. Its per-map percentages are conditional slot weights once a land encounter occurs, not the chance of an encounter while walking. The six audited tables each total 100% after repeated species/family slots are aggregated.
- The generated `wild-encounter-inventory.csv` currently finds 118 enabled families represented on Hoenn-region map tables and 158 across all map regions; 228 have no direct wild source on a Hoenn map. This scan includes Kanto/FRLG tables, does not prove those are part of the Hoenn campaign, and does not count scripted gifts, starters, eggs, trades, or evolutions. These are source-coverage counts only.
- The actual early pool is broad: Route 101 has eight families; Route 102 has eight; Route 103 has seven; Route 104 has six; Petalburg Woods has five; Route 116 has six. Ralts on Route 102 is a 14% land-table family weight (two slots), not a rare encounter. Route 104 is 50% bird-line weight (Taillow, Wingull, Fletchling), and bird lines are already common across Routes 101–103. Those are the first balancing pressure points to revisit after the team audit.
- Route 116 and its six land families are reachable from Rustboro before Roxanne. However, the *Devon Goods quest* is gated by Roxanne in this checkout: Roxanne's victory script sets `VAR_RUSTBORO_CITY_STATE = 1`; Rustboro's coordinate triggers use state 1 to start the Devon Goods scene. That scene sets `FLAG_DEVON_GOODS_STOLEN` and `VAR_RUSTURF_TUNNEL_STATE = 2`; only then do the tunnel's Aqua grunt/Peeko objects appear. The Tunnel encounter pool is Whismur-only, so it adds no new family relative to Route 116.
- The first Gym is a hard story gate to the Devon/Briney sequence. Returning the Devon Goods and completing the Devon Corp event opens Mr. Briney's boat path to Dewford. So the early badge-only cap does not leave the player at cap 15 for Brawly.
- Brawly is **not** a story gate to Slateport or Route 110. In `DewfordTown_EventScript_Briney`, the Slateport option is unlocked by delivering Steven's letter; it does not check `FLAG_BADGE02_GET`. The museum Aqua event sets `FLAG_DELIVERED_DEVON_GOODS` before Route 110 opens. Shiny Vice now treats that flag as a story cap milestone at Lv24, matching the cap from Brawly's badge and covering the Lv20 Route 110 rival and Lv24 Wattson when Brawly was skipped.
- Route 104's south section opens from Petalburg after the Norman scene; its north section is reached through Petalburg Woods. They share one encounter table in the source. The source cannot assign different land species to the north and south halves without splitting maps or adding location-aware encounter logic.
- Surf and fishing encounter data are not usable before the corresponding method unlock. In this source, the Old Rod is given in Dewford, Good Rod on Route 118, and Super Rod in Mossdeep. Surf is field-usable after the HM and its badge gate; Rock Smash also needs its field-use badge. Check the field-move/badge constants if those gates are changed.
- Map access and encounter method are independent. Route 105–109 have water/fishing data, not land pools. None of their water encounters count before Surf is usable. After the player gets the Old Rod in Dewford, Route 106 fishing is open; after delivering Steven's letter and sailing to Slateport, Route 109 Old Rod fishing can also happen before Brawly. Routes 105/107/108 remain out of that pre-Brawly envelope. The same rule applies to Surf-only shore routes throughout the campaign.

## Verified opening progression

| Checkpoint | Reachable catch sources before the fight | Method exclusions / caveats | Boss-design consequence |
|---|---|---|---|
| Route 103 rival | Player's selected Lv. 5 starter only | Rival is fought before Poké Balls; no wild captures yet | Rival uses a same-pool counter starter and remains a one-Pokémon opening tutorial fight. |
| Optional Route 104 rival | Route 101/102/103/104 land, plus any catches obtained along the way | Route 104 rival is opt-in and has its own defeated flag | Treat as optional Normal content; never use it to advance the mandatory cap ladder. |
| Petalburg Woods Aqua grunt | Opening route land pool and Petalburg Woods land | Encounter table has seven species IDs, but several are Wurmple's evolution branches; distinguish species from families | Required story fight; keep it a short bridge battle before the first Gym. |
| Roxanne | Routes 101–104, Petalburg Woods, Route 116 land | Tunnel/Devon sequence is gated behind Roxanne; no Surf/fishing/Rock Smash pool is available in the opening envelope | Build the Gym party for this actual pool, including the player's 27 possible starter choices; cap 15 is the current wired starting value. |
| Rusturf Tunnel Aqua grunt | Route 116 plus Rusturf Tunnel after Roxanne starts the Devon Goods scene | Encounter table has Whismur only, so it adds no new family relative to Route 116 | Required post-Roxanne story fight; keep it a short bridge battle before Dewford. |
| Rustboro optional rival | Opening routes, Petalburg Woods, Route 116; accessible after the Devon Corp story setup | A separate Rustboro event/flag from the Route 104 rival; no Surf/rod pool is open | Optional later same-pool rival test; don't count it as a cap milestone. |
| Dewford / Brawly | Route 106 and Granite Cave land become available after the Devon Goods/letter boat sequence; Old Rod is available from the Dewford fisherman | Granite Cave B2F contains Rock Smash blocks; field use requires the Dynamo Badge. Surf routes remain locked until the Balance Badge | Brawly is reachable after badge 1, but can be skipped. The Slateport museum story flag now raises the cap to 24 before Route 110, so Brawly is optional without leaving the player under-capped on the main path. |

| After Slateport / before Wattson | Route 110, Route 117, and the accessible southern Route 111 land are additions to the previous pool. The Old Rod can be used at fishable shore tiles on these maps; Route 109 Old Rod remains available as recorded in `pre-brawly-encounter-access.csv`. | Route 111's map uses a single land encounter table, so the desert-themed Cacnea slot can roll anywhere on the map's grass before Go-Goggles reveal the desert. Route 112 is blocked behind Route 111's Rock Smash rocks until after Wattson. Surf, Rock Smash, Good Rod, and Super Rod rows do not count before their unlocks. | Wattson's pre-fight pool contains Ground families on Route 111, plus common Electric types on Route 110. His team needs coverage and tempo, but cannot invalidate Ground counterplay. See `wattson-approach-access.csv`. |

The exact next-segment land/fishing source families and slot shares are recorded in `pre-brawly-encounter-access.csv`. Granite Cave B1F is marked high-friction rather than locked because its map requests Flash lighting but has no event gate; its direct encounter table remains active in the dark. B2F land is not counted until its Rock Smash path is fully traced.

## Campaign method gates to use in the next encounter pass

These are method rules, not a claim that every route in the region has been individually audited for every map transition. The map/story order below follows the Hoenn map scripts and the campaign route order; exact one-way cuts and optional interiors should be recorded as separate rows when those encounters are authored.

| Method | Earliest practical unlock in this source | Eligibility rule for acquisition planning |
|---|---|---|
| Land | Opening routes after the starter sequence; new maps as story traversal opens them | Count a map's land families only after Poké Balls are received and the relevant section is reachable. For split maps (Route 104, Route 111, Route 112), preserve section gates. |
| Old Rod | Dewford fishing guru | Count only after the player reaches Dewford and receives the rod; the intended boat path follows the first Gym and Devon Goods sequence. |
| Surf | HM03 plus the Balance Badge field-use gate after Norman (`FIELD_MOVE_SURF` maps to `FLAG_BADGE05_GET`) | Count Surf sources only after Surf can actually be used outside battle, not when its map pool is present in JSON. |
| Good Rod | Fisherman on Route 118 | Route 118 itself requires Surf/Balance Badge; add Good Rod fishing pools after the Route 118 gift. |
| Rock Smash | HM06 plus the Dynamo Badge field-use gate after Wattson (`FIELD_MOVE_ROCK_SMASH` maps to `FLAG_BADGE03_GET`) | Count Rock Smash pools only after the field move is usable. Do not treat rocks visible before then as accessible catches. |
| Super Rod | Mossdeep fisherman | Count only after the player reaches Mossdeep and receives it; map reachability alone does not enable the method. |
| Dive | HM08 and the Mind Badge field-use gate after Tate & Liza (`FIELD_MOVE_DIVE` maps to `FLAG_BADGE07_GET`) | Count Dive-only maps after both the story path and field-use gate are satisfied. |

## Badge-led cap with a story exception

Shiny Vice remains badge-led (15 before badge 1, then 19/24/29/31/33/42/48/58, then 78 after Champion), with one confirmed story exception: `FLAG_DELIVERED_DEVON_GOODS` also grants cap 24. Imperium's `src/caps.c` advances at many story flags as well as badges (including the Rustboro rival, Slateport museum, Route 110 rival, Mt. Chimney, Fly, Lilycove, and Seafloor milestones); its release ladder runs 15/20/25/30/32/34/44/47/56/59/64/68/71/74/76/80/82/84/85. We are adopting only the extra cap necessary to cover Shiny Vice's confirmed Brawly bypass, rather than copying Imperium's denser ladder before verifying those other bypasses.

Keep gyms as the main cap milestones, with a story milestone only where the main path bypasses a Gym and would otherwise trap Hard Cap below the next required boss:

1. **Badge milestones:** remain the primary cap ladder.
2. **Story exception:** `FLAG_DELIVERED_DEVON_GOODS` raises the cap to 24 after the Oceanic Museum event, exactly matching Brawly's badge. This avoids requiring a return trip to Dewford just to make the Route 110 rival and Wattson playable in Hard Cap mode. Verify later Gym bypasses before adding more story flags. Roxanne needs no extra Devon/Briney milestone because she gates that chapter here.

Use cap values as boss ace targets, not proof that a boss is beatable. Recheck them against route access, all starter-region picks, evolution availability, and normal experience flow before finalizing later milestones.

## Imperium lessons carried forward

Use Imperium's method-separated map data and repeated weighted slots where useful; aggregate duplicate slots when communicating encounter odds. Use its map/story progression and multi-event cap model as reference patterns, not as a direct roster copy. For bosses, adopt cohesive roles, stronger move/AI/item packages, and explicit optional-versus-mandatory classification. Shiny Vice must still tune each pool against its curated 733 National Dex species and the save's selected starter region.

## Source references in this checkout

- Encounter definitions: `src/data/wild_encounters.json`.
- Route and story gates: `data/maps/Route101/scripts.inc`, `Route103/scripts.inc`, `Route104/scripts.inc`, `RustboroCity/scripts.inc`, `PetalburgWoods/scripts.inc`, `Route116/scripts.inc`, `RusturfTunnel/scripts.inc`, and `SlateportCity_OceanicMuseum_2F/scripts.inc`.
- Mauville approach map edges: `data/maps/Route110/map.json`, `Route111/map.json`, `Route112/map.json`, and `Route117/map.json`; method-by-method available and blocked species are in `wattson-approach-access.csv`.
- Rod gifts: `data/maps/DewfordTown/scripts.inc`, `data/maps/Route118/scripts.inc`, and `data/maps/MossdeepCity/scripts.inc`.
- Field-move badges: `src/field_move.c` (Surf = Badge 5; Rock Smash = Badge 3; Dive = Badge 7; Waterfall = Badge 8). `data/maps/GraniteCave_B1F/map.json` sets `requires_flash: true`, which is a darkness/visibility property; it is not an encounter-method lock.
- Current cap implementation: `src/caps.c`; provisional ladder: `docs/design/gameplay-tables/normal-cap-milestones.csv`.
- Boss source parties: `src/data/trainers.party`; encounter/checkpoint inventory: `docs/design/gameplay-tables/normal-boss-checkpoints.csv`.

### Verification boundary

This pass verifies the opening route gates through Mauville/Wattson, the Roxanne-to-Devon-to-Briney sequence, the Brawly bypass and its cap compensation, accessible Route 111 land vs. the Rock Smash-gated Route 112 connection, Rod gift locations, and the method-vs-map distinction from current source. It does not yet certify later cave/route transitions, optional side maps, event rematches, or every species acquisition path. Keep those entries marked pending until map connections and scripts are checked, rather than treating the campaign ordering handout as game logic.
