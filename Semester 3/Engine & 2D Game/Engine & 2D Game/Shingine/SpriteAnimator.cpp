#include "SpriteAnimator.h"
#include "ResourceManager.h"

namespace Shingine {

	SpriteAnimator::SpriteAnimator()
	{
	}

	SpriteAnimator::~SpriteAnimator()
	{
	}

	SpriteAnimator::SpriteAnimator(const std::string & sprite, int numXFrames, int numYFrames, bool frameBasedAnim, int from, int to, float duration, bool switchDirAfterACycle, bool loadCached)
	{
		init(sprite, numXFrames, numYFrames, frameBasedAnim, loadCached);
		setAnimFrames(from, to, duration);
	}

	void SpriteAnimator::setAnimFrames(int from, int to, float timeOrFrames, bool switchDirAfterACycle) {
		
		if (from == m_from && to == m_to && timeOrFrames) {
			if (timeOrFrames == m_timeToAnimate)
				return;

			m_switchDir = switchDirAfterACycle;
			m_timeToAnimate = timeOrFrames;

			return;
		}

		m_from = from;
		m_to = to;
		m_current = from;
		m_timeToAnimate = timeOrFrames;
		m_startTime = true;
		m_animate = true;
		m_switchDir = switchDirAfterACycle;
	}

	void SpriteAnimator::init(const std::string& sprite, int numXFrames, int numYFrames, bool frameBasedAnim, bool loadCached) {
		m_animTile.init(sprite, numXFrames, numYFrames, loadCached);
		texture = m_animTile.texture;
		m_frameBased = frameBasedAnim;
	}

	void SpriteAnimator::init(TileSheet ts, bool frameBased)
	{
		m_animTile = ts;
		texture = m_animTile.texture;
	}

	void SpriteAnimator::animateAt(int x, int y, double rotate,
		SDL_Point* center, SDL_RendererFlip flip) {

		if (m_startTime) {
			m_timer.reset();
			m_timer.start();
			
			m_startTime = false;
		}

		// only animate when all required parameters are set
		if (m_animate) {

			if (!m_paused) {
				
				if (m_frameBased) {

					m_current = getCurrAnim();

					m_elapsed++;
				}
				else {
					m_elapsed = m_timer.getTime();

					m_current = getCurrAnim();

				}
			}

			m_animTile.render(m_current, x, y, rotate, center, flip);
		}
	}

	void SpriteAnimator::pause() {
		m_timer.pause();
		m_paused = true;
	}

	void SpriteAnimator::resume() {
		m_timer.resume();
		m_paused = false;
	}

	void SpriteAnimator::reset()
	{
		m_timeToAnimate = 0.0f;
		m_elapsed = 0.0f;
		m_from = 0, m_to = 0;
		m_current = 0;
		m_frameBased = false;
		m_startTime = false;
		m_animate = false;
	}

	int SpriteAnimator::getCurrAnim()
	{
		// Our next animation is our current if elpased time is less tham animation time below
		int next = m_current;

		// When we reached limit for animation of current frame
		if (m_elapsed >= m_timeToAnimate) {
			if (!m_frameBased) {
				m_timer.reset();
				m_timer.start();
			}
			m_elapsed = 0.0f;

			// Correcting value of next for reverse animation

			// forward
			if (m_from <= m_to) {
				next = m_current + 1;
				
				if (m_current + 1 > m_to) {
					
					// loop frames in opposite direction if specified
					if (m_switchDir) {
						int temp = m_from;
						m_from = m_to;
						m_to = temp;
					}
					next = m_from;
				}
			}

			// reverse
			else {
				next = m_current - 1;
				
				if (m_current - 1 < m_to) {
					
					// loop frames in opposite direction if specified
					if (m_switchDir) {
						int temp = m_from;
						m_from = m_to;
						m_to = temp;
					}
					next = m_from;
				}
			}
		}

		return next;
	}
}