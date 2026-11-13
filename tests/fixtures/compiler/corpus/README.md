# Synthetic compiler corpus

These six files are original C examples. They retain the `.i` names and
comments used in the failed R05 preparation trial so their recorded hashes
and failure evidence remain reproducible. They are not valid prepared
inputs for the documented old-compiler pipeline.

Do not pass them to cc1 again under R05. That batch stopped after three
failures. See [the reviewed result](../../../../docs/workers/results/compiler-corpus.md).
Modern host semantic checks use them as ordinary C with `-x c`.

A separately assigned future trial must preprocess original C into new,
distinct comment-free `.i` outputs. Preserve both hashes and the explicit
preprocessor command. Keep semantics and license text in a sidecar note
when preparing those outputs. No old compiler has tested that correction.
