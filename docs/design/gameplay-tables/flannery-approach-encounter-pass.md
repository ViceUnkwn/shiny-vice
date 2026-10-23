# Route 112 through Flannery encounter pass

**Status:** Six land encounter tables implemented in `src/data/wild_encounters.json`; build/emulator review pending. Their species are all present in the 733-species roster input.

## Story and method gates

- Route 111, Route 110, and Route 117 are the previous encounter pass. This pass leaves Route 111's shared land table unchanged.
- The main route chain after Wattson reaches Route 112 and Fiery Path, then Route 113 and Fallarbor. Route 114 leads to the first Meteor Falls room; the story then returns to Mt. Chimney. Jagged Pass leads down to Lavaridge and Flannery.
- The pass edits land slots only. Surf, fishing, and Rock Smash rows remain unchanged and separate from land encounters. Route 115 is outside the Flannery slice in the campaign outline; deeper Meteor Falls rooms are later/exploratory content and were not edited.
- Current Shiny Vice cap data gives cap 29 after Wattson, covering the Flannery and Mt. Chimney band. This pass uses the same broad level bands as Imperium's release source: Route 112/Fiery Path 22–24, Route 113 24–28, Route 114 23–25, and Meteor Falls/Jagged Pass 25–27.

## Land pools

All six maps have twelve distinct species. The engine weights their slots 20%, 20%, 10%, 10%, 10%, 10%, 5%, 5%, 4%, 4%, 1%, 1% in listed order. This gives each map broad roster coverage while retaining a few genuinely rare hunt slots.

| Map | Species in slot order | Levels |
|---|---|---:|
| Route 112 | Numel, Marill, Machop, Rolycoly, Growlithe, Phanpy, Slugma, Ponyta, Teddiursa, Sandshrew, Houndour, Pawniard | 22–24 |
| Fiery Path | Numel, Slugma, Torkoal, Koffing, Grimer, Salandit, Houndour, Litwick, Darumaka, Machop, Growlithe, Sableye | 22–24 |
| Route 113 | Spinda, Slugma, Skarmory, Rolycoly, Cottonee, Stantler, Venipede, Tropius, Hoppip, Teddiursa, Snorunt, Goomy | 24–28 |
| Route 114 | Swablu, Zangoose, Seviper, Lotad, Seedot, Phanpy, Teddiursa, Sneasel, Hoppip, Tinkatink, Goomy, Skarmory | 23–25 |
| Meteor Falls 1F 1R | Zubat, Solrock, Aron, Roggenrola, Noibat, Drilbur, Sableye, Nosepass, Geodude, Misdreavus, Mawile, Bronzor | 25–27 |
| Jagged Pass | Numel, Machop, Spoink, Phanpy, Rolycoly, Growlithe, Ponyta, Sandshrew, Teddiursa, Slakoth, Houndour, Onix | 25–27 |

## Imperium comparison

Imperium is the closest public Emerald Expansion reference, and its release branch is the source for this comparison: [Imperium's wild encounter data](https://github.com/iriv24/pokeemerald-expansion/blob/release/src/data/wild_encounters.json). Its same maps use the same 12-slot land structure and generally place twelve different species in those slots; its Flannery-band levels are 22–24 on Route 112/Fiery Path, 24–28 on Route 113, 23–25 on Route 114, and 25–27 on Jagged Pass and Meteor Falls 1F. We now follow that structural and level-band pattern.

We keep Imperium's map-first approach but curate the choices to Shiny Vice's 733 species and make the mix reflect each area's Hoenn identity. This avoids importing Imperium's specific species list wholesale. In particular, this plan keeps the Bagon hunt in the deeper Meteor Falls area, while offering a dozen cave families in the first room. The slot-weighting also means early-route pools aren't twelve equally common species: the 1% and 4% slots remain meaningful hunt targets.

Imperium's release data also uses a different fishing slot grouping (Old Rod three slots, Good Rod three, Super Rod five) from the current Shiny Vice/Expansion grouping. This pass did not change Shiny Vice's water or fishing rates or rod groups; review those separately against actual rod acquisition and map access before editing them.

## Review still needed

1. Build and play the route chain to check table loading, encounter selection, and whether the levels feel right against the authored trainer/boss teams.
2. Check Route 112's shared land table on both map sections and confirm the cable-car/grunt story sequence is intact.
3. Audit fishing, Surf, and Rock Smash maps/method rows independently; confirm Old Rod, Good Rod, Super Rod, Surf, and badge gates against scripts.
4. Continue the next land-table slice after Flannery, beginning with the post-Gym Route 115/Norman approach and Route 118–120.
