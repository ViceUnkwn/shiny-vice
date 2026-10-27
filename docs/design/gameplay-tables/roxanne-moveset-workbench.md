# Roxanne moveset workbench

**Purpose:** compare proposed Roxanne sets against the move pools and teams players can actually bring before Badge 1, without changing the live trainer or replaying the whole route for every move edit.

## Where to put candidate sets

- The live team is `TRAINER_ROXANNE_1` in `src/data/trainers.party`. That file accepts competitive / Showdown-style set syntax, and `trainerproc` compiles it into the game's trainer data.
- Keep research candidates here or in a separate paste while iterating. Replacing the live `TRAINER_ROXANNE_1` block is the final promotion step. Adding extra trainer blocks to `src/data/trainers.party` is not a scratchpad: they become compiled trainer records.
- For a damage calculator, paste/import each set into the calculator's custom-set/team input. Include Level, nature, IVs, ability, held item, and moves. Set EVs to the actual assumption; the current Roxanne party has authored IVs/natures but no authored EVs. Use Level 13/14/14/15 for the current party, not the level-100 default from many competitive pastes.

## Reference sets to mine

1. **Shiny Vice current:** copy the live `TRAINER_ROXANNE_1` block. This is the baseline to compare against.
2. **Imperium:** copy the Roxanne member sets from the pinned source snapshot recorded in `roxanne-team-draft.md`. It provides the closest Emerald-engine role reference: Geodude, Lileep, Gligar, and Nosepass, with moves/items/abilities/AI authored. Keep its party and AI snapshot separate from the supplied v1.3/v1.3.1 workbook because they do not fully match.
3. **Radical Red:** use the supplied v4.1 Normal Brock workbook and the public Radical Red Showdown data repository as set references. The project research did not find the original v4.1 GBA game source, so do not infer its battle AI or hidden implementation from the Showdown fork or tracker.

Treat reference movesets as a menu of role ideas, not ready-to-copy Lv15 sets. For every borrowed move, check Shiny Vice's configured learnset/TM/tutor and whether the player can obtain that move before Roxanne. For every ability/item, confirm it exists and has a real effect at this checkpoint.

## Fast iteration loop

### 1. Validate the candidate

Record the set, its job, and why each slot is present. Reject or revise a set if a move is inaccessible, a move/ability does nothing, or two slots duplicate the same role without a clear reason. In the current team, explicitly review the three Rock Tomb users, Aron's Rock Head without a recoil move, and Nosepass's Sturdy + Berry Juice interaction.

### 2. Run matchup screens

Use the project party data as the source of levels, natures, IVs, items, abilities, and moves. Screen every starter path and the practical pre-gym counterexamples from the 38-family opening pool. Prioritize worst-case speed and damage breakpoints rather than manually checking every possible four-mon permutation.

For each matchup, record:

- who moves first at actual levels and stats;
- minimum/maximum damage and KO chance for realistic player attacks into each boss member;
- minimum/maximum damage from each boss attack into the player, including Rock Tomb speed drops;
- survival interactions (Sturdy, Berry Juice, Oran Berry), status/confusion odds, and likely turns to KO;
- whether the player has at least two reachable, non-identical answers to the Water, Grass, Fighting, Ground, and Steel checks.

Use a calculator for damage rolls and speed, not win rate. The official Showdown calculator is a fast first screen; verify any result affected by Shiny Vice's custom stats, moves, abilities, or battle configuration against the project's source/engine before changing the team.

### 3. Use the game engine for behavior checks

For move-selection / AI checks, use the existing battle test runner or the Shiny Vice debug trainer selector. The test runner can verify controlled lines and specific AI choices; it is not a complete autonomous matchup simulator. The debug trainer selector starts Roxanne directly, avoiding the route and Gym-trainer replay. Use seeded/repeated test cases for accuracy, confusion, status, and damage-roll variance.

The existing debug workflow is documented in `shiny-vice-debug-test-workflow.md`; battle test syntax is documented in `docs/tutorials/how_to_testing_system.md`.

## First source-level screening results

These are computed from the configured species base stats, trainer IVs/natures/levels, and current move data. Trainer sets omit EVs, so this screen uses 0 EVs. Stat order is HP / Atk / Def / SpA / SpD / Spe.

| Roxanne member | Level | Computed stats | Current move power / accuracy | First finding |
|---|---:|---|---|---|
| Geodude | 13 | 36 / 28 / 36 / 13 / 15 / 12 | Rock Tomb 60/95, Bulldoze 60/100, Tackle 40/100 | Rock Tomb gets STAB and Hard Stone; Bulldoze is its only Ground coverage. |
| Aron | 14 | 40 / 29 / 35 / 17 / 19 / 16 | Metal Claw 50/95, Rock Tomb 60/95 | Rock Head has no effect with this set: none of its four moves causes recoil. |
| Lileep | 14 | 45 / 17 / 31 / 24 / 32 / 14 | Rock Tomb 60/95, Acid 40/100 | Storm Drain is a real Water stop; Acid and Confuse Ray pressure Grass answers. Oran Berry restores 10 HP at its trigger threshold. |
| Nosepass | 15 | 37 / 22 / 53 / 19 / 35 / 17 | Rock Throw 50/90 | Sturdy can leave it at 1 HP from a full-health hit; Berry Juice then restores 20 HP, leaving it at 21/37 before another hit. This is a meaningful extra survival sequence, comparable to the Imperium / Radical Red Sturdy + Berry Juice pattern. |

Type screen from the current four species and moves:

- **Water attackers:** strong into Geodude (4x) and super effective into Aron/Nosepass (2x); Lileep's Storm Drain blanks Water moves and raises its Sp. Atk.
- **Fighting attacks:** super effective into every member, and 4x into Aron, but this is not broadly available by species. The opening tables contain no Fighting-type family; level-up moves before Lv16 found in the starter/encounter envelope are Mudkip’s Rock Smash, Ledyba’s Mach Punch, and Scorbunny’s Double Kick.
- **Ground attacks:** 2x into Geodude/Nosepass and 4x into Aron; neutral into Rock/Grass Lileep. Ground immunity is absent, and pre-Roxanne level-up access is narrow: Pawmi gets Dig at 15, Nincada gets Mud-Slap at 15, and Geodude gets Bulldoze at 12 (Geodude is only a 1% Route 116 encounter).
- **Grass attackers:** 4x into Geodude, 2x into Nosepass, neutral into Lileep, and resisted by Aron. Aron has STAB Metal Claw and Lileep has Acid to punish Grass switches.
- **Steel attacks:** 2x into Geodude/Lileep/Nosepass and neutral into Aron, but no damaging Steel move is present in the audited level-up moves up to Lv15 for the 27 starters and pre-gym encounter species. Check early TM/item access before counting Steel as counterplay.
- Rock Tomb is on three of four members. It is both STAB damage and repeatable speed control, so redundancy may be intentional; test whether repeated speed drops make the fight too oppressive before replacing one.
- The Sturdy test has an available answer: Route 116 offers both Nidoran forms at a combined 20% encounter share; by Lv15, Nidoran♀ learns Fury Swipes and Nidoran♂ Fury Attack. Multi-hit attacks can break Sturdy during one move, but this requires optional hunting and leveling, so test both prepared and unprepared teams.

This is a source/formula screen, not a full turn-by-turn battle simulation. The Fighting/Ground/Steel move scan used configured Gen 9 level-up learnsets through Lv15. A map-script TM grant scan found Bullet Seed on Route 104 before the Gym and Rock Tomb as Roxanne’s post-win reward; it found no pre-gym Fighting, Ground, or Steel TM gift. Shops, hidden pickups, and move-reminder access still need a separate final check. Damage rolls against player teams and AI action sequences are still unmeasured. The current finding that needs a set decision first is Aron's inactive Rock Head. The level-up scan found no Low Kick, Grass Knot, Heavy Slam, or other weight-based attack available to the opening starter/encounter envelope by Lv15, so Heavy Metal is also likely inactive for this checkpoint. Sturdy is the first functional candidate, though it would give Roxanne three Sturdy users. The controlled comparison should be Rock Head baseline vs Sturdy, holding every other field constant; Heavy Metal is a useful control only if the TM/tutor audit finds an accessible weight-based attack.

## Candidate record

Copy one candidate set per version and fill in this row before promoting it:

| Candidate | Set source / version | Role changes | Legal at Lv15? | Reachable player answers | Breakpoint changes | AI concerns | Decision |
|---|---|---|---|---|---|---|---|
| Current live team | Shiny Vice `TRAINER_ROXANNE_1` | Baseline | In source; move/access audit remains | To screen | Not measured yet | Smart Switching + Smart Mon Choices; no flat status preference | Baseline |
| Candidate A | Aron Sturdy, same four moves | Makes the ability slot functional; third Sturdy user | Ability exists; moves unchanged |  |  | Extra survival may extend the fight | First controlled test |
| Candidate B | Aron Heavy Metal, same four moves | Preserves two Sturdy users | Ability exists; likely no early weight-move interaction |  |  | No expected change without Low Kick/Grass Knot/Heavy Slam | Control only if such a move is accessible |

## What this will and will not tell us

The first pass can cheaply identify dead moves, redundant coverage, outspeed/KO breakpoints, boss damage ranges, and inaccessible counters. It cannot establish a true win rate by itself: the player chooses switches and moves, while accuracy, secondary effects, AI scoring, and prior turn state change battle outcomes. Use automated engine cases for repeatable tactical questions and only a small number of isolated debug battles for final feel checks.






## Engine-backed Roxanne cases

The repeatable engine slice in test/battle/roxanne.c is documented in tools/battle_sim/README.md. Run make check TESTS="Roxanne" in the supported build environment. Seven cases cover all four members' move scores, healthy-target status versus a guaranteed knockout, Storm Drain, and the combined Nosepass Sturdy + Berry Juice survival sequence. These cases use the engine but are not full-battle win-rate simulations; the current test DSL still scripts the player's turns.

Verification: make check -j4 TESTS="Roxanne" passed all seven engine cases on 2026-10-26. Scoring showed the flat Prefer Status Moves bonus could block a guaranteed Nosepass knockout, so that flag was removed from the live leader profile. The first build required six blank separators in existing rival party entries; no rival party data changed in that parser fix.
