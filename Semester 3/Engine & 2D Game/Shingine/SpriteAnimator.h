#pragma once

#include "TileSheet.h"
#include "Timing.h"
#include "STexture.h"

namespace Shingine {
	
	class SpriteAnimator
	{
	public:
		SpriteAnimator();
		~SpriteAnimator();
		
		SpriteAnimator(const std::string& sprite, int numXFrames, int numYFrames, bool frameBasedAnim, int from, int to, float duration, bool switchDirAfterACycle = false, bool loadCached = true);

		void init(const std::string& sprite, int numXFrames, int numYFrames, bool frameBasedAnim = false, bool loadCached = true);
		void init(TileSheet ts, bool frameBasedAnim = false);

		// Setters
		void setAnimFrames(int from, int to, float timeOrFrames, bool switchDirAfterACycle = false);
		void setState(bool frameBasedAnim) { m_frameBased = frameBasedAnim; reset(); }
		void setAnimTime(float timeOrFrames) { m_timeToAnimate = timeOrFrames; }
		
		// Getters
		const TileSheet& getTileSheet() const { return m_animTile; }
		int getCurrentFrame() const { return m_current; }

		void animateAt(int x, int y, double rotate = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
		void pause();
		void resume();
		void reset();

		bool paused() const { return m_paused; }
		bool animating() const { return m_animate; }

		STexture texture;

	private:
		TileSheet m_animTile;
		Timer m_timer;

		int getCurrAnim();

		float m_timeToAnimate = 0.0f;
		float m_elapsed = 0.0f;
		int m_from = 0 , m_to = 0;
		int m_current = 0;
		bool m_frameBased = false;
		bool m_startTime = false;
		bool m_animate = false;
		bool m_switchDir = false;
		bool m_paused = false;
	};

}