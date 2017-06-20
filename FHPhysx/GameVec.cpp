#include "GameVec.h"

GameVec::GameVec()
	:GameVec(sf::Vector2f())
{
}

GameVec::GameVec(float x, float y)
	: GameVec(sf::Vector2f(x, y))
{
}

GameVec::GameVec(sf::Vector2f v)
	: sf::Vector2f(v),
	active(true)
{
}
