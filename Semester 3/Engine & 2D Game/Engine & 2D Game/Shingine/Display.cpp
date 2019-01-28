#include "Display.h"
#include "Errors.h"

#include <SDL/SDL.h>

namespace Shingine {

	SDL_Window* Display::s_window = nullptr;
	SDL_Renderer* Display::renderer = nullptr;

	int Display::s_width;
	int Display::s_height;
	std::string Display::s_name;

    Display::Display()
    { /* Empty */ }

    Display::~Display()
    { /* Empty */ }

    int Display::create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags /* 0x00 */) {
		
		if (!s_window) {
			Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_MOUSE_CAPTURE;

			s_width = screenWidth;
			s_height= screenHeight;
			s_name = windowName;

			if (windowFlags & INVISIBLE) {
				flags |= SDL_WINDOW_HIDDEN;
			}
			if (windowFlags & FULLSCREEN) {
				flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			}
			if (windowFlags & BORDERLESS) {
				flags |= SDL_WINDOW_BORDERLESS;
			}

			//Open an SDL WINDOW
			s_window = SDL_CreateWindow(s_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		}

		if (!s_window) {
			fatalError("SDL WINDOW could not be created!");
		}

		if(!renderer)
			renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer == nullptr) {
			fatalError("SDL Renderer could not be created");
		}
		
        return 0;
    }

	void Display::renderBegin(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderClear(renderer);
	}

	void Display::renderEnd() {
		SDL_RenderPresent(renderer);
	}

	void Display::showCursor(bool shouldShow) {
		SDL_ShowCursor(static_cast<int>(shouldShow));
	}

}