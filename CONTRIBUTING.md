# Contributing

Anyone can help. If you use an agent, open it in this repo and say:

Help me contribute. Follow AGENTS.md.

[AGENTS.md](AGENTS.md) is short enough to read yourself. The same steps work with no agent.

## Three ways in

| Kind | You need | You give |
| --- | --- | --- |
| Play and report | a launcher build, once one exists, and a disc you own | what you did, and what the USA disc does |
| Trace a claim | the disc you own, and Ghidra if you want to read the executable | one claim about the retail executable, with the address that supports it |
| Fix or port one gap | this tree | one gap closed, with a research note when the behavior comes from the disc |

## Our side

We ask for those three kinds of work.

We ask you to use a disc you own. We never ask you to upload the disc, the executable, extracted assets, the Ghidra project, or decompiled C.

AGENTS.md and this page are the instructions we give an agent. The agent asks before every issue, pull request, or push.

## Your side

The USA release, serial SLUS-00491, is the behavior reference. A claim cites an address. Someone else should be able to re-check that address on a disc they own.

One gap per change. In our code a gap is marked `// gap:`.

Read what an agent wrote before you send it. Your name is on the change.

## How we check

Run `python tools/pr_guard.py` before you send a change. It fails the tree if a cue, bin, iso, PS-X EXE, Ghidra project, or decompiled C is present.

Do not weaken `pr_guard`.

## License

Our code is GPL-3.0-or-later. See [LICENSE](LICENSE) and [LEGAL.md](LEGAL.md).
