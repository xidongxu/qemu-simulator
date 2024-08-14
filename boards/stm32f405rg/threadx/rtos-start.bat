@echo off

echo starting %1 qemu
start "" "rtos-qemu.bat" %1
echo starting %1 gdb
start "" "rtos-gdb.bat" %1
echo All scripts started.
