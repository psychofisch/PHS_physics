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

void CollisionTriangle::setPosition(const float posX, const float posY)
{
	setPosition(sf::Vector2f(posX, posY));
}

void CollisionTriangle::setPosition(const sf::Vector2f& pos)
{
	ConvexShape::setPosition(pos);

	m_sbv.setPosition(pos);
	m_aabb.setPosition(pos);
}

void CollisionTriangle::init(float size, int seed)
{
	this->setFillColor(TRIANGLE_BASE_COLOR);

	this->setPointCount(3);

	RNGesus rng;
	rng.seed(seed);

	sf::Vector2f* points = new sf::Vector2f[3];
	points[0] = sf::Vector2f(0, 0);
	points[1] = sf::Vector2f(size, 0);
	points[2] = sf::Vector2f(size * 0.5f, size);

	m_centroid = sf::Vector2f(0,0);
	for (int i = 0; i < 3; ++i)
	{
		float x = rng.GetZeroToOne() * size;
		float y = rng.GetZeroToOne() * size;
		points[i] = sf::Vector2f(x, y);
		this->setPoint(i, points[i]);
		m_centroid += points[i];
	}

	m_centroid *= 0.3333f;
	//m_centroid /= 3.f;

	this->setOrigin(m_centroid);

	m_sbv.setFillColor(sf::Color::Transparent);
	m_sbv.setOutlineColor(TRIANGLE_COLLIDER_COLOR);
	m_sbv.setOutlineThickness(1.f);
	m_sbv.setRadius(this->getLongestSide() * 0.5f);
	m_sbv.setOrigin(m_centroid/* + sf::Vector2f(m_sbv.getRadius(), m_sbv.getRadius())*/);

	m_aabb.setFillColor(sf::Color::Transparent);
	m_aabb.setOutlineColor(TRIANGLE_COLLIDER_COLOR);
	m_aabb.setOutlineThickness(1.0f);

	sf::FloatRect globalBounds = this->getGlobalBounds();
	m_aabb.setSize(sf::Vector2f(globalBounds.width, globalBounds.height));
	m_aabb.setOrigin(m_centroid + (sf::Vector2f(globalBounds.width, globalBounds.height) * 0.5f));
	m_aabb.setPosition(sf::Vector2f(globalBounds.left, globalBounds.top));
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

sf::CircleShape & CollisionTriangle::getSBVShape()
{
	return m_sbv;
}

sf::RectangleShape & CollisionTriangle::getAABBShape()
{
	return m_aabb;
}
