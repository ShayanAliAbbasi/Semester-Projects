#include "Enemy.h"

#include <random>
#include <ctime>

#include <Shingine/AudioEngine.h>

std::mt19937 randomEngine(static_cast<unsigned int>(time(NULL)));

Enemy::Enemy() {
	
	m_punchDamage = 0.4f;
	m_shurDamage  = 0.8f;
	m_slashDamage = 1.2f;
	
	m_dir = LEFT;

	std::uniform_int_distribution<int> rand(0, 2);
	m_type = static_cast<Type>(rand(randomEngine));
}

Enemy::Enemy(const glm::ivec2 & pos, const glm::ivec2 & dims, const std::string & sprite, int numXFrames, int numYFrames, bool loadCached) : Agent(pos, dims, sprite, numXFrames, numYFrames, loadCached) {

	m_punchDamage = 0.4f;
	m_shurDamage = 0.8f;
	m_slashDamage = 1.2f;

	m_dir = LEFT;

	std::uniform_int_distribution<int> rand(0, 2);
	m_type = static_cast<Type>(rand(randomEngine));
}


Enemy::~Enemy() {

}

void Enemy::update(Shingine::Camera1D * camera, Shingine::InputManager * inputManager, Agent * enemy, std::vector<Agent*>* enemies) {
	
	// Updating position of enemy through its bounding box if it is present
	if (m_hasBox) m_pos = m_box.getPos();

	// Not allowing enemies to leave game world
	if (m_pos.x < 2)
		m_box.applyImpulseToCenter(glm::ivec2(10, 0));
	else if (m_pos.x > MAX_WORLD_X - 2)
		m_box.applyImpulseToCenter(glm::ivec2(-10, 0));

	// Returning from function ( basically not updating enemies) and removing bounding box when enemies die
	if (m_state == DEAD) { 
		if (m_hasBox && m_box.getVelocity() == glm::vec2(0.0f, 0.0f)) {
			m_box.remove(); 
			m_hasBox = false;
		}
		if (!m_shurikens.empty()) m_shurikens.clear();

		return;
	}

	// Getting states of player ( enemy for enemies :-| ) for AI stuff and applying damage etc 
	const glm::ivec2& enemyPos = enemy->getPos() + glm::ivec2(enemy->getDims().x / 2, 0);
	const glm::ivec2& enemyDims = enemy->getDims();

	const State& enemyState = enemy->getState();
	const Stance& enemyStance = enemy->getStance();
	const Direction& enemyDir= enemy->getDir();

	// If enemy(player) is dead just change animation to shocked and change direction after 30 frames
	if (enemyState == DEAD || m_sleeping) {
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


	// Meh... AI based on my own definition of some probability :) and player's state, stance, direction etc
	static std::mt19937 randomEngine(static_cast<unsigned int>(time(NULL)));
	static std::uniform_real_distribution<float> prob(0.0f, 1.0f);
	const float probability = prob(randomEngine);

	// Applying forces to AI players(enemies) depending on location of player and player's state while taking into account probability
	switch (m_type) {
	
	case RANGED: {
		if (m_pos.x < enemyPos.x - 500) {
			m_box.applyForceToCenter(glm::ivec2(m_speed, 0));
		}

		else if (m_pos.x > enemyPos.x + 500) {
			m_box.applyForceToCenter(glm::ivec2(-m_speed, 0));
		}

		else if (abs(m_pos.x - enemyPos.x) < 450 && m_pos.x < enemyPos.x) {
			m_box.applyForceToCenter(glm::ivec2(-m_speed, 0));
		}

		else if (abs(m_pos.x - enemyPos.x) < 450 && m_pos.x > enemyPos.x) {
			m_box.applyForceToCenter(glm::ivec2(m_speed, 0));
		}
		else {
			glm::vec2 vel = m_box.getVelocity();
			vel.x *= 0.90f;
			m_box.setVelocity(vel);
		}

		if (abs(enemyPos.x - m_pos.x) <= 900 && probability <= 0.01f) {
			if (!m_wasShocked) {
				m_state = SHOCKED;
				m_stance = STANDING;
				m_wasShocked = true;
			}
			else if (m_state == NONE && m_stance == STANDING) {
				m_state = THROWING;
				m_shurikens.emplace_back(glm::ivec4(m_pos.x + m_dims.x / 2, m_pos.y + m_dims.y / 4, SHUR_DIM, SHUR_DIM), glm::ivec2(m_dir == LEFT ? -3 : 3, 0), SHUR_TEXTURE, false);
				Shingine::AudioEngine::playSoundEffect(THROW_EFFECT, 0, 10);
			}
		}
	}
		break;
	
	case NOTRANGED:
		if (m_pos.x <= enemyPos.x - 30) {
			m_box.applyForceToCenter(glm::ivec2(m_speed, 0));
		}

		else if (m_pos.x >= enemyPos.x + 30) {
			m_box.applyForceToCenter(glm::ivec2(-m_speed, 0));
		}

		else {
			glm::vec2 vel = m_box.getVelocity();
			vel.x *= 0.90f;
			m_box.setVelocity(vel);
		}

		if (abs(enemyPos.x - m_pos.x) <= 30 && probability <= 0.015f  && m_state == NONE) {
			m_state = PUNCHING;
			m_stance = STANDING;

			Shingine::AudioEngine::playSoundEffect(PUNCH_EFFECT, 0, 10);
			
			if (abs((m_pos.y + m_dims.y / 2) - (enemy->getPos().y + enemy->getDims().y / 2)) <= m_dims.y / 2)
				inflictDamage(enemy, m_punchDamage);
		}

		else if (abs(enemyPos.x - m_pos.x) <= 30 && probability >= 0.90f && probability <= 0.908f && m_state == NONE) {
			m_state = SLASHING;
			m_stance = STANDING;

			Shingine::AudioEngine::playSoundEffect(SLASH_EFFECT, 0, 10);
			
			if (abs((m_pos.y + m_dims.y / 2) - (enemy->getPos().y + enemy->getDims().y / 2)) <= m_dims.y / 2)
				inflictDamage(enemy, m_slashDamage);
		}

		else if (((probability <= 0.2f && enemyState == THROWING) || (probability <= 0.4f &&
			enemyStance == JUMPING) || probability <= 0.0005) && m_box.isGrounded() && m_pos.y + m_dims.y / 2 > enemyPos.y ) {

			m_box.setVelocity(glm::ivec2(m_box.getVelocity().x, 0));
			m_box.applyImpulseToCenter(glm::ivec2(0, -m_speed * 0.75f));
		}

		break;

	case BOTH:
		if (m_pos.x <= enemyPos.x - 30) {
			m_box.applyForceToCenter(glm::ivec2(m_speed, 0));
		}

		else if (m_pos.x >= enemyPos.x + 30) {
			m_box.applyForceToCenter(glm::ivec2(-m_speed, 0));
		}

		else {
			glm::vec2 vel = m_box.getVelocity();
			vel.x *= 0.90f;
			m_box.setVelocity(vel);
		}

		if (( (probability <= 0.1f && enemyStance == JUMPING) || probability <= 0.001) && m_box.isGrounded()) {
			m_box.setVelocity(glm::ivec2(m_box.getVelocity().x, 0));
			m_box.applyImpulseToCenter(glm::ivec2(0, -m_speed * 0.75f));
		}

		if (abs(enemyPos.x - m_pos.x) <= 30 && probability <= 0.015f  && m_state == NONE) {
			m_state = PUNCHING;
			m_stance = STANDING;
 
			Shingine::AudioEngine::playSoundEffect(PUNCH_EFFECT, 0, 10);
			
			if (abs((m_pos.y + m_dims.y / 2) - (enemy->getPos().y + enemy->getDims().y / 2)) <= m_dims.y / 2)
				inflictDamage(enemy, m_punchDamage);
		}

		else if (probability >= 0.5f && probability <= 0.51f && m_state == NONE) {
			m_state = THROWING;
			m_shurikens.emplace_back(glm::ivec4(m_pos.x + m_dims.x / 2, m_pos.y + m_dims.y / 4, SHUR_DIM, SHUR_DIM), glm::ivec2(m_dir == LEFT ? -3 : 3, 0), SHUR_TEXTURE, false);
			Shingine::AudioEngine::playSoundEffect(THROW_EFFECT, 0, 10);
		}

		else if (abs(enemyPos.x - m_pos.x) <= 30 && probability >= 0.90f && probability <= 0.908f && m_state == NONE) {
			m_state = SLASHING;
			m_stance = STANDING;

			Shingine::AudioEngine::playSoundEffect(SLASH_EFFECT, 0, 10);
			
			if (abs((m_pos.y + m_dims.y / 2) - (enemy->getPos().y + enemy->getDims().y / 2)) <= m_dims.y / 2)
				inflictDamage(enemy, m_slashDamage);
		}
		break;

		// This condition intentionally is for all AI players so they don't get stuck to each other
		if (abs(m_box.getVelocity().x) <= 0.3f && abs(m_box.getVelocity().x) >= 0.001f) {
			m_stance = JUMPING;
		}
	}
	
	// Constraining speed of ai players
	if (fabs(m_box.getVelocity().x) > m_maxSpeed) {
		glm::vec2 vel = m_box.getVelocity();
		vel.x = (m_dir == LEFT) ? -m_maxSpeed : m_maxSpeed;
		m_box.setVelocity(vel);
	}

	// Setting states of ai players
	if (m_currentHealth <= 0.0f) {
		m_animation.setAnimFrames(9, 9, 1);
		m_state = DEAD;
		
		Shingine::AudioEngine::playSoundEffect(DEATH_EFFECT, 1, 100);
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

		if (m_box.getVelocity().x < 0.0f)
			m_dir = LEFT;
		else if (m_box.getVelocity().x > 0.0f)
			m_dir = RIGHT;
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
		static bool shurikenThrown = false;
		
		m_animation.setAnimFrames(11, 13, 2.5f);

		if (!shurikenThrown && m_numShurikens) {
			
			shurikenThrown = true;
			m_numShurikens--;
		}
		if (!m_numShurikens) {
			m_type = NOTRANGED;
		}

		count++;
		if (count == 8) {
			m_state = NONE;
			count = 1;
			shurikenThrown = false;
		}
	}
	else if (m_state == SHOCKED) {
		static int count = 1;

		m_animation.setAnimFrames(15, 15, 30.0f);

		count++;
		if (count == 30) {
			m_state = NONE;
			count = 1;
		}
	}
	else if (m_stance == STANDING) {
		m_animation.setAnimFrames(10, 10, 1.0f);
		m_dir = (m_pos.x + (m_dims.x / 2) < enemyPos.x) ? RIGHT : LEFT;
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

		if (s.collides(enemy)) {
			inflictDamage(enemy, m_shurDamage);
			s.destroy(true);
		}

		// If shuriken is destroyed remove it from player's shuriken list
		if (s.destroyed()) {
			it = m_shurikens.erase(it);
		}
		else {
			it++;
		}
	}

	m_healthBarA.setPos(m_pos - glm::ivec2(0, m_healthBarA.getDims().y));
	m_healthBarB.setPos(m_pos - glm::ivec2(0, m_healthBarA.getDims().y));
	m_healthBarA.setDims({ m_healthBarB.getDims().x * (m_currentHealth / m_totalHealth), m_healthBarA.getDims().y });
}
