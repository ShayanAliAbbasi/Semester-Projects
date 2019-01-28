#pragma once

#include <map>

#include "STexture.h"

namespace Shingine {

	
    //This caches the textures so that multiple sprites can use the same textures
    class TextureCache
    {
    public:
        TextureCache();
        ~TextureCache();

		STexture getTextureFromFile(const std::string& texturePath, bool loadCached = true);
		void add(const std::string& texturePath, STexture texture);
		void remove(const std::string& texturePath);
		void clear();

    private:
        std::map<std::string, STexture> m_textureMap;
    };

}