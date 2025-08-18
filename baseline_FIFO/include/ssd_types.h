#pragma once
#include "ssd_config.h"

enum GCPolicy { GREEDY, FIFO };

enum class PageState {
    invalid,
    valid,
    erased
};

struct PageMeta {
    int lpn;
    PageState state;
};

inline int FIRST_PPN_OF_BLOCK(int bid) { return bid * PAGES_PER_BLOCK; }

