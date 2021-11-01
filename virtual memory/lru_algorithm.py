"""
Least Recently Used (LRU) Algorithm for Page Replacement
between Logical Memory(Virtual Memory) and Physical Memory
"""

import random

# USER PARAMETERS
PAGE_NUM: int = 8   # size of logical memory(page number)
FRAME_NUM: int = 4  # size of physical memory

PAST_NUM: int = 20  # size of past valid page buffer

ITER: int = 10      # iteration number for simulation

# CONSTANT
PAGE_FAULT: int = 0 # the number of final page fault

def ref_str_gen(data: list) -> list:
    """
    For reference string generation
    """
    _r: int = random.randint(1, PAGE_NUM)
    
    if len(data) == PAST_NUM:
            data.pop(0)
        
    data.append(_r)
    
    return data

def lru(frame: list, ref_str: list) -> list:
    """
    For searching Least Recently Used(LRU) page
    """
    global PAGE_FAULT
    
    _r: int = ref_str[-1]
    
    if _r in frame:
        new: list = frame
    else:
        if len(frame) >= FRAME_NUM:
            
            frame_idx = frame.copy() 
            
            for i in range(FRAME_NUM):
                for j in range(len(ref_str)-1, 0, -1):
                    if frame[i] == ref_str[j-1]:
                        frame_idx[i] = j
                        
            idx: int = frame_idx.index(min(frame_idx))
            frame[idx] = _r
        else:
            # initial page fault when frame has empty space
            frame.append(_r)
            idx: int = len(frame) - 1
        
        PAGE_FAULT += 1
        print("Page Fault", str(PAGE_FAULT) + "!", end=" ")
        print("Frame Index :", idx)
        
        new: list = frame
    
    return new

def main():
    frame_list = list()
    ref_str_list = list()
    
    for i in range(ITER):
        ref_str_list = ref_str_gen(ref_str_list)
        print("Reference String :", ref_str_list)
        
        frame_list = lru(frame_list, ref_str_list)
        print("Physical Memory  :", frame_list)
        print()

    print("Final Page Fault :", PAGE_FAULT)

if __name__ == "__main__":
    main()