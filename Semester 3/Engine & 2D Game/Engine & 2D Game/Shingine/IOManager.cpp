#include "IOManager.h"

#include <fstream>
#include <iostream>
#include <string>

namespace Shingine {

    
    bool IOManager::readFileToBuffer(std::string filePath, std::vector<std::string>& buffer) {
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            perror(filePath.c_str());
            return false;
        }

		std::string temp;
		while (std::getline(file, temp))
		{
			buffer.push_back(temp);
			temp.clear();
		}
        return true;
    }

}