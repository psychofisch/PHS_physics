#include "Particle2D.h"



Particle2D::Particle2D()
{
}


Particle2D::~Particle2D()
{
}

void Particle2D::Run()
{

}

void Particle2D::setDebugMode(bool d)
{
	m_debug = d;
}

void Particle2D::setRenderWindow(sf::RenderWindow* wndw)
{
	m_window = wndw;
}

void Particle2D::setWorldDimensions(unsigned int size)
{
	setWorldDimensions(size, size);
}

void Particle2D::setWorldDimensions(unsigned int size_x, unsigned int size_y)
{
	m_dimension = sf::Vector2u(size_x, size_y);
}
