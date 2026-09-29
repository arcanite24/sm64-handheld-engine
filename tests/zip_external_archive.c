#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/pc/fs/fs.h"

extern fs_packtype_t fs_packtype_zip;

char *sys_strdup(const char *source) {
    size_t size = strlen(source) + 1;
    char *copy = malloc(size);
    assert(copy != NULL);
    memcpy(copy, source, size);
    return copy;
}

int main(int argc, char **argv) {
    assert(argc == 2);
    void *archive = fs_packtype_zip.mount(argv[1]);
    assert(archive != NULL);
    const char *paths[] = {
        "gfx/textures/skybox_tiles/bits.22.rgba16.png",
        "sound/sequences.bin.le.64",
        "sound/bank_sets.le.64",
        "sound/sound_data.ctl.le.64",
        "sound/sound_data.tbl.le.64",
    };
    for (size_t i = 0; i < sizeof(paths) / sizeof(paths[0]); i++) {
        assert(fs_packtype_zip.is_file(archive, paths[i]));
        fs_file_t *file = fs_packtype_zip.open(archive, paths[i]);
        assert(file != NULL);
        int64_t size = fs_packtype_zip.size(archive, file);
        assert(size > 16);
        uint8_t first[16], again[16];
        assert(fs_packtype_zip.read(archive, file, first, sizeof(first)) == sizeof(first));
        uint8_t chunk[4096];
        int64_t total = sizeof(first);
        while (total < size) {
            uint64_t wanted = (uint64_t)(size - total);
            if (wanted > sizeof(chunk)) wanted = sizeof(chunk);
            assert(fs_packtype_zip.read(archive, file, chunk, wanted) == (int64_t)wanted);
            total += wanted;
        }
        assert(fs_packtype_zip.eof(archive, file));
        assert(fs_packtype_zip.seek(archive, file, 0));
        assert(fs_packtype_zip.read(archive, file, again, sizeof(again)) == sizeof(again));
        assert(memcmp(first, again, sizeof(first)) == 0);
        if (i == 0) assert(memcmp(first, "\x89PNG\r\n\x1a\n", 8) == 0);
        fs_packtype_zip.close(archive, file);
    }
    fs_packtype_zip.unmount(archive);
    puts("Native ZIP reader opened generated textures and sound");
    return 0;
}
