## Build MyPersonalOS

Run these commands from the project root directory.

### 1. Create the required directories

```bash
mkdir -p Esecutables iso/boot/grub
```

### 2. Compile the kernel

```bash
gcc -ffreestanding -fno-stack-protector -fno-pie -c kernel.c -o Esecutables/kernel.o
```

### 3. Compile the CPU module

```bash
gcc -ffreestanding -fno-stack-protector -fno-pie -c cpu.c -o Esecutables/cpu.o
```

### 4. Compile the assembly boot file

The source file is named `Boot/head.s` (lowercase `s`).

```bash
gcc -c Boot/head.s -o Esecutables/head.o
```

### 5. Link the kernel

```bash
ld --no-warn-rwx-segments -T linker.ld \
  -o Esecutables/kernel.elf \
  Esecutables/head.o Esecutables/kernel.o Esecutables/cpu.o
```

### 6. Check Multiboot2 compatibility

```bash
grub-file --is-x86-multiboot2 Esecutables/kernel.elf
echo $?
```

An exit status of `0` means the check passed. Stop if it reports an error.

### 7. Create the GRUB configuration

Ensure `iso/boot/grub/grub.cfg` contains:

```grub
cat > iso/boot/grub/grub.cfg <<'EOF'
set timeout=0
set default=0

menuentry "MyPersonalOS" {
    multiboot2 /boot/kernel.elf
    boot
}
EOF
```

### 8. Copy the kernel into the ISO directory

```bash
cp Esecutables/kernel.elf iso/boot/kernel.elf
```

### 9. Create the ISO image

```bash
grub-mkrescue -o Esecutables/MyPersonalOS.iso iso
```

### 10. Verify the ISO file

```bash
ls -lh Esecutables/MyPersonalOS.iso
```

The ISO should be created at `Esecutables/MyPersonalOS.iso`.

### 11. Optional: Test with QEMU

```bash
qemu-system-x86_64 -cdrom Esecutables/MyPersonalOS.iso
```

A successful ISO build does not guarantee that the kernel boots correctly, so test it in an emulator before considering the build complete.## Build MyPersonalOS

Run these commands from the project root directory.

### 1. Create the required directories

```bash
mkdir -p Esecutables iso/boot/grub
```

### 2. Compile the kernel

```bash
gcc -c kernel.c -o Esecutables/kernel.o
```

### 3. Compile the assembly boot file

The source file is named `Boot/head.s` (lowercase `s`).

```bash
gcc -c Boot/head.s -o Esecutables/head.o
```

### 4. Link the kernel

```bash
ld --no-warn-rwx-segments -T linker.ld \
  -o Esecutables/kernel.elf \
  Esecutables/head.o Esecutables/kernel.o
```

### 5. Check Multiboot2 compatibility

```bash
grub-file --is-x86-multiboot2 Esecutables/kernel.elf
```

Stop if this command reports an error. To verify the result explicitly:

```bash
grub-file --is-x86-multiboot2 Esecutables/kernel.elf
echo $?
```

An exit status of `0` means the check passed.

### 6. Create the GRUB configuration

Ensure `iso/boot/grub/grub.cfg` contains:

```grub
set timeout=0
set default=0

menuentry "MyPersonalOS" {
    multiboot2 /boot/kernel.elf
    boot
}
```

### 7. Copy the kernel into the ISO directory

```bash
cp Esecutables/kernel.elf iso/boot/kernel.elf
```

### 8. Create the ISO image

```bash
grub-mkrescue -o Esecutables/MyPersonalOS.iso iso
```

### 9. Verify the ISO file

```bash
ls -lh Esecutables/MyPersonalOS.iso
```

The ISO should be created at `Esecutables/MyPersonalOS.iso`.

### 10. Optional: Test with QEMU

If QEMU is installed, run:

```bash
qemu-system-i386 -cdrom Esecutables/MyPersonalOS.iso
```

A successful ISO build does not guarantee that the kernel boots correctly, so test it in an emulator before considering the build complete.
