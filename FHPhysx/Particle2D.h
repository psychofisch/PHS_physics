#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "PhysBall.h"

class Particle2D
{
public:
	Particle2D();
	~Particle2D();

	void Run();
	void setDebugMode(bool d);
	void setRenderWindow(sf::RenderWindow* wndw);
	void setWorldDimensions(unsigned int size);
	void setWorldDimensions(unsigned int size_x, unsigned int size_y);

	float physxTick;

private:
	sf::Vector2u m_dimension;
	sf::RenderWindow* m_window;
	sf::View m_view, m_uiView;
	bool m_debug;
};

