#include <iostream>
#include "ssd_state.h"
#include "ssd_config.h"
#include "ftl.h"

int pickVictimBlock() {
    if (POLICY == FIFO) {
        if (CLOSED_BLOCK_Q.empty()) {
            std::cerr << "[GC] CLOSED_BLOCK_Q empty, fallback victim=0\n";
            return 0;
        }
        int bid = CLOSED_BLOCK_Q.front();
        CLOSED_BLOCK_Q.pop();
        VIC_NUM++;
        return bid;
    } else {
        // TODO: GREEDY policy implementation
        return 0;
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

