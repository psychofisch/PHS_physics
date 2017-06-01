#include "Hull.h"



Hull::Hull() : Previous(this), Next(this)
{}

Hull::Hull(float x, float y) : sf::Vector2f(x,y), Previous(this), Next(this)
{}

Hull::Hull(const sf::Vector2f& copy) : sf::Vector2f(copy), Previous(this), Next(this)
{}

Hull::~Hull()
{
}

Hull* Hull::InsertNext(const sf::Vector2f& point)
{
	Hull* newPoint = new Hull(point);
	newPoint->Previous = this;
	newPoint->Next = Next;

	Next->Previous = newPoint;	

	return (Next = newPoint);
}

sf::Vector2f Hull::GetPoint() const
{
	return sf::Vector2f(x, y);
}
