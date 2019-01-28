#pragma once

#include "STexture.h"
#include <vector>
#include <SDL\SDL.h>

namespace Shingine {
    
	class TileSheet {

	public:

		TileSheet();

		// Initialize tile sheet with sprite (texture) with max frames on x and y
		void init(const std::string& tilePath, int fWidth, int fHeight, bool loadCached = true);

		// Draw a sprite from sprite sheet at given x and y with additional arguments
		void render(int index, int x, int y, double rotation = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
		// Free owned texture
		void free() { texture.free(); };

		STexture texture;
		
		SDL_Rect getClip(int index);
	private:

		int fw;
		int fh;

    };
}