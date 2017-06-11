#pragma once

#include <SFML\Graphics.hpp>

#include "vector2math.h"

class PhysBall : public sf::CircleShape
{
public:
	PhysBall();
	~PhysBall();

	void update();
	sf::Vector2f getVelocity();
	void addImpulse(sf::Vector2f acceleration);

private:
	sf::Vector2f m_velocity;
};

