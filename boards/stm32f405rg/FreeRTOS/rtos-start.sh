echo "Starting QEMU..."
xfce4-terminal --geometry 150x30 -x bash -c "./rtos-qemu.sh" &
sleep 1
echo "Starting GDB..."
xfce4-terminal --geometry 150x30 -x bash -c "./rtos-gdb.sh" &
sleep 1
echo "All scripts started."
