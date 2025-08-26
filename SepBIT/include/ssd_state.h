#pragma once
#include <array>
#include <queue>
#include <map>
#include "ssd_types.h"

class FIFO;

extern std::array<int, class_num> class_offset;
extern std::array<int, class_num> class_current_block;
extern int ERASE_NUM;
extern int VIC_NUM;
extern int MIG_NUM;
extern double waf;
extern double waf2;
extern int timestamp;

extern GCPolicy POLICY;
extern FIFO* fifo_q;

extern std::array<int, LPN_MAX> LPN_TO_PPN;
extern std::array<PageMeta, PPN_MAX> PAGE_OOB;
extern std::array<int, PPN_MAX> DATA;

extern std::queue<int> FREE_BLOCK_Q;
extern std::array<blockMeta, MAX_PBN> BLOCK_OOB;

// init
void OOB_init();

class FIFO {
public:
    // Simplified constructor
    FIFO() {
        mTail = 0;
        mHead = 0;
    }
    
       void Update(int blockAddr) {// void Update(int blockAddr, int threshold
	mArray[mTail] = blockAddr;
	mMap[blockAddr] = mTail;
	mTail += 1;
     	if (mTail == kFileSize) mTail = 0;
    	if ((mTail + kFileSize - mHead) % kFileSize > 1000000)
    	 {
        int oldBlockAddr = mArray[mHead];
        if (mMap[oldBlockAddr] == mHead)
        {
          mMap.erase(oldBlockAddr);
        }
        mHead += 1;
        if (mHead == kFileSize) mHead = 0;

        if ((mTail + kFileSize - mHead) % kFileSize > 1000000)
        {
          oldBlockAddr = mArray[mHead];

          if (mMap[oldBlockAddr] == mHead)
          {
            mMap.erase(oldBlockAddr);
          }
          mHead += 1;
          if (mHead == kFileSize) mHead = 0;
        }
      }
    }
    	
    	
    int Query(int blockAddr)
    {
      auto it = mMap.find(blockAddr);
      if (it == mMap.end())
      {
        return INVALID;
      }
      int position = it->second;
      int lifespan = (mTail < position) ?
        mTail + kFileSize - position : mTail - position;
      return lifespan;
    }

   int mTail = 0;
    int mHead = 0;
    std::map<int, int> mMap;
    int* mArray = NULL;
    const int kFileSize = 128 * 1024 * 1024;
};

    	
    	
    	
