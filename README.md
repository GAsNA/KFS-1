# KFS-1

Discover the world of "Kernel Programming" and learn how to create your very own Kernel from scratch.

**Available options**:
- Color support
- Keyboard handler (no numlock + exception)
- Helper 'printk'
- Create Iso image from kernel binary

**Missing options**:
- Keyboard handler for numlock and exception
- Scroll and cursor support
- Different screens helper and keyboard shortcut

## KERNEL

### Compilation

#### Simple way

```
make
```

#### Hard way

```
$ nasm -f elf32 boot.asm -o boot.o
$ gcc -m32 -c kernel.c -o kernel.o
$ ld -m elf_i386 -T link.ld -o [your kernel name] boot.o kernel.o
```

<i>It is recommended to name your kernel with the formal</i>: ``kernel-<version>``. <i>I named mine "kernel-kfs.1.rleseur".</i>

### Run on QEMU

#### Simple way

```
make run-kernel
```

#### Hard way

```
qemu-system-i386 -kernel [your compiled kernel]
```

### Installation

- Take the last Debian ISO and make a VM in virtualbox.

- Clone the repo in it.

- Copy the compiled kernel in ``/boot`` directory.

- Modify the ``/boot/grub/grub.cfg`` and add an entry:

```
menuentry 'My Kernel' {
	set root='hd0,msdos1'
	multiboot /boot/[your compiled kernel] ro
}
```

- Reboot and select ``My Kernel`` entry.

## ISO

### Compilation

#### Simple way

```
make iso
```

#### Hard way

```
$ mkdir -p /iso/boot/grub
$ cp [your compiled kernel] /iso/boot
$ cp grub.cfg /iso/boot/grub
$ grub-mkrescue -o [your iso name] iso
```

### Run on QEMU

#### Simple way

```
make run-iso
```

#### Hard way

```
qemu-system-i386 -boot d -cdrom [your iso] -m 512
```

## Resources

- The BIBLE, for basic kernel: https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel

- The BIBLE 2, for keyboard: https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard

- For keyboard scancodes: https://aeb.win.tue.nl/linux/kbd/scancodes-1.html

- For color and build iso image: https://theogill.medium.com/creating-a-kernel-from-scratch-1a1aa569780f
