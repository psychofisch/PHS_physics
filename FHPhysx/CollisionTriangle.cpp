#include "CollisionTriangle.h"



CollisionTriangle::CollisionTriangle(sf::Vector2f * points)
{
}

CollisionTriangle::CollisionTriangle(float size)
{
	this->setRadius(size);
	this->setPointCount(3);
	this->setFillColor(sf::Color(64, 214, 213));
	this->setOrigin(size, size);
}

CollisionTriangle::CollisionTriangle()
	:CollisionTriangle(10.0f)
{
}


CollisionTriangle::~CollisionTriangle()
{
}

void CollisionTriangle::isHit(bool hit)
{
	if (hit)
		this->setFillColor(TRIANGLE_HIT_COLOR);
	else
		this->setFillColor(TRIANGLE_BASE_COLOR);
}
