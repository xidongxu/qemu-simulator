echo "Starting QEMU..."
xfce4-terminal --geometry 150x30 -x bash -c "./bare-qemu.sh" &
sleep 1
echo "Starting GDB..."
xfce4-terminal --geometry 150x30 -x bash -c "./bare-gdb.sh" &
sleep 1
echo "All scripts started."
