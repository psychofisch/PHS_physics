#pragma once

#include <SFML\Graphics.hpp>

#include "GameVec.h"
#include "ForceGenerator.h"

class ParticleSystem
{
public:
	enum RotationMode{ ROTATION_NONE = 0, ROTATION_LEFT = -1, ROTATION_RIGHT = 1 };

	ParticleSystem(size_t numberOfParticles);
	~ParticleSystem();

	void setParticleShape(sf::CircleShape* p);
	void setSpawnVelocity(float v);
	void setPosition(sf::Vector2f p);
	void setRotation(float r);
	void setAngularVelocity(float a);
	void setRotationMode(RotationMode rm);
	void setSpawnSpeed(float pps);
	void setLifetime(float lt);
	size_t getNumberOfParticles();
	void forcesFromForceGen(ForceGenerator& fg);
	size_t getActiveParticles();
	void setActive(bool b);
	bool isActive();

	void update(float dt);
	void drawParticles(sf::RenderWindow* w);

private:
	bool m_active;
	sf::CircleShape* m_particleShape;
	sf::Vector2f m_position;
	GameVec* m_particlePos;
	sf::Vector2f* m_particleVel;
	float* m_particleTTL;
	float m_spawnVelocity,
		m_rotation,
		m_angularVelocity,
		m_pps,
		m_tSinceLastSpawn,
		m_lifetime;
	RotationMode m_rotationMode;
	size_t m_numberOfParticles,
		m_activeParticles,
		m_forceCount;
	GameVec** m_forces;
};

