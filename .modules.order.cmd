cmd_/home/pi/embedded/RPIKERNEL/modules.order := {   echo /home/pi/embedded/RPIKERNEL/main.ko; :; } | awk '!x[$$0]++' - > /home/pi/embedded/RPIKERNEL/modules.order
