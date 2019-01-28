#include "SplashScreen.h"
#include "ScreenIndices.h"

#include <Shingine/IMainGame.h>
#include <Shingine/ResourceManager.h>

constexpr auto LOGO_X = 35;
constexpr auto LOGO_Y = 140;
constexpr auto SHUR_LOGO_X = LOGO_X + 314;
constexpr auto SHUR_LOGO_Y = LOGO_Y + 107;
constexpr auto PROMPT_X = SHUR_LOGO_X;
constexpr auto PROMPT_Y = SHUR_LOGO_Y + 350;
constexpr auto LOADING_X = PROMPT_X + 80;
constexpr auto LOADING_Y = PROMPT_Y;
constexpr auto EXIT_X = 230;
constexpr auto EXIT_Y = 350;

const std::string LOGO = "Assets/screen/logo.png";
const std::string SHURIKEN = "Assets/screen/shuriken_logo.png";
const std::string PROMPT = "Assets/screen/prompt.png";
const std::string LOADING = "Assets/screen/loading.png";
const std::string EXIT = "Assets/screen/exit.png";

const std::string ENTRY = "Sounds/splash/splash_screen.wav";
const std::string CONTINUE = "Sounds/splash/continue.wav";

SplashScreen::SplashScreen()
{
	m_screenIndex = SCREEN_INDEX_SPLASHSCREEN;
}


SplashScreen::~SplashScreen()
{
}

int SplashScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_MAINMENU;
}

int SplashScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void SplashScreen::build()
{

}

void SplashScreen::destroy()
{
}


void SplashScreen::onEntry() {
	if (!m_inputManager)
		m_inputManager = &m_game->inputManager;

	if (m_playOnEntry) {
		m_entry = m_game->audio.loadSoundEffect(ENTRY);
		m_entry.play(0);
	}

	m_cont = m_game->audio.loadSoundEffect(CONTINUE);

	m_playOnEntry = false;

	m_logo = Shingine::ResourceManager::getTextureFromFile(LOGO);
	m_logoS = Shingine::ResourceManager::getTextureFromFile(SHURIKEN);
	m_loading = Shingine::ResourceManager::getTextureFromFile(LOADING);
	m_exit = Shingine::ResourceManager::getTextureFromFile(EXIT);
	(m_prompt = Shingine::ResourceManager::getTextureFromFile(PROMPT)).setBlendMode(SDL_BLENDMODE_ADD);

	m_timer.start();
}

void SplashScreen::onExit() {

	m_logoS.setColor(255, 0, 0);

	for (float elapsed = m_timer.getTime(); m_timer.getTime() - elapsed <= 2.0f; ) {

		m_timer.update();

		Shingine::Display::renderBegin();

		m_logoS.render(SHUR_LOGO_X, SHUR_LOGO_Y, NULL, int(m_timer.getFrames() * 0.5) % 360);
		m_loading.setAlpha(m_timer.getFrames() % 250);

		if (m_showLoading)
			m_loading.render(LOADING_X, LOADING_Y);

		Shingine::Display::renderEnd();
	}

	m_logoS.setColor(0, 255, 255);

	m_timer.pause();
	m_showLoading = false;
}

void SplashScreen::draw() {
	static int w = m_logo.getWidth();
	static int h = m_logo.getHeight();

	static int perw = w * 4 / 100;
	static int perh = h * 4 / 100;

	static int animw = 0;
	static int animh = 0;

	m_logo.render({ LOGO_X, LOGO_Y, animw, animh });

	m_logoS.render(SHUR_LOGO_X, SHUR_LOGO_Y, NULL, m_timer.getFrames() % 360);

	if (m_showPrompt && !m_showExit) {
		m_prompt.render(PROMPT_X, PROMPT_Y);
		m_prompt.setAlpha(150 + m_timer.getFrames() * 2 % 255);
	}

	if (m_showExit) {
		dimBackground();
		m_exit.render(EXIT_X, EXIT_Y);
	}
	else resetBackground();


	if (animw < w) {
		animw += perw;
		if (animw > w)
			animw = w;
	}

	if (animh < h) {
		animh += perw;
		if (animh > h)
			animh = h;
	}

}

void SplashScreen::update() {
	m_timer.update();

	if (!m_showPrompt && m_timer.getTime() > 2.0f) m_showPrompt = true;

	if (m_showExit && m_inputManager->isKeyPressed(SDLK_RETURN)) {
		resetBackground();
		m_currentState = Shingine::ScreenState::EXIT_APPLICATION;
	}

	else if (m_showPrompt && m_inputManager->isKeyPressed(SDLK_RETURN)) {

		m_showLoading = true;
		m_cont.play(0);

		m_currentState = Shingine::ScreenState::CHANGE_NEXT;
		return;
	}

	else if (m_inputManager->isKeyPressed(SDLK_ESCAPE)) {
		m_showExit = !m_showExit;
	}

}

void SplashScreen::dimBackground() {
	m_logo.setAlpha(100);
	m_logoS.setAlpha(100);
}

void SplashScreen::resetBackground() {
	m_logo.setAlpha(255);
	m_logoS.setAlpha(255);
}
