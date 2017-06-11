#include "PhysBall.h"



PhysBall::PhysBall()
	:m_velocity(0.f, 0.f)
{
}


PhysBall::~PhysBall()
{
}

void PhysBall::update()
{
	this->setPosition(this->getPosition() + m_velocity);
}

sf::Vector2f PhysBall::getVelocity()
{
	return m_velocity;
}

void PhysBall::addImpulse(sf::Vector2f acceleration)
{
	m_velocity += acceleration;
}
