#!/usr/bin/env python3
"""Check ROM slice metadata without requiring a copyrighted ROM in CI."""

import json
import re
import subprocess
import sys
from pathlib import Path


root = Path(__file__).resolve().parents[1]
rom_size = 8 * 1024 * 1024
anim_files = sorted((root / "assets/anims").glob("*.inc.c"))
slices = re.findall(
    r"ROM_ASSET_LOAD_ANIM\((\w+),\s*(0x[0-9a-fA-F]+),\s*(\d+),\s*(0x[0-9a-fA-F]+),\s*(\d+)\);",
    "\n".join(path.read_text() for path in anim_files),
)
assert len(anim_files) == 193 and len(slices) == 386
assert len({name for name, *_ in slices}) == len(slices)
for name, address, size, segmented_address, segmented_size in slices:
    offset, length = int(address, 16), int(size)
    assert int(segmented_address, 16) == 0 and length == int(segmented_size)
    assert length > 0 and length % 2 == 0 and offset + length <= rom_size, name

assets = json.loads((root / "assets.json").read_text())
for name in ("bbh", "ccm", "hmc", "jrb", "wf", "pss", "unused", "bitdw"):
    size, versions = assets[f"assets/demos/{name}.bin"]
    assert size > 0 and versions["us"][0] + size <= rom_size, name

for script, args, symbol in (
    ("mario_anims_converter.py", [], "mario_anims_load"),
    ("demo_data_converter.py", ["assets/demo_data.json", "-D", "VERSION_US"], "demo_inputs_load"),
):
    output = subprocess.check_output([sys.executable, f"tools/{script}", *args], cwd=root, text=True)
    assert f"int {symbol}(const char *path)" in output

print("386 Mario animation and 8 demo ROM slices valid")
