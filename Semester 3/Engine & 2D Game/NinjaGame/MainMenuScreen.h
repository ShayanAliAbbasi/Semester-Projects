#pragma once

#include <Shingine/IGameScreen.h>
#include <Shingine/InputManager.h>
#include <Shingine/STexture.h>
#include <Shingine/AudioEngine.h>
#include <Shingine/TileSheet.h>
#include <Shingine/SpriteAnimator.h>
#include <Shingine/ButtonMenu.h>
#include <Shingine/Text.h>

class MainMenuScreen : public Shingine::IGameScreen
{
public:

	MainMenuScreen();
	~MainMenuScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
	virtual void draw() override;

private:

	Shingine::InputManager* m_inputManager = nullptr;
	Shingine::Music m_bMusic;
	Shingine::SoundEffect m_fire;
	Shingine::SoundEffect m_play;

	Shingine::STexture m_bg;
	Shingine::STexture m_logo;
	Shingine::STexture m_spinS;
	Shingine::STexture m_helpText;
	Shingine::STexture m_exitText;
	Shingine::STexture m_creditText;
	Shingine::SpriteAnimator m_ninjaEye;
	Shingine::SpriteAnimator m_bladeFlames[3];
	Shingine::Timer m_timer;
	Shingine::ButtonMenu m_menu;
	Shingine::ButtonMenu m_exitMenu;
	Shingine::Text m_control[14];
	std::string m_controlsText[14];

	bool m_showMenu = true;
	bool m_showSpinner = true;
	bool m_showHelp = false;
	bool m_showExit = false;
	bool m_showControls = false;
	bool m_showCredits = false;

	void onPlayPressed();
	void onControlsPressed();
	void onCreditPressed();
	void onHelpPressed();
	void onExitPressed();
	
	void dimBackground();
	void resetBackground();
};

