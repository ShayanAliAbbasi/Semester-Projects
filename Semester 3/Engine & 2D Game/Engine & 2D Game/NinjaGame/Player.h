#pragma once

#include "Agent.h"

#include <Shingine/Timing.h>

class Player : public Agent
{
public:
	Player();
	~Player();
	
	virtual void update(Shingine::Camera1D* camera, Shingine::InputManager* inputManager, Agent* enemy = nullptr, std::vector<Agent*>* enemies = nullptr) override;
};

