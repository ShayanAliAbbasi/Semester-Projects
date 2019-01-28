#pragma once

#include <vector>

#include <Shingine/IGameScreen.h>
#include <Shingine/AudioEngine.h>
#include <Shingine/InputManager.h>
#include <Shingine/ButtonMenu.h>
#include <Shingine/STexture.h>
#include <Shingine/Timing.h>
#include <Shingine/Camera.h>
#include <Shingine/Physics.h>
#include <Shingine/GraphicUtils.h>
#include <Shingine/TileSheet.h>

#include "Player.h"
#include "Enemy.h"

class GamePlayScreen : public Shingine::IGameScreen
{
public:
	GamePlayScreen();
	~GamePlayScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
	virtual void draw() override;

private:

	void animateBackground();
	void displayMap();

	Shingine::InputManager* m_inputManager = nullptr;
	Shingine::Timer m_timer;
	
	Shingine::STexture m_exitText;
	Shingine::ButtonMenu m_exitMenu;

	Shingine::Music m_backMusic;

	Shingine::Camera1D m_scrollCamera;

	Shingine::Text m_pauseText;
	Shingine::Text m_frameRate;
	Shingine::Text m_playerName;
	Shingine::Text m_winText;
	Shingine::Text m_loseText;
	Shingine::Text m_restartText;

	Shingine::BoundingBox m_ground;
	
	Shingine::Rectangle m_playerHealthBarA;
	Shingine::Rectangle m_playerHealthBarB;

	Shingine::TileSheet m_playerLogo;

	std::vector<Shingine::STexture> m_groundTexture;

	Player m_player;
	std::vector<Agent*> m_enemies;

	Shingine::STexture m_backTex;
	Shingine::STexture m_backTextures[4];

	bool m_gameWon = false;
	bool m_gameLost = false;
	bool m_showExitMenu = false;
};

