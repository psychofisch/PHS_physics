#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(size_t numberOfParticles)
	:m_numberOfParticles(numberOfParticles),
	m_particles(new GameVec[numberOfParticles]),
	m_activeParticles(0),
	m_forces(new GameVec*[128]),
	m_forceCount(0)
{
}

ParticleSystem::~ParticleSystem()
{
	delete[] m_particles;
	delete[] m_forces;
}

void ParticleSystem::setParticleShape(sf::CircleShape * p)
{
	m_particleShape = p;
}

void ParticleSystem::setSpawnVelocity(float v)
{
	m_spawnVelocity = v;
}

void ParticleSystem::update(float dt)
{

}
