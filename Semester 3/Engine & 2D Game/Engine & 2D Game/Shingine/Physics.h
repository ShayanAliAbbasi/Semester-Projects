#pragma once

#include <Box2D\Box2D.h>
#include <glm\glm.hpp>

namespace Shingine {
	
	// Physics world in which our entities will lie
	extern std::unique_ptr<b2World> physicsWorld;
	// Box2D Meter to pixels scale
	extern float pixelToMeterScale;
	
	namespace Physics {
		// Called once by game to initialize box 2D physics world
		void initPhysicsWorld(float gravity = -9.8f);

		// Set pixels to meter ratio for world
		void setWorldToPixelScale(float scale);
	
		// Must be called once in gameloop to update entities in physics world
		void updatePhysics(int velocityIterations = 6, int positionIterations = 2);
	}

	// Class to assign Box2D bounding box to our entities for physics
	class BoundingBox
	{
	public:
		enum Type { STATIC, DYNAMIC }; // Types for our bodies

		BoundingBox();
		~BoundingBox();

		// Create a bonding box with given dimensions and position with a type
		void init(int x, int y, int wid, int hei, Type type, float friction = 0.3f, float density = 1.0f, bool fixedRotation = true);

		// Apply force on the entity having this bounding box
		void applyForce(glm::ivec2 force, glm::ivec2 point);
		void applyForceToCenter(glm::ivec2 force);

		void applyImpulse(glm::ivec2 impulse, glm::ivec2 point);
		void applyImpulseToCenter(glm::ivec2 impulse);

		// Set velocity for entity having this bounding box
		void setVelocity(glm::vec2 vel);

		// Renders bounding box for debugging
		void debugRender(glm::ivec4 color = { 255, 255, 255, 255 }) const;

		// Query whether body is on some other entity with bounding box
		bool isGrounded() const;

		// removes bounding box from physics world
		void remove();

		// Getters (conversion from world space to pixel spaces)
		const glm::ivec2 getPos() const;
		const glm::ivec2& getDims() const { return m_dims; }
		glm::vec2 getVelocity() const;
		float getAngle() const;

		b2Body* getB2Body() const { return m_body; }
		b2Fixture* getB2Fixture() const { return m_fixture; }
		
	private:
		b2Body* m_body = nullptr;
		b2Fixture* m_fixture = nullptr;
		glm::ivec2 m_dims = {0, 0};
	};

}
