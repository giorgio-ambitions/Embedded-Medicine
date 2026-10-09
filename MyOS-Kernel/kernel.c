void kernel_main(void)
{
    volatile unsigned char *video = (volatile unsigned char *)0xB8000;

    const char *message = "MyPersonalOS booted!";

    for (int i = 0; message[i] != '\0'; i++) {
        video[i * 2]     = message[i];
        video[i * 2 + 1] = 0x07;
    }

    for (;;) {
        __asm__ volatile ("hlt");
    }
}
