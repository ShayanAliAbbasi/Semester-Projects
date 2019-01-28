#pragma once

//#include "Display.h"

#include <string>
#include <SDL/SDL.h>

namespace Shingine {
	
	// This is a wraper class around SDL_Texture

	class STexture
	{
	public:
		STexture() = default;
		~STexture();

		// Move constructors for efficient copying of data
		STexture(STexture&& other);
		STexture& operator = (STexture&& other);
		
		// Copy constructor and assignment
		STexture(const STexture& other);
		STexture& operator = (const STexture& other);

		// Associate an image with this texture
		void setImage(const std::string& filePath);
		void render(int x, int y, SDL_Rect* clip = NULL, double rotate = 0.0,
					SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void render(SDL_Rect dest, SDL_Rect* clip = NULL, double rotate = 0.0,
					SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		// Some setters and getters for manupulating texture
		void setColor(Uint8 r, Uint8 g, Uint8 b) { SDL_SetTextureColorMod(m_texture, r, g, b); }
		void setBlendMode(SDL_BlendMode flags = SDL_BLENDMODE_BLEND) { SDL_SetTextureBlendMode(m_texture, flags); }
		void setAlpha(Uint8 alpha) { SDL_SetTextureAlphaMod(m_texture, alpha); }
		void setSDLTexture(SDL_Texture* text);

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }
		SDL_Texture* getSDLTexture() { return m_texture; };
		
		void setWidth(int width) { m_width = width; }
		void setHeight(int height) { m_height = height; }

		void free();

	private:
		int m_width = 0;
		int m_height = 0;
		SDL_Texture* m_texture = nullptr; /// Here we are storing actual texture
	};

}