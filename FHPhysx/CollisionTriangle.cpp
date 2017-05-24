#include "CollisionTriangle.h"



//CollisionTriangle::CollisionTriangle(sf::Vector2f * points)
//{
//}
//
//CollisionTriangle::CollisionTriangle(float size, int seed)
//{
//	
//
//}

CollisionTriangle::CollisionTriangle()
{
}


CollisionTriangle::~CollisionTriangle()
{
}

void CollisionTriangle::init(float size, int seed)
{
	this->setFillColor(sf::Color(64, 214, 213));
	this->setOrigin(size, size);

	this->setPointCount(3);

	RNGesus rng;
	rng.seed(seed);

	sf::Vector2f* points = new sf::Vector2f[3];

	for (int i = 0; i < 3; ++i)
	{
		float x = std::max(rng.GetZeroToOne() * size, 1.0f);
		float y = std::max(rng.GetZeroToOne() * size, 1.0f);
		points[i] = sf::Vector2f(x, y);
		this->setPoint(i, points[i]);
		m_centroid += points[i];
	}

	m_centroid *= 0.3333f;

	this->setOrigin(m_centroid);
}

sf::Vector2f CollisionTriangle::getCentroid()
{
	return m_centroid;
}

float CollisionTriangle::getLongestSide()
{
	sf::Vector2f size = sf::Vector2f(this->getGlobalBounds().width, this->getGlobalBounds().height);
	return vectorMath::max(size);
}

void CollisionTriangle::isHit(bool hit)
{
	if (hit)
		this->setFillColor(TRIANGLE_HIT_COLOR);
	else
		this->setFillColor(TRIANGLE_BASE_COLOR);
}
