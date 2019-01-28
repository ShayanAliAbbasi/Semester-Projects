#include "Text.h"
#include "Errors.h"
#include "Display.h"

namespace Shingine {

	Text::Text() {
	}


	Text::~Text() {
		free();
	}

	Text::Text(Text && other) {
		m_x = other.m_x, m_y = other.m_y;
		m_color = other.m_color;
		m_fontSize = other.m_fontSize;
		m_fontName = other.m_fontName;
		m_text = other.m_text;
		m_font = other.m_font;

		other.m_font = nullptr;
	}

	Text& Text::operator=(Text && other) {
		if (this != &other) {
			m_x = other.m_x, m_y = other.m_y;
			m_color = other.m_color;
			m_fontSize = other.m_fontSize;
			m_fontName = other.m_fontName;
			m_text = other.m_text;
			m_font = other.m_font;

			other.m_font = nullptr;
		}

		return *this;
	}

	Text::Text(Text & other) {
		m_x = other.m_x, m_y = other.m_y;
		m_color = other.m_color;
		m_fontSize = other.m_fontSize;
		m_fontName = other.m_fontName;
		m_text = other.m_text;
		m_font = other.m_font;

		other.m_font = nullptr;
	}

	Text& Text::operator=(Text & other) {
		if (this != &other) {
			m_x = other.m_x, m_y = other.m_y;
			m_color = other.m_color;
			m_fontSize = other.m_fontSize;
			m_fontName = other.m_fontName;
			m_text = other.m_text;
			m_font = other.m_font;

			other.m_font = nullptr;
		}

		return *this;
	}

	void Text::init(const std::string & fontName, int fontSize) {
		setFont(fontName, fontSize);
	}

	void Text::setFontSize(int fontSize) {
		if (m_fontSize != fontSize) {
			free();
			m_font = TTF_OpenFont(m_fontName.c_str(), fontSize);
		}
	}

	void Text::setColor(SDL_Color col) {
		if (m_color.r == col.r && m_color.g == col.g && m_color.b == col.b && m_color.a == col.a) return;

		m_color = col;
	}

	void Text::render(const std::string& text, int x, int y) {
		m_x = x;
		m_y = y;
		render(text);
	}

	void Text::render(const std::string& text) {

		if (text != m_text || m_color != m_prevColor)
		{
			m_prevColor = m_color;

			SDL_Surface* surf = nullptr;
			surf = TTF_RenderText_Solid(m_font, text.c_str(), m_color);

			if (!surf) {
				fatalError("Unable to create surface from rendered text");
			}

			SDL_Texture* tex = nullptr;
			tex = SDL_CreateTextureFromSurface(Display::renderer, surf);

			if (!tex) {
				fatalError("Unable to create texture from rendered text surface");
			}

			SDL_FreeSurface(surf);

			texture.setSDLTexture(tex);
			m_text = text;
		}

		texture.render(m_x, m_y);
	}
	
	void Text::setFont(const std::string& fontName, int fontSize) {

		if (m_font && (fontName != m_fontName || fontSize != m_fontSize)) {
			free();
			m_fontName = "";
			m_fontSize = 0;
		}

		if (!m_font) {

			m_font = TTF_OpenFont(fontName.c_str(), fontSize);

			if (!m_font) {
				fatalError("Unable to load font " + fontName + " from file");
			}

			m_fontName = fontName;
			m_fontSize = fontSize;
		}
	}

	std::pair<int, int> Text::getTextDims(const std::string & text) {
		std::pair<int, int> dims{ 0, 0 };
		TTF_SizeText(m_font, text.c_str(), &dims.first, &dims.second);
		return dims;
	}

	void Text::free() {

		if (m_font) {
			TTF_CloseFont(m_font);
			m_font = nullptr;
			texture.free();
		}
	}
}