#include "MainMenuScreen.h"
#include "ScreenIndices.h"

#include <Shingine/ResourceManager.h>
#include <Shingine/Display.h>
#include <Shingine/IMainGame.h>


constexpr auto EYE_POS_X = 771;
constexpr auto EYE_POS_Y = 151;
constexpr auto BLADE_POS_X = 580;
constexpr auto BLADE_POS_Y = 185;
constexpr auto MENU_X = 50;
constexpr auto MENU_Y = 230;
constexpr auto MENU_B_W = 200;
constexpr auto MENU_B_H = 40;
constexpr auto MID_X = 230;
constexpr auto MID_Y = 300;
constexpr auto LOGO_X = 40;
constexpr auto LOGO_Y = 50;
constexpr auto FONT_SIZE = 18;
constexpr auto CONTROL_TEXT_SIZE = 14;
constexpr auto CONTROL_TEXT_X = 60;
constexpr auto CONTROL_TEXT_Y = 250;

const std::string BACKGROUND_MUSIC = "Sounds/mainmenu/mainmenu.ogg";
const std::string FIRE_EFFECT = "Sounds/mainmenu/fire.wav";
const std::string PLAY = "Sounds/mainmenu/play.wav";
const std::string BUTTON_H = "Sounds/hover.wav";
const std::string BUTTON_P = "Sounds/push.wav";

const std::string BACKGROUND = "Assets/screen/mainmenu.png";
const std::string NINJA_EYE = "Assets/screen/ninja_eye.png";
const std::string BLADE_FLAME = "Assets/screen/blade_fire.png";
const std::string LOGO = "Assets/screen/ninja_blade.png";

const std::string PLAY_D = "Assets/screen/mainmenu/play_d.png";
const std::string PLAY_H = "Assets/screen/mainmenu/play_h.png";
const std::string HELP_D = "Assets/screen/mainmenu/help_d.png";
const std::string HELP_H = "Assets/screen/mainmenu/help_h.png";
const std::string CONTROLS_D = "Assets/screen/mainmenu/controls_d.png";
const std::string CONTROLS_H = "Assets/screen/mainmenu/controls_h.png";
const std::string CREDITS_D = "Assets/screen/mainmenu/credits_d.png";
const std::string CREDITS_H = "Assets/screen/mainmenu/credits_h.png";
const std::string EXIT_D = "Assets/screen/mainmenu/exit_d.png";
const std::string EXIT_H = "Assets/screen/mainmenu/exit_h.png";
const std::string SHURIKEN = "Assets/screen/mainmenu/shuriken.png";

const std::string HELP = "Assets/screen/mainmenu/help.png";
const std::string CREDITS = "Assets/screen/mainmenu/credits.png";
const std::string EXIT = "Assets/screen/exit_to.png";
const std::string TO_DESKTOP = "Assets/screen/mainmenu/desktop.png";
const std::string TO_SPLASHSCREEN = "Assets/screen/mainmenu/splash_screen.png";

const std::string FONT = "Fonts/metro.otf";

MainMenuScreen::MainMenuScreen() {
	m_screenIndex = SCREEN_INDEX_MAINMENU;
}

MainMenuScreen::~MainMenuScreen() {
}

int MainMenuScreen::getNextScreenIndex() const {
	return SCREEN_INDEX_GAMESCREEN;
}

int MainMenuScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_SPLASHSCREEN;
}

void MainMenuScreen::build() {
	
	m_menu.init(MENU_X, MENU_Y, MENU_B_W, MENU_B_H, Shingine::ButtonMenu::Allignment::VERTICAL, 20, m_game->audio.loadSoundEffect(BUTTON_H), m_game->audio.loadSoundEffect(BUTTON_P));
	m_menu.addButton([this]() { this->onPlayPressed(); }, PLAY_D, PLAY_H);
	m_menu.addButton([this]() { this->onHelpPressed(); }, HELP_D, HELP_H);
	m_menu.addButton([this]() { this->onControlsPressed(); }, CONTROLS_D, CONTROLS_H);
	m_menu.addButton([this]() { this->onCreditPressed(); }, CREDITS_D, CREDITS_H);
	m_menu.addButton([this]() { this->onExitPressed(); }, EXIT_D, EXIT_H);

	m_exitMenu.init(MID_X + 90, MID_Y + 70, 175, 30, Shingine::ButtonMenu::Allignment::HORIZONTAL, 20, m_game->audio.loadSoundEffect(BUTTON_H), m_game->audio.loadSoundEffect(BUTTON_P));
	m_exitMenu.addButton([this]() { this->m_currentState = Shingine::ScreenState::CHANGE_PREVIOUS; }, TO_SPLASHSCREEN, TO_SPLASHSCREEN);
	m_exitMenu.addButton([this]() { this->m_currentState = Shingine::ScreenState::EXIT_APPLICATION; }, TO_DESKTOP, TO_DESKTOP);

	m_controlsText[0]	= "keybinding";		m_controlsText[1]	= "function";
	m_controlsText[2]	= "left arrow";		m_controlsText[3]	= "move left";
	m_controlsText[4]	= "right arrow";	m_controlsText[5]	= "move right";
	m_controlsText[6]	= "up arrow";		m_controlsText[7]	= "jump";
	m_controlsText[8]	= "ctrl";			m_controlsText[9]	= "punch";
	m_controlsText[10]	= "alt";			m_controlsText[11]	= "slash";
	m_controlsText[12]	= "space";			m_controlsText[13]	= "throw shuriken";
}	

void MainMenuScreen::destroy() {
}

void MainMenuScreen::onEntry() {

	if (!m_inputManager)
		m_inputManager = &m_game->inputManager;

	m_game->audio.setMusicVolume(90);
	
	m_bMusic = m_game->audio.loadMusic(BACKGROUND_MUSIC);
	m_bMusic.play(-1);

	m_fire = m_game->audio.loadSoundEffect(FIRE_EFFECT);
	m_game->audio.setSoundEffectVolume(&m_fire, 80);
	m_fire.play(-1);
	
	m_play = m_game->audio.loadSoundEffect(PLAY);

	m_ninjaEye.init(NINJA_EYE, 24, 1);
	m_ninjaEye.setAnimFrames(0, 23, 0.05f, true);
	m_ninjaEye.texture.setColor(102, 255, 248);

	m_bladeFlames[0].init(BLADE_FLAME, 6, 5, true);
	m_bladeFlames[1].init(BLADE_FLAME, 6, 5, true);
	m_bladeFlames[2].init(BLADE_FLAME, 6, 5, true);

	m_bladeFlames[0].texture.setBlendMode(SDL_BLENDMODE_ADD);

	m_bladeFlames[0].setAnimFrames(7, 11, 60.0f / 5.0f);
	m_bladeFlames[1].setAnimFrames(7, 11, 60.0f / 5.0f);
	m_bladeFlames[2].setAnimFrames(7, 11, 60.0f / 5.0f);

	m_bg = Shingine::ResourceManager::getTextureFromFile(BACKGROUND);
	m_logo = Shingine::ResourceManager::getTextureFromFile(LOGO);
	(m_spinS = Shingine::ResourceManager::getTextureFromFile(SHURIKEN)).setColor(255, 255, 255);
	m_helpText = Shingine::ResourceManager::getTextureFromFile(HELP);
	m_exitText = Shingine::ResourceManager::getTextureFromFile(EXIT);
	m_creditText = Shingine::ResourceManager::getTextureFromFile(CREDITS);
	
	
	for (int i = 0; i < CONTROL_TEXT_SIZE; i++) {
		m_control[i].init(FONT, FONT_SIZE);
	}
	
	m_control[0].setColor({ 43, 255, 255, 255 });
	m_control[1].setColor({ 255, 0, 0, 255 });


	m_showSpinner = true;

	m_timer.start();
}

void MainMenuScreen::onExit() {

	m_showExit = false;

	m_fire.play(0);
	m_spinS.setColor(173, 36, 24);
	
	if (m_currentState == Shingine::ScreenState::CHANGE_NEXT)
		m_play.play(0);
	else
		m_showSpinner = false;

	m_game->audio.freeSoundEffect(FIRE_EFFECT);
	m_bMusic.stop();
	m_game->audio.freeMusic(BACKGROUND_MUSIC);
	
	m_ninjaEye.texture.setColor(255, 0, 0);
	m_bladeFlames[0].texture.setBlendMode();
	m_bladeFlames[0].texture.setAlpha(255);
	m_bladeFlames[0].texture.setColor(255, 0, 0);

	for (float elapsed = m_timer.getTime(); m_timer.getTime() - elapsed <= 2.0f; ) {

		m_timer.update();

		Shingine::Display::renderBegin();
		draw();
		Shingine::Display::renderEnd();
	}

	m_game->audio.freeSoundEffect(PLAY);

	m_bladeFlames[0].texture.setColor(0, 255, 255);
	m_menu.setCurrentButton(0);

	m_showExit = false;
	m_showMenu = true;

	m_timer.pause();
}

void MainMenuScreen::update() {
	m_timer.update();

	if (!m_showMenu && m_inputManager->isKeyPressed(SDLK_ESCAPE)) {
		m_showMenu = true;
		if (m_showControls) m_showControls = false;
		else if (m_showCredits) m_showCredits = false;
		else if (m_showExit) m_showExit = false;
		else if (m_showHelp) m_showHelp = false;
	}
	else if (m_inputManager->isKeyPressed(SDLK_ESCAPE)) {
		onExitPressed();
	}

	if (m_showExit)
		m_exitMenu.update(m_inputManager);
	
	if (m_showMenu)
		m_menu.update(m_inputManager);
}

void MainMenuScreen::draw() {

	m_bg.render(0, 0);
	m_logo.render(LOGO_X, LOGO_Y);
	m_ninjaEye.animateAt(EYE_POS_X, EYE_POS_Y);
	m_bladeFlames[0].animateAt(BLADE_POS_X, BLADE_POS_Y, 0.0, NULL, SDL_FLIP_HORIZONTAL);
	m_bladeFlames[1].animateAt(BLADE_POS_X - 190, BLADE_POS_Y);
	m_bladeFlames[2].animateAt(BLADE_POS_X - 100, BLADE_POS_Y);
	
	if (m_showMenu)
		m_menu.render();
	else
		dimBackground();

	if (m_showExit) {
		m_exitText.render(MID_X, MID_Y);
		m_exitMenu.render();
	}

	else if (m_showControls) {
		static constexpr int offsetx = 350;
		static constexpr int offsety = 40;
		
		m_control[0].render(m_controlsText[0], CONTROL_TEXT_X, CONTROL_TEXT_Y - offsety);
		m_control[1].render(m_controlsText[1], CONTROL_TEXT_X + offsetx, CONTROL_TEXT_Y - offsety);

		for (int i = 2; i < CONTROL_TEXT_SIZE; i += 2) {
			m_control[i].render(m_controlsText[i], CONTROL_TEXT_X, (i / 2) * offsety + CONTROL_TEXT_Y);
		}
		for (int i = 3; i < CONTROL_TEXT_SIZE; i += 2) {
			m_control[i].render(m_controlsText[i], CONTROL_TEXT_X + offsetx, (i / 2) * offsety + CONTROL_TEXT_Y);
		}
	}

	else if (m_showHelp) {
		m_helpText.render(MID_X, MID_Y);
	}

	else if (m_showCredits) {
		static int cY = m_game->screenHeight;
		static float stime = m_timer.getTime();

		cY -= (int)floor(m_timer.getTime() - stime);

		if (cY < MID_Y && cY != MID_Y) {
			cY = MID_Y;
		}

		m_creditText.render(MID_X, cY);
	}

	else {
		resetBackground();
	}

	if (m_showSpinner) {
		SDL_Rect dims = m_menu.getCurrentsDims();
		m_spinS.render(dims.x + dims.w + 10, dims.y + 5, NULL, m_timer.getFrames() % 360);
	}
}

void MainMenuScreen::onPlayPressed() {
	m_currentState = Shingine::ScreenState::CHANGE_NEXT;
}


void MainMenuScreen::onControlsPressed() {
	m_showMenu = false;
	m_showControls = true;
}

void MainMenuScreen::onCreditPressed() {
	m_showMenu = false;
	m_showCredits = true;
}

void MainMenuScreen::onHelpPressed() {
	m_showMenu = false;
	m_showHelp = true;
}

void MainMenuScreen::onExitPressed() {
	m_showMenu = false;
	m_showExit = true;
}

void MainMenuScreen::dimBackground() {
	m_bg.setBlendMode();
	m_bg.setAlpha(100);
	m_spinS.setAlpha(0);
	m_ninjaEye.texture.setAlpha(100);
	m_bladeFlames[0].texture.setAlpha(100);
}

void MainMenuScreen::resetBackground() {
	m_bg.setAlpha(255);
	m_spinS.setAlpha(255);
	m_ninjaEye.texture.setAlpha(255);
	m_bladeFlames[0].texture.setAlpha(255);
}
