arm-none-eabi-gdb.exe -ex "target remote localhost:1234" -ex "file ./build/stm32-qemu.elf" -ex "break main" -ex "continue"
pause
