#pragma once

#include <string>

#include <glm/glm.hpp>

#include <Shingine/Physics.h>
#include <Shingine/STexture.h>
#include <Shingine/Timing.h>
#include <Shingine/Camera.h>

class Agent;

class Shuriken
{
public:
	Shuriken();
	Shuriken(const glm::ivec4& destRect, const glm::ivec2& acceleration, const std::string& texturePath, bool loadCached = true);
	~Shuriken();

	void init(const glm::ivec4& destRect, const glm::ivec2& acceleration, const std::string& texturePath, bool loadCached = true);
	
	void render(Shingine::Camera1D* camera);
	void update();

	bool collides(Agent* agent);
	
	void destroy(bool flag) { m_destroyed = flag; }
	
	bool   destroyed()            const { return m_destroyed; }
	const  glm::ivec2& getPos()   const { return m_pos; }
	const  glm::ivec2& getDims()  const { return m_dims; }
	 
private:
	
	glm::ivec2 m_origPos = glm::ivec2(0);
	glm::ivec2 m_pos = glm::ivec2(0);
	glm::ivec2 m_dims = glm::ivec2(0);
	glm::ivec2 m_vel = glm::ivec2(0);
	glm::ivec2 m_acc = glm::ivec2(0);
	
	bool m_destroyed = false;

	Shingine::STexture m_tex;
};

