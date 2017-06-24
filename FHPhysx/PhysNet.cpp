#include "PhysNet.h"

PhysNet::PhysNet(int width, int height, float springLength, float radius, ForceGenerator* forceGenPtr)
	:m_position(sf::Vector2f()),
	m_springLength(springLength),
	m_forceGen(forceGenPtr),
	m_stiffness(.1f)
{
	m_size.x = width;
	m_size.y = height;

	m_nodeVel = new sf::Vector2f[m_size.x * m_size.y];
	m_nodePos = new sf::Vector2f[m_size.x * m_size.y];

	for (size_t y = 0; y < m_size.y; ++y)
	{
		for (size_t x = 0; x < m_size.x; ++x)
		{
			size_t index = x + y * m_size.x;

			m_nodePos[index].x = x * m_springLength;
			m_nodePos[index].y = y * m_springLength;

			m_nodeVel[index] = sf::Vector2f(0.f, 0.f);
		}
	}

	m_nodeShape.setRadius(radius);
	m_nodeShape.setOutlineThickness(0.f);
	m_nodeShape.setOrigin(radius * 0.5f, radius * 0.5f);
}

PhysNet::~PhysNet()
{
	delete[] m_nodePos;
	delete[] m_nodeVel;
}

void PhysNet::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void PhysNet::setRotation(float rot)
{
	m_rotation = rot;

	for (size_t y = 0; y < m_size.y; ++y)
	{
		for (size_t x = 0; x < m_size.x; ++x)
		{
			size_t index = x + y * m_size.x;
			m_nodePos[index] = vectorMath::rotateD(m_nodePos[index], rot);
		}
	}
}

void PhysNet::setStiffness(float s)
{
	m_stiffness = s;
}

void PhysNet::setNodeRadius(float r)
{
	m_nodeShape.setRadius(r);
}

void PhysNet::setNodeColor(sf::Color c)
{
	m_nodeShape.setFillColor(c);
}

void PhysNet::update(float dt)
{
	for (size_t y = 1; y < m_size.y; ++y)
	{
		for (size_t x = 0; x < m_size.x; ++x)
		{
			size_t index = x + y * m_size.x;
			sf::Vector2f force;
			force = m_forceGen->accumulateForces(m_position + m_nodePos[index]);

			if (true || x < m_size.x - 1 && y < m_size.y - 1)
			{
				//sf::Vector2f d = m_nodePos[index] - m_nodePos[x + (y + 1)*m_size.x];
				sf::Vector2f dUp, dDown, dLeft, dRight;
				sf::Vector2f hardLimit, yForce;

				dUp = m_nodePos[index] - m_nodePos[x + (y - 1)*m_size.x];

				if(y < m_size.y - 1)
					dDown = m_nodePos[index] - m_nodePos[x + (y + 1)*m_size.x];

				if(x < m_size.x - 1)
					dRight = m_nodePos[index] - m_nodePos[x + 1 + y*m_size.x];

				if(x > 0)
					dLeft = m_nodePos[index] - m_nodePos[x - 1 + y*m_size.x];

				//if (vectorMath::magnitude(d) > 1.5f * m_springLength)
				//{
				//	hardLimit = -m_nodeVel[index] / dt;
				//}
				//else if (vectorMath::magnitude(d) > m_springLength)
				//{
				//	//d = vectorMath::normalize(d) * m_springLength * 2.0f;
				//	yForce = - m_stiffness * (vectorMath::magnitude(d) - m_springLength) * d;
				//}

				yForce += -m_stiffness * (vectorMath::magnitude(dUp) - m_springLength) * dUp;
				yForce += -m_stiffness * (vectorMath::magnitude(dDown) - m_springLength) * dDown;
				yForce += -m_stiffness * (vectorMath::magnitude(dLeft) - m_springLength) * dLeft;
				yForce += -m_stiffness * (vectorMath::magnitude(dRight) - m_springLength) * dRight;

				force += yForce;
			}

			//dynamic physBalls calc
			PhysBall** physBalls;
			size_t physBallCount = m_forceGen->getPhysBalls(physBalls);
			for (size_t b = 0; b < physBallCount; ++b)
			{
				sf::Vector2f nodePos = m_position + m_nodePos[index];
				sf::Vector2f distVec = nodePos - physBalls[b]->getPosition();
				float dist = vectorMath::magnitude(distVec);
				if (dist < m_nodeShape.getRadius() + physBalls[b]->getRadius())
				{
					force += physBalls[b]->getVelocity() / dt;
					/*sf::Vector2f normal = vectorMath::normalize(distVec);
					sf::Vector2f reflection = -m_nodeVel[index] + m_physBalls[i]->getVelocity() - (1.f + m_physBalls[i]->bounciness) * vectorMath::dot(m_physBalls[i]->getVelocity(), normal) * normal;
					reflection /= dt;
					force += reflection;
					break;*/
				}
			}
			//*** dpc

			m_nodeVel[index] *= 0.95f;
			m_nodeVel[index] += force * dt;
			m_nodePos[index] += m_nodeVel[index];
		}
	}
}

void PhysNet::draw(sf::RenderWindow * wndw)
{
	for (size_t y = 0; y < m_size.y; ++y)
	{
		for (size_t x = 0; x < m_size.x; ++x)
		{
			size_t index = x + y * m_size.x;

			m_nodeShape.setPosition(m_position + m_nodePos[index]);
			wndw->draw(m_nodeShape);
		}
	}
}
