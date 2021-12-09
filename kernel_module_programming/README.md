## Kernel Module Programming 

#### kernel version
```
uname -r
```

#### makefile
```
sudo make
```

#### insert custom module to kernel
```
sudo insmod [FILE_NAME].ko
```

#### console log messege
```
dmesg | tail
```

#### current module list
```
lsmod | grep [FILE_NAME]
```

#### remove custom module in kernel
```
sudo rmmod [FILE_NAME]
```

#### console log messege
```
demsg | tail
```
