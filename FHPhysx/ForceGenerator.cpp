#include "ForceGenerator.h"



ForceGenerator::ForceGenerator()
	:m_physBallCount(0),
	m_forceCount(0),
	m_colliderCount(0)
{
	m_physBalls = new PhysBall*[128];
	m_forces = new Force*[128];
	m_collider = new sf::ConvexShape*[128];
}

ForceGenerator::~ForceGenerator()
{
	delete[] m_physBalls;
	//delete[] m_forces;
}

void ForceGenerator::addPhysBall(PhysBall* ph)
{
	m_physBalls[m_physBallCount++] = ph;
}

void ForceGenerator::addForce(Force* f)
{
	m_forces[m_forceCount++] = f;
}

void ForceGenerator::addCollider(sf::ConvexShape * rs)
{
	m_collider[m_colliderCount++] = rs;
}

sf::Vector2f ForceGenerator::accumulateForces(sf::Vector2f pos)
{
	sf::Vector2f force;
	for (size_t j = 0; j < m_forceCount; ++j)
		if (m_forces[j]->active == true && pos.y > m_forces[j]->yLimit.x && pos.y < m_forces[j]->yLimit.y)
		{
			force += *m_forces[j];
		}

	return force;
}

size_t ForceGenerator::getForces(Force ** & ptr)
{
	ptr = m_forces;
	return m_forceCount;
}

size_t ForceGenerator::getCollider(sf::ConvexShape **& ptr)
{
	ptr = m_collider;
	return m_colliderCount;
}

size_t ForceGenerator::getPhysBalls(PhysBall **& ptr)
{
	ptr = m_physBalls;
	return m_physBallCount;
}

void ForceGenerator::removeForce(Force * f)
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
		//basic forces
		sf::Vector2f force = accumulateForces(m_physBalls[i]->getPosition());

		sf::Vector2f dragForce = -vectorMath::normalize(m_physBalls[i]->getVelocity())*(.1f * vectorMath::magnitude(m_physBalls[i]->getVelocity()) + .1f * powf(vectorMath::magnitude(m_physBalls[i]->getVelocity()), 2));
		force += dragForce;
		//*** bf

		//dynamic physBalls calc
		for (size_t b = 0; b < m_physBallCount; ++b)
		{
			if (i == b)
				continue;
			sf::Vector2f distVec = m_physBalls[i]->getPosition() - m_physBalls[b]->getPosition();
			float dist = vectorMath::magnitude(distVec);
			if (dist < m_physBalls[i]->getRadius() + m_physBalls[b]->getRadius())
			{
				sf::Vector2f normal = vectorMath::normalize(distVec);

				//if (vectorMath::dot(m_physBalls[i]->getVelocity(), m_physBalls[b]->getVelocity()) > 0.f)
				//{
				//	force += vectorMath::magnitude(m_physBalls[b]->getVelocity()) * normal;
				//	//m_physBalls[i]->setPosition(m_physBalls[i]->getPosition() - normal * (m_physBalls[i]->getRadius() + m_physBalls[b]->getRadius())); //TODO: with forces
				//}
				//else
				{
					sf::Vector2f reflection = -(1.f + m_physBalls[i]->bounciness) * vectorMath::dot(m_physBalls[i]->getVelocity(), normal) * normal;
					reflection /= dt;
					force += reflection;
					force += 25.f * normal;
					//m_physBalls[i]->setPosition(m_physBalls[b]->getPosition() + normal * (m_physBalls[i]->getRadius() + m_physBalls[b]->getRadius())); //TODO: with forces
				}
				//break;
			}
		}
		//*** dpc

		//static collider calcs
		int collision = -1;
		for (size_t c = 0; c < m_colliderCount; ++c)
		{
			if (m_physBalls[i]->getGlobalBounds().intersects(m_collider[c]->getGlobalBounds()))
			{
				sf::ConvexShape& collider = *m_collider[c];
				sf::Vector2f colliderPos = m_collider[c]->getPosition();
				float colliderRot = m_collider[c]->getRotation();

				size_t signCount = 0;
				for (int p = 0; p < collider.getPointCount(); ++p)
				{
					sf::Vector2f p1 = colliderPos + vectorMath::rotateD(collider.getPoint(p), colliderRot),
						p2;

					if (p < collider.getPointCount() - 1)
						p2 = colliderPos + vectorMath::rotateD(collider.getPoint(p + 1), colliderRot);
					else
						p2 = colliderPos + vectorMath::rotateD(collider.getPoint(0), colliderRot);

					sf::Vector2f closestPoint = m_physBalls[i]->getPosition() + vectorMath::normalize(m_physBalls[i]->getVelocity()) * m_physBalls[i]->getRadius();
					float sign = vectorMath::sign(closestPoint, p1, p2);

					if (sign > 0.f)
					{
						++signCount;
					}
				}

				if (signCount == collider.getPointCount())
				{
					collision = c;
					break;
				}
			}
		}

		if (collision != -1)
		{
			sf::ConvexShape& collider = *(m_collider[collision]);
			//collider.setFillColor(sf::Color::Red);
			sf::Vector2f colliderPos = collider.getPosition();
			float colliderRot = collider.getRotation();
			sf::Vector2fLines l1(m_physBalls[i]->getPosition(), m_physBalls[i]->getPosition() + m_physBalls[i]->getVelocity() * 2.0f),
				l2;

			sf::Vector2f intersection;
			
			int collisionIndex = -1;
			for (int p = 0; p < collider.getPointCount(); ++p)
			{
				l2.p1 = colliderPos + vectorMath::rotateD(collider.getPoint(p), colliderRot);

				if(p < collider.getPointCount() - 1)
					l2.p2 = colliderPos + vectorMath::rotateD(collider.getPoint(p + 1), colliderRot);
				else
					l2.p2 = colliderPos + vectorMath::rotateD(collider.getPoint(0), colliderRot);

				intersection = vectorMath::lineIntersection(l1, l2);
				
				if (vectorMath::magnitude(l1.p1 - intersection) < m_physBalls[i]->getRadius())
				{
					collisionIndex = p;
					break;
				}
			}

			if (collisionIndex >= 0)
			{
				if (m_physBalls[i]->getVelocity().y < 1.f)
					m_physBalls[i]->mode = PhysBall::MODE_KINEMATIC;
				else
					m_physBalls[i]->mode = PhysBall::MODE_FREEFALL;

				sf::Vector2f normal = vectorMath::rotateD(vectorMath::normalize(intersection - (colliderPos + vectorMath::rotateD(collider.getPoint(collisionIndex), colliderRot))), -90.f);

				sf::Vector2f reflection = -(1.f + m_physBalls[i]->bounciness) * vectorMath::dot(m_physBalls[i]->getVelocity(), normal) * normal;
				reflection /= dt;
				force += reflection;

				force += 25.f * normal;

				sf::Vector2f friction = m_physBalls[i]->getVelocity() * .1f / dt;
				force -= friction;
				
				//m_physBalls[i]->setPosition(intersection + vectorMath::normalize(normal) * m_physBalls[i]->getRadius());//TODO: with forces

				/*if (vectorMath::magnitude(m_physBalls[i]->getVelocity()) < 0.1f)
					m_physBalls[i]->addImpulse(-m_physBalls[i]->getVelocity() / dt);*/
			}
		}
		else
			m_physBalls[i]->mode = PhysBall::MODE_FREEFALL;
		//*** scc

		m_physBalls[i]->addImpulse(force * dt);
	}
}

Force::Force()
	:Force(0.f,0.f)
{
}

Force::Force(float x, float y)
	: yLimit(-HUGE_VALF, HUGE_VALF),
	GameVec(x, y)
{
}

Force::~Force()
{
}
