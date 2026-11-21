# ALP1 PCSX run handoff (operator pending)

Status: **in progress**. Frames may exist under a local run id. No retail
movement match is claimed until `checklist.tsv` rows are filled and
`alp1_observation_checklist.py validate` is run by an operator with pad input.

## Known local run (2026-11-21)

| Field | Value |
| --- | --- |
| Run id | `20261121-022109` (scripted capture; may differ from live play) |
| Path | `build/coordination/alp1-movement-observation/20261121-022109/` |
| Procedure | [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md) |
| Summarize | `python3 tools/alp1_observation_summarize.py` on that path |

Operator report (same date, separate from scripted run): **NEW GAME** with
**Cross**, ~5 s load, **no** difficulty/memory/mission-select prompts, straight
into a mission. **ALP1 identity not confirmed.** See **Operator report** in
the observation note.

At handoff time the scripted run had many `frames/frame-*.ppm` captures. Map
**pad 1** in PCSX so `pad-input.tsv` records edges during the compare window.

## Operator resume

1. Focus PCSX-Redux with the same portable config under the run's
   `pcsx-config/` if the session is still open, or start a new run with
   `tools/pcsx/run_alp1_observation.sh`.
2. Complete worksheet steps for mission reach and the eight-frame Cross
   compare window.
3. Fill `session.txt` and `checklist.tsv`.
4. `python3 tools/alp1_observation_checklist.py validate <run-dir>`.

Do not commit anything under `build/coordination/`.

## Host prototype checks (no PCSX)

```sh
sh tools/prototype_retail_gate.sh
```

Row 8 retail spawn uses `read_disc_data_file` for `DATA/ALP1.PAD` when the
owner extract is present. See [prototype-task-6.md](prototype-task-6.md).