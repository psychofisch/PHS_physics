#include "Space2D.h"



Space2D::Space2D()
{
}


Space2D::~Space2D()
{
}

void Space2D::Run()
{

}

void Space2D::setDebugMode(bool d)
{
	m_debug = d;
}

void Space2D::setRenderWindow(sf::RenderWindow* wndw)
{
	m_window = wndw;
}

void Space2D::setWorldDimensions(unsigned int size)
{
	setWorldDimensions(size, size);
}

void Space2D::setWorldDimensions(unsigned int size_x, unsigned int size_y)
{
	m_dimension = sf::Vector2u(size_x, size_y);
}
