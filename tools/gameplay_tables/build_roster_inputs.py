#!/usr/bin/env python3
"""Build configured roster input CSVs from Shiny Vice source tables."""
from __future__ import annotations
import csv
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TABLES = ROOT / "docs/design/gameplay-tables"

def read_csv(path):
    with path.open(encoding="utf-8-sig", newline="") as f:
        return list(csv.DictReader(f))

def write_csv(path, rows):
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0]), lineterminator="\n")
        w.writeheader(); w.writerows(rows)

def species_blocks():
    found = {}
    for path in sorted((ROOT / "src/data/pokemon/species_info").glob("gen_*_families.h")):
        lines = path.read_text(encoding="utf-8").splitlines()
        for i, line in enumerate(lines):
            m = re.match(r"\s*\[(SPECIES_[A-Z0-9_]+)\]\s*=\s*$", line)
            if not m: continue
            body, depth, opened = [], 0, False
            for source_line in lines[i + 1:]:
                body.append(source_line)
                stripped = re.sub(r'"(?:\\.|[^"\\])*"', '""', source_line).split("//", 1)[0]
                depth += stripped.count("{") - stripped.count("}")
                opened |= "{" in stripped
                if opened and depth == 0: break
            if opened and m.group(1) not in found:
                found[m.group(1)] = ("\n".join(body), f"{path.relative_to(ROOT).as_posix()}:{i + 1}")
    return found

def field(body, name):
    m = re.search(rf"\.{re.escape(name)}\s*=\s*([^\n]+)", body)
    return m.group(1).strip().removesuffix(",") if m else ""

def current(expr):
    m = re.fullmatch(r"\(?\s*[^?]+\?\s*([^:]+):\s*(.+?)\s*\)?", expr)
    return m.group(1).strip() if m else expr

def ids(expr, pattern):
    return "; ".join(re.findall(pattern, expr))

def main():
    coverage = read_csv(TABLES / "acquisition-coverage.csv")
    balance = read_csv(TABLES / "normal-roster-balance.csv")
    dex_order = [d for d in re.findall(r"^\s*NATIONAL_DEX_([A-Z0-9_]+),", (ROOT / "include/constants/pokedex.h").read_text(encoding="utf-8"), re.M) if d != "NONE"]
    dex_rank = {name: i + 1 for i, name in enumerate(dex_order)}
    family_by_dex, family_forms, generations = {}, {}, {}
    enabled = []
    for row in coverage:
        family = row["family_macro"]
        generations[family] = row["generation"]
        if int(row["enabled_national_dex_count"] or 0) <= 0: continue
        enabled.append(family)
        family_forms[family] = [x.strip() for x in row["enabled_family_species_ids"].split(";") if x.strip()]
        for d in row["enabled_national_dex_species"].split(";"):
            if d.strip(): family_by_dex[d.strip()] = family
    family_dex = defaultdict(list)
    for d, family in family_by_dex.items(): family_dex[family].append(d)
    species_constants = (ROOT / "include/constants/species.h").read_text(encoding="utf-8")
    aliases = {name: target for name, target in re.findall(r"^\s*(SPECIES_[A-Z0-9_]+)\s*=\s*(SPECIES_[A-Z0-9_]+),", species_constants, re.M)}
    blocks = species_blocks()
    # The repository selects P_LVL_UP_LEARNSETS = GEN_LATEST (Gen 9).
    learnset_path = ROOT / "src/data/pokemon/level_up_learnsets/gen_9.h"
    learnset_text = learnset_path.read_text(encoding="utf-8")
    forms = []
    form_by_dex = defaultdict(list)
    for family in enabled:
        dexes = sorted(family_dex[family], key=lambda d: dex_rank.get(d, 9999))
        default = next((d for d in dexes if f"SPECIES_{d}" in family_forms[family]), dexes[0] if dexes else "")
        for sid in family_forms[family]:
            token = sid.removeprefix("SPECIES_")
            linked = token if token in dexes else next((d for d in dexes if token.startswith(d + "_")), "")
            dex = linked or default
            body, source = blocks.get(sid, ("", ""))
            stat_names = ("baseHP", "baseAttack", "baseDefense", "baseSpAttack", "baseSpDefense", "baseSpeed")
            stats = [current(field(body, x)) for x in stat_names]
            stats = [v if re.fullmatch(r"\d+", v or "") else "" for v in stats]
            stat_ok = all(stats)
            types = ids(field(body, "types"), r"TYPE_[A-Z0-9_]+")
            abilities = ids(field(body, "abilities"), r"ABILITY_[A-Z0-9_]+")
            eggs = ids(field(body, "eggGroups"), r"EGG_GROUP_[A-Z0-9_]+")
            evo_expr = field(body, "evolutions")
            evo = "; ".join("/".join(x) for x in re.findall(r"\{\s*(EVO_[A-Z0-9_]+)\s*,\s*([^,}]+)\s*,\s*(SPECIES_[A-Z0-9_]+)", evo_expr))
            learn = field(body, "levelUpLearnset").rstrip(";")
            learn_src, move_count, early_moves = "", "", ""
            if learn:
                lm = re.search(rf"\b{re.escape(learn)}\s*\[\]\s*=\s*\{{(.*?)\n\}};", learnset_text, re.S)
                if lm:
                    learn_src = learnset_path.relative_to(ROOT).as_posix()
                    moves = re.findall(r"LEVEL_UP_MOVE\(\s*(\d+)\s*,\s*(MOVE_[A-Z0-9_]+)", lm.group(1))
                    move_count = str(len(moves))
                    early_moves = "; ".join(f"Lv{lv} {mv.removeprefix('MOVE_')}" for lv, mv in moves[:8])
            row = {
                "national_dex_species": dex, "national_dex_number": str(dex_rank.get(dex, "")),
                "family_macro": family, "generation": generations[family], "species_id": sid,
                "form_link_status": "Direct Dex token" if linked else "Family anchor; verify form semantics",
                "source_location": source,
                "record_status": "Explicit initializer parsed" if source else "No direct initializer; resolve macro/generated record",
                "base_hp": stats[0], "base_attack": stats[1], "base_defense": stats[2],
                "base_sp_attack": stats[3], "base_sp_defense": stats[4], "base_speed": stats[5],
                "base_stat_total": str(sum(map(int, stats))) if stat_ok else "", "types": types,
                "abilities": abilities, "egg_groups": eggs, "evolution_edges_explicit": evo,
                "level_up_learnset_ref": learn, "level_up_learnset_source": learn_src,
                "level_up_move_count": move_count, "first_eight_level_up_moves": early_moves,
                "source_parse_note": "GEN_LATEST configured; conditional numeric stats use updated branch; unresolved fields remain blank."
            }
            forms.append(row); form_by_dex[dex].append(row)
    fam_by_macro = {r["family_macro"]: r for r in coverage}
    species_rows = []
    for dex in sorted(family_by_dex, key=lambda d: dex_rank.get(d, 9999)):
        family = family_by_dex[dex]; fam = fam_by_macro[family]; group = form_by_dex[dex]
        base_id = aliases.get(f"SPECIES_{dex}", f"SPECIES_{dex}")
        base = next((r for r in group if r["species_id"] == base_id), {})
        species_rows.append({
            "national_dex_number": str(dex_rank.get(dex, "")), "national_dex_species": dex,
            "family_macro": family, "generation": generations[family], "configured_form_count": str(len(group)),
            "configured_species_ids": "; ".join(r["species_id"] for r in group),
            "explicit_stats_form_count": str(sum(bool(r["base_stat_total"]) for r in group)),
            "explicit_initializer_count": str(sum(bool(r["source_location"]) for r in group)),
            "base_species_source_id": base_id,
            "base_hp": base.get("base_hp", ""), "base_attack": base.get("base_attack", ""),
            "base_defense": base.get("base_defense", ""), "base_sp_attack": base.get("base_sp_attack", ""),
            "base_sp_defense": base.get("base_sp_defense", ""), "base_speed": base.get("base_speed", ""),
            "base_species_stats": "; ".join(base.get(k, "") for k in ("base_hp", "base_attack", "base_defense", "base_sp_attack", "base_sp_defense", "base_speed")),
            "base_stat_total": base.get("base_stat_total", ""), "base_species_types": base.get("types", ""),
            "base_species_abilities": base.get("abilities", ""), "base_species_egg_groups": base.get("egg_groups", ""),
            "base_species_evolution_edges": base.get("evolution_edges_explicit", ""),
            "base_species_levelup_ref": base.get("level_up_learnset_ref", ""),
            "base_species_levelup_move_count": base.get("level_up_move_count", ""),
            "base_species_first_eight_level_up_moves": base.get("first_eight_level_up_moves", ""),
            "acquisition_evidence_scope": "Family-level evidence only; verify source/form reachability in acquisition ledger",
            "current_hoenn_wild_maps": fam["current_hoenn_wild_maps"],
            "current_hoenn_script_path_records": fam["current_hoenn_script_path_count"],
            "first_access_window": fam["draft_first_access_window"],
            "boss_access_review": "Pending map/story gate and source-level timing verification"
        })
    write_csv(TABLES / "normal-roster-inputs-by-form.csv", forms)
    write_csv(TABLES / "normal-roster-inputs-733.csv", species_rows)
    source_by_dex = {r["national_dex_species"]: r for r in species_rows}
    for row in balance:
        inp = source_by_dex[row["national_dex_species"]]
        row["stats_types_abilities_review"] = (f"See normal-roster-inputs-733.csv; explicit stats for {inp['explicit_stats_form_count']}/{inp['configured_form_count']} forms; "
            f"base types={inp['base_species_types'] or 'needs macro/source resolution'}; abilities={inp['base_species_abilities'] or 'needs macro/source resolution'}")
        row["evolution_move_timing_review"] = (f"Base evolution={inp['base_species_evolution_edges'] or 'no explicit outgoing edge; verify terminal/form/macro'}; "
            f"level-up ref={inp['base_species_levelup_ref'] or 'needs macro/source resolution'}; see normal-roster-inputs-by-form.csv")
    write_csv(TABLES / "normal-roster-balance.csv", balance)
    # Repair the historical family-level screening cues from the rebuilt form
    # inventory. Exclude battle-only transformation entries from normal BST.
    battle_suffixes = ("_MEGA", "_GMAX", "_TERA", "_ULTRA", "_PRIMAL", "_ETERNAMAX", "_FUSION")
    family_source = defaultdict(list)
    for row in forms:
        if row["base_stat_total"] and not row["species_id"].endswith(battle_suffixes):
            family_source[row["family_macro"]].append(row)
    plan = read_csv(TABLES / "acquisition-plan.csv")
    for row in plan:
        candidates = family_source[row["family_macro"]]
        types = sorted({t.removeprefix("TYPE_") for item in candidates for t in item["types"].split("; ") if t})
        row["family_types"] = "/".join(types)
        row["max_normal_form_bst"] = str(max((int(item["base_stat_total"]) for item in candidates), default=""))
        row["balance_class_review_status"] = "Provisional; re-evaluate against rebuilt source profile and boss access"
    for row in plan:
        prefix = re.split(r"; max (?:standard-family|normal-form) BST", row["confidence"], maxsplit=1)[0]
        fam_dex_count = len(family_dex[row["family_macro"]])
        bst = row["max_normal_form_bst"] or "unresolved"
        types = row["family_types"] or "unresolved"
        row["confidence"] = f"{prefix}; max normal-form BST {bst}; types {types}; {fam_dex_count} NatDex entries"
    write_csv(TABLES / "acquisition-plan.csv", plan)

    # Materialize the starter counter-pick and natural level evolution expected
    # for each rival checkpoint. Move sets remain a separate authoring decision.
    starter_pool = read_csv(TABLES / "starter-region-pools.csv")
    starter_lookup = {(r["region_value"], r["starter_slot"]): r for r in starter_pool}
    starter_sources = {r["species_id"]: r for r in forms}
    if any(r["family_macro"] not in enabled or r["starter_species_id"] not in starter_sources for r in starter_pool):
        raise SystemExit("Starter table references a disabled family or missing species initializer")
    rival_checkpoints = [r for r in read_csv(TABLES / "normal-boss-checkpoints.csv")
                         if r["category"] == "Rival" and r["campaign_checkpoint"] in
                         ("Route 103 rival", "Route 104 / Rustboro-area rival", "Route 110 rival", "Route 119 rival", "Lilycove rival")]
    progression = []
    for checkpoint in rival_checkpoints:
        level = int(checkpoint["configured_source_ace_level"])
        for player_row in starter_pool:
            region_value = player_row["region_value"]
            player_slot = int(player_row["starter_slot"])
            rival_slot = (player_slot + 1) % 3
            rival_row = starter_lookup[(region_value, str(rival_slot))]
            species_id = rival_row["starter_species_id"]
            evolution_path = [species_id]
            while True:
                source = starter_sources.get(species_id, {})
                outgoing = source.get("evolution_edges_explicit", "")
                next_edge = None
                for edge in outgoing.split("; "):
                    parts = edge.split("/")
                    if len(parts) == 3 and parts[0] == "EVO_LEVEL" and parts[2].startswith("SPECIES_"):
                        try:
                            req_level = int(parts[1])
                        except ValueError:
                            continue
                        if req_level <= level:
                            next_edge = parts[2]
                            break
                if next_edge is None:
                    break
                species_id = next_edge
                evolution_path.append(species_id)
            progression.append({
                "checkpoint_order": checkpoint["campaign_order"],
                "checkpoint": checkpoint["campaign_checkpoint"],
                "region_value": region_value,
                "region": player_row["region"],
                "player_slot": str(player_slot),
                "player_starter_species_id": player_row["starter_species_id"],
                "rival_slot": str(rival_slot),
                "rival_starter_species_id": rival_row["starter_species_id"],
                "rival_level": str(level),
                "rival_species_at_level": species_id,
                "level_evolution_path": " -> ".join(evolution_path),
                "moveset_status": "Needs authored legal checkpoint set; do not copy a Hoenn starter's moves",
                "party_variant_status": "Use existing player-slot trainer variant; substitute rival starter from this row",
            })
    write_csv(TABLES / "rival-starter-progression.csv", progression)
    unique_forms = {r["species_id"] for r in forms}
    print(f"Dex entries={len(species_rows)}; families={len({r['family_macro'] for r in species_rows})}; forms={len(unique_forms)}")
    print(f"Forms with explicit stats={sum(bool(r['base_stat_total']) for r in forms)}; explicit source initializers={sum(bool(r['source_location']) for r in forms)}")
    print(f"Starter choices={len(starter_pool)}; rival progression rows={len(progression)}")
    if len(species_rows) != 733 or len({r["family_macro"] for r in species_rows}) != 346 or len(unique_forms) != sum(map(len, family_forms.values())):
        raise SystemExit("Roster validation failed")
    if len(starter_pool) != 27 or len(starter_lookup) != 27 or len(progression) != len(rival_checkpoints) * 27:
        raise SystemExit("Starter pool/rival progression validation failed")

if __name__ == "__main__": main()
