#include "Particle2D.h"



Particle2D::Particle2D()
{
}


Particle2D::~Particle2D()
{
}

void Particle2D::Run()
{
	m_view = m_window->getDefaultView();

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

	sf::RectangleShape debugRect;
	debugRect.setFillColor(sf::Color::White);
	debugRect.setSize(sf::Vector2f(1.f, 1.f));
	debugRect.setScale(sf::Vector2f(100.f, 2.f));
	//***d

	unsigned int fps = 0, fpsCount = 0;
	float fpsTimer = 0.f;
	Force gravity(0.f, 9.81f);
	gravity.active = true;

	Force fanForce(-50.0f, 0.f);
	fanForce.active = false;
	fanForce.yLimit.x = 200.f;
	fanForce.yLimit.y = 400.f;

	float radius = 10.f;
	PhysBall testBall;
	testBall.setFillColor(COLOR_0);
	testBall.setRadius(radius);
	testBall.setPosition(420.f, 100.f);
	testBall.setOrigin(sf::Vector2f(radius * 0.5f, radius * 0.5f));

	//Level
	size_t objectsInLevel = 5;
	sf::RectangleShape* levelObjects = new sf::RectangleShape[objectsInLevel];

	levelObjects[0].setFillColor(COLOR_1);
	levelObjects[0].setPosition(-100.f, 650.f);
	levelObjects[0].setSize(sf::Vector2f(1480.0f, 150.f));

	levelObjects[1].setFillColor(COLOR_1);
	levelObjects[1].setPosition(-100.f, 400.f);
	levelObjects[1].setSize(sf::Vector2f(400.f, 150.f));
	levelObjects[1].setRotation(45.f);

	levelObjects[2].setFillColor(COLOR_1);
	levelObjects[2].setPosition(700.f, 350.f);
	levelObjects[2].setSize(sf::Vector2f(250.f, 20.f));
	levelObjects[2].setRotation(145.f);

	levelObjects[3].setFillColor(COLOR_1);
	levelObjects[3].setPosition(690.f, 330.f);
	levelObjects[3].setSize(sf::Vector2f(250.f, 20.f));
	levelObjects[3].setRotation(10.f);

	levelObjects[4].setFillColor(COLOR_1);
	levelObjects[4].setPosition(1200.f, 200.f);
	levelObjects[4].setSize(sf::Vector2f(80.f, 200.f));

	ForceGenerator forceGen;
	forceGen.addForce(&gravity);
	forceGen.addForce(&fanForce);
	forceGen.addPhysBall(&testBall);

	for(size_t i = 0; i < objectsInLevel; ++i)
		forceGen.addCollider(&levelObjects[i]);

	sf::CircleShape particle;
	particle.setFillColor(COLOR_2);
	particle.setRadius(2.f);

	ParticleSystem testSystem(1000, &forceGen);
	testSystem.setPosition(sf::Vector2f(99.f, 77.f));
	testSystem.setParticleShape(&particle);
	testSystem.setActive(false);

	PhysNet* net = new PhysNet(5, 5, 50.f, 10.f, &forceGen);
	net->setPosition(sf::Vector2f(200.f, 50.f));
	net->setRotation(-45.f);
	net->setStiffness(0.1f);

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
				testBall.resetToPosition(mousePos_mapped);
				break;
			}
			else if (eve.type == sf::Event::MouseButtonPressed && eve.mouseButton.button == sf::Mouse::Right)
			{
				testSystem.setPosition(mousePos_mapped);
				net->setPosition(mousePos_mapped);
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
				case sf::Keyboard::R:
					delete net;
					net = new PhysNet(5, 5, 50.f, 10.f, &forceGen);
					net->setPosition(sf::Vector2f(200.f, 5.f));
					break;
				case sf::Keyboard::V:
					break;
				case sf::Keyboard::B:
					testSystem.setActive(!testSystem.isActive());
					break;
				case sf::Keyboard::P:
					pause = !pause;
					break;
				case sf::Keyboard::Equal:
					break;
				case sf::Keyboard::Dash:
					break;
				case sf::Keyboard::F:
					fanForce.active = !fanForce.active;
					break;
				case sf::Keyboard::Q:
					testBall.mass *= 0.9;
					break;
				case sf::Keyboard::E:
					testBall.mass *= 1.1;
					break;
				case sf::Keyboard::U:
					break;
				case sf::Keyboard::T:
				{
					for (size_t c = 0; c < objectsInLevel; ++c)
					{
						sf::RectangleShape& collider = levelObjects[c];
						sf::Vector2f colliderPos = collider.getPosition();
						float colliderRot = collider.getRotation();

						int inside = 0;
						for (int p = 0; p < 4; ++p)
						{
							sf::Vector2f p1 = colliderPos + vectorMath::rotateD(collider.getPoint(p), colliderRot),
								p2;

							if (p < 3)
								p2 = colliderPos + vectorMath::rotateD(collider.getPoint(p + 1), colliderRot);
							else
								p2 = colliderPos + vectorMath::rotateD(collider.getPoint(0), colliderRot);

							float sign = vectorMath::sign(mousePos_mapped, p1, p2);

							if (sign > 0.f)
							{
								inside++;
							}
						}

						if (inside == 4)
						{
							std::cout << c << ": " << inside << std::endl;
							collider.setFillColor(sf::Color::Green);
						}
					}
				}
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
				m_view.setCenter(m_view.getSize() * 0.5f);
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

		//testBall.addImpulse(gravity * dt);
		//physFloor.setFillColor(COLOR_1);
		for (size_t i = 0; i < objectsInLevel; ++i)
			levelObjects[i].setFillColor(COLOR_1);
		forceGen.update(dt);
		testBall.update(dt);
		testSystem.update(dt);
		net->update(dt);

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
		m_window->clear(sf::Color(30, 30, 30));

		m_window->setView(m_view);

		//m_window->draw(physFloor);
		for (size_t i = 0; i < objectsInLevel; ++i)
			m_window->draw(levelObjects[i]);
		testSystem.drawParticles(m_window);
		net->draw(m_window);

		debugRect.setScale(vectorMath::magnitude(testBall.getVelocity()) * 10.f, 2.f);
		debugRect.setPosition(testBall.getPosition() + testBall.getOrigin());
		debugRect.setRotation(vectorMath::angleD(testBall.getVelocity()));
		m_window->draw(debugRect);
		m_window->draw(testBall);

		//ui stuff
		m_window->setView(m_uiView);

		// debug text
		if (m_debug)
		{
			debugString.str(std::string());//to clean string
			debugString << fps << std::endl;
			debugString << static_cast<int>(mousePos_mapped.x) << ":" << static_cast<int>(mousePos_mapped.y) << std::endl;
			debugString << "Active Particles: " << testSystem.getActiveParticles() << std::endl;
			debugString << "testBall.mass: " << testBall.mass << std::endl;
			debug_text.setString(debugString.str());
			m_window->draw(debug_text);
		}
		//*** dt

		//*** ui

		m_window->display();
		//*** render

		dt = clock.getElapsedTime().asSeconds();
		if (dt > 0.16f)
			dt = 0.16f;
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
