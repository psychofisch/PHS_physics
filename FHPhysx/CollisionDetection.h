#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "vector2math.h"
#include "CollisionTriangle.h"

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();

	void StartDemo(int numberOfTriangles, sf::Vector2i worldSize);
	void setDebugMode(bool d);
	void setRenderWindow(sf::RenderWindow* wndw);
	//void setWorldDimensions(unsigned int size); //true = ERROR; false = successful
	//void setWorldDimensions(unsigned int size_x, unsigned int size_y);

	static bool CollideSBV(CollisionTriangle first, CollisionTriangle second);
	static bool CollideAABB(CollisionTriangle first, CollisionTriangle second);

	float physxTick;

private:
	sf::Vector2u m_dimension;
	sf::RenderWindow* m_window;
	sf::View m_view;
	bool m_debug;
};

