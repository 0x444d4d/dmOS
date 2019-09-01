#dmOS


This an OS I decided to program just for fun and as a learning exercise.

It currently does not do much, only prints strings, values in binary and hexadecimal and
reads the RTC.

The development environmet is a debian vagrant box so the os run in quemu in the host machine. To facilitate this task I made a little script that starts/closes the vagrant box, starts qemu, compiles the os, downloads the os to the host machine and also ssh into the virtual machine.
