#include "Timing.h"

#include <SDL/SDL.h>

namespace Shingine {

    FpsLimiter::FpsLimiter() {
    }

    void FpsLimiter::init(float maxFPS) {
        setMaxFPS(maxFPS);
    }

    void FpsLimiter::setMaxFPS(float maxFPS) {
        m_maxFPS = maxFPS;
    }

    void FpsLimiter::begin() {
        m_startTicks = SDL_GetTicks();
    }

    float FpsLimiter::end() {
        
		calculateFPS();
        
		float frameTicks = (float)(SDL_GetTicks() - m_startTicks);
        //Limit the FPS to the max FPS
        if (1000.0f / m_maxFPS > frameTicks) {
            SDL_Delay((Uint32)(1000.0f / m_maxFPS - frameTicks));
        }

        return m_fps;
    }

    void FpsLimiter::calculateFPS() {
        // The number of frames to average
        static const int NUM_SAMPLES = 20;
        //Stores all the frametimes for each frame that we will average
        static float frameTimes[NUM_SAMPLES];
        // The current frame we are on
        static int currentFrame = 0;
        // The ticks of the previous frame
        static Uint32 prevTicks = SDL_GetTicks();

        // Ticks for the current frame
        Uint32 currentTicks = SDL_GetTicks();

        // Calculate the number of ticks (ms) for this frame
        m_frameTime = (float)(currentTicks - prevTicks);
        frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

        // Current ticks is now previous ticks
        prevTicks = currentTicks;

        // The number of frames to average
        int count;

        currentFrame++;
        if (currentFrame < NUM_SAMPLES) {
            count = currentFrame;
        } else {
            count = NUM_SAMPLES;
        }

        // Average all the frame times
        float frameTimeAverage = 0;
        for (int i = 0; i < count; i++) {
            frameTimeAverage += frameTimes[i];
        }
        frameTimeAverage /= count;
        // Calculate FPS
        if (frameTimeAverage > 0) {
            m_fps = 1000.0f / frameTimeAverage;
        } else {
            m_fps = 60.0f;
        }
    }

	Timer::Timer() { /* Empty */ }

	void Timer::start() {
		reset();
		m_start = SDL_GetTicks();
	}

	void Timer::pause() {
		if (m_paused)
			return;
		
		m_paused = true;

		m_wasted = SDL_GetTicks() - m_wasted; /// < assigning m_wasted the point (when paused) form which we will start ignoring time
	}

	float Timer::getTime() {

		update();
		m_frameCount--;

		return (m_elapsed - m_start) / 1000.0f;
	}

	unsigned int Timer::getFrames() {
		return m_frameCount;
	}

	void Timer::resume() {
		if (!m_paused)
			return;

		m_paused = false;

		m_wasted = SDL_GetTicks() - m_wasted; /// < calculate wasted time 
	}

	void Timer::reset() {
		m_start = 0;
		m_elapsed = 0;
		m_wasted = 0;
		m_frameCount = 0;
		m_paused = false;
	}

	void Timer::update() {
		if (!m_paused)
		{
			m_elapsed += SDL_GetTicks() - m_elapsed - m_wasted; /// < getting rid of time when timer was paused
			m_frameCount++;
		} 

	}

	bool Timer::passed(float time) {
		return getTime() >= time;
	}
	
	void pauseGame(float seconds) {
		SDL_Delay(Uint32(seconds * 1000));
	}
}