#pragma once

#include <iostream>

#include "PhysBall.h"
#include "GameVec.h"

struct Force : public GameVec
{
	Force();
	Force(float x, float y);
	~Force();

	enum TYPE { FORCE_GLOBAL = 0, FORCE_TUBE };
	sf::Vector2f yLimit;
};

class ForceGenerator
{
public:
	ForceGenerator();
	~ForceGenerator();

	void addPhysBall(PhysBall* ph);
	void addForce(Force* f);
	void addCollider(sf::RectangleShape* rs);
	size_t getForces(Force**& ptr);
	size_t getCollider(sf::RectangleShape**& ptr);
	void removeForce(Force* f);
	void update(float dt);

private:
	PhysBall** m_physBalls;
	Force** m_forces;
	sf::RectangleShape** m_collider;
	size_t m_physBallCount,
		m_forceCount,
		m_colliderCount;
};

