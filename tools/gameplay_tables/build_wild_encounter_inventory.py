#!/usr/bin/env python3
"""Aggregate wild_encounters.json into enabled-family/method access rows.

Shares are conditional slot weights for a method (and fishing rod tier), not
overall odds of an encounter while walking. Story reachability is deliberately
left pending here; map/script gates must be audited separately.
"""
from __future__ import annotations

import csv
import json
from collections import OrderedDict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TABLES = ROOT / "docs/design/gameplay-tables"
WILD_DATA = ROOT / "src/data/wild_encounters.json"
ROSTER_INPUT = TABLES / "normal-roster-inputs-by-form.csv"
OUTPUT = TABLES / "wild-encounter-inventory.csv"


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(encoding="utf-8-sig", newline="") as f:
        return list(csv.DictReader(f))


def write_csv(path: Path, rows: list[dict[str, str]]) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(rows[0]), lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)


def main() -> None:
    family_by_species: dict[str, str] = {}
    for row in read_csv(ROSTER_INPUT):
        family_by_species[row["species_id"]] = row["family_macro"]

    map_region_by_id: dict[str, str] = {}
    for map_path in (ROOT / "data/maps").rglob("map.json"):
        map_data = json.loads(map_path.read_text(encoding="utf-8"))
        if map_data.get("id"):
            map_region_by_id[map_data["id"]] = map_data.get("region", "REGION_UNKNOWN")

    wild = json.loads(WILD_DATA.read_text(encoding="utf-8"))
    rows: list[dict[str, str]] = []
    unmapped: set[str] = set()
    source_groups = 0

    for group in wild["wild_encounter_groups"]:
        if not group.get("for_maps"):
            continue
        field_by_type = {field["type"]: field for field in group["fields"]}

        for entry in group["encounters"]:
            for method, encounter in entry.items():
                if method in ("map", "base_label") or not isinstance(encounter, dict):
                    continue
                mons = encounter.get("mons", [])
                if not mons:
                    continue

                field = field_by_type.get(method, {})
                rates = field.get("encounter_rates", [])
                groups = field.get("groups", {})
                tier_indexes = (
                    {tier: indexes for tier, indexes in groups.items()}
                    if method == "fishing_mons"
                    else {"": list(range(len(mons)))}
                )

                for tier, indexes in tier_indexes.items():
                    source_groups += 1
                    weight_sum = sum(int(rates[i]) for i in indexes)
                    if weight_sum != 100:
                        raise SystemExit(
                            f"{entry['map']} {method} {tier or '-'} weights sum to {weight_sum}, expected 100"
                        )

                    by_family: OrderedDict[str, dict] = OrderedDict()
                    for index in indexes:
                        mon = mons[index]
                        species = mon["species"]
                        family = family_by_species.get(species, "UNMAPPED_OR_DISABLED")
                        if family == "UNMAPPED_OR_DISABLED":
                            unmapped.add(species)
                        item = by_family.setdefault(
                            family,
                            {"species": [], "levels": set(), "weight": 0, "slots": 0},
                        )
                        item["species"].append(species)
                        item["levels"].add((int(mon["min_level"]), int(mon["max_level"])))
                        item["weight"] += int(rates[index])
                        item["slots"] += 1

                    for family, item in by_family.items():
                        levels = sorted(item["levels"])
                        level_text = "; ".join(
                            f"Lv{minimum}" if minimum == maximum else f"Lv{minimum}-Lv{maximum}"
                            for minimum, maximum in levels
                        )
                        rows.append(
                            {
                                "map_id": entry["map"],
                                "map_region": map_region_by_id.get(entry["map"], "REGION_UNKNOWN"),
                                "method": method.removesuffix("_mons"),
                                "method_tier": tier,
                                "family_macro": family,
                                "species_in_slots": "; ".join(sorted(set(item["species"]))),
                                "aggregate_slot_weight": f"{item['weight']}%",
                                "slot_count": str(item["slots"]),
                                "levels": level_text,
                                "method_encounter_rate": str(encounter.get("encounter_rate", "")),
                                "story_gate_status": "Pending map/script audit",
                                "source": "src/data/wild_encounters.json",
                            }
                        )

    write_csv(OUTPUT, rows)
    print(f"Encounter family rows={len(rows)}; method groups={source_groups}; unmapped species={len(unmapped)}")
    if unmapped:
        print("Unmapped species IDs: " + "; ".join(sorted(unmapped)))


if __name__ == "__main__":
    main()
