#include "save.h"
#include <stdio.h>

static const char *slot_name(int slot) {
    static char buf[32];
    snprintf(buf, sizeof(buf), "save_slot_%d.bin", slot);
    return buf;
}

void save_init(void) {}

bool save_write(int slot, const void *data, size_t size) {
    if (slot < 0 || slot >= SAVE_SLOTS) return false;
    FILE *f = fopen(slot_name(slot), "wb");
    if (!f) return false;
    fwrite(data, size, 1, f);
    fclose(f);
    return true;
}

bool save_read(int slot, void *out, size_t size) {
    if (slot < 0 || slot >= SAVE_SLOTS) return false;
    FILE *f = fopen(slot_name(slot), "rb");
    if (!f) return false;
    fread(out, size, 1, f);
    fclose(f);
    return true;
}

bool save_exists(int slot) {
    FILE *f = fopen(slot_name(slot), "rb");
    if (!f) return false;
    fclose(f);
    return true;
}
