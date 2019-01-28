#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Shingine.h"

namespace Shingine {

	int init() {
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
			return -1;
		}

		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
			return -2;
		}

		if (TTF_Init() == -1) {
			return -3;
		}

        return 0;
    }

	void quit() {
		//Quit SDL
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

}