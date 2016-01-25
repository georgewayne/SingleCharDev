# SingleCharDev
Example of creating a single Linux character device. Tested on kernel 4.1.15

Usage:
1. first copy the files to your local machine by
    $> git clone https://github.com/georgewayne/SingleCharDev
2. compile with make. if all goes well, you'll have kernel module named single.ko
    $> make
3. use below command to monitor the kernel massages
    $> tail -f /var/log/kern.log
4. install the compiled kernel module. if sucessful, you'll see your new device /dev/mydevname.
    $> sudo insmod single.ko
5. run the test program
    $> sudo ./test
6. try all choices (open, read, write, close) and exit the test program
7. remove the kernel module
    $> sudo rmmod single

A sample log from /var/log/kern.log is below:

Jan 24 18:54:49 raspberrypi kernel: [84420.579635] /dev/mydevname sucessfuly created
Jan 24 18:55:01 raspberrypi kernel: [84433.250364] Driver: open()
Jan 24 18:55:04 raspberrypi kernel: [84436.435252] Driver: read()
Jan 24 18:55:07 raspberrypi kernel: [84439.284525] Driver: write()
Jan 24 18:55:08 raspberrypi kernel: [84440.319827] Driver: close()
Jan 24 18:55:25 raspberrypi kernel: [84456.564710] /dev/mydevname unregistered

