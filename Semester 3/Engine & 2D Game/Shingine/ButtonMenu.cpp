#include "ButtonMenu.h"

#include "AudioEngine.h"
#include "InputManager.h"

namespace Shingine {
	
	ButtonMenu::ButtonMenu() {
		m_buttons.reserve(2);
	}


	ButtonMenu::~ButtonMenu() {
	}

	void ButtonMenu::init(int x, int y, int bWidth, int bHeight, Allignment align, int buttonSpacing) {
		m_x = x;
		m_y = y;
		m_b_width = bWidth;
		m_b_height = bHeight;
		m_allignment = align;
		m_spacing = buttonSpacing;
	}

	void ButtonMenu::init(int x, int y, int bWidth, int bHeight, Allignment align, int buttonSpacing, SoundEffect hoverEffect, SoundEffect pushEffect) {
		init(x, y, bWidth, bHeight, align, buttonSpacing);
		m_hover = hoverEffect;
		m_push = pushEffect;
	}

	void ButtonMenu::render() {
		for (Button& but : m_buttons) {
			but.render();
		}
	}

	void ButtonMenu::update(InputManager* inputManager) {

		m_buttons[m_current].m_state = Button::ButtonState::HOVER;

		// setting up and down key to change go through menu button if allignment is vertical
		if (m_allignment == Allignment::VERTICAL) {
			if (inputManager->isKeyPressed(SDLK_DOWN)) {
				m_buttons[m_current].m_state = Button::ButtonState::DEFAULT;
				m_current = (m_current + 1) % m_buttons.size();
				m_buttons[m_current].m_state = Button::ButtonState::HOVER;
				m_buttons[m_current].m_hover.play(0);
			}

			else if (inputManager->isKeyPressed(SDLK_UP)) {
				m_buttons[m_current].m_state = Button::ButtonState::DEFAULT;
				m_current = ((m_current - 1) >= 0) ? m_current - 1 : m_buttons.size() - 1;
				m_buttons[m_current].m_state = Button::ButtonState::HOVER;
				m_buttons[m_current].m_hover.play(0);

			}
		}

		// if allignment is horizonal setting left and right keys to switch menu buttons
		else
		{
			if (inputManager->isKeyPressed(SDLK_RIGHT)) {
				m_buttons[m_current].m_state = Button::ButtonState::DEFAULT;
				m_current = (m_current + 1) % m_buttons.size();
				m_buttons[m_current].m_state = Button::ButtonState::HOVER;
				m_buttons[m_current].m_hover.play(0);

			}

			else if (inputManager->isKeyPressed(SDLK_LEFT)) {
				m_buttons[m_current].m_state = Button::ButtonState::DEFAULT;
				m_current = ((m_current - 1) >= 0) ? m_current - 1 : m_buttons.size() - 1;
				m_buttons[m_current].m_state = Button::ButtonState::HOVER;
				m_buttons[m_current].m_hover.play(0);

			}
		}

		if (inputManager->isKeyPressed(SDLK_RETURN)) {
			m_buttons[m_current].m_state = Button::ButtonState::PUSH;
			m_buttons[m_current].m_push.play();
		}
		
		for (auto& but : m_buttons) {
			but.update();
		}
	}

	void ButtonMenu::addButton(std::function<void(void)> callback, const std::string& defaultTexture, const std::string& hoverTexture) {
		
		if (m_allignment == Allignment::HORIZONTAL) {
			m_buttons.emplace_back((m_buttons.size() != 0) ? m_buttons[m_buttons.size() - 1].m_dest.x + m_b_width + m_spacing : m_x, m_y , m_b_width, m_b_height, callback, defaultTexture, hoverTexture, m_hover, m_push);
		}
		else {
			m_buttons.emplace_back(m_x, (m_buttons.size() != 0) ? m_buttons[m_buttons.size()-1].m_dest.y + m_b_height + m_spacing : m_y, m_b_width, m_b_height, callback, defaultTexture, hoverTexture, m_hover, m_push);
		}

		if (m_current == -1) m_current = 0;
	}

	void ButtonMenu::addButton(std::function<void(void)> callback, const std::string & text, const std::string & font, int fontSize, SDL_Color fontColor) {
		
		if (m_allignment == Allignment::HORIZONTAL) {
			m_buttons.emplace_back((m_buttons.size() != 0) ? m_buttons[m_buttons.size() - 1].m_dest.x + m_b_width + m_spacing : m_x, m_y, m_b_width, m_b_height, callback, text, font, fontSize, fontColor,m_hover, m_push);
		}
		else {
			m_buttons.emplace_back(m_x, (m_buttons.size() != 0) ? m_buttons[m_buttons.size() - 1].m_dest.y + m_b_height + m_spacing : m_y, m_b_width, m_b_height, callback, text, font, fontSize, fontColor, m_hover, m_push);
		}

		if (m_current == -1) m_current = 0;
	}
}