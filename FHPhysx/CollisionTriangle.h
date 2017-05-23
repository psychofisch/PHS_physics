#pragma once

#include <SFML\Graphics.hpp>

#define TRIANGLE_BASE_COLOR sf::Color(64, 214, 213)
#define TRIANGLE_HIT_COLOR sf::Color(199, 12, 91)

class CollisionTriangle : public sf::CircleShape
{
public:
	CollisionTriangle(sf::Vector2f* points);//pointer to array of 3 vec2's
	CollisionTriangle(float size);
	CollisionTriangle();
	~CollisionTriangle();

	void isHit(bool hit);

private:
	//sf::CircleShape m_shape;
};

