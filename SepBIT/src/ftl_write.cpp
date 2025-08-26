#include <iostream>
#include "fifo.h"
#include "ssd_state.h"
#include "ssd_config.h"
#include "ftl.h"


void write_lpn(int lpn) {
    if (LPN_TO_PPN[lpn] != INVALID) {
        int page_num = LPN_TO_PPN[lpn];
        int block_num = page_num / PAGES_PER_BLOCK;
        BLOCK_OOB[block_num].invalid_counter++;}
        
	int lifespan= fifo_q-> Query(lpn);
	fifo_q-> Update(lpn)
	int blockclass = (lifespan >= l || lifespan == INVALID) ? 1 : 0; 
	int ppn = class_current_block[blockclass] * PAGES_PER_BLOCK + class_offset[blockclass];
    class_offset[blockclass]++;

    PAGE_OOB[ppn].write_num = timestamp;
    PAGE_OOB[ppn].lpn = lpn;
    PAGE_OOB[ppn].state = PageState::valid;
    LPN_TO_PPN[lpn] = ppn;
    DATA[ppn] = 1;
    waf++;
    waf2++;
    timestamp++;

    if (class_offset[blockclass] == PAGES_PER_BLOCK) {
            if (FREE_BLOCK_Q.empty()) {
            std::cout << "No free blocks available!\n";
            return;}
    class_current_block[blockclass] = FREE_BLOCK_Q.front();
    BLOCK_OOB[class_current_block[blockclass]].invalid_counter=0;
    BLOCK_OOB[class_current_block[blockclass]].blockclass=blockclass;
        FREE_BLOCK_Q.pop();
        class_offset[blockclass] = 0;
    }
}


void write_lpn_gc(int lpn) {
    int page_num = LPN_TO_PPN[lpn];
    int block_num = page_num / PAGES_PER_BLOCK;
    int c=BLOCK_OOB[block_num].blockclass;
    int blockclass=-1;
    if(c==0)
    {blockclass=2;}
    else {
        int age = timestamp - PAGE_OOB[page_num].write_num;
        
        if (age >= 0 && age < 4*l) {
            blockclass = 3;
        } else if (age >= 4*l && age < 16*l) {
            blockclass = 4;
        } else if (age >= 16*l) {
           blockclass = 5;
        }
    }
	
    int ppn = class_current_block[blockclass] * PAGES_PER_BLOCK + class_offset[blockclass];
    PAGE_OOB[ppn] = PAGE_OOB[page_num]; 
    LPN_TO_PPN[lpn] = ppn;
    DATA[ppn] = 1;

    class_offset[blockclass]++;
    waf++;
    waf2++;

    if (class_offset[blockclass] == PAGES_PER_BLOCK) {
        class_current_block[blockclass] = FREE_BLOCK_Q.front();
        BLOCK_OOB[class_current_block[blockclass]].invalid_counter=0;
        BLOCK_OOB[class_current_block[blockclass]].blockclass=blockclass;
        FREE_BLOCK_Q.pop();
        class_offset[blockclass] = 0;
    }
}
