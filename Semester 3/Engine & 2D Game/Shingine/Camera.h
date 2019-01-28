#pragma once

#include <glm/glm.hpp>

namespace Shingine {
	
	// Simple Camera for 1D scrolling
	class Camera1D
	{
	public:
		Camera1D();
		~Camera1D();

		// Initialze camera with starting x position
		void init(int startPos, int screenWidth);

		// Checks whether an entity is inside screen box bounded by camera
		bool insideView(int xPos);

		// Setters
		void setTranslation(int x, int offset = 0); // Sets position of camera at specific location
		void setTranslationOffset(int offset); // Offsets the camera position by a given value

		// Getters
		int getTranslation() const; // This must be added to every entity in game for scrolling effect while they are drawn
		int getTranslationOffset() const; // This is for getting offset of camera from original position
		int getWorldPos() const; // Returns x position from start to current world location

	private:
		int m_posX = 0;
		int m_offset = 0;
		int m_screenWidth;
	};

}
