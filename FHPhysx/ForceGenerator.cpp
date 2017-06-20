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

		if (collision == -1)
		{
			size_t forceCount = 0;
			for (size_t j = 0; j < m_forceCount; ++j)
				if (m_forces[j]->active == true)
				{
					force += *m_forces[j];
					forceCount++;
				}
			force /= float(forceCount);
		}
		else
		{
			sf::RectangleShape& collider = *(m_collider[collision]);
			sf::Vector2fLines l1(m_physBalls[i]->getPosition(), collider.getPosition()),
				l2(l1.p2 + collider.getPoint(0), l1.p2 + collider.getPoint(1));

			sf::Vector2f intersection = vectorMath::lineIntersection(l1, l2);

			if (vectorMath::magnitude(intersection) < 0.001)
				continue;



			//force = m_physBalls[i]->getPosition() - m_collider[collision]->getPosition();
			force = -1.9f * m_physBalls[i]->getVelocity() / dt;
		}

		m_physBalls[i]->addImpulse(force * dt);
	}
}
