#pragma once
#include "TextureCache.h"

#include <string>

namespace Shingine {
	
    class ResourceManager
    {
    
	public:
        static STexture getTextureFromFile(const std::string& texturePath, bool loadCached = true);
		static void addTexture(const std::string& texturePath, STexture texture);
		static void removeTexture(const std::string& texturePath);
		static void clearTextureCache();

    private:
        static TextureCache m_textureCache;
    };

}