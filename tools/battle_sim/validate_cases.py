#!/usr/bin/env python3
"""Check that Roxanne test fixtures only reference known game constants."""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "test/battle/roxanne.c"
CHECKS = (
    ("SPECIES_", "include/constants/species.h"),
    ("MOVE_", "include/constants/moves.h"),
    ("ITEM_", "include/constants/items.h"),
    ("ABILITY_", "include/constants/abilities.h"),
    ("AI_FLAG_", "include/constants/battle_ai.h"),
)

source = SOURCE.read_text(encoding="utf-8")
failed = False
for prefix, relative_path in CHECKS:
    symbols = sorted(set(re.findall(rf"\b{prefix}[A-Z0-9_]+", source)))
    definitions = (ROOT / relative_path).read_text(encoding="utf-8")
    missing = [symbol for symbol in symbols if symbol not in definitions]
    print(f"{relative_path}: {len(symbols)} symbols checked; {len(missing)} missing")
    if missing:
        print("  " + ", ".join(missing), file=sys.stderr)
        failed = True

if "AI_SINGLE_BATTLE_TEST" not in source or "SINGLE_BATTLE_TEST" not in source:
    print("Expected both AI and mechanics battle cases", file=sys.stderr)
    failed = True

sys.exit(1 if failed else 0)
