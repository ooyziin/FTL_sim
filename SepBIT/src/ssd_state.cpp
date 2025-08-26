#include "ssd_state.h"
#include "ssd_config.h"

int ERASE_NUM = 0;
int VIC_NUM = 0;
int MIG_NUM = 0;
double waf = 0;
double waf2 = 0;
int timestamp = 0;

GCPolicy POLICY = GREEDY;

std::array<int, LPN_MAX> LPN_TO_PPN{};
std::array<PageMeta, PPN_MAX> PAGE_OOB{};
std::array<int, PPN_MAX> DATA{};
std::array<int, class_num> class_offset{};
std::array<int, class_num> class_current_block{};
std::queue<int> FREE_BLOCK_Q;
std::array<blockMeta, MAX_PBN > BLOCK_OOB;

void OOB_init() {
    // Initialize 
    for (int j = 0; j < MAX_PBN; ++j) {
        int base = FIRST_PPN_OF_BLOCK(j);
        for (int i = 0; i < PAGES_PER_BLOCK; ++i) {
            int ppn = base + i;
            PAGE_OOB[ppn].lpn = INVALID;
            PAGE_OOB[ppn].write_num = INVALID;
            PAGE_OOB[ppn].state = PageState::invalid;
            DATA[ppn] = 0;
        }
    }

    // Initialize mapping table
    for (int lpn = 0; lpn < LPN_MAX; ++lpn) {
        LPN_TO_PPN[lpn] = INVALID;
    }

    // Initialize invalid counters
    for (int i = 0; i < MAX_PBN ; ++i) {
        BLOCK_OOB[i].invalid_counter = -1;  
        BLOCK_OOB[i].blockclass = -1; 
    }

    // Initialize MIDA pointers
for (int i = 0; i < class_num; ++i) {
    class_current_block[i] = FREE_BLOCK_Q.front();
    BLOCK_OOB[class_current_block[i]].invalid_counter = 0;
    BLOCK_OOB[class_current_block[i]].blockclass = i; 
    FREE_BLOCK_Q.pop();
    class_offset[i] = 0;
    
}
}
