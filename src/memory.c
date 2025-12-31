#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "memory.h"

void memory_init(Memory *m) {
  memset(m->memory, 0, sizeof(m->memory));
  memcpy(&m->memory[FONTSET_ADDR], chip8_fontset, sizeof(chip8_fontset));
}

uint8_t memory_read(const Memory *m, uint16_t addr) {
  if (addr >= MEM_SIZE)
    return 0;
  return m->memory[addr];
}

void memory_write(Memory *m, uint16_t addr, uint8_t val) {
  if (addr >= MEM_SIZE)
    return;
  m->memory[addr] = val;
}

int memory_load_rom(Memory *m, const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return -ENOENT;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return -EIO;
    }

    long size = ftell(file);
    if (size < 1) {
        fclose(file);
        return -EINVAL;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return -EIO;
    }

    if (START_ADDR + size > MEM_SIZE) {
        fclose(file);
        return -ENOMEM;
    }

    size_t read = fread(&m->memory[START_ADDR], 1, (size_t)size, file);
    fclose(file);

    if (read != (size_t)size) {
        return -EIO;
    }

    return 0;
}
