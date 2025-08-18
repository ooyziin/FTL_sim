#include "ssd_state.h"
#include "ssd_config.h"

int offset = 0;
int current_block = INVALID;
int ERASE_NUM = 0;
int VIC_NUM = 0;
int MIG_NUM = 0;
double waf = 0;
double waf2 = 0;

GCPolicy POLICY = GREEDY;

std::array<int, LPN_MAX> LPN_TO_PPN{};
std::array<PageMeta, PPN_MAX> PAGE_OOB{};
std::array<int, PPN_MAX> DATA{};

std::queue<int> FREE_BLOCK_Q;
std::array<int, MAX_PBN> invalid_counter;

void OOB_init() {
    // Initialize OOB/Data
    for (int j = 0; j < MAX_PBN; ++j) {
        int base = FIRST_PPN_OF_BLOCK(j);
        for (int i = 0; i < PAGES_PER_BLOCK; ++i) {
            int ppn = base + i;
            PAGE_OOB[ppn].lpn = INVALID;
            PAGE_OOB[ppn].state = PageState::invalid;
            DATA[ppn] = 0;
        }
    }
    // Initialize map
    for (int lpn = 0; lpn < LPN_MAX; ++lpn) {
        LPN_TO_PPN[lpn] = INVALID;
    }
    for (int i = 0; i < MAX_PBN; ++i) {
       invalid_counter[i] = INVALID;
    }
}

