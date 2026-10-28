#include "paging.h"
asmlinkage __visible void *extract_kernel(void *rmode, unsigned char *output)
{
    unsigned long virt_addr = LOAD_PHYSICAL_ADDR;
    memptr heap = (memptr)boot_heap;
    unsigned long needed_size;
    size_t entry_offset;

    /* Retain x86 boot parameters pointer passed from startup_32/64. */
    boot_params_ptr = rmode;

    /* Clear flags intended for solely in-kernel use. */
    boot_params_ptr->hdr.loadflags &= ~KASLR_FLAG;

    parse_mem_encrypt(&boot_params_ptr->hdr);
    sanitize_boot_params(boot_params_ptr);

    // ... [video setup code remains unchanged] ...

    init_default_io_ops();
    early_tdx_detect();
    early_sev_detect();

    /* ========================================== */
    /* INTEGRATE YOUR PAGING CHECK HERE           */
    /* ========================================== */
    if (paging_init() != 0) {
        error("Unsupported paging mode detected at early boot");
    }

    if (paging_cpu_supports_la57()) {
        debug_putstr("CPU supports 5-level paging (LA57)\n");
    } else {
        debug_putstr("CPU restricted to 4-level paging\n");
    }
    /* ========================================== */

    console_init();
    boot_params_ptr->acpi_rsdp_addr = get_rsdp_addr();
    
    // ... [rest of extract_kernel continues normally] ...
