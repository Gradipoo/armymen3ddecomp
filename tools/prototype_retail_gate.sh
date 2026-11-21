#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# Local owner-disc prototype gate. Output stays under build/.
# Run from anywhere; cds to repository root.

set -e

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname "$0")" && pwd)
REPO_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
cd "$REPO_ROOT"

if [ ! -d build/disc/DATA ]; then
    echo "prototype_retail_gate.sh: missing build/disc/DATA; run: python3 tools/disc.py" >&2
    exit 1
fi

echo "prototype_retail_gate.sh: pr_guard"
python3 tools/pr_guard.py

echo "prototype_retail_gate.sh: disc-free prototype ctests"
ctest --test-dir build --output-on-failure \
    -R '^(prototype_task_|prototype_playable_smoke_headless|test_disc_data_file_read|front_tim)$'

echo "prototype_retail_gate.sh: owner *_retail ctests (ctest cwd build/, paths disc/DATA/)"
ctest --test-dir build --output-on-failure -R '_retail'

if [ -x build/am3d_prototype_playable_smoke ]; then
    echo "prototype_retail_gate.sh: SDL capture + checkpoint (dummy video)"
    export SDL_VIDEODRIVER=dummy
    build/am3d_prototype_playable_smoke --hidden --capture --checkpoint
    echo "prototype_retail_gate.sh: task9 checkpoint:"
    cat build/platform/task9-checkpoint.txt
fi

echo "prototype_retail_gate.sh: ok"