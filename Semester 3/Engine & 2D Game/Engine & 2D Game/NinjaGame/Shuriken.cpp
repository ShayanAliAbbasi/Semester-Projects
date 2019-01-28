#include "Shuriken.h"
#include "Agent.h"

#include <Shingine/ResourceManager.h>

Shuriken::Shuriken() {
}

Shuriken::Shuriken(const glm::ivec4 & destRect, const glm::ivec2 & acceleration, const std::string & texturePath, bool loadCached) {
	init(destRect, acceleration, texturePath, loadCached);
}


Shuriken::~Shuriken() {
	m_tex.free();
}

void Shuriken::init(const glm::ivec4& destRect, const glm::ivec2& acceleration, const std::string& texturePath, bool loadCached) {
	m_pos.x = destRect.x;
	m_pos.y = destRect.y;
	m_dims.x = destRect.z;
	m_dims.y = destRect.w;

	m_acc = acceleration;

	m_origPos = m_pos;
	m_tex = Shingine::ResourceManager::getTextureFromFile(texturePath, loadCached);
}

void Shuriken::render(Shingine::Camera1D* camera) {
	
	static int count = 0;
	
	m_tex.render({ m_pos.x + camera->getTranslation(), m_pos.y, m_dims.x, m_dims.y }, NULL, count );

	count = (count + 6) % 361;
}

void Shuriken::update() {

	if (m_destroyed) return;
	m_vel += m_acc;
	m_pos += m_vel;

	if (abs(m_vel.x) >= 5)
		m_vel.x = (m_acc.x < 0) ? -5 : 5;
	
	constexpr auto SCREEN_WIDTH = 1024;

	if (abs(m_origPos.x - m_pos.x) > SCREEN_WIDTH) {
		m_destroyed = true;
	};

}

bool Shuriken::collides(Agent* agent) {

	if (!m_destroyed)
		if (abs((m_pos.x + m_dims.x / 2) - (agent->getPos().x + agent->getDims().x / 2)) <= m_dims.x / 2 + agent->getDims().x / 2
			&& abs((m_pos.y + m_dims.y / 2) - (agent->getPos().y + agent->getDims().y / 2)) <= m_dims.y / 2 + agent->getDims().y / 2)
			return true;

	return false;
}
