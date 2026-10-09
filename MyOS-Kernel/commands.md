## Build MyPersonalOS

Run these commands from the project directory.

**1. Compile the kernel**
```bash
gcc -c kernel.c -o Esecutables/kernel.o
```

**2. Compile the assembly boot file**
```bash
gcc -c Boot/head.S -o Esecutables/head.o
```

**3. Link the kernel**
```bash
ld -n -T linker.ld -o Esecutables/kernel.elf Esecutables/head.o Esecutables/kernel.o
```

**4. Check Multiboot2 compatibility**
```bash
grub-file --is-x86-multiboot2 Esecutables/kernel.elf
```

**5. Copy the kernel into the ISO directory**
```bash
cp Esecutables/kernel.elf iso/boot/kernel.elf
```

**6. Create the ISO image**
```bash
grub-mkrescue -o Esecutables/MyPersonalOS.iso iso
```

**7. Check the ISO file**
```bash
ls -lh Esecutables/MyPersonalOS.iso
```
