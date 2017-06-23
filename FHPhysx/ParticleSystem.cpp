#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(size_t numberOfParticles, ForceGenerator* forceGenPtr)
	:m_numberOfParticles(numberOfParticles),
	m_forceGen(forceGenPtr),
	m_particlePos(new GameVec[numberOfParticles]),
	m_particleVel(new sf::Vector2f[numberOfParticles]),
	m_particleTTL(new float[numberOfParticles]),
	m_lifetime(4.f),
	m_activeParticles(0),
	m_pps(1000.f),
	m_tSinceLastSpawn(HUGE_VALF),
	m_angularVelocity(420.f * 2.f),
	m_rotationMode(ROTATION_RIGHT),
	m_spawnVelocity(2.f),
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

void ParticleSystem::setParticleMass(float m)
{
	m_particleMass = m;
}

size_t ParticleSystem::getNumberOfParticles()
{
	return m_numberOfParticles;
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

			int collide = -1;
			sf::RectangleShape** colliders;
			size_t colliderCount = m_forceGen->getCollider(colliders);

			for (size_t c = 0; c < colliderCount; ++c)
			{
				sf::RectangleShape& collider = *colliders[c];

				sf::Vector2f colliderPos = collider.getPosition();
				float colliderRot = collider.getRotation();

				int inside = 0;
				for (int p = 0; p < 4; ++p)
				{
					sf::Vector2f p1 = colliderPos + vectorMath::rotateD(collider.getPoint(p), colliderRot),
						p2;

					if (p < 3)
						p2 = colliderPos + vectorMath::rotateD(collider.getPoint(p + 1), colliderRot);
					else
						p2 = colliderPos + vectorMath::rotateD(collider.getPoint(0), colliderRot);

					float sign = vectorMath::sign(m_particlePos[i], p1, p2);

					if (sign > 0.f)
					{
						inside++;
					}
				}

				if (inside == 4)
				{
					collide = c;
					break;
				}
			}

			sf::Vector2f force;
			if (collide == -1)
			{
				force = m_forceGen->accumulateForces(m_particlePos[i]);

				sf::Vector2f dragForce = -vectorMath::normalize(m_particleVel[i])*(1.f * vectorMath::magnitude(m_particleVel[i]) + 1.f * powf(vectorMath::magnitude(m_particleVel[i]), 2));
				force += dragForce;
			}
			else
			{
				force = -m_particleVel[i] / dt;
			}

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
