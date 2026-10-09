.code32

.section .multiboot
.align 8

multiboot_header:
    .long 0xE85250D6
    .long 0
    .long multiboot_header_end - multiboot_header
    .long -(0xE85250D6 + 0 + (multiboot_header_end - multiboot_header))

    /* Multiboot2 end tag */
    .short 0
    .short 0
    .long 8

multiboot_header_end:


/*
 * ============================================================================
 * 32-bit bootstrap
 * ============================================================================
 */

.section .text
.global _start
.type _start, @function

_start:
    cli
    cld

    /*
     * Multiboot gives:
     *
     *   EAX = Multiboot2 magic
     *   EBX = address of Multiboot2 information structure
     *
     * Preserve EBX because kernel_main() will eventually need it.
     */
    mov %ebx, %esi

    /*
     * Temporary stack.
     */
    mov $stack_top, %esp

    /*
     * Load bootstrap GDT.
     */
    lgdt gdt_descriptor

    /*
     * Load data segments.
     */
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss

    /*
     * Verify that long mode exists.
     */
    call check_long_mode
    test %eax, %eax
    jz no_long_mode

    /*
     * Enable PAE.
     */
    mov %cr4, %eax
    or $0x20, %eax
    mov %eax, %cr4

    /*
     * Build identity-mapped page tables.
     */
    call setup_page_tables

    /*
     * Load PML4.
     */
    mov $page_table_l4, %eax
    mov %eax, %cr3

    /*
     * Enable Long Mode in EFER.
     */
    mov $0xC0000080, %ecx
    rdmsr

    or $0x100, %eax
    wrmsr

    /*
     * Enable paging + protected mode.
     */
    mov %cr0, %eax
    or $0x80000001, %eax
    mov %eax, %cr0

    /*
     * Enter 64-bit code segment.
     */
    ljmp $0x08, $long_mode_entry


no_long_mode:
1:
    cli
    hlt
    jmp 1b


/*
 * ============================================================================
 * CPU detection
 * ============================================================================
 */

check_long_mode:

    /*
     * Check CPUID availability.
     *
     * Toggle ID bit in EFLAGS.
     */

    pushfl
    pop %eax

    mov %eax, %ecx

    xor $0x200000, %eax

    push %eax
    popfl

    pushfl
    pop %eax

    xor %ecx, %eax
    and $0x200000, %eax

    jz .no_cpuid

    /*
     * Check extended CPUID functions.
     */
    mov $0x80000000, %eax
    cpuid

    cmp $0x80000001, %eax
    jb .no_long_mode

    /*
     * Check Long Mode bit.
     */
    mov $0x80000001, %eax
    cpuid

    test $0x20000000, %edx
    jz .no_long_mode

    mov $1, %eax
    ret


.no_cpuid:
.no_long_mode:
    xor %eax, %eax
    ret


/*
 * ============================================================================
 * Page tables
 * ============================================================================
 *
 * Identity-map the first 1 GiB using 2 MiB pages.
 */

setup_page_tables:

    /*
     * Clear PML4, PDPT and page directory.
     */

    mov $page_table_l4, %edi
    xor %eax, %eax
    mov $(4096 * 3 / 4), %ecx
    rep stosl

    /*
     * PML4[0] -> PDPT
     *
     * Present | Writable
     */
    mov $page_table_l3, %eax
    or $0x003, %eax
    mov %eax, page_table_l4

    /*
     * PDPT[0] -> PD
     */
    mov $page_table_l2, %eax
    or $0x003, %eax
    mov %eax, page_table_l3

    /*
     * Fill 512 PDEs.
     *
     * Each PDE maps 2 MiB.
     */

    mov $page_table_l2, %edi
    mov $0x00000083, %eax

    mov $512, %ecx

1:
    mov %eax, (%edi)

    add $0x200000, %eax
    add $8, %edi

    loop 1b

    ret


/*
 * ============================================================================
 * 64-bit entry
 * ============================================================================
 */

.code64

long_mode_entry:

    cli
    cld

    /*
     * Reload data segments.
     */
    xor %eax, %eax

    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov %ax, %fs
    mov %ax, %gs

    /*
     * 64-bit stack.
     */
    lea stack_top(%rip), %rsp

    /*
     * Align stack according to the x86-64 ABI.
     */
    and $-16, %rsp

    /*
     * Preserve Multiboot information pointer.
     *
     * We originally copied EBX -> ESI in 32-bit mode.
     * RSI is therefore still available here.
     *
     * First argument to kernel_main():
     *
     *     RDI = Multiboot information pointer
     */
    mov %rsi, %rdi

    /*
     * Call C kernel.
     */
    call kernel_main

1:
    cli
    hlt
    jmp 1b


/*
 * ============================================================================
 * GDT
 * ============================================================================
 */

.section .data

.align 8

gdt:

    /*
     * Null descriptor
     */
    .quad 0x0000000000000000

    /*
     * 64-bit kernel code
     */
    .quad 0x00AF9A000000FFFF

    /*
     * Kernel data
     */
    .quad 0x00CF92000000FFFF

gdt_end:

gdt_descriptor:
    .word gdt_end - gdt - 1
    .long gdt


/*
 * ============================================================================
 * Page tables
 * ============================================================================
 */

.section .pgtable
.align 4096

page_table_l4:
    .skip 4096

page_table_l3:
    .skip 4096

page_table_l2:
    .skip 4096


/*
 * ============================================================================
 * Stack
 * ============================================================================
 */

.section .bss
.align 16

stack_bottom:
    .skip 16384

stack_top:
