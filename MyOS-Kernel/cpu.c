#include "cpu.h"

void cpu_get_vendor(char vendor[13])
{
    unsigned int eax, ebx, ecx, edx;

    __asm__ volatile (
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(0)
    );

    /* CPUID returns the vendor in EBX, EDX, ECX order. */
    vendor[0]  = (char)(ebx);
    vendor[1]  = (char)(ebx >> 8);
    vendor[2]  = (char)(ebx >> 16);
    vendor[3]  = (char)(ebx >> 24);

    vendor[4]  = (char)(edx);
    vendor[5]  = (char)(edx >> 8);
    vendor[6]  = (char)(edx >> 16);
    vendor[7]  = (char)(edx >> 24);

    vendor[8]  = (char)(ecx);
    vendor[9]  = (char)(ecx >> 8);
    vendor[10] = (char)(ecx >> 16);
    vendor[11] = (char)(ecx >> 24);

    vendor[12] = '\0';
}
