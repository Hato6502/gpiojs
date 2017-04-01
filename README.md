# The GPIO Device Driver as Joystick
This is the device driver to recognize buttons and analog stick connected to GPIO as joystick device.

It makes buttons can be used to games with generic input libraries instead of own prepared ones.

## Installation
First of all, edit "config.c" to set allocating gpio and keys. 

The device drivers depend on the Linux kernel. 

Please install the kernel headers, and run "make" command. 

ex.(Raspberry Pi only)

    # apt-get install raspberrypi-kernel-headers
    $ make

Then, just run the following command by root. 

    # insmod gpiojs.ko
