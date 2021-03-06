#include "IMainGame.h"
#include "Timing.h"

#include "ScreenList.h"
#include "IGameScreen.h"
#include "Display.h"
#include "ResourceManager.h"

namespace Shingine {

    IMainGame::IMainGame() {
        m_screenList = std::make_unique<ScreenList>(this);
    }

    IMainGame::~IMainGame() {
		Shingine::quit();
    }

    void IMainGame::run() {

        if (!init()) return;

        FpsLimiter limiter;
		
        limiter.setMaxFPS(60.0f);

        // Game loop
        m_isRunning = true;

        while (m_isRunning) {

            limiter.begin();

            inputManager.update();

            // Call the custom update and draw method
            update();

            if (m_isRunning) {

                draw();

                m_fps = limiter.end();
            }
        }

    }

    void IMainGame::exitGame() {
        
		if(m_currentScreen) m_currentScreen->onExit();

        if (m_screenList) {

            m_screenList->destroy();
            m_screenList.reset();
        }
		
		audio.destroy();
		ResourceManager::clearTextureCache();

		m_isRunning = false;
    }

    void IMainGame::onSDLEvent(SDL_Event& evnt) {
        switch (evnt.type) {
            case SDL_QUIT:
				if (!m_quitTriggered) {
					m_quitTriggered = true;
					exitGame();
				}
                break;
            case SDL_MOUSEMOTION:
                inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                inputManager.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                inputManager.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                inputManager.releaseKey(evnt.button.button);
                break;
        }
    }

    bool IMainGame::init() {
       
        onInit();
        
		if (!initSystems()) return false;

        addScreens();

        m_currentScreen = m_screenList->getCurrent();

		if (m_currentScreen) {
        
			m_currentScreen->onEntry();
			m_currentScreen->setRunning();

		}

        return true;
    }

    bool IMainGame::initSystems() {

		Shingine::init();

		audio.init();

		Display::create(screenName, screenWidth, screenHeight, NULL);
   
		return true;
    }


    void IMainGame::update() {

		static SDL_Event evnt;

		// get all events from sdl and update our input manager
		while(SDL_PollEvent(&evnt))
			onSDLEvent(evnt);

        if (m_currentScreen) {

            switch (m_currentScreen->getState()) {

                case ScreenState::RUNNING:
                    m_currentScreen->update();
                    break;

                case ScreenState::CHANGE_NEXT:
                    m_currentScreen->onExit();
                    m_currentScreen = m_screenList->moveNext();

                    if (m_currentScreen) {
                        m_currentScreen->setRunning();
                        m_currentScreen->onEntry();
                    }
                    break;

                case ScreenState::CHANGE_PREVIOUS:
                    m_currentScreen->onExit();
                    m_currentScreen = m_screenList->movePrevious();

                    if (m_currentScreen) {
                        m_currentScreen->setRunning();
                        m_currentScreen->onEntry();
                    }
                    break;

                case ScreenState::EXIT_APPLICATION:
                    exitGame();
                    break;

                default:
                    break;
            }
        } else {
            exitGame();
        }
    }

    void IMainGame::draw() {

		Display::renderBegin(); /// < all upcomming rendering calls in screens will be updated on screen

        if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
            m_currentScreen->draw();
        }
		
		Display::renderEnd(); /// < actually renders updated screen
    }
}