#include "CollisionDetection.h"



CollisionDetection::CollisionDetection()
{
}


CollisionDetection::~CollisionDetection()
{
}

void CollisionDetection::StartDemo(int numberOfTriangles, sf::Vector2i worldSize)
{
	int mouseMoveRectSize = 200;
	sf::IntRect mouseMoveRect = sf::IntRect((m_window->getSize().x - mouseMoveRectSize) / 2, (m_window->getSize().x - mouseMoveRectSize) / 2, mouseMoveRectSize, mouseMoveRectSize);
	sf::Vector2f windowCenter(m_window->getSize());
	windowCenter /= 2.0f;

	sf::Clock time;
	float dt = 0.16f;
	//float tickRun = tick;
	int currentTile = -1;

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

	//setup scene
	RNGesus rng;
	CollisionTriangle* m_triangles = new CollisionTriangle[numberOfTriangles];
	float tmpX = 0, tmpY = 0, tmpFactor = 40.0f;
	for (int i = 0; i < numberOfTriangles; ++i)
	{
		tmpX += tmpFactor;

		if (i % 18 == 0)
		{
			tmpX = tmpFactor;
			tmpY += tmpFactor;
		}

		m_triangles[i].init(30.0f, rng.GetNumber());
		m_triangles[i].setPosition(tmpX, tmpY);
	}

	CollisionTriangle mouseTriangle;
	mouseTriangle.init(50.0f, 1337);
	mouseTriangle.setFillColor(sf::Color(237, 179, 0));
	mouseTriangle.setPosition(0, 0);

	/*sf::RectangleShape colliderRect;
	colliderRect.setFillColor(sf::Color::Transparent);
	colliderRect.setOutlineColor(sf::Color(255, 121, 57));
	colliderRect.setOutlineThickness(1.0f);*/

	sf::CircleShape centerCircle;
	centerCircle.setFillColor(TRIANGLE_COLLIDER_COLOR);
	centerCircle.setRadius(1.f);
	centerCircle.setOrigin(sf::Vector2f(1.0f, 1.0f));

	/*sf::CircleShape debugCircle;
	debugCircle.setFillColor(TRIANGLE_BASE_COLOR);
	debugCircle.setOrigin(sf::Vector2f(10.0f, 10.0f));
	debugCircle.setRadius(100.f);
	debugCircle.setPosition(0, 0);*/
	//*** ss

	unsigned int fps = 0, fpsCount = 0;
	float fpsTimer = 0.f;

	bool quit = false;
	while (!quit)
	{
		time.restart();

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
				case sf::Keyboard::R:
					std::cout << "Mouse -> " <<	mousePos_mapped << std::endl;
					__debugbreak();
					std::cout << "OBB -> " << mouseTriangle.getOBBShape().getPosition() << std::endl;
					std::cout << "OBB-Origin -> " << mouseTriangle.getOBBShape().getOrigin() << std::endl;
					std::cout << "Centroid -> " << mouseTriangle.getCentroid() << std::endl;
					break;
				case sf::Keyboard::M:
					break;
				case sf::Keyboard::V:
					break;
				case sf::Keyboard::N:
					//m_step = true;
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			mouseTriangle.scale(1.1f, 1.1f);
			//mouseSBV.scale(1.1f, 1.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			mouseTriangle.scale(0.9f, 0.9f);
			//mouseSBV.scale(0.9f, 0.9f);
		}

		//*** controls

		//updates
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

		mouseTriangle.setPosition(mousePos_mapped);
		//mouseTriangle.getOBBShape().setPosition(mousePos_mapped);

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

		m_window->draw(mouseTriangle);
		m_window->draw(mouseTriangle.getSBVShape());
		m_window->draw(mouseTriangle.getAABBShape());
		m_window->draw(mouseTriangle.getOBBShape());

		for (int i = 0; i < numberOfTriangles; ++i)
		{
			m_window->draw(m_triangles[i]);

			sf::Vector2f triPos = m_triangles[i].getPosition();

			/*centerCircle.setPosition(triPos);
			m_window->draw(centerCircle);*/

			centerCircle.setPosition(m_triangles[i].getLongestSideCenter());
			m_window->draw(centerCircle);

			m_window->draw(m_triangles[i].getOBBShape());

			//SBV
			bool hit;

			hit = CollideSBV(m_triangles[i], mouseTriangle);
			m_triangles[i].isHit(hit);

			if (hit == false)
				continue;

			m_window->draw(m_triangles[i].getSBVShape());

			/*centerCircle.setPosition(m_triangles[i].getSBVShape().getPosition());
			m_window->draw(centerCircle);*/

			//*** sbv

			//AABB
			hit = CollideAABB(m_triangles[i], mouseTriangle);

			if (hit == false)
				continue;

			m_window->draw(m_triangles[i].getAABBShape());

			//*** AABB
		}

		/*centerCircle.setPosition(0, 0);
		m_window->draw(debugCircle);
		m_window->draw(centerCircle);*/

		// debug text
		m_window->setView(m_window->getDefaultView());

		debugString.str(std::string());//to clean string
									   //int fps = int(1.f / dt);
		debugString << fps << std::endl;
		debugString << static_cast<int>(mousePos_mapped.x) << ":" << static_cast<int>(mousePos_mapped.y) << std::endl;
		debug_text.setString(debugString.str());

		m_window->draw(debug_text);
		//*** dt
		//m_window->draw(m_currentTile);

		m_window->display();
		//*** render

		dt = time.getElapsedTime().asSeconds();
	}
}

void CollisionDetection::setDebugMode(bool d)
{
	m_debug = d;
}

void CollisionDetection::setRenderWindow(sf::RenderWindow * wndw)
{
	m_window = wndw;
}

bool CollisionDetection::CollideSBV(CollisionTriangle first, CollisionTriangle second)
{
	sf::CircleShape& firstSBV = first.getSBVShape();
	sf::CircleShape& secondSBV = second.getSBVShape();
	float dist = vectorMath::magnitude(first.getSBVCenter() - second.getSBVCenter());
	float addedRadius = firstSBV.getRadius() * first.getScale().x + secondSBV.getRadius() * second.getScale().x;

	if (dist > addedRadius)
		return false;
	else
		return true;
}

bool CollisionDetection::CollideAABB(CollisionTriangle first, CollisionTriangle second)
{
	if (first.getGlobalBounds().intersects(second.getGlobalBounds()))
		return true;
	else
		return false;
}

std::ostream & operator<<(std::ostream & os, const sf::Vector2f & v)
{
	return os /*<< /*<< "x: "*/ << v.x << ":"
		/*<< "y: "*/ << v.y;
}
