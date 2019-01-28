#pragma once

#include <Shingine/IGameScreen.h>
#include <Shingine/InputManager.h>
#include <Shingine/STexture.h>
#include <Shingine/Timing.h>
#include <Shingine/AudioEngine.h>

class SplashScreen : public Shingine::IGameScreen
{
public:
	
	SplashScreen();
	~SplashScreen();
	
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void draw() override;
	virtual void update() override;

private:
	Shingine::InputManager* m_inputManager;
	Shingine::SoundEffect m_entry;
	Shingine::SoundEffect m_cont;
	Shingine::STexture m_logo;
	Shingine::STexture m_logoS;
	Shingine::STexture m_prompt;
	Shingine::STexture m_loading;
	Shingine::STexture m_exit;

	Shingine::Timer m_timer;

	bool m_showPrompt = false;
	bool m_showLoading = false;
	bool m_playOnEntry = true;
	bool m_showExit = false;

	void dimBackground();
	void resetBackground();
};

