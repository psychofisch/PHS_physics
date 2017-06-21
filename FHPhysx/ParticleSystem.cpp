#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(size_t numberOfParticles)
	:m_numberOfParticles(numberOfParticles),
	m_particlePos(new GameVec[numberOfParticles]),
	m_particleVel(new sf::Vector2f[numberOfParticles]),
	m_particleTTL(new float[numberOfParticles]),
	m_lifetime(2.f),
	m_activeParticles(0),
	m_pps(1000.f),
	m_tSinceLastSpawn(HUGE_VALF),
	m_angularVelocity(420.f * 2.f),
	m_rotationMode(ROTATION_RIGHT),
	m_spawnVelocity(2.f),
	m_forceCount(0),
	m_active(true)
{
}

ParticleSystem::~ParticleSystem()
{
	delete[] m_particlePos;
	delete[] m_particleVel;
	delete[] m_particleTTL;
}

void ParticleSystem::setParticleShape(sf::CircleShape * p)
{
	m_particleShape = p;
}

void ParticleSystem::setSpawnVelocity(float v)
{
	m_spawnVelocity = v;
}

void ParticleSystem::setPosition(sf::Vector2f p)
{
	m_position = p;
}

void ParticleSystem::setRotation(float r)
{
	m_rotation = r;
}

void ParticleSystem::setAngularVelocity(float a)
{
	m_angularVelocity = a;
}

void ParticleSystem::setRotationMode(RotationMode rm)
{
	m_rotationMode = rm;
}

void ParticleSystem::setSpawnSpeed(float pps)
{
	m_pps = pps;
}

void ParticleSystem::setLifetime(float lt)
{
	m_lifetime = lt;
}

size_t ParticleSystem::getNumberOfParticles()
{
	return m_numberOfParticles;
}

void ParticleSystem::forcesFromForceGen(ForceGenerator & fg)
{
	m_forceCount = fg.getForces(m_forces);
}

size_t ParticleSystem::getActiveParticles()
{
	return m_activeParticles;
}

void ParticleSystem::setActive(bool b)
{
	m_active = b;
}

bool ParticleSystem::isActive()
{
	return m_active;
}

void ParticleSystem::update(float dt)
{
	if (!m_active)
		return;

	//System Calculations
	m_rotation += m_angularVelocity * dt;
	if (m_rotation > 360.f)
		m_rotation = 0.f;
	//*** sc
	
	//Particle Calculations
	if (m_tSinceLastSpawn > 1.f/m_pps)
	{
		for (size_t i = 0; i < m_numberOfParticles; ++i)
		{
			if (!m_particlePos[i].active)
			{
				m_particlePos[i] = m_position;
				m_particlePos[i].active = true;
				m_particleVel[i] = vectorMath::rotateD(sf::Vector2f(1.f, 0), m_rotation * m_rotationMode) * m_spawnVelocity;
				m_particleTTL[i] = m_lifetime;
				m_tSinceLastSpawn = 0.0f;
				break;
			}
		}
	}
	else
		m_tSinceLastSpawn += dt;

	m_activeParticles = 0;
	for (size_t i = 0; i < m_numberOfParticles; ++i)
	{
		if (m_particlePos[i].active)
		{
			m_particleTTL[i] -= dt;
			if (m_particleTTL[i] < 0.f)
			{
				m_particlePos[i].active = false;
				continue;
			}

			m_activeParticles++;

			sf::Vector2f force;
			size_t forceCount = 0;
			for (size_t j = 0; j < m_forceCount; ++j)
				if (m_forces[j]->active == true)
				{
					force += *m_forces[j];
					forceCount++;
				}

			force /= ((forceCount > 0) ? float(forceCount) : 1.0f);

			sf::Vector2f dragForce = -vectorMath::normalize(m_particleVel[i])*(1.f * vectorMath::magnitude(m_particleVel[i]) + 1.f * powf(vectorMath::magnitude(m_particleVel[i]), 2));
			force += dragForce;

			m_particleVel[i] += force * dt;
			m_particlePos[i] += m_particleVel[i];
		}
	}
	//*** pc
}

void ParticleSystem::drawParticles(sf::RenderWindow * w)
{
	for (size_t i = 0; i < m_numberOfParticles; ++i)
	{
		if (m_particlePos[i].active)
		{
			m_particleShape->setPosition(m_particlePos[i]);
			w->draw(*m_particleShape);
		}
	}
}
