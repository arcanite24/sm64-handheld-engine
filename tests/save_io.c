#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <PR/os_eeprom.h>
#include "pc/fs/fs.h"

static char save_path[SYS_MAX_PATH];

const char *fs_get_write_path(const char *name) {
    (void) name;
    return save_path;
}

fs_file_t *fs_open(const char *name) { (void) name; abort(); }
int64_t fs_read(fs_file_t *file, void *buf, const uint64_t size) {
    (void) file; (void) buf; (void) size; abort();
}
void fs_close(fs_file_t *file) { (void) file; abort(); }

int main(void) {
    char directory[SYS_MAX_PATH];
    const char *temp_root = getenv("TMPDIR");
    if (!temp_root) temp_root = "/tmp";
    assert(snprintf(directory, sizeof(directory), "%s/sm64-save-XXXXXX", temp_root) < (int) sizeof(directory));
    assert(mkdtemp(directory));
    assert(snprintf(save_path, sizeof(save_path), "%s/save.bin", directory) < (int) sizeof(save_path));
    unsigned char data[512];
    memset(data, 0x42, sizeof(data));
    assert(osEepromLongWrite(NULL, 0, data, sizeof(data)) == 0);

    char temp[SYS_MAX_PATH];
    assert(snprintf(temp, sizeof(temp), "%s.tmp", save_path) < (int) sizeof(temp));
    assert(mkdir(temp, 0700) == 0);
    memset(data, 0x43, sizeof(data));
    assert(osEepromLongWrite(NULL, 0, data, sizeof(data)) != 0);
    FILE *file = fopen(save_path, "rb");
    assert(file);
    for (size_t i = 0; i < sizeof(data); i++) assert(fgetc(file) == 0x42);
    assert(fgetc(file) == EOF);
    assert(fclose(file) == 0);

    assert(rmdir(temp) == 0);
    assert(osEepromLongWrite(NULL, 0, data, sizeof(data)) == 0);
    file = fopen(save_path, "rb");
    assert(file);
    for (size_t i = 0; i < sizeof(data); i++) assert(fgetc(file) == 0x43);
    assert(fgetc(file) == EOF);
    assert(fclose(file) == 0);
    assert(access(temp, F_OK) != 0);
    assert(unlink(save_path) == 0);
    assert(rmdir(directory) == 0);
}
