#include <iostream>
#include "ssd_state.h"
#include "ssd_config.h"
#include "ftl.h"

// 일반 host write
void write_lpn(int lpn) {
    if (LPN_TO_PPN[lpn] != INVALID) {
        int page_num = LPN_TO_PPN[lpn];
        int block_num = page_num / PAGES_PER_BLOCK;
        ++invalid_counter[block_num];}

    int ppn = MIDA_current_block[0] * PAGES_PER_BLOCK + MIDA_offset[0];
    MIDA_offset[0]++;

    PAGE_OOB[ppn].mig_count = 0; // host write: 0
    PAGE_OOB[ppn].lpn = lpn;
    PAGE_OOB[ppn].state = PageState::valid;
    LPN_TO_PPN[lpn] = ppn;
    DATA[ppn] = 1;

    waf++;
    waf2++;

    if (MIDA_offset[0] == PAGES_PER_BLOCK) {
            if (FREE_BLOCK_Q.empty()) {
            std::cout << "No free blocks available!\n";
            return;}
    MIDA_current_block[0] = FREE_BLOCK_Q.front();
    invalid_counter[MIDA_current_block[0]]=0;
        FREE_BLOCK_Q.pop();
        MIDA_offset[0] = 0;
    }
}


void write_lpn_gc(int lpn) {
    int page_num = LPN_TO_PPN[lpn];

    int i = (PAGE_OOB[page_num].mig_count < MIDA_n - 1) ? PAGE_OOB[page_num].mig_count + 1 : MIDA_n - 1;
 

    int ppn = MIDA_current_block[i] * PAGES_PER_BLOCK + MIDA_offset[i];
    PAGE_OOB[ppn] = PAGE_OOB[page_num]; 
    PAGE_OOB[ppn].mig_count = i;

    LPN_TO_PPN[lpn] = ppn;
    DATA[ppn] = 1;

    MIDA_offset[i]++;
    waf++;
    waf2++;

    if (MIDA_offset[i] == PAGES_PER_BLOCK) {
        MIDA_current_block[i] = FREE_BLOCK_Q.front();
        invalid_counter[MIDA_current_block[i]]=0;
        FREE_BLOCK_Q.pop();
        MIDA_offset[i] = 0;
    }
}
