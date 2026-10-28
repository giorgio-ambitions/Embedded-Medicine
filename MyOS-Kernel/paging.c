#include "paging.h"

#define CR4_LA57 (1ULL << 12)

uint64_t paging_read_cr3(void)
{
    uint64_t value;

    __asm__ volatile (
        "mov %%cr3, %0"
        : "=r"(value)
    );

    return value;
}

uint64_t paging_read_cr4(void)
{
    uint64_t value;

    __asm__ volatile (
        "mov %%cr4, %0"
        : "=r"(value)
    );

    return value;
}

static void cpuid(
    uint32_t leaf,
    uint32_t subleaf,
    uint32_t *a,
    uint32_t *b,
    uint32_t *c,
    uint32_t *d)
{
    __asm__ volatile (
        "cpuid"
        : "=a"(*a), "=b"(*b),
          "=c"(*c), "=d"(*d)
        : "a"(leaf), "c"(subleaf)
    );
}

int paging_cpu_supports_la57(void)
{
    uint32_t a, b, c, d;

    cpuid(0, 0, &a, &b, &c, &d);

    if (a < 7)
        return 0;

    cpuid(7, 0, &a, &b, &c, &d);

    return (c & (1U << 16)) != 0;
}

int paging_init(void)
{
    /*
     * The boot assembly already established four-level paging.
     * Verify that five-level paging is not active.
     */
    if (paging_read_cr4() & CR4_LA57)
        return -1;

    /*
     * Keep the current paging mode for now.
     * Do not change CR4.LA57 here.
     */
    return 0;
}
