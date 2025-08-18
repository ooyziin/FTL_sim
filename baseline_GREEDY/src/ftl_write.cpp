#include <iostream>
#include "ssd_state.h"
#include "ssd_config.h"
#include "ftl.h"

void write_lpn(int lpn) {
    if (offset == 0) {
        if (FREE_BLOCK_Q.empty()) {
            std::cout << "No free blocks available!\n";
            return;
        }
        current_block = FREE_BLOCK_Q.front();
    }
    if (LPN_TO_PPN[lpn] != INVALID) {
    int page_num= LPN_TO_PPN[lpn];
    int block_num=page_num/PAGES_PER_BLOCK;
        ++invalid_counter[block_num];
    }

    int ppn = current_block * PAGES_PER_BLOCK + offset;
    offset++;

    LPN_TO_PPN[lpn] = ppn;
    PAGE_OOB[ppn].lpn = lpn;
    PAGE_OOB[ppn].state = PageState::valid;
    DATA[ppn] = 1;

    waf++;
    waf2++;

    if (offset == PAGES_PER_BLOCK) {
        FREE_BLOCK_Q.pop();
        offset = 0;
    }
}

