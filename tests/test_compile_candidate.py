# SPDX-License-Identifier: GPL-3.0-or-later

import importlib.util
import json
import subprocess
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

SPEC = importlib.util.spec_from_file_location(
    'am3d_compile', Path(__file__).resolve().parents[1] / 'tools/compile_candidate.py')
COMPILE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(COMPILE)


class CompileTests(unittest.TestCase):
    def test_failed_stage_invalidates_old_success_and_stops(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source = root / 'input.i'
            source.write_text('int f(void) { return 0; }')
            out = root / 'output'
            out.mkdir()
            for name in ('candidate.o', 'provenance.json', 'compiler.s', 'assembler.s',
                         'compiler.log', 'adapter.log', 'assembler.log'):
                (out / name).write_text('stale success')
            tool = root / 'tool'
            tool.write_text('synthetic tool')
            with patch.object(COMPILE.subprocess, 'run',
                              side_effect=subprocess.CalledProcessError(1, ['tool'])) as run:
                with self.assertRaises(subprocess.CalledProcessError):
                    COMPILE.compile_candidate(source, tool, tool, tool, '2.56', [], out)
                self.assertEqual(run.call_count, 1)
            self.assertFalse((out / 'provenance.json').exists())
            self.assertFalse((out / 'candidate.o').exists())
            self.assertTrue((out / 'compiler.log').exists(), 'current failing-stage log is retained')
            for name in ('compiler.s', 'assembler.s', 'adapter.log', 'assembler.log'):
                self.assertFalse((out / name).exists(), f'stale later-stage output remains: {name}')

    def test_input_and_tool_collisions_are_rejected_before_cleanup(self):
        for slot, name in ((0, 'provenance.json'), (1, 'compiler.log'),
                           (2, 'assembler.s'), (3, 'candidate.o')):
            with self.subTest(slot=slot), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                out = root / 'output'
                out.mkdir()
                source = root / 'input.i'
                source.write_text('int f(void) { return 0; }')
                tool = root / 'tool'
                tool.write_text('synthetic tool')
                collision = out / name
                collision.write_text('must preserve supplied input')
                marker = out / 'adapter.log'
                marker.write_text('cleanup must not start')
                inputs = [source, tool, tool, tool]
                inputs[slot] = collision
                with patch.object(COMPILE.subprocess, 'run') as run:
                    with self.assertRaisesRegex(ValueError, 'collides'):
                        COMPILE.compile_candidate(*inputs, '2.56', [], out)
                    run.assert_not_called()
                self.assertEqual(collision.read_text(), 'must preserve supplied input')
                self.assertEqual(marker.read_text(), 'cleanup must not start')

    def test_symlink_or_hardlink_to_supplied_tool_is_preserved(self):
        for link_kind in ('symlink', 'hardlink'):
            with self.subTest(link_kind=link_kind), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                out = root / 'output'
                out.mkdir()
                source = root / 'input.i'
                source.write_text('int f(void) { return 0; }')
                tool = root / 'tool'
                tool.write_text('synthetic tool')
                collision = out / 'compiler.log'
                try:
                    if link_kind == 'symlink':
                        collision.symlink_to(tool)
                    else:
                        collision.hardlink_to(tool)
                except OSError:
                    continue
                with patch.object(COMPILE.subprocess, 'run') as run:
                    with self.assertRaisesRegex(ValueError, 'collides'):
                        COMPILE.compile_candidate(source, tool, tool, tool, '2.56', [], out)
                    run.assert_not_called()
                self.assertTrue(collision.exists())
                self.assertEqual(tool.read_text(), 'synthetic tool')

    def test_success_records_input_and_output_hashes_with_spaces(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp) / 'path with spaces'
            root.mkdir()
            source = root / 'input.i'
            source.write_text('int f(void) { return 0; }')
            tool = root / 'tool.py'
            tool.write_text('# synthetic tool')
            out = root / 'output'

            def fake_run(command, **kwargs):
                if len(command) > 1 and command[-2] == '-o':
                    Path(command[-1]).write_bytes(b'synthetic output')
                else:
                    kwargs['stdout'].write(b'synthetic adapter output')

            with patch.object(COMPILE.subprocess, 'run', side_effect=fake_run):
                result = COMPILE.compile_candidate(source, tool, tool, tool, '2.56', ['-O2'], out)
            saved = json.loads((out / 'provenance.json').read_text())
            self.assertEqual(saved, result)
            self.assertEqual(saved['input_sha256']['source'], COMPILE.digest(source))
            self.assertEqual(saved['object_sha256'], COMPILE.digest(out / 'candidate.o'))
            self.assertEqual(saved['commands'][0][-3], str(source.resolve()))
            self.assertEqual(saved['compiler_flags'], ['-O2'])


if __name__ == '__main__':
    unittest.main()
