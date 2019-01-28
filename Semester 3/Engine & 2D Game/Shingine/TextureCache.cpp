#include "TextureCache.h"

#include "Display.h"

#include <SDL/SDL.h>
#include <SDL/SDl_image.h>
#include <SDL/SDL_ttf.h>

namespace Shingine {

	TextureCache::TextureCache() {
	}

	TextureCache::~TextureCache() {
		clear();
	}

	STexture TextureCache::getTextureFromFile(const std::string& texturePath, bool loadCached) {

		//lookup the texture and see if its in the map
		auto mit = m_textureMap.find(texturePath);

		if (mit != m_textureMap.end() && loadCached)
			return mit->second;

		STexture newTexture;

		newTexture.setImage(texturePath);

		if(loadCached)
			m_textureMap.insert(make_pair(texturePath, newTexture));

		return newTexture;
	}

	void TextureCache::add(const std::string & texturePath, STexture texture) {
		m_textureMap.insert(std::make_pair(texturePath, texture));
	}

	void TextureCache::remove(const std::string & texturePath) {
		auto it = m_textureMap.find(texturePath);

		if (it != m_textureMap.end()) {
			(it->second).free();
			m_textureMap.erase(it);
		}
	}

	void TextureCache::clear() {
		for (auto& pair : m_textureMap) {
			pair.second.free();
		}

		m_textureMap.clear();
	}

}
