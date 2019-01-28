#include "Button.h"

#include "ResourceManager.h"
#include "IGameScreen.h"
#include "Display.h"
#include "InputManager.h"
#include "AudioEngine.h"

namespace Shingine {

	Button::Button() { /* Empty */ 
	}


	Button::Button(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string& dTex, const std::string& hTex, SoundEffect hover, SoundEffect push) {
		init(x, y, wid, hei, callback, dTex, hTex, hover, push);
	}

	Button::Button(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string & text, const std::string & font, int fontSize, SDL_Color fontColor, SoundEffect hover, SoundEffect push) {
		init(x, y, wid, hei, callback, text, font, fontSize, fontColor, hover, push);
	}

	Button::~Button() { /* Empty */
	}

	Button::Button(const Button& other) {
		this->m_dest = other.m_dest;
		this->m_dTex = other.m_dTex;
		this->m_hTex = other.m_hTex;
		this->m_callback = other.m_callback;
		this->m_hover = other.m_hover;
		this->m_push = other.m_push;
		this->m_state = other.m_state;
		this->m_text = *const_cast<Text*>(&other.m_text);
		this->m_textToRender = other.m_textToRender;
		this->m_textColor = other.m_textColor;
	}

	void Button::init(int x, int y, int wid, int hei) {
		m_dest.x = x;
		m_dest.y = y;
		m_dest.w = wid;
		m_dest.h = hei;
	}

	void Button::init(int x, int y, int wid, int hei, std::function<void(void)> callback) {
		init(x, y, wid, hei);
		m_callback = callback;
	}

	void Button::init(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string& dTex, const std::string& hTex) {
		init(x, y, wid, hei, callback);
		setDefaultTexture(dTex);
		setHoverTexture(hTex);
	}

	void Button::init(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string& dTex, const std::string& hTex, SoundEffect hover, SoundEffect push) {
		init(x, y, wid, hei, callback, dTex, hTex);
		m_hover = hover;
		m_push = push;
	}

	void Button::init(int x, int y, int wid, int hei, std::function<void(void)> callback, const std::string & text, const std::string & font, int fontSize, SDL_Color fontColor, SoundEffect hover, SoundEffect push) {
		init(x, y, wid, hei, callback);
		m_text.setColor(fontColor);
		m_text.init(font, fontSize);
		m_text.setPos(x + wid / 2 - m_text.getTextDims(text).first / 2, y + hei / 2 - m_text.getTextDims(text).second / 2);
		m_textToRender = text;
		m_hover = hover;
		m_push = push;
	}

	void Button::setHoverTexture(const std::string& texturePath) {
		m_hTex = ResourceManager::getTextureFromFile(texturePath);
	}

	void Button::setDefaultTexture(const std::string& texturePath) {
		m_dTex = ResourceManager::getTextureFromFile(texturePath);
	}

	void Button::setPushSoundEffect(SoundEffect effect) {
		m_push = effect;
	}

	void Button::setHoverSoundEffect(SoundEffect effect) {
		m_hover = effect;
	}

	void Button::update() {
		if (m_state == ButtonState::PUSH)
			m_callback();
	}

	void Button::render() {

		if (m_state == ButtonState::DEFAULT) {
			SDL_SetRenderDrawColor(Display::renderer, 79, 200, 255, 255);
			m_dTex.render(m_dest.x + m_dest.w / 2 - m_dTex.getWidth() / 2, m_dest.y + m_dest.h / 2 - m_dTex.getHeight() / 2);
		}
		else if (m_state == ButtonState::HOVER) {
			SDL_SetRenderDrawColor(Display::renderer, 255, 255, 255, 255);
			m_hTex.render(m_dest.x + m_dest.w / 2 - m_dTex.getWidth() / 2, m_dest.y + m_dest.h / 2 - m_dTex.getHeight() / 2);
		}
		else {
			SDL_SetRenderDrawColor(Display::renderer, 173, 36, 24, 255);
			m_hTex.render(m_dest.x + m_dest.w / 2 - m_dTex.getWidth() / 2, m_dest.y + m_dest.h / 2 - m_dTex.getHeight() / 2);
		}

		m_text.render(m_textToRender);
		SDL_RenderDrawRect(Display::renderer, &m_dest);

	}
}