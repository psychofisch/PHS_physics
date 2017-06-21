#pragma once

#include <iostream>

#include "PhysBall.h"
#include "GameVec.h"

struct Force : public GameVec
{
	Force();
	~Force();
};

class ForceGenerator
{
public:
	ForceGenerator();
	~ForceGenerator();

	void addPhysBall(PhysBall* ph);
	void addForce(GameVec* f);
	void addCollider(sf::RectangleShape* rs);
	size_t getForces(GameVec**& ptr);
	void removeForce(GameVec* f);
	void update(float dt);

private:
	PhysBall** m_physBalls;
	GameVec** m_forces;
	sf::RectangleShape** m_collider;
	size_t m_physBallCount,
		m_forceCount,
		m_colliderCount;
};

