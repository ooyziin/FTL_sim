#include <fstream>
#include <iostream>
#include <sstream>
#include "ftl.h"
#include "ssd_state.h"
#include "ssd_config.h"
#include "progress.h"

void processTraceFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open trace file: " << filename << "\n";
        return;
    }

    std::string line;
    double timestamp;
    int io_type, lba, io_size, stream_number;

    constexpr long long CHUNK_LINES = 2LL * 1024 * 1024; // 2,097,152
    long long write_lines = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss >> timestamp >> io_type >> lba >> io_size >> stream_number)) {
            continue; // malformed line
        }

        if (io_type == 1) { // WRITE
            while (static_cast<int>(FREE_BLOCK_Q.size()) <= GC_TRIGGER_FREE_BLOCKS) {
        garbageCollection();
    }
            write_lpn(lba);
            ++write_lines;
            output_progress_if_needed(write_lines, CHUNK_LINES);
        }
    }
}

