@echo off

set tool=%1
set file=""
set qemu=qemu-system-arm.exe

if %tool% == gcc (
    set file=./build/gcc/stm32-qemu.elf
) 
if %tool% == iar (
    set file=./build/iar/stm32-qemu.out
) 
if %tool% == mdk (
    set file=./build/mdk/stm32-qemu.axf
) 
if not exist "%file%" (
    echo executable file not found for tool: %1
    goto finish
)

echo executable file is exist, start qemu:
%qemu% -M netduinoplus2 -nographic -kernel %file% -S -s

:finish
pause