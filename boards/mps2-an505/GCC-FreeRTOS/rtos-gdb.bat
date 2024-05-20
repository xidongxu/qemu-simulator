arm-none-eabi-gdb.exe -ex "target remote localhost:1234" -ex "file ./build/an505-qemu.elf" -ex "break main" -ex "continue"
pause
