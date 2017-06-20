#pragma once

#include <SFML\Graphics.hpp>

#include "GameVec.h"

class ParticleSystem
{
public:
	ParticleSystem(size_t numberOfParticles);
	~ParticleSystem();

	void setParticleShape(sf::CircleShape* p);
	void setSpawnVelocity(float v);
	void update(float dt);

private:
	sf::CircleShape* m_particleShape;
	GameVec* m_particles;
	float m_spawnVelocity;
	size_t m_numberOfParticles,
		m_activeParticles,
		m_forceCount;
	GameVec** m_forces;
};

