#include <vector>
#include "memoryaccess.h"

class TraceHandler {
    public:
        std::vector<MemoryAccess> parse_trace(const std::string& trace_file);
};