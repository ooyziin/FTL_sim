#include <iostream>
#include "ssd_state.h"
#include "ssd_config.h"
#include "trace.h"

int main() {
    // Initialize free blocks
    for (int i = 0; i < MAX_PBN; ++i) {
        FREE_BLOCK_Q.push(i);
    }
    fifo_q = new FIFO();
    OOB_init();

    std::string trace_file = "test-fio-small";
    processTraceFile(trace_file);
    std::cout << " DONE ";
    return 0;
}

