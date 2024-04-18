arm-none-eabi-gdb.exe -ex "target remote localhost:1234" -ex "file ./stm32-qemu/stm32-qemu.axf" -ex "break main" -ex "continue"
pause
