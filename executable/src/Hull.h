#pragma once
#include <SFML/System/Vector2.hpp>

class Hull : public sf::Vector2f
{
public:
	Hull();
	Hull(float x, float y);
	Hull(const sf::Vector2f& copy);
	~Hull();

	Hull* InsertNext(const sf::Vector2f& point);
	sf::Vector2f GetPoint() const;

	Hull* Previous;
	Hull* Next;
};

