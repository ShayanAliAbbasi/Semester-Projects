#include "Errors.h"
#include "Shingine.h"

#include <iostream>

namespace Shingine {

    //Prints out an error message and exits the game
    void fatalError(std::string errorString) {
        std::cout << errorString << std::endl;
        std::cout << "\aEnter any key to quit...";
		std::cin.get();

		Shingine::quit();

		exit(-100);
    }
}