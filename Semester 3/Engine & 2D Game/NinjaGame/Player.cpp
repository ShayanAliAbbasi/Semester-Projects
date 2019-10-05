#include "Player.h"
#include "Enemy.h"

#include <Shingine/AudioEngine.h>

Player::Player() {

}


Player::~Player() {
}

void Player::update(Shingine::Camera1D* camera, Shingine::InputManager* inputManager, Agent* enemy, std::vector<Agent*>* enemies) {

	// Updating position of player through its bounding box
	m_pos = m_box.getPos();

	// Not allowing player to leave game world
	if (m_pos.x < 2)
		m_box.applyImpulseToCenter(glm::ivec2(10, 0));

	else if (m_pos.x > MAX_WORLD_X - 2)
		m_box.applyImpulseToCenter(glm::ivec2(-10, 0));

	if (m_state == DEAD) {
		if (!m_shurikens.empty()) m_shurikens.clear();
		return;
	}

	// If all enemies are dead just change animation to shocked and change direction after 30 frames
	if (m_sleeping) {
		m_animation.setAnimFrames(15, 15, 30.0f);

		static int count = 1;
		count++;
		if (count == 30) {
			m_dir = (m_dir == LEFT) ? RIGHT : LEFT;
			count = 1;
		}
		
		if (!m_shurikens.empty()) m_shurikens.clear();

		return;
	}

	// Focusing our 1 dimesional camera on the player to mimic side scrolling
	camera->setTranslation(m_pos.x, static_cast<int>(1024 / 4.0f));

	if (camera->getTranslation() > 0) {
		camera->setTranslation(0);
	}


	// Lambda function to applyDamage to vector of enemies
	static auto applyDamageToEnemies = [&](float damage) {
		
		for (size_t i = 0; i < enemies->size(); i++) {
			
			Enemy* e = dynamic_cast<Enemy*>((*enemies)[i]);
			
			if ( e->getState() != DEAD && abs((m_pos.x + m_dims.x / 2) - e->getPos().x) < 30 && abs((m_pos.y + m_dims.y / 2) - (e->getPos().y + e->getDims().y / 2)) <= m_dims.y / 2 ) {

				inflictDamage(e, damage);
				
				if (!(damage == m_slashDamage))
					return; // Inflict damage to only one enemy
			}
		}
	};

	// Applying forces to player on certain keyPresses
	if (inputManager->isKeyDown(SDLK_RIGHT)) {
		m_box.applyForceToCenter(glm::ivec2(m_speed, 0));
		m_dir = Direction::RIGHT;
	}
	else if (inputManager->isKeyDown(SDLK_LEFT)) {
		m_box.applyForceToCenter(glm::ivec2(-m_speed, 0));
		m_dir = Direction::LEFT;
	}
	else {
		glm::vec2 vel = m_box.getVelocity();
		vel.x *= 0.90f;
		m_box.setVelocity(vel);
	}
	if (inputManager->isKeyPressed(SDLK_UP) && m_box.isGrounded()) {
		m_box.applyImpulseToCenter(glm::ivec2(0, -m_speed * 0.75f));
	}
		
	if (m_state == NONE) {
		if (inputManager->isKeyPressed(SDLK_LCTRL) || inputManager->isKeyPressed(SDLK_RCTRL)) {
			m_state = PUNCHING;
			Shingine::AudioEngine::playSoundEffect(PUNCH_EFFECT, 0, 50);
			applyDamageToEnemies(m_punchDamage);
		}
		else if (inputManager->isKeyPressed(SDLK_LALT) || inputManager->isKeyPressed(SDLK_RALT)) {
			m_state = SLASHING;
			Shingine::AudioEngine::playSoundEffect(SLASH_EFFECT, 0, 50);
			applyDamageToEnemies(m_slashDamage);
		}
		else if (inputManager->isKeyPressed(SDLK_SPACE)) {
			m_state = THROWING;
			m_shurikens.emplace_back(glm::ivec4(m_pos.x + m_dims.x / 2, m_pos.y + m_dims.y / 4, SHUR_DIM, SHUR_DIM), glm::ivec2( m_dir == LEFT ? -3:3,  0), SHUR_TEXTURE, false);
			Shingine::AudioEngine::playSoundEffect(THROW_EFFECT, 0, 50);
		}
	}
	// Constraining speed of player
	if (fabs(m_box.getVelocity().x) > m_maxSpeed) {
		glm::vec2 vel = m_box.getVelocity();
		vel.x = (m_dir == LEFT) ? - m_maxSpeed: m_maxSpeed;
		m_box.setVelocity(vel);
	}

	// Setting states of player
	if (m_currentHealth <= 0.0f) {
		m_animation.setAnimFrames(9, 9, 1);
		m_state = DEAD;
		
		Shingine::AudioEngine::playSoundEffect(DEATH_EFFECT, 0, 128);
		return;
	}

	else if (m_box.getVelocity() == glm::vec2(0.0f, 0.0f)) {
		m_stance = STANDING;
	}
	else if (m_box.getVelocity().y < 0.0f) {
		m_stance = JUMPING;
	}

	else if (m_box.getVelocity().y > 0.0f) {
		m_stance = FALLING;

	}
	else if (fabs(m_box.getVelocity().x) > 0.0f) {
		m_stance = MOVING;
	}

	// Setting different animations && stuff based on different stances, states set above
	if (m_state == PUNCHING) {
		static int count = 1;
		m_animation.setAnimFrames(14, 14, 10.0f);
		
		count++;
		if (count == 10) {
			m_state = NONE;
			count = 1;
		}
	}
	else if (m_state == SLASHING) {
		static int count = 1;
		
		m_animation.setAnimFrames(11, 14, 6.0f);
		
		count++;
		if (count == 18) {
			m_state = NONE;
			count = 1;
		}
	}
	else if (m_state == THROWING) {
		static int count = 1;

		m_animation.setAnimFrames(11, 13, 2.5f);

		count++;
		if (count == 8) {
			m_state = NONE;
			count = 1;
		}
	}
	else if (m_state == SHOCKED) {
		static int count = 1;

		m_animation.setAnimFrames(15, 15, 15.0f);

		count++;
		if (count == 15.0f) {
			m_state = NONE;
			count = 1;
		}
	}
	else if (m_stance == STANDING) {
		m_animation.setAnimFrames(10, 10, 1.0f);
	}
	else if (m_stance == MOVING) {
		m_animation.setAnimFrames(0, 5, abs(m_maxSpeed / m_box.getVelocity().x) * m_maxSpeed);
	}
	else if (m_stance == JUMPING) {
		glm::vec2 vel = m_box.getVelocity();
		vel.x *= 0.98f;
		m_box.setVelocity(vel);
		m_animation.setAnimFrames(6, 6, 1.0f);

	}
	else if (m_stance == FALLING) {
		glm::vec2 vel = m_box.getVelocity();
		vel.x *= 0.98f;
		m_box.setVelocity(vel);
		m_animation.setAnimFrames(7, 7, 1.0f);
	}
	
	// Updating the shurkens thrown by player and removing them from list if necessary
	for (auto it = m_shurikens.begin(); it != m_shurikens.end(); ) {

		Shuriken& s = *it;
		
		// Update shurikens
		s.update();

		// Check for shuriken collision with enemies and apply damage to enemies
	
		for (auto& e : *enemies) {
			if (e->getState() != Agent::DEAD && s.collides(e)) {
				inflictDamage(e, m_shurDamage);
				s.destroy(true);
				break;
			}
		}

		// If shuriken is destroyed remove it from player's shuriken list
		if (s.destroyed()) {
			it = m_shurikens.erase(it);
		}
		else {
			it++;
		}
	}

	// Updating health bar of player based on its health
	m_healthBarA.setPos(m_pos - glm::ivec2(0, m_healthBarA.getDims().y));
	m_healthBarB.setPos(m_pos - glm::ivec2(0, m_healthBarA.getDims().y));
	m_healthBarA.setDims({ m_healthBarB.getDims().x * (m_currentHealth / m_totalHealth), m_healthBarA.getDims().y });
}
