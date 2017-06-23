#pragma once

#include <SFML\Graphics.hpp>

#include "PhysBall.h"
#include "ForceGenerator.h"

class PhysNet
{
public:
	PhysNet(int width, int height, float gap, float radius, ForceGenerator* forceGenPtr);
	~PhysNet();

	void setPosition(sf::Vector2f pos);
	void setStiffness(float s);
	void setNodeRadius(float r);
	void setNodeColor(sf::Color c);
	void update(float dt);
	void draw(sf::RenderWindow* wndw);

private:
	sf::Vector2f m_position,
		m_size;
	sf::CircleShape m_nodeShape;
	sf::RectangleShape m_springShape;
	float m_stiffness;
	sf::Vector2f* m_nodePos;
	sf::Vector2f* m_nodeVel;
	ForceGenerator* m_forceGen;
};

