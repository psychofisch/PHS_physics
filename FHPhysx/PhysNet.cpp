#include "PhysNet.h"

PhysNet::PhysNet(int width, int height, float gap, float radius)
	:m_position(sf::Vector2f()),
	m_stiffness(1.f)
{
	m_size.x = width;
	m_size.y = height;

	m_nodePos = new sf::Vector2f[m_size.x * m_size.y];
	for (size_t y = 0; y < m_size.y; ++y)
	{
		for (size_t x = 0; x < m_size.x; ++x)
		{
			size_t index = x + y * m_size.x;

			m_nodePos[index].x = x * gap;
			m_nodePos[index].y = y * gap;
		}
	}

	m_nodeShape.setRadius(radius);
	m_nodeShape.setOutlineThickness(0.f);
	m_nodeShape.setOrigin(radius * 0.5f, radius * 0.5f);
}

PhysNet::~PhysNet()
{
	delete[] m_nodePos;
}

void PhysNet::setPosition(sf::Vector2f pos)
{
	m_position = pos;
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

void PhysNet::forcesFromForceGen(ForceGenerator & fg)
{
	m_forceCount = fg.getForces(m_forces);
}

void PhysNet::update(float dt)
{

}

void PhysNet::draw(sf::RenderWindow * wndw)
{
	for (size_t y = 0; y < m_size.y; ++y)
	{
		for (size_t x = 0; x < m_size.x; ++x)
		{
			size_t index = x + y * m_size.x;

			m_nodeShape.setPosition(m_nodePos[index] + m_position);
			wndw->draw(m_nodeShape);
		}
	}
}
