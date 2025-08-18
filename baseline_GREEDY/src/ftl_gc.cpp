#include <iostream>
#include <cstdlib>
#include "ssd_state.h"
#include "ssd_config.h"
#include "ftl.h"

int pickVictimBlock() {
    if (POLICY == GREEDY) {
 
    int best_idx = 0;
    int best_val = invalid_counter[0];

    for (int i = 1; i < PPN_MAX; ++i) {
        int v = invalid_counter[i];
        if (v > best_val) {
            best_val = v;
            best_idx = i;
        }
    }

    if (best_val == -1) {
        std::cerr << "some error exists\n";
        std::exit(EXIT_FAILURE);
    }
    VIC_NUM++;
    return best_idx;
}  
 	else {
        std::cerr << "incorrect policy.\n";
       	std::exit(EXIT_FAILURE);
    }
}

void migrateValidPage(int src_ppn) {
int lpn = PAGE_OOB[src_ppn].lpn;
if (lpn == INVALID) return;

if (LPN_TO_PPN[lpn] != src_ppn) {
return;
}
write_lpn(lpn);
MIG_NUM++;}

void erase(int bid) {
    int base = FIRST_PPN_OF_BLOCK(bid);
    for (int i = 0; i < PAGES_PER_BLOCK; ++i) {
        int ppn = base + i;
        PAGE_OOB[ppn].lpn = INVALID;
        PAGE_OOB[ppn].state = PageState::erased;
        DATA[ppn] = 0;
    }
    ERASE_NUM++;
}

void garbageCollection() {
    int victim = pickVictimBlock();
    int base = FIRST_PPN_OF_BLOCK(victim);

    for (int i = 0; i < PAGES_PER_BLOCK; ++i) {
        int ppn = base + i;
        migrateValidPage(ppn);
    }
    erase(victim);
    FREE_BLOCK_Q.push(victim);
}

