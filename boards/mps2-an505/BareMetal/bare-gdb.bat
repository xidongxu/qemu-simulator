@echo off

set tool=%1
set file=""
set exec=""

if %tool% == gcc (
    set file="./build/gcc/an505-qemu.elf"
    set exec="file ./build/gcc/an505-qemu.elf"
) 
if %tool% == iar (
    set file="./build/iar/an505-qemu.out"
    set exec="file ./build/iar/an505-qemu.out"
) 
if %tool% == mdk (
    set file="./build/mdk/an505-qemu.axf"
    set exec="file ./build/mdk/an505-qemu.axf"
) 
if not exist %file% (
    echo Executable file not found for tool: %1
    goto finish
)

echo executable file is exist, start gdb:
arm-none-eabi-gdb.exe -ex "target remote localhost:1234" -ex %exec% -ex "break main" -ex "continue"

:finish
pause
