#pragma once

#include <SFML\Graphics.hpp>

#include "RNGesus.h"
#include "vector2math.h"

#define TRIANGLE_BASE_COLOR sf::Color(64, 214, 213)
#define TRIANGLE_HIT_COLOR sf::Color(199, 12, 91)
#define TRIANGLE_COLLIDER_COLOR sf::Color(255, 121, 57)

class CollisionTriangle : public sf::ConvexShape
{
public:
	//CollisionTriangle(sf::Vector2f* points);//pointer to array of 3 vec2's
	//CollisionTriangle(float size, int seed);
	CollisionTriangle();
	~CollisionTriangle();

	void setPosition(const float posX, const float posY);
	void setPosition(const sf::Vector2f& pos);

	void init(float size, int seed);
	sf::Vector2f getCentroid();
	float getLongestSide();
	void isHit(bool hit);

	sf::CircleShape& getSBVShape();

private:
	sf::Vector2f m_centroid;
	sf::CircleShape m_sbv;
};

