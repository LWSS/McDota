#!/bin/bash
# Starts a GDB session on Dota,
# Sets a couple of things up and then you can use GDB normally


dota_pid=$(pidof dota2)
if [ -z "$dota_pid" ]; then
    /bin/echo -e "\e[31mDota2 needs to be open...\e[0m"
    exit 1
fi

# pBypass for crash dumps being sent
# You may also want to consider using -nobreakpad in your launch options.
sudo rm -rf /tmp/dumps # Remove if it exists
sudo mkdir /tmp/dumps # Make it as root
sudo chmod 000 /tmp/dumps # No permissions

#https://www.kernel.org/doc/Documentation/security/Yama.txt
sudo echo "2" | sudo tee /proc/sys/kernel/yama/ptrace_scope # Only allows root to inject code. This is temp until reboot.

echo "Dota PID: " $dota_pid

(sudo echo -e "set \$dlopen = (void*(*)(char*, int)) dlopen\n" \
"set \$dlmopen = (void* (*)(long int, char*, int)) dlmopen\n" \
"set \$dlinfo = (int (*)(void*, int, void*)) dlinfo\n" \
"set \$malloc = (void* (*)(long long)) malloc\n" \
"set \$dlerror = (char* (*)(void)) dlerror\n" \
""; cat) | sudo gdb -p $dota_pid
