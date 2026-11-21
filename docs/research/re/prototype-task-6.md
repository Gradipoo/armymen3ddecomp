# PROTOTYPE task 6 disc file read boundary

Status: **synthetic** met through `read_disc_data_file` and `prototype_task_6`;
**disc-backed** when owner `DATA/ALP1.TXT` is present (same test reads the
measured name and non-zero size). This is a host synchronous stand-in, not
retail `CdRead` recreation.

## Retail observation

[first-screen-observation.md](first-screen-observation.md) matched eight
`CdRead` returns with eight `CdReadSync` returns on the first screen path. Retail
file reads are asynchronous with a later sync point. The host helper reads bytes
from `build/disc/` in one synchronous call.

## Host API

| Piece | Path |
| --- | --- |
| Bounded binary read | `components/platform/disc_data_file_read.hpp` |
| ALP1.TXT probe consumer | `run_prototype_task_8_mission_slice` sets `alp1_txt_header` |

`read_disc_data_file(path, max_bytes, out_buffer)` returns `DiscDataFileReadResult`
with `ok`, `bytes_read`, `truncated`, and `error`. Callers join `disc_root` with
`DATA/` names such as `MissionSliceDeclaration::kTxtPath`. The helper does not
canonicalize paths outside the disc tree.

The row 8 slice reads up to 256 bytes from `DATA/ALP1.TXT` when `disc_root` is
non-empty and sets `alp1_txt_header` when the first line contains `Alpine1`.

## Acceptance

| Check | Role |
| --- | --- |
| `ctest prototype_task_6` | Alias of `test_disc_data_file_read`: tiny file under `build/test_disc_data_file_read/`, truncation, missing file, invalid buffer |
| Owner `ALP1.TXT` | When present in the same test: name `DATA/ALP1.TXT`, non-zero size, first line contains `Alpine1`, truncated flag when probe cap is smaller than file |
| `ctest prototype_task_8` | Disc-free; `alp1_txt_header` stays false |
| `ctest prototype_task_8_retail` | Uses mission slice probe instead of ad-hoc text open |

## Honest limits

| Gap | Note |
| --- | --- |
| CdRead / CdReadSync | No async queue, no BIOS callbacks, no sector addressing |
| Path policy | Callers must keep paths under owner `disc_root` |
| Full ALP1.TXT parse | Header probe only; MAP, MDL, and mission ini loop stay later rows |
| Other disc opens | `load_alp1_pad_spawn_from_disc_root` and FRONT.TIM loads still use local ifstream until a later gap |

Rows 5 and 7 retail checkpoint tier: [prototype-task-5.md](prototype-task-5.md),
[prototype-task-7.md](prototype-task-7.md).