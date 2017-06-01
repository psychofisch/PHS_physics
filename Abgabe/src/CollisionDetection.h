#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "vector2math.h"
#include "CollisionTriangle.h"
#include "Hull.h"
#include "HullPoint.h"

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& v);

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();

	void StartDemo(int numberOfTriangles, float gap);
	void setDebugMode(bool d);
	void setRenderWindow(sf::RenderWindow* wndw);
	//void setWorldDimensions(unsigned int size); //true = ERROR; false = successful
	//void setWorldDimensions(unsigned int size_x, unsigned int size_y);

	static bool CollideSBV(CollisionTriangle& first, CollisionTriangle& second);
	static bool CollideAABB(CollisionTriangle& first, CollisionTriangle& second);
	bool CollideOBB(CollisionTriangle& first, CollisionTriangle& second);
	static bool CollideMinkowski(CollisionTriangle& first, CollisionTriangle& second);
	static bool CollideForeal(CollisionTriangle& first, CollisionTriangle& second);
	static Hull* ConvexHull(std::vector<sf::Vector2f>& points, int recursionDepth);
	static void HullSet(::Hull* A, Hull* B, std::vector<HullPoint>& points, int recursionDepth);
	
	static int ConvexHull(sf::Vector2f* points, size_t pointSize, int recursionDepth, sf::Vector2f* hullOut);

	float physxTick;

private:
	sf::Vector2u m_dimension;
	sf::RenderWindow* m_window;
	sf::View m_view,
		m_uiView;
	bool m_debug;

	static void i_HullSet(::Hull* A, Hull* B, std::vector<HullPoint>& points, int& recursionDepth);
};

