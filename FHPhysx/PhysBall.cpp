#include "PhysBall.h"



PhysBall::PhysBall()
	:m_velocity(0.f, 0.f),
	//mass(1.0f),
	bounciness(.5f)
{
	sf::CircleShape::setPointCount(16);
}


PhysBall::~PhysBall()
{
}

void PhysBall::update(float dt)
{
	float drag = 0.9999f;
	drag = 0.0f;
	this->setPosition(this->getPosition() + m_velocity);
	m_velocity -= m_velocity * (drag * dt);
}

sf::Vector2f PhysBall::getVelocity()
{
	return m_velocity;
}

void PhysBall::addImpulse(sf::Vector2f acceleration)
{
	m_velocity += acceleration/* / mass*/; //TODO: add mass -> not sure about this one 0o
}

void PhysBall::resetToPosition(sf::Vector2f pos)
{
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
	sf::CircleShape::setPosition(pos);
}
