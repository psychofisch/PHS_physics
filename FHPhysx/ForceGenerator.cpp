#include "ForceGenerator.h"



ForceGenerator::ForceGenerator()
	:m_physBallCount(0),
	m_forceCount(0),
	m_colliderCount(0)
{
	m_physBalls = new PhysBall*[128];
	m_forces = new GameVec*[128];
	m_collider = new sf::RectangleShape*[128];
}

ForceGenerator::~ForceGenerator()
{
	delete[] m_physBalls;
	delete[] m_forces;
}

void ForceGenerator::addPhysBall(PhysBall* ph)
{
	m_physBalls[m_physBallCount++] = ph;
}

void ForceGenerator::addForce(GameVec* f)
{
	m_forces[m_forceCount++] = f;
}

void ForceGenerator::addCollider(sf::RectangleShape * rs)
{
	m_collider[m_colliderCount++] = rs;
}

size_t ForceGenerator::getForces(GameVec ** & ptr)
{
	ptr = m_forces;
	return m_forceCount;
}

void ForceGenerator::removeForce(GameVec * f)
{
	for (size_t j = 0; j < m_forceCount; ++j)
	{
		if (m_forces[j] == f)
		{
			m_forces[j] = m_forces[m_forceCount];
			m_forceCount--;
		}
	}
}

void ForceGenerator::update(float dt)
{
	for (size_t i = 0; i < m_physBallCount; ++i)
	{
		sf::Vector2f force;

		int collision = -1;
		for (size_t c = 0; c < m_colliderCount; ++c)
		{
			if (m_physBalls[i]->getGlobalBounds().intersects(m_collider[c]->getGlobalBounds()))
			{
				collision = c;
				break;
			}
		}

		
		size_t forceCount = 0;
		for (size_t j = 0; j < m_forceCount; ++j)
			if (m_forces[j]->active == true)
			{
				force += *m_forces[j];
				forceCount++;
			}

		force /= ((forceCount > 0)? float(forceCount) : 1.0f);

		if (collision != -1)
		{
			sf::RectangleShape& collider = *(m_collider[collision]);
			sf::Vector2f colliderPos = collider.getPosition();
			float colliderRot = collider.getRotation();
			sf::Vector2fLines l1(m_physBalls[i]->getPosition(), colliderPos + vectorMath::rotateD((0.5f * collider.getSize()), colliderRot)),
				l2;

			sf::Vector2f intersection;
			
			int collisionIndex = -1;
			for (int p = 0; p < 4; ++p)
			{
				l2.p1 = colliderPos + vectorMath::rotateD(collider.getPoint(p), colliderRot);

				if(p < 3)
					l2.p2 = colliderPos + vectorMath::rotateD(collider.getPoint(p + 1), colliderRot);
				else
					l2.p2 = colliderPos + vectorMath::rotateD(collider.getPoint(0), colliderRot);

				intersection = vectorMath::lineIntersection(l1, l2);
				
				if (vectorMath::magnitude(l1.p1 - intersection) < 100.0f)
				{
					collisionIndex = p;
					break;
				}
			}

			if(collisionIndex >= 0)
			//force = m_physBalls[i]->getPosition() - m_collider[collision]->getPosition();
				force = -1.9f * m_physBalls[i]->getVelocity() / dt;
		}

		m_physBalls[i]->addImpulse(force * dt);
	}
}
