@echo off

echo starting %1 qemu
start "" "bare-qemu.bat" %1
echo starting %1 gdb
start "" "bare-gdb.bat" %1
echo All scripts started.
