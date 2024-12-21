# KFS-1

Discover the world of "Kernel Programming" and learn how to create your very own Kernel from scratch.

**NB**: The project technically works (for the mandatory part), but there is a lot of rework to do (I will do it very soon), and the bonus part is missing (I think it can be easy).

## Compilation (temporary)

``nasm -f elf32 boot.asm -o boot.o``

``gcc -m32 -c kernel.c -o kernel.o``

``ld -m elf_i386 -T link.ld -o [your kernel name] boot.o kernel.o``

<i><u>It is recommended to name your kernel with the formal</u></i>: ``kernel-<version>``. I named mine "kernel-kfs.1.rleseur".

## Installation

- Take the last Debian ISO and make a VM in virtualbox.

- Clone the repo in it.

- Install vim with ``sudo apt install vim``.

- Copy the compiled kernel in ``/boot`` directory.

- Modify the ``/boot/grub/grub.cfg`` and add an entry:

```
menuentry 'My Kernel' {
	set root='hd0,msdos1'
	multiboot /boot/[your compiled kernel] ro
}
```

- Reboot and select ``My Kernel`` entry.

## Resources

The BIBLE: https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel
