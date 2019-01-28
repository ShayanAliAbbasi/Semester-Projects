#include "Agent.h"



Agent::Agent() {
	m_shurikens.clear();
}

Agent::Agent(const glm::ivec2 & pos, const glm::ivec2 & dims, const std::string & sprite, int numXFrames, int numYFrames, bool loadCached) {
	
	m_shurikens.clear();
	init(pos, dims, sprite, numXFrames, numYFrames, loadCached);
}


Agent::~Agent() {
}

void Agent::init(const glm::ivec2& pos, const glm::ivec2& dims, const std::string& sprite, int numXFrames, int numYFrames, bool loadCached) {

	m_shurikens.clear();

	m_pos = pos;
	m_dims = dims;

	m_animation.reset();
	m_animation.init(sprite, numXFrames, numYFrames, true, loadCached);
	
	m_displayBar = true;
	m_sleeping = false;

	m_totalHealth = 100.0f;
	m_currentHealth = m_totalHealth;

	m_stance = STANDING;
	m_state = NONE;
	m_dir = RIGHT;

	m_box.remove();
	m_box.init(pos.x, pos.y, dims.x / dims.x, dims.y, Shingine::BoundingBox::DYNAMIC, 0.6f, dims.x);

	m_healthBarA.init(pos.x, pos.y - 8, dims.x, 8, { 0, 0, 0, 0}, { 0, 255, 0, 255 });
	m_healthBarB.init(pos.x, pos.y - 8 , dims.x, 8, { 255, 255, 255, 255 }, {0, 0, 0, 0});
}

void Agent::render(Shingine::Camera1D* camera) {
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	
	if (m_state != State::DEAD) {
	
		if (m_dir == LEFT)
			flip = SDL_FLIP_HORIZONTAL;
		else
			flip = SDL_FLIP_NONE;

		if (m_displayBar) {
			m_healthBarA.render(m_healthBarA.getPos() + glm::ivec2(camera->getTranslation(), 0));
			m_healthBarB.render(m_healthBarB.getPos() + glm::ivec2(camera->getTranslation(), 0));
		}
	}
	
	for (auto& s : m_shurikens)
		s.render(camera);

	m_animation.animateAt(m_pos.x + camera->getTranslation(), m_pos.y, 0, NULL, flip);
}

void Agent::inflictDamage(Agent * to, float damage) {
	if (m_state == DEAD) return;
	
	to->m_currentHealth -= damage;
}
