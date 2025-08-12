#include "ssd_config.h"

int main() {
    // Sample input: Free block initialization (for simulation)
    for (int i = 0; i < MAX_PBN; ++i) {
        FREE_BLOCK_Q.push(i);
    }

	  int offset = 0;
    std::string trace_file = "test-fio-small";  // Path to the trace file
    processTraceFile(trace_file);
  
    std::cout << "DONE";
    return 0;
}
