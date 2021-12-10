## Device Driver Programming

f : char_driver_device

#### device major number > MAJOR_NUM
```
cat proc/devices
```

#### maekfile
```
sudo make
```

#### create system file
```
sudo mknod /dev/[FILE_NAME] c [MAJOR_NUM] [MINOR_NUM]
```
// c = character device

#### change mode for other user
```
sudo chmod 0666 /dev/[FILE_NAME]
```
// 0666 = 110110110 = rw-rw-rw

#### insert custom module to kernel
```
sudo insmod [FILE_NAME].ko
```

#### current module list
```
lsmod | grep [FILE_NAME]
```

// if you check the log in real-time, in other terminal use the following command:
```
tail -f /var/log/syslog
```

#### console log messege
```
dmesg | tail
```

#### test file
```
gcc [TEST_FILE].c
./a.out
```

#### console log messege
```
dmesg | tail
```

#### remove custom module in kernel
```
sudo rmmod [FILE_NAME ]
```

#### clean makefile
```
make clean
```
