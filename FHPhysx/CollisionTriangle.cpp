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

	m_sbv.setPosition(pos + m_sbvCenter);
	
	sf::FloatRect globalBounds = this->getGlobalBounds();
	m_aabb.setPosition(sf::Vector2f(globalBounds.left, globalBounds.top));
	
	m_obb.setPosition(pos + m_obbOrigin - m_centroid);
}

void CollisionTriangle::init(float size, int seed)
{
	std::random_device rng;
	std::mt19937 urng(rng());
	urng.seed(0);
	std::uniform_real_distribution<> zeroToOne(0, 1);
	//random number between 0 and 1: zeroToOne(urng)

	this->setFillColor(TRIANGLE_BASE_COLOR);
	m_baseColor = TRIANGLE_BASE_COLOR;
	this->setPointCount(3);

	//RNGesus rng;
	//rng.seed(seed);

	sf::Vector2f* points = new sf::Vector2f[3];
	points[0] = sf::Vector2f(0, 0);
	points[1] = sf::Vector2f(size, 0);
	points[2] = sf::Vector2f(size * 0.5f, size);

	m_centroid = sf::Vector2f(0, 0);
	for (int i = 0; i < 3; ++i)
	{
		//float x = rng.GetZeroToOne() * size;
		//float y = rng.GetZeroToOne() * size;
		float x = zeroToOne(urng) * size;
		float y = zeroToOne(urng) * size;
		points[i] = sf::Vector2f(x, y);
		//this->setPoint(i, points[i]);
		m_centroid += points[i];
	}

	if (vectorMath::sign(points[0], points[1], points[2]) < 0.0f)//fix "clockwise-counterclockwise" issue with OBB
	{
		sf::Vector2f tmp = points[1];
		points[1] = points[2];
		points[2] = tmp;
	}

	for (int i = 0; i < 3; ++i)
	{
		this->setPoint(i, points[i]);
	}

	m_centroid *= 0.3333f;

	this->setOrigin(m_centroid);

	//SBV
	sf::Vector2f longestSide = calcLongestSideAndCoords();
	float sbvRadius = this->m_longestSide * 0.5f;
	m_sbv.setFillColor(sf::Color::Transparent);
	m_sbv.setOutlineColor(TRIANGLE_COLLIDER_COLOR);
	m_sbv.setOutlineThickness(.5f);
	m_sbv.setRadius(sbvRadius);
	m_sbv.setOrigin(sf::Vector2f(sbvRadius, sbvRadius) + m_centroid);
	//*** sbv

	//AABB
	sf::FloatRect globalBounds = this->getGlobalBounds();
	m_aabb.setFillColor(sf::Color::Transparent);
	m_aabb.setOutlineColor(TRIANGLE_COLLIDER_COLOR);
	m_aabb.setOutlineThickness(.5f);
	m_aabb.setSize(sf::Vector2f(globalBounds.width, globalBounds.height));
	m_aabb.setPosition(sf::Vector2f(globalBounds.left, globalBounds.top));
	//*** aabb
	
	//OBB
	m_obb.setFillColor(sf::Color::Transparent);
	m_obb.setOutlineColor(TRIANGLE_COLLIDER_COLOR);
	m_obb.setOutlineThickness(.5f);
	m_obb.setSize(sf::Vector2f(-this->m_longestSide, m_obbHeight));
	m_obb.setRotation(vectorMath::angleD(longestSide));
	//*** obb
}

sf::Vector2f CollisionTriangle::getCentroid() const
{
	return m_centroid;
}

sf::Vector2f CollisionTriangle::getLongestSideCenter() const
{
	return m_longestSideCenter + this->getPosition() - this->getOrigin();
}

sf::Vector2f CollisionTriangle::getSBVCenter() const
{
	return m_sbvCenter + this->getPosition() - this->getOrigin();
}

sf::Vector2f CollisionTriangle::calcLongestSideAndCoords()
{
	sf::Vector2f t = this->getPoint(0) - this->getPoint(2);
	sf::Vector2f u = this->getPoint(2) - this->getPoint(1);
	sf::Vector2f s = this->getPoint(1) - this->getPoint(0);

	sf::Vector2f* longest = &t;

	float tl = vectorMath::magnitude(t);
	float ul = vectorMath::magnitude(u);
	float sl = vectorMath::magnitude(s);

	if (vectorMath::magnitude(*longest) < ul)
		longest = &u;

	if (vectorMath::magnitude(*longest) < sl)
		longest = &s;

	sf::Vector2f tmpVec;
	float height = sqrtf(2 * (
		vectorMath::pow2(tl)*vectorMath::pow2(ul) +
		vectorMath::pow2(ul)*vectorMath::pow2(sl) +
		vectorMath::pow2(sl)*vectorMath::pow2(tl)
		) - (
			powf(tl, 4) + powf(ul, 4) + powf(sl, 4)
			));
	if (longest == &t)
	{
		m_longestSideCenter = this->getPoint(2) + t * 0.5f;

		tmpVec = m_longestSideCenter - this->getPoint(1);
		height /= (2 * tl);
		m_obbOrigin = this->getPoint(0);
	}
	else if (longest == &u)
	{
		m_longestSideCenter = this->getPoint(1) + u * 0.5f;

		tmpVec = m_longestSideCenter - this->getPoint(0);
		height /= (2 * ul);
		m_obbOrigin = this->getPoint(2);
	}
	else if (longest == &s)
	{
		m_longestSideCenter = this->getPoint(0) + s * 0.5f;

		tmpVec = m_longestSideCenter - this->getPoint(2);
		height /= (2 * sl);
		m_obbOrigin = this->getPoint(1);
	}

	m_sbvCenter = m_longestSideCenter;

	if (vectorMath::magnitude(tmpVec) > (vectorMath::magnitude(*longest) * 0.5f))
	{
		float diff = (vectorMath::magnitude(tmpVec) - (vectorMath::magnitude(*longest) * 0.5f)) / vectorMath::magnitude(tmpVec);
		m_sbvCenter -= (tmpVec * diff);
		m_longestSide *= 1.0f + diff * 0.5f;
	}

	m_longestSide = vectorMath::magnitude(*longest);
	m_obbHeight = abs(height);

	return *longest;
}

float CollisionTriangle::getLongestSide() const
{
	return m_longestSide;
}

void CollisionTriangle::isHit(bool hit)
{
	if (hit)
		this->setFillColor(TRIANGLE_HIT_COLOR);
	else
		//this->setFillColor(TRIANGLE_BASE_COLOR);
		this->setFillColor(m_baseColor);
}

sf::CircleShape & CollisionTriangle::getSBVShape()
{
	return m_sbv;
}

sf::RectangleShape & CollisionTriangle::getAABBShape()
{
	return m_aabb;
}

sf::RectangleShape & CollisionTriangle::getOBBShape()
{
	return m_obb;
}
