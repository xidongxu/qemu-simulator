arm-none-eabi-gdb -ex "target remote localhost:1234" -ex "file ./build/gcc/stm32-qemu.elf" -ex "break main" -ex "continue"