#include "TileSheet.h"
#include "ResourceManager.h"

namespace Shingine {
	
	TileSheet::TileSheet()  { /* Empty */ }

	void TileSheet::init(const std::string& tilePath, int fWidth, int fHeight, bool loadCached) {
		
		texture = ResourceManager::getTextureFromFile(tilePath, loadCached);
		fw = fWidth;
		fh = fHeight;
	}

	void TileSheet::render(int index, int x, int y, /* Defaults: */ double rotation, SDL_Point* center, SDL_RendererFlip flip) {
		SDL_Rect clip = getClip(index);

		texture.render(x, y, &clip, rotation, center, flip);

	}

	SDL_Rect TileSheet::getClip(int index) {

		const int& w = texture.getWidth();
		const int& h = texture.getHeight();
		const int& tw = w / fw;
		const int& th = h / fh;

		int xTile = index % fw;
		int yTile = index / fw;

		SDL_Rect clip;
		clip.x = tw * xTile;
		clip.y = th * yTile;
		clip.w = tw;
		clip.h = th;

		return clip;
	}
}