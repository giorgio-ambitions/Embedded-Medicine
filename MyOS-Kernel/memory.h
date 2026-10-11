#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MB2_BOOTLOADER_MAGIC 0x36d76289u
#define MEM_MAX_REGIONS      32

#define MEM_AVAILABLE        1   /* usable RAM; other types are reserved, ACPI, etc. */

struct mem_region {
    uint64_t base;
    uint64_t length;
    uint32_t type;
};

/*
 * Parse the Multiboot2 boot information that GRUB passes at boot.
 * magic    : value GRUB leaves in EAX (must be MB2_BOOTLOADER_MAGIC)
 * mbi_addr : physical address GRUB leaves in EBX
 * Returns 0 on success, -1 if the magic or structure is invalid.
 */
int memory_unit(uint32_t magic, uint64_t mbi_addr);

int memory_region_count(void);
const struct mem_region *memory_region(int index);
uint64_t memory_total_available(void);

#endif
