#pragma once
#include <SFML/System/Vector2.hpp>

enum Side
{
	Left, Right
};

class HullPoint : public sf::Vector2f	
{
public:
	HullPoint::HullPoint(const sf::Vector2f& copy, const sf::Vector2f& a, const sf::Vector2f& b);

	float GetDistance() const;
	Side GetSide() const;

protected:
	Side side_;
	float distance_;
};

