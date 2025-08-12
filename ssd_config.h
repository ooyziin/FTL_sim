// set up H.W configuration
const int SSD_W_OP = 32GB;  
const int SSD_WO_OP = 32*1000*1000*1000B; 
const int PAGE_SIZE = 4KB; 
const int BLOCK_SIZE = 2MB; 
const int GC_TRIGGER_FREE_BLOCKS = 4; 
GCPolicy POLICY = FIFO;

// no need to touch
const int INVALID = -1;     
const int PAGES_PER_BLOCK = BLOCK_SIZE/PAGE_SIZE;
const int MAX_LBN = SSD_WO_OP/BLOCK_SIZE;
const int LPN_MAX = MAX_LBN * PAGES_PER_BLOCK; 
const int MAX_PBN = (SSD_W_OP-SSD_WO_OP)/BLOCK_SIZE;
const int PPN_MAX = MAX_PBN * PAGES_PER_BLOCK; 


//struct
enum GCPolicy { GREEDY, FIFO };

enum class PageState {
    invalid,  
    valid,    
    erased   
};

struct PageMeta {
    int lpn;      // Logical Page Number
    PageState state;   // Whether the page is valid or not
};

std::array<int, LPN_MAX> LPN_TO_PPN;  // Map from Logical Page Number to Physical Page Number
std::queue<int> FREE_BLOCK_Q; 
std::queue<int> CLOSED_BLOCK_Q;  // Blocks that are full

std::array<PageMeta, PPN_MAX> PAGE_OOB;
std::array<int, PPN_MAX> DATA;
    
inline int FIRST_PPN_OF_BLOCK(int bid){ return bid * PAGES_PER_BLOCK; } 
