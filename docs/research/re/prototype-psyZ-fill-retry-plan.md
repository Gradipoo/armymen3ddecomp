# PROTOTYPE row 3 PsyZ fill retry plan

Status: **parked pending a specific fix**. Do not re-run the November 17, 2026
PsyZ coordination trial unchanged. See [psyz-synthetic-trial.md](psyz-synthetic-trial.md)
and the fill row in [prototype-psyZ-trial-status.md](prototype-psyZ-trial-status.md).

## Failing check

Synthetic rectangle `(3, 0, 1, 1)` on GP0 fill `0x02`.

Our reference fill sink ([gpu-fill-adapter-trial.md](gpu-fill-adapter-trial.md),
`fill_vram`) after horizontal alignment and width rounding requires red
`0x7c00` at VRAM `(0, 0)` and `(15, 0)`. The PsyZ software clear path left
both pixels at zero. Source review noted the full GP0 fill dispatcher was not
exercised in that runner, so the mismatch may sit in dispatch or clear, not
only in raster semantics.

`ctest fill_vram` and the shared adapter trial remain the in-tree reference.
The SDL2 window and menu submit path stay on that sink until row 3 proves
otherwise.

## Retry preconditions (all required before another PsyZ import trial)

- [ ] Cite which layer failed: GP0 opcode dispatch, rectangle unpack, or
      `software_rasterizer` clear.
- [ ] One concrete change hypothesis (upstream patch, adapter shim, or documented
      retail quirk we intentionally keep).
- [ ] License scope re-checked for any file touched (MPL-2.0 vs unlicensed
      `psyz/include`; see [PROTOTYPE.md](../../PROTOTYPE.md) PsyZ pins).
- [ ] Same synthetic rectangle plus at least one masked-width case from
      [gpu-fill-adapter-trial.md](gpu-fill-adapter-trial.md) must pass before
      textured-quad checklist items count toward row 3.

## Alternative path (default)

Advance observed first-screen services on the existing SDL fill sink and
`menu_submit_frame` stand-ins. Reopen PsyZ only when the preconditions above
are satisfied. Do not combine a backend migration with a new stand-in in one
change.

## Stop rules

After **three** failed attempts at the **same** fill mismatch, stop PsyZ fill
work. Record commands, exits, and the next bounded outcome in
[psyz-synthetic-trial.md](psyz-synthetic-trial.md). Attempt count today: **1**.