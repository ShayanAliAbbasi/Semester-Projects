#pragma once

#include "Shingine.h"
#include "Display.h"
#include "InputManager.h"
#include "AudioEngine.h"

#include <memory>
#include <SDL/SDL.h>

namespace Shingine {

    class ScreenList;
    class IGameScreen;

    class IMainGame {
    public:
        IMainGame();
        virtual ~IMainGame();

        // Runs and initializes the game
        void run();
        // Exits the game
        void exitGame();

        // Called on initialization
        virtual void onInit() = 0;
        // For adding all screens
        virtual void addScreens() = 0;
        // Called when exiting
        virtual void onExit() = 0;

        void onSDLEvent(SDL_Event& evnt);

        const float getFps() const {
            return m_fps;
        }

        InputManager inputManager;
		AudioEngine audio;
		int screenWidth = 800, screenHeight = 600;
		std::string screenName = "Window";

    protected:
        // Custom update function
        virtual void update();
        // Custom render function
        virtual void draw();

        bool init();
        bool initSystems();

        std::unique_ptr<ScreenList> m_screenList = nullptr;
        IGameScreen* m_currentScreen = nullptr;
        
		bool m_isRunning = false;
		bool m_quitTriggered = false;
        
		float m_fps = 0.0f;
	};
}