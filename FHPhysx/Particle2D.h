#pragma once

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "PhysBall.h"
#include "ForceGenerator.h"
#include "GameVec.h"
#include "ParticleSystem.h"
#include "PhysNet.h"

#define COLOR_0 sf::Color(78, 253, 255)
#define COLOR_1 sf::Color(37, 131, 232)
#define COLOR_2 sf::Color(57, 53, 255)
#define COLOR_3 sf::Color(142, 37, 232)
#define COLOR_4 sf::Color(255, 51, 233)

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

