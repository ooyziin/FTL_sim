#pragma once
#include <cstddef>
#include <cstdint>

// ---- Size helpers (C++ 표준 방식) ----
constexpr std::uint64_t KB(std::uint64_t x) { return x * 1024ULL; }
constexpr std::uint64_t MB(std::uint64_t x) { return x * 1024ULL * 1024ULL; }
constexpr std::uint64_t GB(std::uint64_t x) { return x * 1024ULL * 1024ULL * 1024ULL; }

// ---- Capacity model ----
// TOTAL = 사용자영역 + OP영역
constexpr std::uint64_t SSD_TOTAL_BYTES = GB(32);       // 총 물리 용량(예: 32 GiB)
constexpr std::uint64_t SSD_USER_BYTES  = GB(32);       // 사용자 노출 용량(예시는 동일하게 표기했지만 필요 시 조정)
static_assert(SSD_TOTAL_BYTES >= SSD_USER_BYTES, "TOTAL must be >= USER");

// ---- Geometry ----
constexpr std::uint64_t PAGE_SIZE      = KB(4);         // 4 KiB
constexpr std::uint64_t BLOCK_SIZE     = MB(2);         // 2 MiB
constexpr int           GC_TRIGGER_FREE_BLOCKS = 4;

constexpr int INVALID = -1;

constexpr int PAGES_PER_BLOCK = static_cast<int>(BLOCK_SIZE / PAGE_SIZE);
static_assert((BLOCK_SIZE % PAGE_SIZE) == 0, "BLOCK_SIZE must be multiple of PAGE_SIZE");

// 논리/물리 블록 개수
constexpr int MAX_LBN = static_cast<int>(SSD_USER_BYTES  / BLOCK_SIZE);  // 논리(사용자) 블록 수
constexpr int MAX_PBN = static_cast<int>(SSD_TOTAL_BYTES / BLOCK_SIZE);  // 물리(총) 블록 수
static_assert(MAX_PBN >= MAX_LBN, "Physical blocks must be >= logical blocks");

// 페이지 개수
constexpr int LPN_MAX = MAX_LBN * PAGES_PER_BLOCK;
constexpr int PPN_MAX = MAX_PBN * PAGES_PER_BLOCK;

// ---- Policies / Metadata types ----
enum GCPolicy { GREEDY, FIFO };

enum class PageState {
    invalid,
    valid,
    erased
};

struct PageMeta {
    int lpn;           // Logical Page Number in this physical page (or INVALID)
    PageState state;   // page state
};

// 편의 함수
inline int FIRST_PPN_OF_BLOCK(int bid) { return bid * PAGES_PER_BLOCK; }
