#pragma once
#include <cstddef>
#include <cmath>

constexpr int SSDsize_GB = 8;
constexpr int PAGE_SIZE_KB = 4;
constexpr int PAGES_PER_BLOCK = 1024;
constexpr int INVALID = -1;
constexpr int MIDA_n = 4; // (2,n) n is tunable

constexpr int MAX_LBN = static_cast<int>(
    (1LL * SSDsize_GB * 1000LL * 1000LL * 1000LL * 8) /
    (1LL * PAGE_SIZE_KB * 1024LL * 8 * PAGES_PER_BLOCK) + 1LL
);

constexpr int MAX_PBN = static_cast<int>(
    (1LL * SSDsize_GB * 1024LL * 1024LL * 1024LL * 8) /
    (1LL * PAGE_SIZE_KB * 1024LL * 8 * PAGES_PER_BLOCK)
);

constexpr int LPN_MAX = MAX_LBN * PAGES_PER_BLOCK;
constexpr int PPN_MAX = MAX_PBN * PAGES_PER_BLOCK;
constexpr int GC_TRIGGER_FREE_BLOCKS = 4;

