#pragma once

#include <SDL/SDL.h>
#include <glm/glm.hpp>

// Simple graphics utilities

namespace Shingine {

	class Rectangle {
	public:

		Rectangle();
		Rectangle(int x, int y, int wid, int hei,
			glm::ivec4 outlineColor = { 1, 255, 255, 255 },
			glm::ivec4 fillColor = { 255, 255, 255, 255 });
		~Rectangle();

		// Initialze rectangle with values in case default contructor was used
		void init(int x, int y, int wid, int hei,
			glm::ivec4 outlineColor = { 1, 255, 255, 255 },
			glm::ivec4 fillColor = { 255, 255, 255, 255 });

		// Renders rectangle on screen
		void render() const;
		// Render rectangle on screen with specified position
		void render(const glm::ivec2& pos);

		// Setters
		void setPos(const glm::ivec2& pos) { m_x = pos.x; m_y = pos.y; }
		void setDims(const glm::ivec2& dims) { m_width = dims.x; m_height = dims.y; }
		void setOutline(const glm::ivec4& color) {	m_outline.r = color.r; m_outline.b = color.b; m_outline.g = color.g; m_outline.a = color.a; }
		void setFill(const glm::ivec4& color) { m_fill.r = color.r; m_fill.g = color.g; m_fill.b = color.b; m_fill.a = color.a; }

		// Getters
		glm::ivec2 getPos() const { return glm::ivec2(m_x, m_y); }
		glm::ivec2 getDims() const { return glm::ivec2(m_width, m_height); }
		glm::ivec4 getOutlineColor() const { glm::ivec4(m_outline.r, m_outline.g, m_outline.b, m_outline.a); }
		glm::ivec4 getFillColor() const { glm::ivec4(m_fill.r, m_fill.g, m_fill.b, m_fill.a); }

	private:

		int m_x = 0, m_y = 0;
		int m_width = 0, m_height = 0;
		SDL_Color m_outline = { 255, 255, 255, 255 };
		SDL_Color m_fill = { 255, 255, 255, 255 };
	};

	namespace Graphics {

		void drawRect(const glm::ivec4& dest, glm::ivec4 outline, glm::ivec4 fill);
		void drawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::ivec4& color);
		void drawPoint(const glm::ivec2& p, const glm::ivec4 color);

	}
}