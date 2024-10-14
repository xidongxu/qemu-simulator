@echo off

set tool=%1
set file=""
set qemu=qemu-system-arm.exe

if %tool% == gcc (
    set file=./build/gcc/an505-qemu.elf
) 
if %tool% == iar (
    set file=./build/iar/an505-qemu.out
) 
if %tool% == mdk (
    set file=./build/mdk/an505-qemu.axf
) 
if not exist "%file%" (
    echo executable file not found for tool: %1
    goto finish
)

echo executable file is exist, start qemu:
%qemu% -machine mps2-an505 -cpu cortex-m33 -m 16M -nographic -kernel %file% -S -s

:finish
pause