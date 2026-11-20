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
