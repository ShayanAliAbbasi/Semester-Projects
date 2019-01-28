#pragma once

#include <SDL/SDL_mixer.h>
#include <string>
#include <map>

namespace Shingine {

    class SoundEffect {
    public:
        friend class AudioEngine;

		// Plays the effect file
        // param loops: If loops == -1, loop forever,
        // otherwise play it loops+1 times 
        void play(int loops = 0);

    private:
        Mix_Chunk* m_chunk = nullptr;
    };

    class Music {
    public:
        friend class AudioEngine;

        // Plays the music file
        // param loops: If loops == -1, loop forever,
        // otherwise play it loops times 
        void play(int loops = 1);

        // Pauses whatever music is currently playing
        static void pause();
        // Stops whatever music is currently playing
        static void stop();
        // Resumes whatever music is currently playing
        static void resume();

    private:
        Mix_Music* m_music = nullptr;
    };

    class AudioEngine {
    public:

        AudioEngine();
        ~AudioEngine();

        void init();
        void destroy();

		// Returns sound effect loaded from sound effect cache
        SoundEffect loadSoundEffect(const std::string& filePath);
		// Returns music loaded from sound effect cache
        Music loadMusic(const std::string& filePath);
		
		// Free sound effect from cache
		void freeSoundEffect(const std::string& filePath);
		// Free music from cache
		void freeMusic(const std::string& filePath);
		
		// Set the volume of music globablly
		// Volume ranges from 0 to 128
		void setMusicVolume(uint8_t vol);
		
		// Set the volume of specific sound effect
		// Volume ranges from 0 to 128
		void setSoundEffectVolume(SoundEffect* soundEffect, uint8_t vol);
		
		// Plays sound effect from a file path
		// Should only be called again when previous sound effect finishes
		static void playSoundEffect(const std::string & filePath, int loop = 0, uint8_t vol = 50);

    private:

        std::map<std::string, Mix_Chunk*> m_effectMap; // Effects cache
        std::map<std::string, Mix_Music*> m_musicMap;  // Music cache

        bool m_isInitialized = false;
    };

}