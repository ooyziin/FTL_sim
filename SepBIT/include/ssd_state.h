#pragma once
#include <array>
#include <queue>
#include <map>
#include "ssd_types.h"

class fifo;

extern std::array<int, class_num> class_offset;
extern std::array<int, class_num> class_current_block;
extern int ERASE_NUM;
extern int VIC_NUM;
extern int MIG_NUM;
extern double waf;
extern double waf2;
extern int timestamp;
extern int l;
extern int n_c;
extern int n_tot;

extern GCPolicy POLICY;
extern fifo* fifo_q;

extern std::array<int, LPN_MAX> LPN_TO_PPN;
extern std::array<PageMeta, PPN_MAX> PAGE_OOB;
extern std::array<int, PPN_MAX> DATA;

extern std::queue<int> FREE_BLOCK_Q;
extern std::array<blockMeta, MAX_PBN> BLOCK_OOB;

// init
void OOB_init();


    	
    	
    	
