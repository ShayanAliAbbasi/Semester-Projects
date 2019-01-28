#include "Game.h"

#include <Shingine/ScreenList.h>
#include <Shingine/Display.h>

Game::Game() {

}

Game::~Game() {

}

void Game::onInit() {
	screenWidth = 1024;
	screenHeight = 768;
	screenName = "NinjaBlade";
}

void Game::addScreens() {
    
	m_mainMenuScreen = std::make_unique<MainMenuScreen>();
	m_splashScreen = std::make_unique<SplashScreen>();
	m_gamePlayScreen = std::make_unique<GamePlayScreen>();
	
	m_screenList->addScreen(m_splashScreen.get());
    m_screenList->addScreen(m_mainMenuScreen.get());
    m_screenList->addScreen(m_gamePlayScreen.get());

    m_screenList->setScreen(m_splashScreen->getScreenIndex());
	
	Shingine::Display::showCursor(false);
}

void Game::onExit() {
}
