#include "PhysBall.h"



PhysBall::PhysBall()
	:m_velocity(0.f, 0.f),
	mass(1.0f)
{
	sf::CircleShape::setPointCount(8);
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
	m_velocity += acceleration;
}
