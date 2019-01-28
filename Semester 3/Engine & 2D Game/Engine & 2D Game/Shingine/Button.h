#pragma once

#include <SDL/SDL.h>
#include <string>
#include <functional>

#include "AudioEngine.h"
#include "STexture.h"
#include "Text.h"

namespace Shingine {
	
	class SoundEffect;
	class IGameScreen;
	class InputManager;
	
	class Button /// A button that ButtonMenu will control through keyboard input only
	{

	friend class ButtonMenu;

	public:
		Button();
		Button(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string& dTex, const std::string& hTex, SoundEffect hover, SoundEffect push);
		Button(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string& text, const std::string& font, int fontSize, SDL_Color textColor, SoundEffect hover, SoundEffect push);
		Button(const Button& other);
		~Button();

		void init(int x, int y, int wid, int hei);
		void init(int x, int y, int wid, int hei, std::function<void(void)> callback);
		void init(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string& dTex, const std::string& hTex);
		void init(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string& text, const std::string& font, int fontSize, SDL_Color fontColor, SoundEffect hover, SoundEffect push);
		void init(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string& dTex, const std::string& hTex, SoundEffect hover, SoundEffect push);
		
		/// Setters
		void setHoverTexture(const std::string& texturePath);
		void setDefaultTexture(const std::string& texturePath);
		void setText(const std::string& text) { m_textToRender = text; }
		void setPushSoundEffect(SoundEffect effect);
		void setHoverSoundEffect(SoundEffect effect);
		void setCallBack(std::function<void(void)> callback) { m_callback = callback; };
		
		void update();
		void render();

	private:
		SDL_Rect m_dest;
		STexture m_dTex;
		STexture m_hTex;
		
		Text m_text;
		std::string m_textToRender;
		SDL_Color m_textColor;

		std::function<void()> m_callback;

		SoundEffect m_hover;
		SoundEffect m_push;

		enum class ButtonState { DEFAULT, HOVER, PUSH } m_state = ButtonState::DEFAULT;
	};

};