#pragma once

#include <Shingine/IMainGame.h>

#include "SplashScreen.h"
#include "MainMenuScreen.h"
#include "GamePlayScreen.h"

class Game : public Shingine::IMainGame {
public:
    Game();
    ~Game();

    // Called on initialization
    virtual void onInit() override;
    // For adding all screens
    virtual void addScreens() override;
    // Called when exiting
    virtual void onExit() override;

private:
	std::unique_ptr<SplashScreen> m_splashScreen = nullptr;
    std::unique_ptr<MainMenuScreen> m_mainMenuScreen = nullptr;
	std::unique_ptr<GamePlayScreen> m_gamePlayScreen = nullptr;
};

