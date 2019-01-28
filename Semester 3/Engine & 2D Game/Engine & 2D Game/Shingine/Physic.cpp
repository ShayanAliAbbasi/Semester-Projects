#include "Physics.h"
#include "Display.h"

#include <SDL/SDL.h>

#include "Errors.h"

namespace Shingine {

	// Some helper functions to convert from pixels to box 2D coordinates and vice versa
	b2Vec2 pixelToWorldCoords(glm::ivec2 pixelCoord);
	b2Vec2 pixelToWorldDims(glm::ivec2 pixelDims);
	glm::ivec2 worldToPixelCoords(b2Vec2 coords);
	glm::ivec2 worldToPixelDims(b2Vec2 dims);
	float pixelToWorldScalar(float scalar);
	float worldToPixelScalar(float scalar);

	// Wrapping box2D's physics world in unique pointer for automatic memory management
	std::unique_ptr<b2World> physicsWorld = nullptr;
	float pixelToMeterScale = 32.0f;

	static constexpr auto DESIRED_FRAMES = 60.0f;

	BoundingBox::BoundingBox() {
	}


	BoundingBox::~BoundingBox() {
	}

	// Initializes bounding box using Box2D
	void BoundingBox::init(int x, int y, int wid, int hei, Type type, float friction, float density,  bool fixedRotation) {

		if (!m_body) {
			// Making a definition for b2Body 
			b2BodyDef bodyDef;
			bodyDef.type = (type == STATIC) ? b2_staticBody : b2_dynamicBody;
			bodyDef.fixedRotation = fixedRotation;
			bodyDef.position.Set(pixelToWorldCoords({ x, y }).x + pixelToWorldDims({ wid, hei }).x, pixelToWorldCoords({ x, y }).y - pixelToWorldDims({ wid, hei }).y);

			m_body = physicsWorld->CreateBody(&bodyDef); // creating a body from body definition

			// Shape of our body
			b2PolygonShape polyShape;
			polyShape.SetAsBox(pixelToWorldDims({ wid, hei }).x, pixelToWorldDims({ wid, hei }).y);//pixelToWorldDims({ wid, hei }).x, pixelToWorldDims({ wid, hei }).y); // setting polygon shape as rectangle

			// Fixture to define behaviour of our body 
			b2FixtureDef fixtureDef;
			fixtureDef.density = (type == STATIC) ? 0.0f : density;
			fixtureDef.friction = friction;
			fixtureDef.shape = &polyShape;

			m_fixture = m_body->CreateFixture(&fixtureDef); // creating a fixture from fixture Definiton

			// Storing dimension of our box so it can be queried later
			m_dims.x = wid;
			m_dims.y = hei;
		}
	}

	void BoundingBox::applyForce(glm::ivec2 force, glm::ivec2 point) {
		if (m_body) {
			m_body->ApplyForce(b2Vec2(pixelToWorldScalar(force.x) * DESIRED_FRAMES, -pixelToWorldScalar(force.y) * DESIRED_FRAMES) , pixelToWorldCoords(point), true);
		}
	}

	void BoundingBox::applyForceToCenter(glm::ivec2 force) {
		if (m_body) {
			m_body->ApplyForceToCenter(b2Vec2(pixelToWorldScalar(force.x) * DESIRED_FRAMES, -pixelToWorldScalar(force.y) * DESIRED_FRAMES), true);
		}
	}

	void BoundingBox::applyImpulse(glm::ivec2 impulse, glm::ivec2 point) {
		if (m_body) {
			m_body->ApplyLinearImpulse(b2Vec2(pixelToWorldScalar(impulse.x) * DESIRED_FRAMES, pixelToWorldScalar(impulse.y) * DESIRED_FRAMES), -pixelToWorldCoords(point), true);
		}
	}

	void BoundingBox::applyImpulseToCenter(glm::ivec2 impulse) {
		if (m_body) {
			m_body->ApplyLinearImpulseToCenter(b2Vec2(pixelToWorldScalar(impulse.x) * DESIRED_FRAMES, -pixelToWorldScalar(impulse.y) * DESIRED_FRAMES), true);
		}
	}

	void BoundingBox::setVelocity(glm::vec2 vel) {
		if (m_body) {
			m_body->SetLinearVelocity(b2Vec2(Shingine::pixelToWorldScalar(vel.x) * DESIRED_FRAMES, Shingine::pixelToWorldScalar(vel.y) * DESIRED_FRAMES));
		}
	}

	void BoundingBox::debugRender(glm::ivec4 color) const {

		if (m_body) {
			SDL_SetRenderDrawColor(Display::renderer, color.r, color.g, color.b, color.a);
			SDL_Rect dest = { getPos().x, getPos().y, getDims().x, getDims().y };
			SDL_RenderFillRect(Display::renderer, &dest);
			SDL_SetRenderDrawColor(Display::renderer, color.r / 255, color.g, color.b, color.a);
			SDL_RenderDrawRect(Display::renderer, &dest);
		}
	}

	bool BoundingBox::isGrounded() const {

		for (b2ContactEdge* ce = m_body->GetContactList(); ce != nullptr; ce = ce->next) {
			b2Contact* c = ce->contact;

			if (c->IsTouching()) {
				
				b2WorldManifold manifold;
				c->GetWorldManifold(&manifold);
				
				for (int i = 0; i < b2_maxManifoldPoints; i++)
					if (manifold.points[i].y < m_body->GetPosition().y - pixelToWorldScalar(getDims().y / 2.0f) + 0.1f)
						return true;
			}
		}

		return false;
	}

	void BoundingBox::remove() {
		if (m_body) {
			physicsWorld->DestroyBody(m_body);
			m_body = nullptr;
			m_fixture = nullptr;
		}
	}
	
	const glm::ivec2 BoundingBox::getPos() const {
		float x = m_body->GetPosition().x - pixelToWorldScalar(m_dims.x) / 2.0f;
		float y = m_body->GetPosition().y + pixelToWorldScalar(m_dims.y) / 2.0f;
		float angleRad = m_body->GetAngle();

		if (m_body)
			return worldToPixelCoords( { x * cos(angleRad) - y * sin(angleRad), x * sin(angleRad) + y * cos(angleRad) } );
	}

	glm::vec2 BoundingBox::getVelocity() const {
		if (m_body)
			return { worldToPixelScalar(m_body->GetLinearVelocity().x / DESIRED_FRAMES),
				   worldToPixelScalar(m_body->GetLinearVelocity().y / DESIRED_FRAMES) };
	}

	float BoundingBox::getAngle() const {		
		if (m_body) {
			return m_body->GetAngle();
		}

		return 0.0f;
	}

	namespace Physics {
		
		void initPhysicsWorld(float gravity) {
			// Create a world only if there is not any
			if (!physicsWorld) {
				physicsWorld = std::make_unique<b2World>(b2Vec2(0.0f, gravity));
			}
		}

		void setWorldToPixelScale(float scale) {
			pixelToMeterScale = scale;
		}

		void updatePhysics(int velocityIterations, int positionIterations) {
			if (physicsWorld)
				physicsWorld->Step(1.0f / DESIRED_FRAMES, velocityIterations, positionIterations);
		}
	}

	float pixelToWorldScalar(float scalar) {
		return scalar / pixelToMeterScale;
	}

	float worldToPixelScalar(float scalar) {
		return scalar * pixelToMeterScale;
	}

	b2Vec2 pixelToWorldCoords(glm::ivec2 pixelCoord) {
		b2Vec2 newCoords = { 0, 0 };

		// Box 2D coordinates have origin at center of screen and y is flipped
		newCoords.x = pixelToWorldScalar(pixelCoord.x - (Display::getWidth() / 2));
		newCoords.y = pixelToWorldScalar((pixelCoord.y - (Display::getHeight() / 2)) * -1);

		return newCoords;
	}

	b2Vec2 pixelToWorldDims(glm::ivec2 pixelDims) {
		return b2Vec2(pixelToWorldScalar(pixelDims.x) / 2.0f, pixelToWorldScalar(pixelDims.y) / 2.0f);
	}

	glm::ivec2 worldToPixelCoords(b2Vec2 coords) {
		glm::ivec2 newCoords = { 0, 0 };

		// Box 2D coordinates have origin at center of screen and y is flipped
		newCoords.x = static_cast<int>(worldToPixelScalar(coords.x) + Display::getWidth() / 2.0f);
		newCoords.y = static_cast<int>((-1 * worldToPixelScalar(coords.y)) + Display::getHeight() / 2.0f);

		return newCoords;
	}

	glm::ivec2 worldToPixelDims(b2Vec2 dims) {
		return glm::ivec2((dims.x * 2) * pixelToMeterScale, (dims.y * 2) * pixelToMeterScale);
	}

}