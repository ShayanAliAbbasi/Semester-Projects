#include "ResourceManager.h"

namespace Shingine {

    TextureCache ResourceManager::m_textureCache;

    STexture ResourceManager::getTextureFromFile(const std::string& texturePath, bool loadCached) {
		return m_textureCache.getTextureFromFile(texturePath, loadCached);
    }

	void ResourceManager::addTexture(const std::string & texturePath, STexture texture) {
		m_textureCache.add(texturePath, texture);
	}

	void ResourceManager::removeTexture(const std::string & texturePath) {
		m_textureCache.remove(texturePath);
	}

	void ResourceManager::clearTextureCache() {
		m_textureCache.clear();
	}

}