#include "HullPoint.h"
#include <math.h>

HullPoint::HullPoint(const sf::Vector2f& copy, const sf::Vector2f& a, const sf::Vector2f& b) : sf::Vector2f(copy)
{
	float cross = (b.x - a.x)*(y - a.y) - (b.y - a.y)*(x - a.x);
	side_ = cross < 0 ? Left : Right;
	distance_ = fabsf(cross);
}

float HullPoint::GetDistance() const
{
	return distance_;
}

Side HullPoint::GetSide() const
{
	return side_;
}
