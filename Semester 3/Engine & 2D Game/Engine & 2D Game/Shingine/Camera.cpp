#include "Camera.h"
#include "Display.h"

namespace Shingine {

	Camera1D::Camera1D() {
	}

	Camera1D::~Camera1D() {
	}

	void Camera1D::init(int startPos, int screenWidth) {
		m_posX = -startPos;
		m_screenWidth = screenWidth;
	}

	bool Camera1D::insideView(int xPos) {
		
		if (abs(getWorldPos() - xPos) < m_screenWidth + m_offset) {
			return true;
		}
		return false;
	}

	void Camera1D::setTranslation(int x, int offset) {
		m_posX = -(x - offset);

		if (offset != m_offset) m_offset = offset;
	}

	void Camera1D::setTranslationOffset(int offset) {
		m_offset = offset;
	}

	int Camera1D::getTranslation() const {
		return m_posX;
	}

	int Camera1D::getTranslationOffset() const {
		return m_offset;
	}

	int Camera1D::getWorldPos() const {
		return -m_posX;
	}
}