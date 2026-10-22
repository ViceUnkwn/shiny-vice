# Starter and rival planning

Keep current slot meaning: 0 = Grass, 1 = Fire, 2 = Water. The menu's region value selects only which trio Professor Birch places in his bag. The player always starts in Hoenn and follows the Emerald story; no other region's professor, map, or story is selected. The rival picks from the same chosen trio using the counter-pick map.

`starter-region-pools.csv` is the canonical 27-choice code-ordered mapping. Its region column names the starter set, not the game region. Birch's bag must show the selected trio in its three Poké Balls. The existing shiny-in-the-bag code must hand the exact previewed roll to the player when its ball is chosen. `rival-starter-progression.csv` expands those choices across all five current rival checkpoints and derives the rival's expected evolved species from the repository's level-based evolution rules. Each row still needs an authored legal moveset and trainer metadata before it becomes a Normal battle proposal.

| Region | Slot 0: Grass | Slot 1: Fire | Slot 2: Water |
|---|---|---|---|
| Kanto | Bulbasaur | Charmander | Squirtle |
| Johto | Chikorita | Cyndaquil | Totodile |
| Hoenn | Treecko | Torchic | Mudkip |
| Sinnoh | Turtwig | Chimchar | Piplup |
| Unova | Snivy | Tepig | Oshawott |
| Kalos | Chespin | Fennekin | Froakie |
| Alola | Rowlet | Litten | Popplio |
| Galar | Grookey | Scorbunny | Sobble |
| Paldea | Sprigatito | Fuecoco | Quaxly |

## Counter-pick

| Player slot | Rival slot | Hoenn example |
|---|---|---|
| Grass (0) | Fire (1) | Treecko → Torchic |
| Fire (1) | Water (2) | Torchic → Mudkip |
| Water (2) | Grass (0) | Mudkip → Treecko |

Resolve the starter set during new-game setup and save it. Derive the rival species from saved starter set and player starter slot. Existing Route 103 `VAR_STARTER_MON` values 0/1/2 align with Grass/Fire/Water. The trainer suffix names the player's starter; party species below are the rival's current team. Keep all dialogue, maps, and campaign events in Hoenn.

Implementation note: current `src/starter_choose.c` still hardcodes the Hoenn/FRLG arrays; the starter-set setting is saved but does not select the bag contents yet. Existing rival scripts and parties also branch only on the Hoenn starter slot.

## Current configured rival-party inventory

This is a source snapshot, not a proposed balance. Non-Route-103 reachability needs script confirmation. Levels and species are current configured parties.

| Checkpoint | Trainer ID | Player starter | Current rival party (species:level) | Status |
|---|---|---|---|---|
| Route 103 | `TRAINER_BRENDAN_ROUTE_103_TREECKO` | Treecko | Torchic:5 | Opening branch |
| Route 103 | `TRAINER_BRENDAN_ROUTE_103_TORCHIC` | Torchic | Mudkip:5 | Opening branch |
| Route 103 | `TRAINER_BRENDAN_ROUTE_103_MUDKIP` | Mudkip | Treecko:5 | Opening branch |
| Route 103 | `TRAINER_MAY_ROUTE_103_TREECKO` | Treecko | Torchic:5 | Opening branch |
| Route 103 | `TRAINER_MAY_ROUTE_103_TORCHIC` | Torchic | Mudkip:5 | Opening branch |
| Route 103 | `TRAINER_MAY_ROUTE_103_MUDKIP` | Mudkip | Treecko:5 | Opening branch |
| Route 110 | `TRAINER_BRENDAN_ROUTE_110_TREECKO` | Treecko | Wingull:18, Lombre:18, Combusken:20 | Audit timing/cap |
| Route 110 | `TRAINER_BRENDAN_ROUTE_110_TORCHIC` | Torchic | Lombre:18, Slugma:18, Marshtomp:20 | Audit timing/cap |
| Route 110 | `TRAINER_BRENDAN_ROUTE_110_MUDKIP` | Mudkip | Slugma:18, Wingull:18, Grovyle:20 | Audit timing/cap |
| Route 110 | `TRAINER_MAY_ROUTE_110_TREECKO` | Treecko | Wingull:18, Lombre:18, Combusken:20 | Audit timing/cap |
| Route 110 | `TRAINER_MAY_ROUTE_110_TORCHIC` | Torchic | Lombre:18, Slugma:18, Marshtomp:20 | Audit timing/cap |
| Route 110 | `TRAINER_MAY_ROUTE_110_MUDKIP` | Mudkip | Wingull:18, Slugma:18, Grovyle:20 | Audit timing/cap |
| Route 119 | `TRAINER_BRENDAN_ROUTE_119_TREECKO` | Treecko | Pelipper:29, Lombre:29, Combusken:31 | Audit timing/cap |
| Route 119 | `TRAINER_BRENDAN_ROUTE_119_TORCHIC` | Torchic | Lombre:29, Slugma:29, Marshtomp:31 | Audit timing/cap |
| Route 119 | `TRAINER_BRENDAN_ROUTE_119_MUDKIP` | Mudkip | Slugma:29, Pelipper:29, Grovyle:31 | Audit timing/cap |
| Route 119 | `TRAINER_MAY_ROUTE_119_TREECKO` | Treecko | Pelipper:29, Lombre:29, Combusken:31 | Audit timing/cap |
| Route 119 | `TRAINER_MAY_ROUTE_119_TORCHIC` | Torchic | Lombre:29, Slugma:29, Marshtomp:31 | Audit timing/cap |
| Route 119 | `TRAINER_MAY_ROUTE_119_MUDKIP` | Mudkip | Slugma:29, Lombre:29, Grovyle:31 | Audit timing/cap |
| Rustboro | `TRAINER_BRENDAN_RUSTBORO_TREECKO` | Treecko | Lotad:13, Torchic:15 | Verify script reachability |
| Rustboro | `TRAINER_BRENDAN_RUSTBORO_TORCHIC` | Torchic | Slugma:13, Mudkip:15 | Verify script reachability |
| Rustboro | `TRAINER_BRENDAN_RUSTBORO_MUDKIP` | Mudkip | Wingull:13, Treecko:15 | Verify script reachability |
| Rustboro | `TRAINER_MAY_RUSTBORO_TREECKO` | Treecko | Lotad:13, Torchic:15 | Verify script reachability |
| Rustboro | `TRAINER_MAY_RUSTBORO_TORCHIC` | Torchic | Torkoal:13, Mudkip:15 | Verify script reachability |
| Rustboro | `TRAINER_MAY_RUSTBORO_MUDKIP` | Mudkip | Wingull:13, Treecko:15 | Verify script reachability |
| Lilycove | `TRAINER_BRENDAN_LILYCOVE_TREECKO` | Treecko | Tropius:31, Pelipper:32, Ludicolo:32, Combusken:34 | Audit timing/cap |
| Lilycove | `TRAINER_BRENDAN_LILYCOVE_TORCHIC` | Torchic | Tropius:31, Ludicolo:32, Slugma:32, Marshtomp:34 | Audit timing/cap |
| Lilycove | `TRAINER_BRENDAN_LILYCOVE_MUDKIP` | Mudkip | Tropius:31, Slugma:32, Pelipper:32, Grovyle:34 | Audit timing/cap |
| Lilycove | `TRAINER_MAY_LILYCOVE_TREECKO` | Treecko | Tropius:31, Pelipper:32, Ludicolo:32, Combusken:34 | Audit timing/cap |
| Lilycove | `TRAINER_MAY_LILYCOVE_TORCHIC` | Torchic | Tropius:31, Ludicolo:32, Slugma:32, Marshtomp:34 | Audit timing/cap |
| Lilycove | `TRAINER_MAY_LILYCOVE_MUDKIP` | Mudkip | Tropius:31, Slugma:32, Pelipper:32, Grovyle:34 | Audit timing/cap |

Placeholder records `TRAINER_BRENDAN_PLACEHOLDER` (Groudon:5) and `TRAINER_MAY_PLACEHOLDER` (Kyogre:5) are excluded until a live story reference is found.

## Open design choices

- Confirm the story rival checkpoints and script reachability for Rustboro/Lilycove variants.
- Recommended first scope for non-Hoenn trios: replace only the rival's starter at each milestone, then rebalance the other slots to match actual availability. Decide if rival has a regional team identity instead.
- Define opening fight level/team/moves and how starter acquisition affects early Normal-mode challenge.
- Decide postgame rival and rematch scope.


## Current source alignment

All 27 starter families listed above are currently enabled in the roster config. The regional trio list is therefore eligible against today's family switches, but the data row records these as planned new-game choices; it does not prove that selecting the region grants the corresponding Pokemon yet.

The existing source rival parties are still Hoenn-specific. Route 103, Route 104/Rustboro, Route 110, Route 119, and Lilycove currently reference Treecko/Torchic/Mudkip branches. The counter-pick rule only solves the rival's starter slot. The rest of each rival team must be redesigned for the selected region and for the player's actual acquisition options before those encounters can be balanced.

Rival logic should use a stored region plus starter slot. For the player's slot s, the counter-pick slot is (s + 1) % 3 under the Grass/Fire/Water ordering above. This preserves the current Hoenn rule and makes the same selection deterministic at later checkpoints.
