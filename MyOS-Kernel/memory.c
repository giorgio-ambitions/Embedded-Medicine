#include "memory.h"

#define MB2_TAG_END  0
#define MB2_TAG_MMAP 6

struct mb2_tag {
    uint32_t type;
    uint32_t size;
};

struct mb2_mmap_tag {
    uint32_t type;
    uint32_t size;
    uint32_t entry_size;
    uint32_t entry_version;
};

struct mb2_mmap_entry {
    uint64_t addr;
    uint64_t len;
    uint32_t type;
    uint32_t reserved;
};

static struct mem_region regions[MEM_MAX_REGIONS];
static int region_count;

int memory_init(uint32_t magic, uint64_t mbi_addr)
{
    region_count = 0;

    if (magic != MB2_BOOTLOADER_MAGIC || mbi_addr == 0 || (mbi_addr & 7))
        return -1;

    /* Header: u32 total_size, u32 reserved, then tags aligned to 8 bytes. */
    uint32_t total = *(const volatile uint32_t *)mbi_addr;
    uint64_t addr  = mbi_addr + 8;
    uint64_t end   = mbi_addr + total;

    while (addr + sizeof(struct mb2_tag) <= end) {
        const struct mb2_tag *tag = (const struct mb2_tag *)addr;

        if (tag->type == MB2_TAG_END)
            break;
        if (tag->size < sizeof(struct mb2_tag) || addr + tag->size > end)
            return -1;

        if (tag->type == MB2_TAG_MMAP) {
            const struct mb2_mmap_tag *mm = (const struct mb2_mmap_tag *)addr;
            uint64_t entry = addr + sizeof(struct mb2_mmap_tag);
            uint64_t tag_end = addr + mm->size;

            if (mm->entry_size < sizeof(struct mb2_mmap_entry))
                return -1;

            while (entry + mm->entry_size <= tag_end && region_count < MEM_MAX_REGIONS) {
                const struct mb2_mmap_entry *e = (const struct mb2_mmap_entry *)entry;

                /* Copy field by field: avoids a hidden memcpy call in a freestanding build. */
                regions[region_count].base   = e->addr;
                regions[region_count].length = e->len;
                regions[region_count].type   = e->type;
                region_count++;

                entry += mm->entry_size;
            }
        }

        addr += ((uint64_t)tag->size + 7) & ~7ULL;   /* tags are 8-byte aligned */
    }

    return region_count ? 0 : -1;
}

int memory_region_count(void)
{
    return region_count;
}

const struct mem_region *memory_region(int index)
{
    if (index < 0 || index >= region_count)
        return 0;
    return &regions[index];
}

uint64_t memory_total_available(void)
{
    uint64_t total = 0;
    for (int i = 0; i < region_count; i++)
        if (regions[i].type == MEM_AVAILABLE)
            total += regions[i].length;
    return total;
}
