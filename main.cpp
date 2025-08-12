#include <iostream>
#include "ssd_config.h"
#include "trace.h"

int main() {
    init_state();

    const std::string trace_file = "test-fio-small";
    processTraceFile(trace_file);

    std::cout << "DONE\n";
    return 0;
}
