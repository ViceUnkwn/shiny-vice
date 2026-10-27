# Badge 1 Opening Chunk: Normal Design Draft

**Status:** Draft 0.3. The live encounter pass edits Route 104 and Route 116 land tables; the first Normal trainer-party pass is now implemented. See [badge-1-trainer-balance-pass.md](badge-1-trainer-balance-pass.md) for changed parties and movesets plus the remaining starter-branch/access/play-through checks. Roxanne's runtime party remains unchanged in this pass.

## Scope and play contract

This chunk begins with Birch’s rescue and ends when Roxanne awards the Stone Badge. It covers the required Route 103 rival fight, every reachable pre-gym route, the Petalburg Woods Aqua battle, the optional Route 104 rival, Route 116, Rustboro services, the Gym trainers, and Roxanne.

- **Difficulty:** Normal is the intended game and should be challenging throughout. Hard mode is a later, separate pass.
- **Level cap:** 15 from the beginning until Roxanne is defeated; badge 1 advances the cap to 19.
- **Healing:** The player may leave and heal between trainer battles, including before Roxanne. Do not make the Gym leader’s difficulty depend on carrying damage from optional Gym trainers.
- **Trainer battle items:** No Bag use during trainer battles under the current Normal rules. Healing at Pokémon Centers and with field items between battles remains available.
- **Method gates:** Pre-Roxanne catches are land encounters only. Rod and Surf tables exist in the data but are not usable in this band; HM field-use methods such as Cut, Rock Smash, and Surf remain gated.

## Route order and intended content

| Order | Segment | Current source content | Draft direction |
|---|---|---|---|
| 1 | Littleroot → Route 101 | Birch’s scripted Lv2 Zigzagoon rescue, then starter choice. Route 101 is walkable, but the player has no Poké Balls yet. | Keep the rescue short and preserve the chosen starter as the only party Pokémon for the required rival fight. Route 101 catches begin only after the Pokédex/Poké Ball handoff. |
| 2 | Route 103 opening crossing | Required one-Pokémon Lv5 rival counter-starter battle. Birch gives the Pokédex and five Poké Balls afterward; the player can then backtrack and catch in Routes 101/103. | Keep the vanilla battle shape and level. Support all 27 curated starter choices, select a fair counter, and make AI consistent across all rival variants. This is the opening gate, not a team check. |
| 3 | Oldale → Route 102 | Land encounters Lv3–4; Calvin, Rick, Tiana, and Allen; one Potion. | First catch-and-train route. Preserve distinct trainer identities, but author intentional moves/roles for Normal. Avoid making Ralts or a Grass answer mandatory or guaranteed. |
| 4 | Petalburg City | Norman’s introduction. Wally borrows the player’s Zigzagoon, catches a wild Ralts in a tutorial battle, and returns the player’s party. | Keep this as a tutorial, not a Wally trainer battle. Do not count the temporary Zigzagoon or tutorial Ralts as player acquisitions. |
| 5 | Route 104 south | Shares one land table with north Route 104; Ivan, Billy, Haley, Winston, Cindy, and Gina & Mia; Chesto Berry gift, Bullet Seed TM, item balls and berry trees. | Treat the south and north sections as one encounter habitat. Route trainers should be readable, individually challenging fights; the twins stay a double battle. Winston/Cindy each carry a Full Restore and their Zigzagoon holds a Nugget; these are vanilla data, not Shiny Vice additions. Decide separately whether to retain them in the Normal redesign. |
| 6 | Petalburg Woods | Land Lv5–6; optional Lyle and James; mandatory Aqua grunt (Poochyena Lv9); Ether, X Attack, Paralyze Heal, Miracle Seed; grunt reward Great Ball. | Use the forest for the bug/grass/poison role mix. Keep the Aqua fight mandatory and clearly stronger than a route trainer, but still below the rival/Roxanne difficulty tier. Decide whether its vanilla one-Poochyena party needs a second member for Normal. |
| 7 | Route 104 north / Briney’s Cottage | Same land table as the south. Optional yes/no rival fight, current ace Lv15, with separate defeat flag. Route trainers include Darian. | Keep the rival optional and do not attach cap progress to it. Its support Pokémon now have authored legal sets, abilities, held berries, natures, and IVs; the counter-starter remains dynamically generated. Review fairness across starter choices and retain its optional status. |
| 8 | Rustboro → optional Route 116 | Rustboro Center/Mart and Quick Claw; Route 116 is reachable before Roxanne and now has eleven land families at Lv6–8 and ten trainer objects. | Route 116 is an optional preparation detour. Verify Cut-side paths and trainer sightlines; do not count blocked east-side objects or post-badge Devon items. Players can return to Rustboro to heal. |
| 9 | Rustboro Gym | Three Gym trainers (Josh, Tommy, Marc), then Roxanne. Roxanne awards badge 1 and TM Rock Tomb. | Gym trainers should teach distinct Rock-team tactics. Their fights can be skipped or completed as the map allows; the player can leave and heal before the leader. Roxanne is a standalone capstone at Lv15. |

After badge 1, the Devon Goods scene and Rusturf Tunnel Aqua battle begin. They belong in the next badge band, not in this chunk.

## Encounter draft and vanilla comparison

The six live land tables use Emerald’s 12 weighted slots. The current slot-weight vector remains the Emerald vector; table contents, slot assignments, and some level ranges differ. Table odds below are conditional on a land encounter occurring.

| Map | Current Normal land pool and share | Emerald comparison | Draft decision |
|---|---|---|---|
| Route 101, Lv2–3 | Poochyena 24%, Wurmple 20%, Pidgey 14%, Zigzagoon 11%, Caterpie 10%, Rattata 10%, Sentret 6%, Weedle 5% | Custom; vanilla has Poochyena, Wurmple, and Zigzagoon. | Keep as the broad opening catch table for this draft. |
| Route 102, Lv3–4 | Lotad 21%, Seedot 20%, Ralts 14%, Mareep 14%, Hoppip 11%, Zigzagoon 10%, Poochyena 5%, Wurmple 5% | Custom; adds Mareep/Hoppip and redistributes the six vanilla families. | Keep the multi-answer grass route; validate Ralts and early move pacing. |
| Route 103, Lv2–4 | Wingull 24%, Shinx 24%, Starly 11%, Pawmi 11%, Poochyena 10%, Rookidee 10%, Zigzagoon 10% | Custom; adds Shinx, Starly, Pawmi, and Rookidee to the vanilla Poochyena/Wingull/Zigzagoon pool. | Keep the table separate from the pre-ball rival timing. Review how much bird/electric overlap this creates with other routes. |
| Route 104, Lv4–5 | Taillow 25%, Wurmple 24%, Marill 15%, Hoppip 11%, Surskit 10%, Teddiursa 10%, Wingull 4%, Fletchling 1% | Custom; adds Surskit and Teddiursa while redistributing the native pool. | Adopt the revised table. Taillow/Wingull/Fletchling fall from 50% to 30%; retain rare Wingull/Fletchling hunts and add Bug/Water and Normal options. Both new species are enabled. |
| Petalburg Woods, Lv5–6 | Poochyena 20%, Wurmple line 40%, Shroomish 10%, Oddish 10%, Paras 5%, Spinarak 5%, Taillow 4%, Slakoth 4%, Ledyba 2% | Custom; adds Oddish, Paras, Spinarak, and Ledyba to the vanilla pool of Poochyena, Wurmple line, Shroomish, Taillow, and Slakoth. | Keep the woods as the first dense ecology shift. Preserve Ledyba as a deliberate low-rate hunt and retain the direct Silcoon/Cascoon slots: the separate low-level slots make both Wurmple branches independently huntable. |
| Route 116, Lv6–8 | Nincada 20%, Whismur 20%, Budew 10%, Nidoran♀ 10%, Nidoran♂ 10%, Abra 10%, Drowzee 5%, Magby 5%, Skitty 4%, Taillow 4%, Poochyena 1%, Geodude 1% | The old table was vanilla-equivalent; this pass replaces it with a custom 12-species pool. | Adopt this first custom allocation: it retains all six vanilla Route 116 species and uses seven Imperium families, including both Nidoran species. It adds five families to pre-gym access and makes Geodude huntable at 1% before Roxanne. All twelve species are enabled. |

The current six-map union is **38 families**, versus **15** across the corresponding vanilla land tables. Route 104 adds two families to its earlier draft; the Route 116 redesign adds five. Water/fishing has a project-wide fishing-slot layout change, but those methods are locked before Roxanne and belong in the later method-unlock band.

## Imperium cross-reference

Compared against the current public `release` branch of Imperium's `src/data/wild_encounters.json`. Imperium uses the same weighted 12-slot land vector, but its opening tables generally place a different species in each slot and span a wider level interval. We use its species placement as a design reference, not as a direct replacement for Shiny Vice's curated roster. The branch is moving, so this table identifies the reference branch rather than implying a pinned ROM version.

| Area | Imperium land pool | What we carry into Shiny Vice |
|---|---|---|
| Route 101, Lv2–5 | Shinx, Poochyena, Pidgey, Blipbug, Alolan Meowth, Bunnelby, Wurmple, Rolycoly, Fomantis, Sewaddle, Vulpix, Growlithe | Keep the constrained Lv2–3 opening and current familiar/catch variety; do not adopt species outside the 733 roster. |
| Route 102, Lv3–5 | Rattata, Mankey, Lillipup, Timburr, Rookidee, Phanpy, Ralts, Bounsweet, Poliwag, Joltik, Alolan Vulpix, Alolan Sandshrew | Keep this as the early meadow with several counter types; current Lotad/Seedot/Mareep/Hoppip picks remain distinct from the opening road. |
| Route 103, Lv3–5 | Croagunk, Wooloo, Wingull, Snubbull, Wattrel, Tangela, Galarian Meowth, Galarian Zigzagoon, Oddish, Rufflet, Crabrawler, Scatterbug | Retain the current route's bird/electric identity while recognizing the opening rival occurs before catches. |
| Route 104, Lv4–6 | Starly, Lotad, Teddiursa, Seedot, Galarian Farfetch'd, Nickit, Smoliv, Gossifleur, Galarian Ponyta, Lechonk, Panpour (two slots) | Adopt Teddiursa as a low-level land option; our Surskit substitution uses an enabled family and lowers the combined bird-line share to 30%. |
| Petalburg Woods, Lv5–6 | Caterpie, Pikipek, Zigzagoon, Exeggcute, Hoothoot, Weedle, Tarountula, Swinub, Purrloin, Toedscool, Pansage, Frigibax | Keep the forest's distinct bug/grass/poison habitat and low encounter levels; retain direct Wurmple branches intentionally for now. |
| Route 116, Lv6–8 | Petilil, Skorupi, Nidoran♀, Nidoran♂, Magby, Bidoof, Nincada, Skitty, Vullaby, Budew, Abra, Drowzee | Carry over Nidoran♀/♂, Magby, Nincada, Skitty, Budew, Abra, and Drowzee; retain Whismur/Taillow/Poochyena and add a 1% Geodude hunt for the Rustboro-side route. |

Imperium source: [current release encounter table](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/wild_encounters.json). Route 101 raw rows are at [the opening table](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L79-L148), Petalburg Woods at [its land table](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L1942-L2008), and Route 116 at [its land table](https://raw.githubusercontent.com/iriv24/pokeemerald-expansion/release/src/data/wild_encounters.json#L1396-L1462).

## Battle ledger and proposed normal treatment

| Checkpoint | Current source snapshot | Draft treatment |
|---|---|---|
| Route 103 rival | One opposing starter Lv5; three starter branches for each rival character. | Keep the one-on-one structure and starter-only timing. Normalize AI across variants; validate every one of the 27 player starters against the assigned counter. |
| Route 102 | Calvin: Poochyena 5. Rick: two Wurmple 4. Tiana: Zigzagoon + Shroomish 4. Allen: Zigzagoon 4 + Taillow 3. | Use as the first trainer progression. Keep their vanilla parties/levels as the baseline; give each an intentional move/ability role only where the early learnset supports it. |
| Petalburg Woods | Lyle: four Wurmple 3. James: two Nincada 6. Aqua grunt: Poochyena 9. | The basic trainers remain optional. The grunt is mandatory. Compare party counts with vanilla before changing; avoid padding the story battle with high-level moves unavailable to the player. |
| Route 104 | Ivan: Magikarp 5/6/7. Billy: Zigzagoon 5 + Seedot 7. Haley: Lotad + Shroomish 6. Winston/Cindy: Zigzagoon Lv7 @ Nugget, with one Full Restore each. Gina & Mia: Seedot + Lotad 6 double. Darian: Magikarp 9. | Keep the twins double battle and route’s species identity. Treat the Full Restores as inherited vanilla configuration and decide through playtesting whether they support difficulty or only lengthen a low-level one-mon fight. |
| Route 104 rival | Optional, yes/no; two Pokémon, Lv13 and Lv15. Each branch now has a bespoke support Pokémon set (Lotad, Wingull, Slugma, or Torkoal) plus the dynamic counter-starter. | Keep the opt-in prompt and separate flag. The support species have legal moves, items, abilities, natures, and IVs. Check fairness across all starter choices and whether Slugma/Torkoal are intended to remain rival-only; keep Roxanne the required-boss peak. |
| Route 116 | Joey: Machop 10 + Makuhita 9. Jose: Wurmple 9 + Nincada 10. Jerry: Ralts 11 + Drowzee 10. Clark: Geodude 10 + Roggenrola 11. Janice: Marill 11 + Surskit 10. Karen: Shroomish 11 + Budew 10. Sarah: Lotad + Zigzagoon 10. Dawson: Zigzagoon + Poochyena 10. Devan: Geodude 10/11. Johnson: Shroomish + Lotad 10. | Optional, stand-alone prep fights with Rustboro healing available. Route 116 now has a Lv9–11 two-Pokémon curve; learnset-based move roles are authored; progression play-through remains open. |
| Rustboro Gym trainers | Josh: Geodude 11. Tommy: Aron 11 + Geodude 12. Marc: Lileep 11 + Nosepass 12. Gym trainers use Check Bad Move / Try To Faint / Check Viability. | Distinct party previews now lead into Roxanne’s four-mon Rock team. The player may heal before the leader; moves still need a level-up compatibility audit. |
| Roxanne | Already custom in runtime Normal: Geodude 13 @ Hard Stone, Aron 14, Lileep 14 @ Oran Berry, Nosepass 15 @ Berry Juice; custom moves/abilities, elevated IVs, tactical AI. | Treat this as the existing boss draft, not unwired work. Validate its counterplay against all 27 starters and the reachable 38-family pool. Review Sturdy count, Storm Drain interaction, berry strength, and whether the moves make a meaningful answer test without a single required species. |

### Custom versus vanilla: current confidence

- **Land encounters:** Routes 101–104, Petalburg Woods, and Route 116 land data are custom; fishing/Surf method tables remain a later pass. Baseline is [pret/pokeemerald wild_encounters.json](https://github.com/pret/pokeemerald/blob/master/src/data/wild_encounters.json).
- **Roxanne:** custom party and battle package in current Shiny Vice. Vanilla’s first party is Geodude Lv12, Geodude Lv12, Nosepass Lv15, with the original held berry/move package; see [pret/pokeemerald trainer parties](https://github.com/pret/pokeemerald/blob/master/src/data/trainer_parties.h) and [trainer definitions](https://github.com/pret/pokeemerald/blob/master/src/data/trainers.h).
- **Route 104 rival event:** present in vanilla Emerald’s Route 104 scripts, including the yes/no flow. Do not classify the event itself as a new Shiny Vice encounter. The expanded starter support and party implementation still need field-by-field comparison.
- **Winston/Cindy Full Restores:** inherited from vanilla trainer definitions; their presence is not a customization.
- **Other standard trainer parties:** current-source inventory is recorded above. Mark party species/levels as inherited only after confirming the corresponding vanilla array; do not infer changes from the Normal AI table or difficulty-tier format.
- **Opening rival:** vanilla one-starter Lv5 battle structure; Shiny Vice expands the selectable starter families and uses per-branch AI records.

## Progression resources and recovery

| Source | Draft access/use |
|---|---|
| Birch | Starter; Pokédex and five Poké Balls after the opening rival. |
| Route 102 | Potion item ball. |
| Route 104 | Chesto Berry gift, Bullet Seed TM, Potion, Poké Ball, X Accuracy, PP Up, berry trees. White Herb is badge-gated later. |
| Petalburg Woods | Ether, X Attack, Paralyze Heal, Miracle Seed, and Great Ball after the required grunt. |
| Rustboro | Pokémon Center and Mart before the leader; Quick Claw from the Pokémon School; Premier Ball from a house. HM Cut can be obtained, but outside use is badge-gated. |
| Route 116 | Ether, Repel, Potion, X Special, hidden Super Potion. Exclude far-east and Devon rewards unless the pre-badge path is verified. |
| Roxanne | Badge 1, TM Rock Tomb, cap 19. The player does not have this TM before the fight. |

Because recovery is available between trainer battles and before Roxanne, balance each encounter on its own terms. Optional fights can reward exploration and experience; they should not function as hidden tolls before the boss.

## Lock criteria for this chunk

Before calling the Lv15 band finished:

1. Trace Route 103 eastern objects and Route 116 side paths with map collision/connection data; mark only genuinely reachable trainers and items as pre-gym.
2. Verify all live capture methods and every route’s first-access families against the enabled 733-species roster. No family may be counted from a locked rod/Surf table.
3. The Route 104 bird share, Petalburg Woods branch slots, and Route 116 allocation are resolved in the first encounter pass.
4. Compare each opening standard trainer’s Normal party record with Emerald’s matching party and decide explicitly what stays vanilla versus what is redesigned for Normal difficulty.
5. Review the Route 103 dynamic counter and Route 104 optional rival across all 27 starter choices, then test Normal Roxanne against representative teams from the full opening pool.
6. Play through the route order with field healing available, confirm no unintended level-cap advance past 15, and ensure badge 1 alone advances the cap to 19.

This draft records the content envelope, Imperium/vanilla comparisons, first live Route 104/116 encounter edits, and the current trainer-party pass. See the companion trainer document for party deltas and open move/rival checks. Access-path checks and a first-chunk playthrough still need completion.