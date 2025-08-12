#include <iostream>
#include "ssd_config.h"
#include "ftl.h"

int pickVictimBlock() {
    if (POLICY == FIFO) {
        if (CLOSED_BLOCK_Q.empty()) {
            std::cerr << "[GC] CLOSED_BLOCK_Q empty; cannot pick victim.\n";
            return INVALID;
        }
        int bid = CLOSED_BLOCK_Q.front();
        CLOSED_BLOCK_Q.pop();
        return bid;
    }
    // TODO: GREEDY 구현(유효 페이지 수 가장 적은 블록 선택)
    return INVALID;
}

void migrateValidPage(int src_ppn) {
    int lpn = PAGE_OOB[src_ppn].lpn;
    if (lpn == INVALID) return;                   // 비어있는 페이지
    if (LPN_TO_PPN[lpn] != src_ppn) return;       // 최신본이 아님

    if (offset == 0) {
        if (FREE_BLOCK_Q.empty()) {
            std::cerr << "No free blocks available during GC migrate!\n";
            return;
        }
        current_block = FREE_BLOCK_Q.front();
    }

    int ppn = current_block * PAGES_PER_BLOCK + offset;
    offset++;

    LPN_TO_PPN[lpn]   = ppn;
    PAGE_OOB[ppn].lpn = lpn;
    PAGE_OOB[ppn].state = PageState::valid;
    DATA[ppn] = 1;

    std::cout << "GCWRITE: LPN " << lpn << " -> PPN " << ppn << "\n";

    if (offset == PAGES_PER_BLOCK) {
        FREE_BLOCK_Q.pop();
        CLOSED_BLOCK_Q.push(current_block);
        offset = 0;
    }
}

void erase(int bid) {
    if (bid == INVALID) return;
    int base = FIRST_PPN_OF_BLOCK(bid);
    for (int i = 0; i < PAGES_PER_BLOCK; ++i) {
        PAGE_OOB[base + i].lpn = INVALID;
        PAGE_OOB[base + i].state = PageState::erased;
        DATA[base + i] = 0;
    }
}

void garbageCollection() {
    int victim = pickVictimBlock();
    if (victim == INVALID) {
        std::cerr << "[GC] No victim block selected.\n";
        return;
    }
    int base = FIRST_PPN_OF_BLOCK(victim);
    for (int i = 0; i < PAGES_PER_BLOCK; ++i) {
        int ppn = base + i;
        migrateValidPage(ppn);
    }
    erase(victim);
    FREE_BLOCK_Q.push(victim);
}

void write_lpn(int lpn) {
    while ((int)FREE_BLOCK_Q.size() <= GC_TRIGGER_FREE_BLOCKS) {
        std::cout << "[GC] Free blocks low; running GC...\n";
        garbageCollection();
        // 주의: CLOSED_BLOCK_Q가 비어있으면 GC가 아무것도 못 할 수 있음
        if ((int)FREE_BLOCK_Q.size() <= GC_TRIGGER_FREE_BLOCKS && CLOSED_BLOCK_Q.empty()) {
            std::cerr << "[GC] No closed blocks to reclaim. Write may stall.\n";
            break;
        }
    }

    if (offset == 0) {
        if (FREE_BLOCK_Q.empty()) {
            std::cerr << "No free blocks available!\n";
            return;
        }
        current_block = FREE_BLOCK_Q.front();
    }

    int ppn = current_block * PAGES_PER_BLOCK + offset;
    offset++;

    LPN_TO_PPN[lpn]   = ppn;
    PAGE_OOB[ppn].lpn = lpn;
    PAGE_OOB[ppn].state = PageState::valid;
    DATA[ppn] = 1;

    // if (offset == PAGES_PER_BLOCK) 로테이션
    if (offset == PAGES_PER_BLOCK) {
        FREE_BLOCK_Q.pop();                 // active block 소비 완료
        CLOSED_BLOCK_Q.push(current_block); // 닫힌 블록으로 이동
        offset = 0;
    }
}
