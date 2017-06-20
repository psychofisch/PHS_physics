#pragma once

#include <SFML\Graphics.hpp>

#include "vector2math.h"

class PhysBall : public sf::CircleShape
{
public:
	PhysBall();
	~PhysBall();

	void update(float dt);
	sf::Vector2f getVelocity();
	void addImpulse(sf::Vector2f acceleration);

	float mass;

//private:
	sf::Vector2f m_velocity;
};

