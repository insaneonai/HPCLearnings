#include "tracehandler.h"
#include <fstream>


std::vector<MemoryAccess> TraceHandler::parse_trace(const std::string& trace_file) {
    std::vector<MemoryAccess> accesses;
    std::fstream file(trace_file, std::ios::in);

    if (!file.is_open()){
        std::cerr << "Error: Could not open trace file: " << trace_file << std::endl;
        return accesses;
    }

    std::string line;

    while (std::getline(file, line)) {
        // convert line to MemoryAccess object
        // add to accesses vector
        // 0x1000, 0x10004 ...
        uint64_t addr;
        std::sscanf(line.c_str(), "0x%lx", &addr);
        accesses.push_back(MemoryAccess(addr, false));
    }


    return accesses;
}