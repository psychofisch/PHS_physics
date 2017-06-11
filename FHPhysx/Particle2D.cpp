#include "Particle2D.h"



Particle2D::Particle2D()
{
}


Particle2D::~Particle2D()
{
}

void Particle2D::Run()
{
	sf::Clock clock;
	float dt = 0.16f;

	int mouseMoveRectSize = 200;
	sf::IntRect mouseMoveRect = sf::IntRect((m_window->getSize().x - mouseMoveRectSize) / 2, (m_window->getSize().x - mouseMoveRectSize) / 2, mouseMoveRectSize, mouseMoveRectSize);
	sf::Vector2f windowCenter(m_window->getSize());
	windowCenter *= .5f;

	m_uiView.setCenter(windowCenter);
	m_uiView.setSize(windowCenter * 2.0f);

	//DEBUG
	sf::Font debug_font;
	debug_font.loadFromFile("./NotoSans-Regular.ttf");
	sf::Text debug_text;
	debug_text.setFont(debug_font);
	debug_text.setCharacterSize(24);
	debug_text.setOutlineColor(sf::Color::Black);
	debug_text.setOutlineThickness(1.f);
	debug_text.setPosition(20.f, 20.f);
	bool measure = true,
		pause = false;

	std::stringstream debugString;
	//***d

	unsigned int fps = 0, fpsCount = 0;
	float fpsTimer = 0.f;
	sf::Vector2f gravity(0.f, 9.81f);

	PhysBall testBall;
	testBall.setFillColor(sf::Color::Green);
	testBall.setRadius(10.0f);
	testBall.setPosition(420.f, 100.f);

	bool quit = false;
	while (!quit)
	{
		clock.restart();

		sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
		sf::Vector2f mousePos_mapped = m_window->mapPixelToCoords(mousePos, m_view);

		//controls
		sf::Event eve;
		while (m_window->pollEvent(eve))
		{
			if (eve.type == sf::Event::Closed)
			{
				quit = true;
				break;
			}
			else if (eve.type == sf::Event::MouseButtonPressed && eve.mouseButton.button == sf::Mouse::Left)
			{
				break;
			}
			else if (eve.type == sf::Event::MouseButtonPressed && eve.mouseButton.button == sf::Mouse::Right)
			{
				break;
			}
			else if (eve.type == sf::Event::MouseWheelScrolled)
			{
				if (eve.mouseWheelScroll.delta < 0)
				{
					m_view.zoom(1.1f);
				}
				else if (eve.mouseWheelScroll.delta > 0)
				{
					m_view.zoom(0.9f);
				}
				break;
			}
			else if (eve.type == sf::Event::KeyPressed)
			{
				switch (eve.key.code)
				{
				case sf::Keyboard::H: std::cout << "no one can help you :)" << std::endl;
					break;
				case sf::Keyboard::M:
					break;
				case sf::Keyboard::V:
					break;
				case sf::Keyboard::P:
					pause = !pause;
					break;
				case sf::Keyboard::Equal:
					break;
				case sf::Keyboard::Dash:
					break;
				case sf::Keyboard::Q:
					break;
				case sf::Keyboard::E:
					break;
				case sf::Keyboard::U:
					break;
				case sf::Keyboard::T:
					break;
				case sf::Keyboard::Num1:
					break;
				case sf::Keyboard::Num2:
					break;
				case sf::Keyboard::Escape:
					quit = true;
					break;
				}
			}
			else if (eve.type == sf::Event::Resized)
			{
				m_view = sf::View(sf::FloatRect(0, 0, static_cast<float>(eve.size.width), static_cast<float>(eve.size.height)));
				//sf::Vector2f view_center((m_grid[0].getPosition() + m_grid[m_grid.size() - 1].getPosition()) / 2.0f);
				m_view.setCenter(sf::Vector2f(0, 0));
				windowCenter = sf::Vector2f(m_window->getSize());
				windowCenter /= 2.0f;

				m_uiView.setCenter(windowCenter);
				m_uiView.setSize(windowCenter * 2.0f);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !mouseMoveRect.contains(mousePos))
		{
			m_view.move((sf::Vector2f(mousePos) - windowCenter)*dt);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			m_view.move(sf::Vector2f(0.f, -1.f)*50.0f*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_view.move(sf::Vector2f(-1.f, 0.f)*50.0f*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			m_view.move(sf::Vector2f(0.f, 1.f)*50.0f*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_view.move(sf::Vector2f(1.f, 0.f)*50.0f*dt);

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
		mouseTriangle.scale(1.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
		mouseTriangle.scale(0.9f);
		}*/

		//*** controls

		//updates

		testBall.addImpulse(gravity * dt);
		testBall.update();

		//tickRun -= dt;
		//if (tickRun <= 0.f)
		//{
		//	tickRun = tick;
		//	if (m_step == true)
		//	{
		//		if (measure)
		//		{
		//			std::cout << "FPS: " << 1 / dt << std::endl;
		//			measure = false;
		//		}
		//		m_step = false;
		//	}

		//	//if (stepMode)
		//	//m_step = false;
		//	if (!pause)
		//		;//do something
		//}

		++fpsCount;

		if (fpsTimer < .5f)
			fpsTimer += dt;
		else
		{
			fps = fpsCount * 2;
			fpsCount = 0;
			fpsTimer = 0.f;
		}
		//*** updates

		//render
		m_window->clear(sf::Color(69, 69, 69));

		m_window->setView(m_view);

		m_window->draw(testBall);

		//ui stuff
		m_window->setView(m_uiView);

		// debug text
		if (m_debug)
		{
			debugString.str(std::string());//to clean string
			debugString << fps << std::endl;
			debugString << static_cast<int>(mousePos_mapped.x) << ":" << static_cast<int>(mousePos_mapped.y) << std::endl;
			debug_text.setString(debugString.str());
			m_window->draw(debug_text);
		}
		//*** dt

		//*** uis

		m_window->display();
		//*** render

		dt = clock.getElapsedTime().asSeconds();
	}
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
