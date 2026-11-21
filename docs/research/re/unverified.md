# Unverified

A claim stays here until someone re-checks the address on a disc they own.

One claim per entry:

- Address
- What you claim
- The command or Ghidra step that re-checks it

- Address: `0x8007f9f8`
- Claim: pc `0x8007f9f8`, load `0x80010000`, text size `0x000b5800`
- Re-check: `python3 tools/exe_info.py build/disc/SLUS_004.91`

- Address: none (procedure, not a code address)
- Claim: ALP1 movement observation is procedure only until a local checklist run
- Re-check: fill one row in [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md) on a disc you own

- Address: none (procedure, not a code address)
- Claim: PROTOTYPE rows 5 through 9 `*_retail` and related owner-file CTests are not green in disc-free CI; they need an owner extract under `build/disc/`
- Re-check: [prototype-verification-runbook.md](prototype-verification-runbook.md) (table **Prototype CTest names**); run the matching `prototype_task_*_retail` or `prototype_task_*_smoke_headless_retail` after `python tools/disc.py`

- Address: none (procedure, not a code address)
- Claim: Host FRONT presentation and menu smoke BMPs are not an automated pixel match vs PCSX-Redux retail
- Re-check: limits in [prototype-task-7.md](prototype-task-7.md) (**Remaining gaps**, **Visible transition**); [prototype-playable-smoke.md](prototype-playable-smoke.md) (integration note header); optional local compare in [prototype-task-7-pixel-checkpoint.md](prototype-task-7-pixel-checkpoint.md)

- Address: none (procedure, not a code address)
- Claim: No operator has validated an ALP1 PCSX session; `build/coordination/alp1-movement-observation/` stays empty in-repo
- Re-check: run `sh tools/pcsx/run_alp1_observation.sh` then `python3 tools/alp1_observation_checklist.py validate` on the run dir (see **Operator quick start** in [prototype-alp1-movement-observation.md](prototype-alp1-movement-observation.md)); same row-8 procedure as the ALP1 entry above

- Address: none (procedure, not a code address)
- Claim: Row 3 PsyZ adapter trial and row 4 replay harness are not executed in-tree
- Re-check: open checklists in [prototype-psyZ-trial-status.md](prototype-psyZ-trial-status.md) and [prototype-replay-trial-status.md](prototype-replay-trial-status.md); row notes in [prototype-tier-index.md](prototype-tier-index.md)
