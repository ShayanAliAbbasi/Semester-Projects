#pragma once

#include <string>

struct SDL_Renderer;
struct SDL_Window;

namespace Shingine {

    class Display
    {
    public:
		enum WindowFlags { INVISIBLE = 0 << 1, FULLSCREEN = 1 << 1, BORDERLESS = 2 << 1 };
		
		Display();
        ~Display();

        static int create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags = 0x00);

        static int getWidth() { return s_width; }
        static int getHeight() { return s_height; }
		
		static std::string getName() { return s_name; }
		static void renderBegin(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0);
		static void renderEnd();
		
		static void showCursor(bool shouldShow);

		static SDL_Renderer* renderer;
    private:
        static SDL_Window* s_window;
        static int s_width, s_height;
		static std::string s_name;
    };

}