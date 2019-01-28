#pragma once

#include "Button.h"

#include <vector>
#include <functional>

namespace Shingine {

	class Button;
	class SoundEffect;
	class InputManager;

	class ButtonMenu
	{
	public:

		enum class Allignment { HORIZONTAL, VERTICAL };

		ButtonMenu();
		~ButtonMenu();

		void init(int x, int y, int bWidth, int bHeight, Allignment align, int buttonSpacing);
		void init(int x, int y, int bWidth, int bHeight, Allignment align, int buttonSpacing, SoundEffect hoverEffect, SoundEffect pushEffect);

		void render();
		void update(InputManager* inputManager);

		void addButton(std::function<void(void)> callback, const std::string& defaultTexture, const std::string& hoverTexture);
		void addButton(std::function<void(void)> callback, const std::string& text, const std::string& font, int fontSize, SDL_Color fontColor);

		void setCurrentButton(int index) { resetCurrentButton();  m_current = index; };

		int getCurrentButton() const { return m_current; };

		void resetCurrentButton() { m_buttons[m_current].m_state = Button::ButtonState::DEFAULT; }

		SDL_Rect getCurrentsDims() { return m_buttons[m_current].m_dest; }

	private:
		int m_x, m_y, m_b_width, m_b_height;
		int m_current = -1;
		int m_spacing = 0;
		
		Allignment m_allignment = Allignment::HORIZONTAL;

		SoundEffect m_hover;
		SoundEffect m_push;

		std::vector<Button> m_buttons;
	};

}
