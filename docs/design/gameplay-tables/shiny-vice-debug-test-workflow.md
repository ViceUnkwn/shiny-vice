# Shiny Vice debug test workflow

This workflow uses the existing Emerald Expansion overworld debug menu, with a Shiny Vice test submenu for cap presets, cap modes, encounter items, and direct map-coordinate warps. The debug menu is available in normal development builds and is disabled in release builds.

## Open the menu

While standing in the overworld, hold **R** and press **Start**. Open **Shiny Vice Tests…** for the project-specific helpers.

## Encounter tables and map gates

1. Use **Warp to map coordinates…** to select the map group, map number, X, and Y. The selector shows the map name while choosing its number. This bypasses walking through story gates and enters the selected map at the chosen tile.
2. Find a passable tile near the grass/water you want to inspect, then walk into the encounter area. The warp can land on an impassable tile; choose a nearby coordinate if that happens.
3. **Give test balls and rods** adds Poké Balls and all three rods, allowing catches and fishing-method checks without waiting for their gifts.
4. For Surf, Dive, and Rock Smash methods, use **Utilities… → Cheat start** on a disposable test save. That setup provides the badges and field-move Pokémon. It also changes story flags and gives a sample party; don't use it on the save you intend to keep.

Current useful map numbers in Emerald's map group `000` include Route 110 = `025` and Route 117 = `032`. Encounter availability still depends on using the correct terrain and method; map warping does not make grass encounters occur on a path tile.

## Level cap and gym-boss checks

Choose **Set cap mode: OFF**, **SOFT**, or **HARD** first; the boss presets preserve that setting. Then select a boss preset to establish the preceding cap milestone and warp directly to the Leader:

- **15 -> Roxanne (cap 19)** clears badge/story cap flags, resets Roxanne's defeated state, and places you in front of her in Rustboro Gym.
- **24 -> Wattson (cap 29)** sets Devon Goods and badges 1–2, resets Wattson's defeated/hidden state, and places you in front of him in Mauville Gym.
- **29 -> Flannery (cap 31)** sets badges 1–3, resets Flannery's defeated state, and places you in front of her in Lavaridge Gym.

Face the Leader and interact to start the normal gym battle. Winning should award the badge through the map script and advance the cap. These fixtures intentionally change saved progression flags and put you on a gym map, so use a disposable save. Check the Trainer Card before and after the win; in Hard mode, also check battle EXP and non-battle level gains at the cap. Soft mode should reduce battle EXP above the cap without blocking other level gains.

## Trainer and boss battles

Use **Trainers…** from the main debug menu. The trainer selector can start a chosen trainer battle directly, avoiding map events and story triggers. For trainers loaded on the current map, **Choose trainer from map** is the convenient selector. Use a test team appropriate to the checkpoint; the debug trainer battle does not recreate story flags, preceding battles, or battle-specific event scenes.

## Starter and rival validation

Starter region is a new-game choice committed into SaveBlock3 and read by both the starter preview/reward and rival starter logic. Validate each region by starting a fresh game with that region selected, then check Birch's three previews, select one, and confirm the rival picks from the same region pool. There is no safe in-save shortcut that replays this sequence: reopening the existing starter screen would also run the first-battle callback and could grant another starter or start a battle against stale story state.

## Suggested test order

1. Use a disposable save or emulator state.
2. Test starter/rival pairs via fresh games for each region you need to verify.
3. On a separate save, use cap mode + cap presets to verify trainer-card display and leveling rules.
4. Warp to encounter maps and test land, water, and fishing methods; use Cheat Start only when badge-gated field moves are needed.
5. Use the trainer selector for isolated boss-party checks, then perform at least one normal story-triggered battle later to validate its map script and progression flags.