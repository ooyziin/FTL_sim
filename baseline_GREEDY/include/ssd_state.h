#pragma once
#include <array>
#include <queue>
#include "ssd_types.h"

// === global states (defined in ssd_state.cpp) ===
extern int offset;
extern int current_block;
extern int ERASE_NUM;
extern int VIC_NUM;
extern int MIG_NUM;
extern double waf;
extern double waf2;

extern GCPolicy POLICY;

extern std::array<int, LPN_MAX> LPN_TO_PPN;
extern std::array<PageMeta, PPN_MAX> PAGE_OOB;
extern std::array<int, PPN_MAX> DATA;

extern std::queue<int> FREE_BLOCK_Q;
extern std::array<int, MAX_PBN> invalid_counter;

// init
void OOB_init();

