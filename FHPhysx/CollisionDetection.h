#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

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

	float physxTick;

private:
	sf::Vector2u m_dimension;
	sf::RenderWindow* m_window;
	bool m_debug;
};

