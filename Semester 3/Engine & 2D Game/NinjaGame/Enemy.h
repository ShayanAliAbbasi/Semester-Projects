#pragma once

#include "Agent.h"

class Enemy : public Agent
{
public:
	Enemy();
	Enemy(const glm::ivec2& pos, const glm::ivec2& dims, const std::string& sprite, int numXFrames, int numYFrames, bool loadCached = true);

	~Enemy();

	virtual void update(Shingine::Camera1D* camera, Shingine::InputManager* inputManager, Agent* enemy = nullptr, std::vector<Agent*>* enemies = nullptr) override;

private:
	enum Type { RANGED, NOTRANGED, BOTH } m_type;
	int m_numShurikens = 25;
	bool m_wasShocked = false;
	bool m_hasBox = true;
};

