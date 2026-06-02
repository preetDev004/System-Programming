savedcmd_Hardware-Device.mod := printf '%s\n'   hardwareDevice.o | awk '!x[$$0]++ { print("./"$$0) }' > Hardware-Device.mod
