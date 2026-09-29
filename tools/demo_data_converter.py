#!/usr/bin/env python3
import sys
import re
import json

def main():
    need_help = False
    defines = []
    skip_next = 0
    prog_args = []
    for i, a in enumerate(sys.argv[1:], 1):
        if skip_next > 0:
            skip_next -= 1
            continue
        if a == "--help" or a == "-h":
            need_help = True
        if a == "-D":
            defines.append(sys.argv[i + 1])
            skip_next = 1
        elif a.startswith("-D"):
            defines.append(a[2:])
        else:
            prog_args.append(a)

    defines = [d.split("=")[0] for d in defines]
    
    if len(prog_args) < 1 or need_help:
        print("Usage: {} <demo_data.json> [-D <symbol>] > <demo_data.c>".format(sys.argv[0]))
        sys.exit(0 if need_help else 1)

    with open(prog_args[0], "r") as file:
        descr = json.loads(re.sub(r"/\*[\w\W]*?\*/", "", file.read()))

    table = []
    for item in descr["table"]:
        if not "ifdef" in item or any(d in defines for d in item["ifdef"]):
            table.append(item)

    demofiles = []
    for item in descr["demofiles"]:
        if not "ifdef" in item or any(d in defines for d in item["ifdef"]):
            demofiles.append(item)

    if "VERSION_US" not in defines:
        raise ValueError("Runtime demo inputs currently support only the US ROM")
    with open("assets.json", "r") as file:
        assets = json.load(file)

    structdef = ["u32 numEntries;",
                 "const void *addrPlaceholder;",
                 "struct OffsetSizePair entries[" + str(len(table)) + "];"]
    structobj = [str(len(table)) + ",",
                 "NULL,"]

    structobj.append("{")
    for item in table:
        offset_to_data = "offsetof(struct DemoInputsObj, " + item["demofile"] + ")"
        size = "sizeof(gDemoInputs." + item["demofile"] + ")"
        if "extraSize" in item:
            size += " + " + str(item["extraSize"])
        structobj.append("{" + offset_to_data + ", " + size + "},")
    structobj.append("},")

    slices = []
    for item in demofiles:
        name = item["name"]
        size, versions = assets["assets/demos/" + name + ".bin"]
        offset = versions["us"][0]
        structdef.append("u8 " + name + "[" + str(size) + "];")
        structobj.append("{0},")
        slices.append((name, offset, size))

    print("#include \"types.h\"")
    print("#include <stddef.h>")
    print("#include <stdio.h>")
    print("")

    print("struct DemoInputsObj {")
    for s in structdef:
        print(s)
    print("} gDemoInputs = {")
    for s in structobj:
        print(s)
    print("};")
    print("int demo_inputs_load(const char *path) {")
    print("    FILE *rom = fopen(path, \"rb\");")
    print("    if (!rom) return -1;")
    for name, offset, size in slices:
        print("    if (fseek(rom, %d, SEEK_SET) != 0 || fread(gDemoInputs.%s, 1, %d, rom) != %d) { fclose(rom); return -1; }" % (offset, name, size, size))
    print("    return fclose(rom) == 0 ? 0 : -1;")
    print("}")

if __name__ == "__main__":
    main()
