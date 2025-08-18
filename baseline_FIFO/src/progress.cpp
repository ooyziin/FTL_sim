#include <iostream>
#include "ssd_state.h"
#include "ssd_config.h"

void print_progress(long long chunk_idx_now) {
    const long long gb_now = chunk_idx_now * 8; // 8GiB per chunk
    double mig_num = MIG_NUM;
    double vic_num = static_cast<double>(VIC_NUM) * PAGES_PER_BLOCK;
    double gc = (vic_num > 0.0) ? (mig_num / vic_num) : 0.0;

    std::cout << "[Progress: " << gb_now << "GiB]\n";
    std::cout << "TMP_WAF: " << waf / 1953125.0 << "\n";
    std::cout << "WAF: "     << waf / (1953125.0 * chunk_idx_now) << "\n";
    std::cout << "USED_BLOCKS: " << (MAX_PBN - static_cast<int>(FREE_BLOCK_Q.size())) << "\n";
    std::cout << "GC_policy_efficiency: " << gc << "\n";
    std::cout << "ERASE: " << ERASE_NUM << "\n";
}

void output_progress_if_needed(long long write_lines, long long CHUNK_LINES) {
    if (write_lines == 0) return;
    if (write_lines % CHUNK_LINES != 0) return;

    const long long chunk_idx_now = write_lines / CHUNK_LINES;
    print_progress(chunk_idx_now);

    // reset per-chunk counters (same semantics as your original)
    ERASE_NUM = 0;
    waf = 0;
}

