#pragma once

#include "STexture.h"

#include <SDL/SDL_ttf.h>
#include <string>

namespace Shingine {

	class Text
	{
	public:
		Text();
		~Text();

		//Move and copy contructors for managing pointer m_font
		Text(Text&& other);
		Text& operator = (Text&& other);
		Text(Text& other);
		Text& operator = (Text& other);

		//Initialze object with a font and its size
		void init(const std::string& fontName, int fontSize);

		//Show specified text on screen at a particular position
		void render(const std::string& text, int x, int y);
		void render(const std::string& text);

		//setters
		void setPos(int x, int y) { m_x = x; m_y = y; }
		void setFontSize(int fontSize);
		void setFont(const std::string& fontName, int fontSize);
		void setColor(SDL_Color col);
		
		//getter
		int getFontHeight() const { return TTF_FontHeight(m_font); }
		std::pair<int, int> getTextDims(const std::string& text);
		TTF_Font* getTTFFont() const { return m_font; }
		//free memory bound by TTF_Font
		void free();

		//Text is basically a texture created from font rather than image
		STexture texture;
	
	private:
		int m_x = 0, m_y = 0;
		SDL_Color m_color = { 255, 255, 255, 255 };
		SDL_Color m_prevColor = { 255, 255, 255, 255 };
		int m_fontSize = 0;
		std::string m_fontName = "";
		std::string m_text = "";
		TTF_Font* m_font = nullptr; // Must be freed manually using free() member function
	};

}