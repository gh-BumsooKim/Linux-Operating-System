# Linux Operating System
Understanding Kernel and Interface with Linux Operating System 

## Environment

- Linux Ubuntu 20.04 (LTS)
- kernel 5.11.0-36-generic
- Bash
- gcc 9.3.0

## Multi-threading using POSIX standard API <pthread.h>

- System Flow

<p align="center">
  <img src="imgs/multi_thread_shared_resource.png">
</p>

- Result

<p align="center">
  <img src="imgs/multi_thread_shared_resource_screen.png">
</p>

- Result in prompt

```bash
$ gcc multi_thread_shared_resource.c -lpthread
$ ./a.out

Producer : 12
    Consumer : 12
Producer : 82
    Consumer : 82
Producer : 17
    Consumer : 17
Producer : 32
    Consumer : 32
Producer : 55
    Consumer : 55
Success with P : C = 198 : 198
```

## Least Recently Used (LRU) Algorithm for Page Replacement
between Logical Memory(Virtual Memory) and Physical Memory

- python 3.X

```
Reference String : [4]
Page Fault 1! Frame Index : 0
Physical Memory  : [4]

Reference String : [4, 7]
Page Fault 2! Frame Index : 1
Physical Memory  : [4, 7]

Reference String : [4, 7, 5]
Page Fault 3! Frame Index : 2
Physical Memory  : [4, 7, 5]

Reference String : [4, 7, 5, 3]
Page Fault 4! Frame Index : 3
Physical Memory  : [4, 7, 5, 3]

Reference String : [4, 7, 5, 3, 8]
Page Fault 5! Frame Index : 0
Physical Memory  : [8, 7, 5, 3]

Reference String : [4, 7, 5, 3, 8, 5]
Physical Memory  : [8, 7, 5, 3]

Reference String : [4, 7, 5, 3, 8, 5, 8]
Physical Memory  : [8, 7, 5, 3]

Reference String : [4, 7, 5, 3, 8, 5, 8, 6]
Page Fault 6! Frame Index : 1
Physical Memory  : [8, 6, 5, 3]

Reference String : [4, 7, 5, 3, 8, 5, 8, 6, 2]
Page Fault 7! Frame Index : 2
Physical Memory  : [8, 6, 2, 3]

Reference String : [4, 7, 5, 3, 8, 5, 8, 6, 2, 5]
Page Fault 8! Frame Index : 3
Physical Memory  : [8, 6, 2, 5]

Final Page Fault : 8
```
