#pragma once

namespace Shingine {

    ///Calculates FPS and also limits FPS
    class FpsLimiter {
    public:
        FpsLimiter();

        // Initializes the FPS limiter. For now, this is
        // analogous to setMaxFPS
        void init(float maxFPS);

        // Sets the desired max FPS
        void setMaxFPS(float maxFPS);

        void begin();

        // end() will return the current FPS as a float
        float end();
    private:
        // Calculates the current FPS
        void calculateFPS();

        // Variables
        float m_fps;
        float m_maxFPS;
        float m_frameTime;
        unsigned int m_startTicks;
    };

	//Calculate time passed in seconds (like stopwatch)
	class Timer {
	public:

		Timer();

		// Start measuring time
		void start();
		// Pause measuring time
		void pause();
		// Resme it 
		void resume();
		// Retruns time elapsed in seconds
		float getTime();
		// Get elapsed frames
		unsigned int getFrames();
		// Reset every thing
		void reset();
		// To be called at every iteration of game loop to update time
		void update();
		// query whether specified time is passed
		bool passed(float time);
		
	private:
		unsigned int m_start = 0;
		unsigned int m_elapsed = 0;
		unsigned int m_wasted = 0;
		unsigned int m_frameCount = 0;
		bool m_paused = false;
	};

	// stop thread for specified amound of time in seconds
	void pauseGame(float seconds);
}