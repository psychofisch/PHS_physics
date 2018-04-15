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
	void resetToPosition(sf::Vector2f pos);

	//float mass;
	float bounciness;

private:
	sf::Vector2f m_velocity;
};
