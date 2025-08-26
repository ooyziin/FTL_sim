#pragma once
#include <map>  
#include "ssd_types.h"
#include "ssd_state.h"

class fifo {
public:
    // Simplified constructor
    fifo() {
        mTail = 0;
        mHead = 0;
        mArray = new int[kFileSize];
    }
    
       void Update(int blockAddr) {

	mArray[mTail] = blockAddr;
	mMap[blockAddr] = mTail;
	mTail += 1;

     	if (mTail == kFileSize) mTail = 0;

    	if ((mTail + kFileSize - mHead) % kFileSize > l)
    	 {
        int oldBlockAddr = mArray[mHead];
        if (mMap[oldBlockAddr] == mHead)
        {
          mMap.erase(oldBlockAddr);
        }
        mHead += 1;
        if (mHead == kFileSize) mHead = 0;

        if ((mTail + kFileSize - mHead) % kFileSize > l)
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
