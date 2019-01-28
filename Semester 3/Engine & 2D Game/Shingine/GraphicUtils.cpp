#include "GraphicUtils.h"
#include "Display.h"

namespace Shingine {

	Rectangle::Rectangle() {
	}

	Rectangle::Rectangle(int x, int y, int wid, int hei, glm::ivec4 outlineColor, glm::ivec4 fillColor) {
		m_x = x;
		m_y = y;
		m_width = wid;
		m_height = hei;
		m_outline.r = outlineColor.r; m_outline.b = outlineColor.b; m_outline.g = outlineColor.g; m_outline.a = outlineColor.a;
		m_fill.r = fillColor.r; m_fill.g = fillColor.g; m_fill.b = fillColor.b; m_fill.a = fillColor.a;
	}

	Rectangle::~Rectangle() {
	}

	void Rectangle::init(int x, int y, int wid, int hei, glm::ivec4 outlineColor , glm::ivec4 fillColor) {
		m_x = x;
		m_y = y;
		m_width = wid;
		m_height = hei;
		m_outline.r = outlineColor.r; m_outline.b = outlineColor.b; m_outline.g = outlineColor.g; m_outline.a = outlineColor.a;
		m_fill.r = fillColor.r; m_fill.g = fillColor.g; m_fill.b = fillColor.b; m_fill.a = fillColor.a;
	}

	void Rectangle::render() const {
		SDL_Rect rect = { m_x, m_y, m_width, m_height };

		SDL_BlendMode oldBlendmode;
		SDL_GetRenderDrawBlendMode(Display::renderer, &oldBlendmode);

		SDL_SetRenderDrawBlendMode(Display::renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Display::renderer, m_fill.r, m_fill.g, m_fill.b, m_fill.a);
		SDL_RenderFillRect(Display::renderer, &rect);

		SDL_SetRenderDrawColor(Display::renderer, m_outline.r, m_outline.g, m_outline.b, m_outline.a);
		SDL_RenderDrawRect(Display::renderer, &rect);
		
		SDL_SetRenderDrawBlendMode(Display::renderer, oldBlendmode);
	}

	void Rectangle::render(const glm::ivec2 & pos) {
		SDL_Rect rect = { pos.x, pos.y, m_width, m_height };

		SDL_BlendMode oldBlendmode;
		SDL_GetRenderDrawBlendMode(Display::renderer, &oldBlendmode);

		SDL_SetRenderDrawBlendMode(Display::renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Display::renderer, m_fill.r, m_fill.g, m_fill.b, m_fill.a);
		SDL_RenderFillRect(Display::renderer, &rect);

		SDL_SetRenderDrawColor(Display::renderer, m_outline.r, m_outline.g, m_outline.b, m_outline.a);
		SDL_RenderDrawRect(Display::renderer, &rect);
		
		SDL_SetRenderDrawBlendMode(Display::renderer, SDL_BLENDMODE_NONE);
	}


	namespace Graphics {

		void Shingine::Graphics::drawRect(const glm::ivec4 & dest, glm::ivec4 outline, glm::ivec4 fill) {
			SDL_Rect rect = { dest.x, dest.y, dest.z, dest.w };
			
			SDL_BlendMode oldBlendmode;
			SDL_GetRenderDrawBlendMode(Display::renderer, &oldBlendmode);

			SDL_SetRenderDrawBlendMode(Display::renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(Display::renderer, fill.r, fill.g, fill.b, fill.a);
			SDL_RenderFillRect(Display::renderer, &rect);

			SDL_SetRenderDrawColor(Display::renderer, outline.r, outline.g, outline.b, outline.a);
			SDL_RenderDrawRect(Display::renderer, &rect);
			
			SDL_SetRenderDrawBlendMode(Display::renderer, oldBlendmode);
		}

		void drawLine(const glm::ivec2 & p1, const glm::ivec2 & p2, const glm::ivec4 & color) {
			SDL_BlendMode oldBlendmode;
			SDL_GetRenderDrawBlendMode(Display::renderer, &oldBlendmode);

			SDL_SetRenderDrawBlendMode(Display::renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(Display::renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawLine(Display::renderer, p1.x, p1.y, p2.x, p2.y);
			
			SDL_SetRenderDrawBlendMode(Display::renderer, oldBlendmode);
		}

		void drawPoint(const glm::ivec2 & p, const glm::ivec4 color) {
			SDL_BlendMode oldBlendmode;
			SDL_GetRenderDrawBlendMode(Display::renderer, &oldBlendmode);

			SDL_SetRenderDrawBlendMode(Display::renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(Display::renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawPoint(Display::renderer, p.x, p.y);

			SDL_SetRenderDrawBlendMode(Display::renderer, oldBlendmode);
		}

	}

}