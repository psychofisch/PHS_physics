#pragma once

#include <SFML\System.hpp>

class GameVec : public sf::Vector2f
{
public:
	GameVec();
	GameVec(sf::Vector2f v);
	GameVec(float x, float y);

	bool active;
};

