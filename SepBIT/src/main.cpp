#include <iostream>
#include "ssd_state.h"
#include "ssd_config.h"
#include "trace.h"
#include "fifo.h"

fifo* fifo_q = nullptr;

int main() {
    // Initialize free blocks
    for (int i = 0; i < MAX_PBN; ++i) {
        FREE_BLOCK_Q.push(i);
    }
    fifo_q = new fifo();
    OOB_init();

    std::string trace_file = "test-fio-small";
    processTraceFile(trace_file);
    std::cout << " DONE ";
    return 0;
}

