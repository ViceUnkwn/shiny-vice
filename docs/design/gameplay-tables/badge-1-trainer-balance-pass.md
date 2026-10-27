# Badge 1 trainer balance: Normal pass 1

**Status:** Runtime party and level-legal movesets applied for ordinary route/Gym trainers and the optional Route 104 rival supports; required rival branches, access audit, and play-through balance remain open. This is the first Trainer-focused implementation in the Lv15 opening chunk. Normal is the intended difficult mode; Hard mode is a later project pass.

## Battle contract

- The player may heal at Pokémon Centers and use field items between trainer fights, including between Gym trainers and Roxanne. No ordinary trainer or boss is balanced around accumulated damage.
- Lv15 remains the active cap through Roxanne. Optional fights can add experience, but the cap contains overleveling.
- Route 116 is optional preparation. Each of its ten trainer battles should be challenging on its own and skippable; they are not a mandatory gauntlet.
- First-badge route, Woods, Aqua, Route 116, Gym-trainer, and rival records use `Basic Trainer` (avoid bad moves, seek knockouts, and evaluate move viability). Roxanne keeps the stronger authored status and smart-switching profile. No first-badge trainer gets omniscient knowledge of the player's unseen moves, ability, or held item.
- Route and Gym teams now have explicit moves drawn from each Pokémon's Gen 9 level-up learnset by its trainer level. The Gym teams also have distinct held-item, ability, nature, and IV roles. This gives battles tactics without handing ordinary trainers moves the player cannot learn yet.

## Runtime party changes

| Area | Updated party | Design intent |
|---|---|---|
| Route 102 | Calvin: Poochyena 5 (unchanged). Rick: Wurmple 5/5. Tiana: Zigzagoon 5 + Shroomish 5. Allen: Zigzagoon 5 + Taillow 5. | Preserve a gentle first trainer while raising the other three to the player's post-rival catch-and-train window. |
| Route 104 south | Ivan: Magikarp 6/7/8. Billy: Zigzagoon 7 + Seedot 8. Haley: Lotad 7 + Shroomish 8. Winston/Cindy: Zigzagoon 7 @ Nugget + Taillow 8; removed each trainer's Full Restore. Gina & Mia: Seedot + Lotad 8/8 double. | Put this segment after Route 102 at a clear level step; remove the Full Restore from each one-Pokémon vanilla party and make both wealthy-trainer battles two-Pokémon fights while preserving the Nugget reward. Keep the Twins fight a double. |
| Petalburg Woods | Lyle: four Wurmple at 6/6/7/7. James: two Nincada 7/7. Aqua grunt: Poochyena 9 + Carvanha 8. | Optional bug catchers now offer meaningful battles. The required story battle becomes a short two-stage Aqua encounter using families in the curated roster. |
| Route 104 north | Darian: Magikarp 9 (unchanged species/party size). Optional rival branches: Lotad 13 + dynamic counter-starter 15; Wingull 13 + dynamic counter-starter 15; Slugma/Torkoal 13 + dynamic counter-starter 15. | Rival supports now carry four legal moves, natures, abilities, Oran Berries, and 18 IVs; the level 15 counter-starter keeps the source-driven dynamic species and generated level-up moves. The event remains optional. |
| Route 116 | Joey: Machop 10 + Makuhita 9. Jose: Wurmple 9 + Nincada 10. Jerry: Ralts 11 + Drowzee 10. Clark: Geodude 10 + Roggenrola 11. Janice: Marill 11 + Surskit 10. Karen: Shroomish 11 + Budew 10. Sarah: Lotad 10 + Zigzagoon 10. Dawson: Zigzagoon 10 + Poochyena 10. Devan: Geodude 10/11. Johnson: Shroomish 10 + Lotad 10. Sarah's Full Restore was removed; Dawson's Nugget-held Zigzagoon remains. | Raise Route 116 from mostly single Lv8–9 teams to a high-preparation side route with compact two-mon matchups, while keeping the route optional and allowing Rustboro healing. |
| Rustboro Gym | Josh: Geodude 11. Tommy: Aron 11 + Geodude 12. Marc: Lileep 11 + Nosepass 12. | Replace the two duplicate Geodude pairs with an escalating preview of Roxanne's Rock, Steel, and fossil roles. Roxanne remains the capstone. |

The existing Roxanne party is unchanged: Geodude 13, Aron 14, Lileep 14, Nosepass 15. The Gym teams now teach setup and pressure: Josh's Geodude pairs Defense Curl with Rollout; Tommy introduces Aron's Metal Claw/Rock Tomb and a Bulldoze/Rollout Geodude; Marc uses Lileep's Confuse Ray/Acid with Nosepass's Block/Rock Throw. Their held items, Sturdy/Storm Drain abilities, natures, and 20 IVs give them a small version of the leader's item-and-ability layer.

## Source comparison

Vanilla Emerald is the structural baseline. Its first route trainers have the familiar small parties and the Woods Aqua grunt is a one-Poochyena fight; Winston and Cindy each have a single Zigzagoon holding a Nugget and a Full Restore in the trainer inventory. The Rustboro Gym trainers repeat Geodude. This pass keeps several familiar species and scripts but explicitly customizes levels, party sizes, the Aqua second member, Route 116 teams, and Gym party composition. Check the Emerald party source before assigning any additional species or move package: [pret/pokeemerald trainer parties](https://github.com/pret/pokeemerald/blob/master/src/data/trainer_parties.h).

Imperium shows the value of a gradual rising curve and compact mixed parties, while its curated families and exact party choices are not copied. Its corresponding early ordinary teams generally step toward Lv9–12 and its Roxanne uses role-based parties at Lv14–15. This pass puts the optional Route 116 opponents at Lv9–11 and the Gym trainers at Lv11–12 before the Shiny Vice Lv15 capstone. References: [Imperium trainer parties](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party) and [Imperium Roxanne party](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party#L5773-L5807).

## Open items before this is locked

1. Verify the trainer party format in a build and keep the level-up move audit aligned if learnsets change.
2. Review the six optional Route 104 rival matchups and all 27 player starter choices against the generated Route 103 counter. Route 103 preserves its one-on-one Lv5 structure and now uses consistent AI; the optional rival uses authored support sets while the selected counter-starter receives dynamic species and level-up moves.
3. Play through the route to confirm that stronger move scoring produces sensible choices at low levels and in the Gina & Mia double battle. No battle-behavior claim is play-through-verified yet.
4. Walk the route, confirm trainer access and item rewards, and verify the 15 cap and heal access. Then play the leader independently with all 27 starters and representative captured teams. No balance claim is play-through-verified yet.
