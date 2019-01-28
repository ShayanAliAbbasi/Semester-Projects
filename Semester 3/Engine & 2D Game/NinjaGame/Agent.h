#pragma once

#include <string>

#include <glm/glm.hpp>

#include <Shingine/Physics.h>
#include <Shingine/SpriteAnimator.h>
#include <Shingine/GraphicUtils.h>
#include <Shingine/InputManager.h>
#include <Shingine/Camera.h>

#include "Shuriken.h"

const std::string PUNCH_EFFECT	= "Sounds/gameplay/punch.wav";
const std::string SLASH_EFFECT	= "Sounds/gameplay/slash.wav";
const std::string THROW_EFFECT	= "Sounds/gameplay/throw.wav";
const std::string DEATH_EFFECT  = "Sounds/gameplay/death.wav";

const std::string SHUR_TEXTURE  = "Assets/screen/gameplay/shuriken.png";

constexpr auto SHUR_DIM = 15;
extern int MAX_WORLD_X;

class Agent
{
public:

	enum Stance { STANDING, MOVING, JUMPING, FALLING };
	enum State  { NONE, PUNCHING, SLASHING, THROWING, SHOCKED, DEAD};
	enum Direction { LEFT, RIGHT };

	Agent();
	Agent(const glm::ivec2& pos, const glm::ivec2& dims, const std::string& sprite, int numXFrames, int numYFrames, bool loadCached = true);

	virtual ~Agent();

	virtual void init(const glm::ivec2& pos, const glm::ivec2& dims, const std::string& sprite, int numXFrames, int numYFrames, bool loadCached = true);

	virtual void render(Shingine::Camera1D* camera);

	virtual void update(Shingine::Camera1D* camera, Shingine::InputManager* inputManager = nullptr, Agent* enemy = nullptr, std::vector<Agent*>* enemies = nullptr) = 0;
	
	void inflictDamage(Agent* to, float damage);
	
	// Some getters for member variables	
	float getCurrentHealth() const { return m_currentHealth; }
	float getTotalHealth() const { return m_totalHealth; }
	
	glm::ivec2 getPos() const { return m_pos; }
	glm::ivec2 getDims() const { return m_dims; }

	Stance getStance() const { return m_stance; }
	State getState() const { return m_state; }
	Direction getDir() const { return m_dir; }
	bool sleeping() const { return m_sleeping; }
	
	void setDir(Direction dir) { m_dir = dir; }
	void setStance(Stance stance) { m_stance = stance; }
	void setState(State state) { m_state = state; }
	void sleep(bool flag) { m_sleeping = flag; }

	void displayHealthBar(bool flag) { m_displayBar = flag; };

	Shingine::BoundingBox& getBoundingBox() { return m_box; }
	Shingine::SpriteAnimator& getSpriteAnimator() {return m_animation; }

protected:

	Shingine::BoundingBox m_box;
	Shingine::SpriteAnimator m_animation;

	Shingine::Rectangle m_healthBarA;
	Shingine::Rectangle m_healthBarB;

	bool m_displayBar = true;
	bool m_sleeping = false;

	glm::ivec2 m_pos = { 0, 0 };
	glm::ivec2 m_dims = { 0, 0 };

	float m_shurDamage  = 10.0f;
	float m_punchDamage = 15.0f;
	float m_slashDamage = 25.0f;

	float m_totalHealth = 100.0f;
	float m_currentHealth = m_totalHealth;

	float m_speed = 20;
	float m_maxSpeed = 3;

	Stance m_stance = STANDING;
	State m_state = NONE;
	Direction m_dir = RIGHT;

	std::list<Shuriken> m_shurikens;
};

