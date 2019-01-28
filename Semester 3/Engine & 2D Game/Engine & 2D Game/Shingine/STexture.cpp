#include "STexture.h"
#include "Errors.h"

#include <SDL/SDL_image.h>

#include "Display.h"

namespace Shingine {
	
	STexture::STexture(STexture&& other) {

		m_texture = other.m_texture;
		m_width = other.m_width;
		m_height = other.m_height;
	}

	STexture& STexture::operator=(STexture&& other) {

		if (this != &other) {
			m_texture = other.m_texture;
			m_width = other.m_width;
			m_height = other.m_height;
		}

		return *this;
	}

	STexture::STexture(const STexture& other) {

		m_texture = other.m_texture;
		m_width = other.m_width;
		m_height = other.m_height;
	}

	STexture& STexture::operator=(const STexture& other)
	{	
		if (this != &other) {
			m_texture = other.m_texture;
			m_width = other.m_width;
			m_height = other.m_height;

		}

		return *this;
	}
	

	STexture::~STexture() {
		//free();
	}

	void STexture::setImage(const std::string& filePath) {
		
		//free();
		m_texture = IMG_LoadTexture(Display::renderer, filePath.c_str());

		if (!m_texture) {
			fatalError("Unable to create texture form surface" + std::string(SDL_GetError()) );
		}

		SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);


	}

	void STexture::render(int x, int y, SDL_Rect* clip, double rotate,
						  SDL_Point* center, SDL_RendererFlip flip) {

		SDL_Rect dest = { x, y, m_width, m_height };
		
		if (clip) {
			dest.w = clip->w;
			dest.h = clip->h;
		}

		if (m_texture) {
			SDL_RenderCopyEx(Display::renderer, m_texture, clip, &dest, rotate, center, flip);
		}

	}

	void STexture::render(SDL_Rect dest, SDL_Rect* clip, double rotate,
		SDL_Point* center, SDL_RendererFlip flip) {

		if (clip) {
			dest.w = clip->w;
			dest.h = clip->h;
		}

		if (m_texture) {
			SDL_RenderCopyEx(Display::renderer, m_texture, clip, &dest, rotate, center, flip);
			SDL_RenderCopyEx(Display::renderer, m_texture, clip, &dest, rotate, center, flip);
		}

	}

	void STexture::setSDLTexture(SDL_Texture * text) {
		free();
		m_texture = text;
		if (m_texture) SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);
	}

	void STexture::free() {
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;
		}

		m_width = 0;
		m_height = 0;
	}
}