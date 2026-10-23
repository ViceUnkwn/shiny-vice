#!/usr/bin/env python3
"""Build the source-backed encounter-method envelope before Wattson.

Map/story gates are intentionally explicit here: wild_encounters.json records
what exists, while this table records whether each method is usable before the
Mauville Gym battle.
"""
from __future__ import annotations

import csv
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TABLES = ROOT / "docs/design/gameplay-tables"
SOURCE = TABLES / "wild-encounter-inventory.csv"
OUTPUT = TABLES / "wattson-approach-access.csv"

MAP_GATES = {
    "MAP_ROUTE110": "Route 110 opens north from Slateport after the Oceanic Museum Aqua event; the rival event occurs on this route.",
    "MAP_ROUTE111": "Route 111 is reachable north from Mauville. The southern land remains reachable; Route 112's western connection lies beyond the Rock Smash rocks.",
    "MAP_ROUTE117": "Route 117 opens west from Mauville without a Gym badge and connects to Verdanturf.",
}


def read_rows(path: Path) -> list[dict[str, str]]:
    with path.open(encoding="utf-8-sig", newline="") as f:
        return list(csv.DictReader(f))


def eligibility(row: dict[str, str]) -> tuple[str, str]:
    method, tier = row["method"], row["method_tier"]
    if method == "land":
        return "Available", "Walkable encounter area is reachable before the Wattson fight."
    if method == "fishing" and tier == "old_rod":
        return "Available if obtained", "Old Rod is an optional Dewford pickup available before leaving for Slateport."
    if method == "fishing" and tier == "good_rod":
        return "Locked", "Good Rod is obtained on Route 118, which requires Surf after Norman."
    if method == "fishing" and tier == "super_rod":
        return "Locked", "Super Rod is obtained in Mossdeep after the Wattson checkpoint."
    if method == "water":
        return "Locked", "Surf encounter method is unusable until HM03 and the Balance Badge (badge 5)."
    if method == "rock_smash":
        return "Locked until Wattson is defeated", "Rock Smash field use requires HM06 and the Dynamo Badge awarded by this Gym."
    return "Needs review", "No method gate rule is recorded for this method."


def main() -> None:
    output_rows: list[dict[str, str]] = []
    for row in read_rows(SOURCE):
        map_id = row["map_id"]
        if map_id not in MAP_GATES:
            continue
        status, method_gate = eligibility(row)
        output_rows.append(
            {
                "checkpoint": "Route 110 rival / Wattson, before defeating Wattson",
                "map_id": map_id,
                "map_gate": MAP_GATES[map_id],
                "method": row["method"],
                "method_tier": row["method_tier"],
                "family_macro": row["family_macro"],
                "species_in_slots": row["species_in_slots"],
                "weighted_share": row["aggregate_slot_weight"],
                "levels": row["levels"],
                "availability": status,
                "method_gate": method_gate,
                "balance_note": (
                    "Single Route 111 land table includes Cacnea slots outside the desert;"
                    " table data are map-wide, not terrain-specific."
                    if map_id == "MAP_ROUTE111" and row["family_macro"] == "P_FAMILY_CACNEA"
                    else ""
                ),
                "source": row["source"],
            }
        )

    with OUTPUT.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(output_rows[0]), lineterminator="\n")
        writer.writeheader()
        writer.writerows(output_rows)
    print(f"Wattson approach method rows={len(output_rows)}")


if __name__ == "__main__":
    main()
