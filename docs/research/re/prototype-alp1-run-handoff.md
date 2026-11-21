# ALP1 PCSX run handoff (operator pending)

Status: **in progress**. Frames may exist under a local run id. No retail
movement match is claimed until `checklist.tsv` rows are filled and
`alp1_observation_checklist.py validate` is run by an operator with pad input.

## Known local run (2026-11-21)

| Field | Value |
| --- | --- |
| Run id | `20261121-022109` |
| Path | `build/coordination/alp1-movement-observation/20261121-022109/` |
| Procedure | [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md) |
| Summarize | `python3 tools/alp1_observation_summarize.py` on that path |

At handoff time the run had many `frames/frame-*.ppm` captures from the Lua
helper. `pad-input.tsv` had no guest edges because host window keys do not feed
the pad API. An operator must map **pad 1** in PCSX before the compare window.

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