#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# Start a portable PCSX-Redux session for ALP1 movement observation.
# Run from anywhere; the script cds to the repository root.
# Does not commit game files. Output stays under build/coordination/.

set -e

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname "$0")" && pwd)
REPO_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/../.." && pwd)

CUE="${AM3D_DISC:-${1:-}}"
if [ -z "$CUE" ]; then
    echo "run_alp1_observation.sh: set AM3D_DISC or pass the cue path as the first argument." >&2
    exit 1
fi
if [ ! -f "$CUE" ]; then
    echo "run_alp1_observation.sh: cue not found: $CUE" >&2
    exit 1
fi

PCSX="/Applications/PCSX-Redux.app/Contents/MacOS/PCSX-Redux"
if [ ! -x "$PCSX" ]; then
    echo "run_alp1_observation.sh: PCSX-Redux not found at $PCSX" >&2
    echo "Install from tools/pcsx/README.md (macOS dev channel DMG, copy to /Applications)." >&2
    exit 2
fi

RUN_ID=$(date -u +%Y%m%d-%H%M%S)
RUN_DIR="$REPO_ROOT/build/coordination/alp1-movement-observation/$RUN_ID"
mkdir -p "$RUN_DIR/frames" "$RUN_DIR/pcsx-config"

COMMIT=$(CDPATH= cd -- "$REPO_ROOT" && git rev-parse --short HEAD 2>/dev/null || echo "unknown")
UNAME_LINE=$(uname -a 2>/dev/null || uname)
PCSX_VERSION=$("$PCSX" -version 2>/dev/null | python3 -c "
import json, sys
try:
    data = json.load(sys.stdin)
    print(data.get('version', 'unknown'), data.get('changeset', '')[:12])
except Exception:
    print('unknown')
" 2>/dev/null || echo "unknown")

SESSION="$RUN_DIR/session.txt"
{
    echo "run_id: $RUN_ID"
    echo "repo_commit: $COMMIT"
    echo "uname: $UNAME_LINE"
    echo "disc_cue: $CUE"
    echo "emulator_path: $PCSX"
    echo "emulator_version: $PCSX_VERSION"
    echo "disc_serial: SLUS-00491"
    echo "log_disc_id:"
    echo "log_bios_label:"
    echo "memory_card_slots:"
    echo "memory_card_blank:"
    echo "pad_settings:"
    echo "frame_stable_in_mission:"
    echo "frame_idle_hold_start:"
    echo "frame_cross_down:"
    echo "frame_cross_up:"
    echo "position_readout:"
    echo "file_reads:"
    echo "# checklist placeholders (also in checklist.tsv)"
    echo "checklist_run_id: $RUN_ID"
    echo "checklist_date:"
    echo "checklist_reach_alp1:"
    echo "checklist_spawn_sanity:"
    echo "checklist_after_sequence_notes:"
    echo "checklist_capture_paths:"
} >"$SESSION"

cd "$REPO_ROOT"
python3 "$REPO_ROOT/tools/alp1_observation_checklist.py" init "$RUN_DIR"

export PCSX_ALP1_OUT="$RUN_DIR/frames"

echo "run_alp1_observation.sh: run directory $RUN_DIR"
echo "run_alp1_observation.sh: frames -> PCSX_ALP1_OUT=$PCSX_ALP1_OUT"
echo "run_alp1_observation.sh: fill session.txt and checklist.tsv after the session."

exec "$PCSX" \
    -portable "$RUN_DIR/pcsx-config" \
    -interpreter -debugger -run -iso "$CUE" \
    -exec "dofile('tools/pcsx/alp1_movement_observation.lua')"