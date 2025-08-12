#include "ssd_config.h"
#include <algorithm>
#include <cstring>

GCPolicy POLICY = FIFO;

std::array<int, LPN_MAX> LPN_TO_PPN{};
std::queue<int> FREE_BLOCK_Q;
std::queue<int> CLOSED_BLOCK_Q;

std::array<PageMeta, PPN_MAX> PAGE_OOB{};
std::array<int, PPN_MAX> DATA{};

int offset = 0;
int current_block = INVALID;

void init_state() {
    std::fill(LPN_TO_PPN.begin(), LPN_TO_PPN.end(), INVALID);
    for (int i = 0; i < PPN_MAX; ++i) {
        PAGE_OOB[i].lpn = INVALID;
        PAGE_OOB[i].state = PageState::invalid; // 초기값
        DATA[i] = 0;
    }
    for (int b = 0; b < MAX_PBN; ++b) {
        FREE_BLOCK_Q.push(b);
    }
    offset = 0;
    current_block = INVALID;
}
