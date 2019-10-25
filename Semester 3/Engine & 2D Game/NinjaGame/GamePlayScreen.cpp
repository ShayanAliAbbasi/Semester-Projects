#include "GamePlayScreen.h"
#include "ScreenIndices.h"

#include <Shingine/IMainGame.h>
#include <Shingine/ResourceManager.h>
#include <Shingine/Display.h>
#include <Shingine/Physics.h>

constexpr auto MID_X = 230;
constexpr auto MID_Y = 300;
constexpr auto FRAMERATE_F_X = 940;
constexpr auto FRAMERATE_F_Y = 0;
constexpr auto MENU_B_W = 175;
constexpr auto MENU_B_H = 30;
constexpr auto MENU_B_F_SIZE = 14;
constexpr auto GROUND_POS_X = 0;
constexpr auto GROUND_POS_Y = 600;
constexpr auto GROUND_TEX_DIM = 32;
constexpr auto PLAYER_POS_X = 100;
constexpr auto PLAYER_POS_Y = GROUND_POS_Y / 2;
constexpr auto PLAYER_DIM_X = 50;
constexpr auto PLAYER_DIM_Y = 64;
constexpr auto TOTAL_ENEMIES = 100;

// An extern variable defined here
int MAX_WORLD_X = 15000;

const std::string BUTTON_H = "Sounds/hover.wav";
const std::string BUTTON_P = "Sounds/push.wav";
const std::string BACKGROUND_MUSIC = "Sounds/gameplay/background.ogg";

const std::string EXIT = "Assets/screen/exit_to.png";
const std::string GROUND_TEX = "Assets/screen/gameplay/glass_metal_frame.png";
const std::string PLAYER_SPRITE = "Assets/screen/gameplay/blue_ninja.png";
const std::string BACKGROUND_TEX = "Assets/screen/shuriken_logo.png";

const std::string FONT = "Fonts/metro.otf";

GamePlayScreen::GamePlayScreen() {
}

GamePlayScreen::~GamePlayScreen() {
}

int GamePlayScreen::getNextScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int GamePlayScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_MAINMENU;
}

void GamePlayScreen::build() {

	m_exitMenu.init(MID_X, MID_Y + 70, MENU_B_W, MENU_B_H, Shingine::ButtonMenu::Allignment::HORIZONTAL, 20, m_game->audio.loadSoundEffect(BUTTON_H), m_game->audio.loadSoundEffect(BUTTON_P));
	m_exitMenu.addButton([this]() { this->m_showExitMenu = false; }, "continue", FONT, MENU_B_F_SIZE, { 43, 255, 255, 255 });
	m_exitMenu.addButton([this]() { this->m_currentState = Shingine::ScreenState::CHANGE_PREVIOUS; }, "mainmenu", FONT, MENU_B_F_SIZE, { 43, 255, 255, 255 });
	m_exitMenu.addButton([this]() { this->m_currentState = Shingine::ScreenState::EXIT_APPLICATION; }, "desktop", FONT, MENU_B_F_SIZE, { 43, 255, 255, 255 });

	Shingine::Physics::initPhysicsWorld();
	Shingine::Physics::setWorldToPixelScale(32);
}

void GamePlayScreen::destroy() {
	
}

void GamePlayScreen::onEntry() {
	if (!m_inputManager)
		m_inputManager = &m_game->inputManager;

	m_game->audio.setMusicVolume(60);
	m_backMusic = m_game->audio.loadMusic(BACKGROUND_MUSIC);
	m_backMusic.play(-1);

	m_scrollCamera.init(0, m_game->screenWidth);

	m_exitText = Shingine::ResourceManager::getTextureFromFile(EXIT);

	m_showExitMenu = false;
	m_gameWon = false;
	m_gameLost = false;

	m_frameRate.setFont(FONT, 12);
	m_frameRate.setColor({ 23, 144, 255, 255 });
	m_frameRate.setPos(FRAMERATE_F_X, FRAMERATE_F_Y);
		
	m_playerName.setFont(FONT, 14);
	m_playerName.setColor({ 23, 134, 255, 255 });
	m_playerName.setPos(70, 10);

	m_pauseText.init(FONT, 18);
	m_pauseText.setColor({ 23, 134, 255, 255 });
	m_pauseText.setPos(MID_X + 160, MID_Y - 30);

	m_winText.init(FONT, 18);
	m_winText.setColor({ 23, 134, 255, 255 });
	m_winText.setPos(MID_X + 200, MID_Y - 30);

	m_loseText.init(FONT, 18);
	m_loseText.setColor({ 255, 0, 0, 255 });
	m_loseText.setPos(MID_X + 200, MID_Y - 30);

	m_restartText.init(FONT, 14);
	m_restartText.setColor({ 255, 255, 255, 255 });
	m_restartText.setPos(MID_X + 100, MID_Y);

	// Making a wide ground at bottom of screen 
	m_ground.init(GROUND_POS_X - 200, GROUND_POS_Y, MAX_WORLD_X + 400, GROUND_TEX_DIM, Shingine::BoundingBox::STATIC);

	Shingine::STexture groundTex = Shingine::ResourceManager::getTextureFromFile(GROUND_TEX);
	m_groundTexture.resize(m_game->screenWidth / GROUND_TEX_DIM);

	for (int i = 0; i < m_game->screenWidth / GROUND_TEX_DIM; i++)
		m_groundTexture[i] = groundTex;

	m_playerHealthBarA.init(70, 35, 250, 25, { 0, 0, 0, 0 }, { 33, 51, 248, 255 });
	m_playerHealthBarB.init(70, 35, 250, 25, { 255, 255, 255, 255 }, { 0, 0, 0, 0 });

	m_player.init({ PLAYER_POS_X, PLAYER_POS_Y }, { PLAYER_DIM_X, PLAYER_DIM_Y }, PLAYER_SPRITE, 10, 2, false);
	m_player.getSpriteAnimator().setAnimFrames(10, 10, 1);

	m_playerLogo = m_player.getSpriteAnimator().getTileSheet();

	for (int i = 0; i < TOTAL_ENEMIES; i++) {
		m_enemies.emplace_back( new Enemy({ 800 + i * ((MAX_WORLD_X - 850) / TOTAL_ENEMIES) , GROUND_POS_Y - PLAYER_DIM_Y }, { PLAYER_DIM_X, PLAYER_DIM_Y }, PLAYER_SPRITE, 10, 2, true));
	}
	m_enemies[0]->getSpriteAnimator().texture.setColor(255, 0, 0);

	for (int i = 0; i < 4; i++) {
		m_backTextures[i] = Shingine::ResourceManager::getTextureFromFile(BACKGROUND_TEX, true);
	}
	m_backTextures[0].setColor(255, 0, 0);

	m_backTex = Shingine::ResourceManager::getTextureFromFile(BACKGROUND_TEX, false);
	m_backTex.setColor(14, 162, 255);

	m_timer.start();
}

void GamePlayScreen::onExit()  {

	m_backMusic.stop();
	m_game->audio.freeMusic(BACKGROUND_MUSIC);

	for (auto& e : m_enemies)
		e->getBoundingBox().remove();

	for (size_t i = 0; i < m_enemies.size(); i++) {
		delete m_enemies[i];
		m_enemies[i] = nullptr;
	}

	m_enemies.clear();
	m_timer.pause();

	m_backTextures[0].setColor(0, 255, 255);

	m_backTex.free();
}
			  
void GamePlayScreen::update()  {

	if (!m_showExitMenu) {
		
		Shingine::Physics::updatePhysics();
		
		if (m_player.getState() == Agent::DEAD || m_player.getPos().y > GROUND_POS_Y) m_gameLost = true; 

		// Updates player using camera, inputManager and enemies
		m_player.update(&m_scrollCamera, m_inputManager, nullptr, &m_enemies);
		
		int enemyDead = 0;
		for (auto& e : m_enemies) {
				if (m_scrollCamera.insideView(e->getPos().x))
					e->update(&m_scrollCamera, nullptr, &m_player); 

				if (e->getState() == Agent::DEAD)
					enemyDead++;

				if (m_gameLost) { e->displayHealthBar(false); e->sleep(true); }
		}

		if (enemyDead == TOTAL_ENEMIES) {
			m_player.displayHealthBar(false);
			m_player.sleep(true);
			
			m_gameWon = true;
			m_player.setState(Agent::SHOCKED);
		}

		if ((m_gameWon || m_gameLost) && m_inputManager->isKeyPressed(SDLK_RETURN)) {
			onExit();
			onEntry();
			return;
		}
	}

	if (m_inputManager->isKeyPressed(SDLK_ESCAPE)) {	
		m_showExitMenu = !m_showExitMenu;
	}

	if (m_showExitMenu)
		m_exitMenu.update(m_inputManager);

	if (!(m_player.getState() == Agent::DEAD))
		m_playerHealthBarA.setDims({ m_playerHealthBarB.getDims().x * (m_player.getCurrentHealth() / m_player.getTotalHealth()), m_playerHealthBarA.getDims().y });

	m_timer.update();
}

void GamePlayScreen::draw() {

	static bool pauseAnimation = false;
	
	// Draw rotating shurikens as background
	if (!m_showExitMenu && !m_gameWon && !m_gameLost) {
		animateBackground();
	}

	if (m_showExitMenu) {
		m_pauseText.render("game paused");
		m_exitText.render(MID_X, MID_Y);
		m_exitMenu.render();
		
		// Stopping animation of player and enemy sprite when game is paused
		if (!m_player.getSpriteAnimator().paused()) 
			m_player.getSpriteAnimator().pause();

		for (auto& e : m_enemies) {
			if (!e->getSpriteAnimator().paused())
				e->getSpriteAnimator().pause();
		}

		pauseAnimation = true;
	}
	else if (pauseAnimation) {
		
		if (m_player.getSpriteAnimator().paused())
			m_player.getSpriteAnimator().resume();
		for (auto& e : m_enemies) {
			if (e->getSpriteAnimator().paused())
				e->getSpriteAnimator().resume();
		}

		pauseAnimation = false;
	}

	m_ground.debugRender({33, 51, 248, 255});

	m_playerLogo.render(m_player.getSpriteAnimator().getCurrentFrame(), 0, 0);

	for (int i = 0; i < (int)m_groundTexture.size(); i++) {
		m_groundTexture[i].render({ GROUND_POS_X + i * GROUND_TEX_DIM, GROUND_POS_Y, GROUND_TEX_DIM, GROUND_TEX_DIM });
	}

	m_frameRate.render(std::to_string(static_cast<int>(m_game->getFps())) + " fps");
	m_playerName.render("player");

	if (!(m_player.getState() == Agent::DEAD))
		m_playerHealthBarA.render();
	m_playerHealthBarB.render();
	
	// Showing player on screen
	m_player.render(&m_scrollCamera);
	
	// Showing all enemies on screen
	for (auto& e : m_enemies) {
		if (m_scrollCamera.insideView(e->getPos().x)) {
			e->render(&m_scrollCamera);
		}
	}

	// Displying sort of a map at the bottom of screen
	displayMap();

	if (m_gameWon && !m_showExitMenu) {
		m_winText.render("you win");
		m_restartText.render("press enter to restart");
	}
	else if (m_gameLost && !m_showExitMenu) {
		m_loseText.render("you lose");
		m_restartText.render("press enter to restart");
	}
}

// Lambda to map value from one range to another
static auto map = [](float val, float fromMin, float fromMax, float toMin, float toMax) {
	return toMin + (toMax - toMin) * ((val - fromMin) / (fromMax - fromMin));
};

void GamePlayScreen::displayMap() {

	Shingine::Graphics::drawLine(glm::ivec2(GROUND_POS_X + 100, GROUND_POS_Y + 100), glm::ivec2(m_game->screenWidth - 100, GROUND_POS_Y + 100), glm::ivec4(255, 255, 255, 255));
	Shingine::Graphics::drawLine(glm::ivec2(GROUND_POS_X + 100, GROUND_POS_Y + 90), glm::ivec2(GROUND_POS_X + 100, GROUND_POS_Y + 110), glm::ivec4(0, 255, 0, 255));
	Shingine::Graphics::drawLine(glm::ivec2(m_game->screenWidth - 100, GROUND_POS_Y + 90), glm::ivec2(m_game->screenWidth - 100, GROUND_POS_Y + 110), glm::ivec4(0, 255, 0, 255));

	int mappedPlayerPosX = map(m_player.getPos().x, 0, MAX_WORLD_X, GROUND_POS_X + 110, m_game->screenWidth - 140);
	Shingine::Graphics::drawLine(glm::ivec2(mappedPlayerPosX, GROUND_POS_Y + 90), glm::ivec2(mappedPlayerPosX, GROUND_POS_Y + 98), glm::ivec4(14, 162, 255, 255));

	for (auto& e : m_enemies) {
		glm::ivec4 color = { 255, 0, 0, 255 };

		if (e->getState() == Agent::DEAD) {
			color = { 0, 255, 0, 255 };
		}

		Shingine::Graphics::drawPoint(glm::ivec2(map(e->getPos().x, 0, MAX_WORLD_X, GROUND_POS_X + 110, m_game->screenWidth - 140), GROUND_POS_Y + 90), color);
	}
}

void GamePlayScreen::animateBackground() {
	static SDL_Rect s1;
	static SDL_Rect s2;
					  
	static SDL_Rect S1;
					  
	static SDL_Rect s3;
	static SDL_Rect s4;

	int camera = m_scrollCamera.getTranslation();

	constexpr auto SHUR_DIM = 100;
	constexpr auto BIG_SHUR_DIM = 150;

	static int s1x = 0;
	static int s2x = 0;
	static int S1x = 0;
	static int s3x = 0;
	static int s4x = 0;

	if (s1.x + s1.w < 0) {
		s1x += m_game->screenWidth + s1.w;
	}
	else if (s1.x > m_game->screenWidth) {
		s1x -= m_game->screenWidth + s1.w;
	}
	else if (s2.x + s2.w < 0) {
		s2x += m_game->screenWidth + s2.w;
	}
	else if (s2.x > m_game->screenWidth) {
		s2x -= m_game->screenWidth + s1.w;
	}
	else if (S1.x + S1.w < 0) {
		S1x += m_game->screenWidth + SHUR_DIM;
	}
	else if (S1.x > m_game->screenWidth) {
		S1x -= m_game->screenWidth + SHUR_DIM;
	}
	else if (s3.x + s3.w < 0) {
		s3x += m_game->screenWidth + s3.w;
	}
	else if (s3.x > m_game->screenWidth) {
		s3x -= m_game->screenWidth + s3.w;
	}
	else if (s4.x + s4.w < 0) {
		s4x += m_game->screenWidth + s4.w;
	}
	else if (s4.x > m_game->screenWidth) {
		s4x -= m_game->screenWidth + s4.w;
	}

	s1 = { s1x + camera, 50 + m_game->screenHeight / 3 - SHUR_DIM / 2, SHUR_DIM, SHUR_DIM };
	s2 = { s2x + 150 + camera, 50 + m_game->screenHeight / 3 - SHUR_DIM / 2, SHUR_DIM, SHUR_DIM };
	
	S1 = { S1x + 450 + camera, 50 + m_game->screenHeight / 3 - BIG_SHUR_DIM / 2, BIG_SHUR_DIM, BIG_SHUR_DIM };

	s3 = { s3x + m_game->screenWidth - (2 * SHUR_DIM) - 50 + camera, 50 + m_game->screenHeight / 3 - SHUR_DIM / 2, SHUR_DIM, SHUR_DIM };
	s4 = { s4x + m_game->screenWidth - SHUR_DIM + camera, 50 + m_game->screenHeight / 3 - SHUR_DIM / 2, SHUR_DIM, SHUR_DIM };

	m_backTextures[0].render(s1, NULL, 6 * m_timer.getFrames() % 361);
	m_backTextures[1].render(s2, NULL, 6 * m_timer.getFrames() % 361);
	
	m_backTex.render(S1, NULL, 7 * m_timer.getFrames() % 361);
	
	m_backTextures[2].render(s3, NULL, 6 * m_timer.getFrames() % 361);
	m_backTextures[3].render(s4, NULL, 6 * m_timer.getFrames() % 361);

	m_backTextures[0].render(S1, NULL, 6 * m_timer.getFrames() % 361);

	int color = int(map(m_player.getCurrentHealth(), 0.0f, 100.0f, 0.0f, 255.0f));

	m_backTex.setColor(color, color, color);
}

