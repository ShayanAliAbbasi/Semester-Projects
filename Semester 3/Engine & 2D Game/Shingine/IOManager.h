#pragma once

#include <vector>
#include <string>

namespace Shingine {

    class IOManager
    {
    public:
        static bool readFileToBuffer(std::string filePath, std::vector<std::string>&);
    };

}
