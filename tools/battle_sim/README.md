# Battle matchup harness

The first slice is an engine-backed Roxanne scenario suite in `test/battle/roxanne.c`. It uses the existing battle test runner, so damage, move effects, abilities, items, and the tested opponent AI scores come from Shiny Vice's battle code.

## Run it

From the repository's supported build shell:

```sh
make check TESTS="Roxanne"
```

To build a test ROM for interactive inspection:

```sh
make pokeemerald-test.elf TESTS="Roxanne"
```

The C test sources are collected automatically by the Makefile. The test names share the `Roxanne` prefix, so the filter runs this scenario group.

## Add or compare a set

Add a `PLAYER(...)`/`OPPONENT(...)` setup to `test/battle/roxanne.c`, use `Moves(...)` to provide the candidate moves, and keep levels, IVs, natures, ability, and held item aligned with the live trainer or player checkpoint. Use `AI_SINGLE_BATTLE_TEST` when the question is what Roxanne's trainer AI scores or selects; use `SINGLE_BATTLE_TEST` when the question is an engine mechanic. Prefer `PARAMETRIZE` to compare controlled variants that differ in one field.

Candidate sets belong in these test fixtures while iterating. The live party remains in `src/data/trainers.party` until a candidate is promoted.

## Scope

These tests run actual engine turns, but the test DSL scripts the player's actions before battle. They validate specific matchups and mechanics; they do not yet run an autonomous player through a complete six-Pokémon battle or produce player win rates. The next extension is a test-only battle controller that chooses player actions during battle.

## Verified

On 2026-10-26, `make check -j4 TESTS="Roxanne"` built the test ROM and passed all seven cases. The first build also exposed six missing blank separators between existing rival Pokémon entries in `src/data/trainers.party`; those separators were added without changing the parties' data.
The full engine suite also ran on this source snapshot: 5,412 passed; five failed (SaveBlock3 compatibility, an experience comparison, and three animation task cleanup checks); 18 are marked known-failing, 421 TODO, and nine expected-failing.
The AI score cases showed that Roxanne's flat Prefer Status Moves bonus could outweigh a guaranteed Nosepass knockout. The live leader profile now omits that bonus: the engine still prefers Thunder Wave against a healthy target, then chooses Rock Throw when it can finish the target.

For a quick source-symbol sanity check before the ROM build:

```sh
python3 tools/battle_sim/validate_cases.py
```

This checks that referenced species, moves, items, abilities, and AI flags exist in the project's constants headers; `make check` remains the engine-level verification.


