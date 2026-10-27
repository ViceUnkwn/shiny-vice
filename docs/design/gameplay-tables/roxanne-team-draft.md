# Roxanne Team Draft - Lv15 First Badge

Status: Normal party draft is authored in src/data/trainers.party; Aron is selected over Gligar. Final AI tuning and playthrough balance remain open. All four families are enabled in the curated 733 roster. Draft assumes Roxanne is a four-Pokemon single battle, ace Lv15, and the player may heal after the Gym trainers before challenging her. No player bag items during trainer battles.


## Source comparison: Emerald Imperium and Shiny Vice

This pass checked authored trainer records and the Rustboro Gym map scripts, not just planning summaries. Imperium source reference: the public release branch src/data/trainers.party (moving branch; snapshot checked 2026-10-25). Shiny Vice source: src/data/trainers.party and data/maps/RustboroCity_Gym/scripts.inc in this checkout.

| Fight | Emerald Imperium source | Shiny Vice source baseline before this pass |
|---|---|---|
| Roxanne | Four Pokémon: Geodude Lv14, Lileep Lv15, Gligar Lv15, Nosepass Lv15. Geodude has Sturdy + Custap Berry and Sandstorm / Rock Tomb / Bulldoze / Self-Destruct; Lileep has Storm Drain + Oran Berry and Ancient Power / Mega Drain / Acid; Gligar has Oran Berry and Wing Attack / Poison Tail / Bulldoze; Nosepass has Sturdy + Berry Juice and Rock Blast / Spark / Bulldoze / Thunder Wave. 31 IVs, authored natures/items/abilities, and AI flags Check Bad Move / Try to Faint / Check Viability / Setup First Turn / Will Suicide / Prefer Status Moves / Smart Switching / Omniscient / Smart Mon Choices. |
| Gym trainers | Josh: Hisuian Growlithe Lv12. Tommy: Scraggy and Alolan Diglett Lv10. Marc: Anorith Lv10 and Archen Lv11. Each uses Check Bad Move AI. | Josh: Geodude Lv10 with Tackle. Tommy and Marc: two Geodude each at Lv8, with no authored moves (level-up defaults). All use Check Bad Move AI. |

The Imperium leader uses the same four-family shell as the earlier Shiny Vice draft except it uses Gligar instead of Aron. It demonstrates a strong boss construction: role coverage, full authored movesets, weather, Sturdy/item interactions, sustain, speed control, and stronger tactical AI. Imperium's Gym trainers are not built to that same complexity; they preview the leader and remain easier fights. That supports keeping the difficulty budget concentrated in Roxanne, with the player allowed to heal before her.

The Normal draft keeps Aron in place of Gligar to test Grass counterplay directly while preserving the Rock theme. Aron brings a sturdy anti-Grass pivot; Gligar would add Ground immunity and broader offensive coverage, but is not selected for this first version.

## Authored Normal party

| Order | Pokemon | Level | Ability | Held item | Nature / IVs | Moves | Job |
|---|---:|---:|---|---|---|---|
| 1 | Geodude | 13 | Sturdy | Hard Stone | Impish / 20 | Rock Tomb, Bulldoze, Defense Curl, Tackle | Opening pressure and speed control; Bulldoze gives coverage beyond Rock. |
| 2 | Aron | 14 | Rock Head | None | Adamant / 20 | Metal Claw, Rock Tomb, Roar, Harden | Steel-armored pivot that checks Grass answers; 4x weak to Fighting and Ground, 2x weak to Water and Fire. |
| 3 | Lileep | 14 | Storm Drain | Oran Berry | Bold / 20 | Rock Tomb, Acid, Confuse Ray, Ingrain | Water-punishing pivot and sustain check; Acid pressures Grass answers, while Grass damage remains neutral by typing. |
| 4 | Nosepass | 15 | Sturdy | Berry Juice | Impish / 24 | Rock Throw, Thunder Wave, Block, Harden | Signature ace; durable, slows faster attackers, and can pressure a player who leaves the wrong Pokemon in. |

### Why these four

- All four families are on in species_enabled.h and represented in the 733-species roster input. None of the disabled Rock families (such as Dwebble or Rellor) are used. Rock Head on Aron limits the team to two Sturdy users rather than stacking three guaranteed full-health survival checks.
- The team stays visibly Rock-themed while giving Roxanne separate jobs: a Ground coverage lead, a Steel/Rock Grass check, a Storm Drain water pivot, and her signature defensive ace.
- Before this pass, ShinyVice Roxanne repeated Geodude and had only three Pokemon. This authored team replaces those duplicates with distinct roles while staying at four members.
- Lileep is a hard check to Water and Acid pressures Grass answers; Grass damage itself remains neutral by typing. The team retains clear weaknesses to Water (Geodude, Aron, Nosepass), Fighting, Ground, and Steel.
- No trainer Potions for Roxanne. Her sustain package is Oran Berry Lileep plus Berry Juice Sturdy Nosepass; test the combination for meaningful counterplay and fight length.


## Level and move legality notes

- Keep the ace at Lv15. Proposed support levels 13/14/14 leave a visible rise to Nosepass without giving the whole team cap-level bulk.
- Geodude learns Defense Curl at 1, Rollout at 10, and Bulldoze at 12; Rock Tomb is a TM move rather than a level-up move in this configured learnset. Its lead set intentionally avoids Defense Curl + Rollout stacking, which could snowball too hard against a first-gym party.
- Aron learns Metal Claw at 4, Rock Tomb at 8, and Roar at 12. Its level-14 set is supported by the configured Gen 9 learnset.
- Lileep learns Acid at 4, Confuse Ray at 8, and Ingrain at 12. Ancient Power is learned at 16, above the cap, so do not give it that move here. Rock Tomb is confirmed in Lileep compatibility data at src/data/pokemon/all_learnables.json.
- Nosepass learns Block at 7, Rock Throw at 10, and Thunder Wave at 13; these give its ace role without relying on a late move.
- The TM Rock Tomb reward can also be Roxanne's own prepared move. Boss parties may use their own reward TM.
- The Normal party uses 20 IVs on the three supporting Pokémon and 24 IVs on Nosepass, with deliberate natures and no custom EV spread. This gives the first-badge boss above-route-trainer stats without using endgame-perfect IVs. Add EVs only if matchup review shows a specific need.


## Normal AI and item direction

The earlier boss draft proposed a flat status preference. The current live profile keeps Check Bad Move, Try to Faint, Check Viability, Smart Switching, and Smart Mon Choices, but omits Prefer Status Moves: engine scoring showed that flat bonus could outweigh a guaranteed knockout. Ordinary trainers and Gym trainers stay simpler so the leader is a clear difficulty spike. Smart Switching gives Lileep/Storm Drain a real job against repeated Water attacks and lets Aron punish an exposed Grass move; the player can respond by switching, using neutral coverage, or exploiting the boss's other weaknesses.

Imperium also enables Omniscient, Setup First Turn, and Will Suicide. Treat those as separate decisions, not a copied bundle. Start without Omniscient so Roxanne does not act on concealed player information; add it only if playthroughs show the boss needs more pressure. Setup First Turn and Will Suicide should only be enabled if a move set gives those flags a deliberate job. The prepared four-member party, full movesets, held items, and tactical switching already set a challenging Normal target compared with the current source team.

The authored item plan gives Geodude Hard Stone, Lileep an Oran Berry, and Nosepass Berry Juice. Test whether Sturdy plus Berry Juice on the ace creates a meaningful Normal-mode decision or just extends the fight. Avoid trainer Potions if the goal is for difficulty to come from team play and switch pressure rather than extra HP bars; the player can heal before the leader, and both sides should enter the boss fight on clear terms.

Use strong but transparent stat assumptions: the authored Normal set uses 20 IVs on support members and 24 on the ace, with deliberate natures and no custom EV spread. Review damage and speed breakpoints against the entire reachable Lv15 roster before adding EVs. Keep player build knowledge, obtainable items, move access, and all 27 starter choices in the matchup pass.

## Encounter implications

The six pre-Roxanne land maps currently have no Rock-type family in their configured wild pools. Families on this proposal have different existing acquisition timing:

- Geodude currently appears later (including Route 111/114 and Granite Cave).
- Aron and Nosepass are currently associated with Granite Cave access after the first badge.
- Lileep has no current direct Hoenn wild-map path in the inventory; its fossil/script acquisition still needs a source audit.

That does not prevent Roxanne using them. For a better hunt-and-battle loop, decide whether to introduce one Rock family before the Gym as an optional hunt target, or let the first Gym preview families that become accessible later. The present 38-family opening pool already has multiple Grass and Water counter options; do not add an early Rock slot merely to make Roxanne beatable. Check the party against all 27 starter selections and their available level-15 moves before reweighting encounters.


## Design checks before calling this final

1. Check all four parties/moves at their actual level using current stat/type/move configuration.
2. Review player access to early Grass, Water, Fighting, Ground, Steel, and multi-hit answers; include the worst-case starter choices.
3. Validate the selected Aron set, Sturdy/item interactions, level distribution, and whether Lileep's Oran Berry makes the fight too long.
4. Tune Gym trainer battles as a lower-intensity preview of Roxanne; healing between them and the leader is available, so they do not need to drain the boss attempt.
5. Only then revise encounter weights or add a new early Rock hunt. Keep the Lv15 cap unchanged unless this complete slice shows a genuine pacing mismatch.

## Source references

- Emerald Imperium authored Roxanne party and AI: https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party#L5773-L5817.
- Emerald Imperium Rustboro Gym trainer parties: Josh and Tommy at https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party#L7245-L7273; Marc at https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/trainers.party#L12328-L12343.
- Shiny Vice Gym scripts and trainer call order: data/maps/RustboroCity_Gym/scripts.inc; authored parties: src/data/trainers.party.
- Enabled roster and configured stats: include/config/species_enabled.h; docs/design/gameplay-tables/normal-roster-inputs-733.csv; docs/design/gameplay-tables/normal-roster-inputs-by-form.csv.
- Gen 9 level-up learnsets: src/data/pokemon/level_up_learnsets/gen_9.h.
- Types, abilities and evolution data: src/data/pokemon/species_info/gen_1_families.h; gen_3_families.h; gen_9_families.h.
- Current Roxanne party: src/data/trainers.party, TRAINER_ROXANNE_1.
- Current access and story gates: docs/design/gameplay-tables/opening-hoenn-access.csv; docs/design/gameplay-tables/normal-encounter-gate-audit.md; docs/design/gameplay-tables/normal-boss-checkpoints.csv.



