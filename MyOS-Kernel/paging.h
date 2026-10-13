#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

int paging_init(void);
uint64_t paging_read_cr3(void);
uint64_t paging_read_cr4(void);
int paging_cpu_supports_la57(void);

#endif
