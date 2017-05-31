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

		/*if (i == 6)
			__debugbreak();*/

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

	sf::Vector2f outPoints[10];

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
			m_triangles[i].isHit(false);

			sf::Vector2f triPos = m_triangles[i].getPosition();
			sf::Vector2f triCentroid = m_triangles[i].getCentroid();

			/*centerCircle.setPosition(triPos);
			m_window->draw(centerCircle);*/

			/*centerCircle.setPosition(m_triangles[i].getLongestSideCenter());
			m_window->draw(centerCircle);*/

			m_window->draw(m_triangles[i].getOBBShape());
			//CollideOBB(m_triangles[i], mouseTriangle);

			/*centerCircle.setFillColor(sf::Color::Red);
			centerCircle.setPosition(triPos - triCentroid + m_triangles[i].getPoint(0));
			m_window->draw(centerCircle);

			centerCircle.setFillColor(sf::Color::Green);
			centerCircle.setPosition(triPos - triCentroid + m_triangles[i].getPoint(1));
			m_window->draw(centerCircle);

			centerCircle.setFillColor(sf::Color::Blue);
			centerCircle.setPosition(triPos - triCentroid + m_triangles[i].getPoint(2));
			m_window->draw(centerCircle);*/

			int outCount = 0;
			//bool realhit = CollideMinkowski(mouseTriangle, m_triangles[i], outPoints, &outCount);
			bool realhit = CollideMinkowski(m_triangles[i], mouseTriangle, outPoints, &outCount);
			centerCircle.setFillColor(sf::Color::Black);
			for (int i = 0; i < outCount; ++i)
			{
				centerCircle.setPosition(/*mousePos_mapped - mouseTriangle.getCentroid() + /*outPoints[9] + */outPoints[i]);
				m_window->draw(centerCircle);
			}

			centerCircle.setFillColor(sf::Color::White);
			//centerCircle.setPosition(outPoints[9]);
			centerCircle.setPosition(sf::Vector2f());
			m_window->draw(centerCircle);

			m_triangles[i].isHit(realhit);

			continue;
			//SBV
			bool hit;

			hit = CollideSBV(m_triangles[i], mouseTriangle);
			//hit = true;

			if (hit == false)
				continue;

			m_window->draw(m_triangles[i].getSBVShape());

			/*centerCircle.setPosition(m_triangles[i].getSBVShape().getPosition());
			m_window->draw(centerCircle);*/

			//*** sbv

			//AABB
			hit = CollideAABB(m_triangles[i], mouseTriangle);
			//hit = true;

			if (hit == false)
				continue;

			m_window->draw(m_triangles[i].getAABBShape());

			//*** aabb

			//minkowski
			//hit = CollideMinkowski(m_triangles[i], mouseTriangle);
			m_triangles[i].isHit(hit);
			//*** mk

			//real
			//hit = CollideForeal(m_triangles[i], mouseTriangle);
			//m_triangles[i].isHit(hit);
			//*** real
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

bool CollisionDetection::CollideOBB(CollisionTriangle first, CollisionTriangle second)
{
	sf::RectangleShape firstOBB = first.getOBBShape();
	sf::RectangleShape secondOBB = second.getOBBShape();

	sf::Vector2f projVector;

	int cutCount = 0;

	sf::RectangleShape debugLine;
	debugLine.setSize(sf::Vector2f(100.f, 2.f));

	//projection axis
	for (int i = 0; i < 4; ++i)
	{
		if (i == 0)
		{
			projVector = vectorMath::rotateD(firstOBB.getPoint(1) - firstOBB.getPoint(0), firstOBB.getRotation());
		}
		else if (i == 1)
		{
			projVector = vectorMath::rotateD(firstOBB.getPoint(3) - firstOBB.getPoint(0), firstOBB.getRotation());
		}
		else if (i == 2)
		{
			projVector = vectorMath::rotateD(secondOBB.getPoint(1) - secondOBB.getPoint(0), secondOBB.getRotation());
		}
		else if (i == 3)
		{
			projVector = vectorMath::rotateD(secondOBB.getPoint(3) - secondOBB.getPoint(0), secondOBB.getRotation());
		}

		projVector = vectorMath::normalize(projVector);

		debugLine.setRotation(vectorMath::angleD(projVector));
		m_window->draw(debugLine);


	}

	return false;
}

bool CollisionDetection::CollideMinkowski(CollisionTriangle first, CollisionTriangle second, sf::Vector2f* outPoints, int* outCount)
{
	sf::Vector2f sum[9];

	//invert second
	for(int i = 0; i < 3; ++i)
		second.setPoint(i, second.getCentroid() - second.getPoint(i));

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			sum[(i * 3) + j] = (first.getPosition() - first.getCentroid() + first.getPoint(i)) + (second.getPosition() - second.getCentroid() + second.getPoint(j));
			//sum[(i * 3) + j] = first.getPoint(i) + second.getPoint(j);
			outPoints[(i * 3) + j] = sum[(i * 3) + j];
		}
	}

	outPoints[9] = (((first.getPosition()) + (second.getPosition())) * 0.5f);
	*outCount = 9;

	std::vector<sf::Vector2f> pointVector;
	pointVector.resize(9);
	for (int i = 0; i < 9; ++i)
		pointVector[i] = outPoints[i];
	Hull* hull = ConvexHull(pointVector, -1);
	Hull* hullFirst = hull;
	int cnt = 1;
	outPoints[0] = hull->GetPoint();
	while (hullFirst != hull->Next)
	{	
		hull = hull->Next;
		outPoints[cnt] = hull->GetPoint();
		++cnt;
	}
	*outCount = cnt;

	for (int i = 0; i < cnt - 1; ++i)
	{
		float right = vectorMath::sign(sf::Vector2f(0, 0), outPoints[i], outPoints[i + 1]);

		if (right < 0.0f)
			return false;
	}

	return true;
}

bool CollisionDetection::CollideForeal(CollisionTriangle first, CollisionTriangle second)
{
	sf::Vector2f firstPoints[3] = { first.getPoint(0), first.getPoint(1), first.getPoint(2) };
	sf::Vector2f secondPoints[3] = { second.getPoint(0), second.getPoint(1), second.getPoint(2) };

	for (int i = 0; i < 3; ++i)
	{
		firstPoints[i] += first.getPosition() - first.getOrigin();
		secondPoints[i] += second.getPosition() - second.getOrigin();
	}

	/*sf::Vector2f intersection;

	for (int i = 0; i < 6; ++i)
	{
		sf::Vector2fLines lineA = sf::Vector2fLines(firstPoints[0], firstPoints[1]),
							lineB = sf::Vector2fLines(secondPoints[0], secondPoints[1]);
		intersection = vectorMath::lineIntersection(lineA, lineB);

		if(vectorMath::magnitude())
	}*/

	//point in triangle method
	if (vectorMath::pointInTriangle(first.getPosition(), secondPoints[0], secondPoints[1], secondPoints[2]))
	{
		return true;
	}

	if (vectorMath::pointInTriangle(second.getPosition(), firstPoints[0], firstPoints[1], firstPoints[2]))
	{
		return true;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (vectorMath::pointInTriangle(firstPoints[i], secondPoints[0], secondPoints[1], secondPoints[2]))
		{
			return true;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (vectorMath::pointInTriangle(secondPoints[i], firstPoints[0], firstPoints[1], firstPoints[2]))
		{
			return true;
		}
	}
	//*** pitm

	return false;
}

Hull * CollisionDetection::ConvexHull(std::vector<sf::Vector2f>& points, int recursionDepth)
{
	Hull* hull = nullptr;

	if (recursionDepth == 0)
		return hull;

	std::vector<sf::Vector2f>::const_iterator left(points.begin()), right(points.begin()), top(points.begin()), bottom(points.begin());
	for (std::vector<sf::Vector2f>::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		if (it->x < left->x)
			left = it;

		if (it->x > right->x)
			right = it;
	}

	hull = new Hull(*left);
	hull->InsertNext(*right);

	if (recursionDepth == 1)
		return hull;

	Hull *A = hull, *B = hull->Next;
	std::vector<HullPoint> topSet, bottomSet;
	for (std::vector<sf::Vector2f>::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		if (*it == *A || *it == *B)
			continue;

		HullPoint point(*it, *A, *B);
		//TODO: CHECK (CW) vs (CCW)
		if (point.GetSide() == Left)
			topSet.push_back(point);
		else
			bottomSet.push_back(point);
	}

	HullSet(A, B, topSet, recursionDepth);
	HullSet(B, A, bottomSet, recursionDepth);

	return hull;
}

void CollisionDetection::HullSet(::Hull * A, Hull * B, std::vector<HullPoint>& points, int recursionDepth)
{
	if (points.size() == 0 || recursionDepth == 0)
		return;

	if (points.size() == 1)
	{
		A->InsertNext(points[0]);
		return;
	}

	std::vector<HullPoint>::iterator farthest = points.begin();
	for (std::vector<HullPoint>::iterator it = points.begin(); it != points.end(); ++it)
	{
		if (it->GetDistance() > farthest->GetDistance())
			farthest = it;
	}

	Hull* P = A->InsertNext(*farthest);
	points.erase(farthest);

	std::vector<HullPoint> setAP, setPB;
	for (std::vector<HullPoint>::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		HullPoint point(*it, *A, *P);
		//TODO: CHECK (CW) vs (CCW)
		if (point.GetSide() == Left)
			setAP.push_back(point);
	}
	for (std::vector<HullPoint>::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		HullPoint point(*it, *P, *B);
		//TODO: CHECK (CW) vs (CCW)
		if (point.GetSide() == Left)
			setPB.push_back(point);
	}

	HullSet(A, P, setAP, recursionDepth - 1);
	HullSet(P, B, setPB, recursionDepth - 1);
}

//int CollisionDetection::ConvexHull(sf::Vector2f* points, size_t pointSize, int recursionDepth, sf::Vector2f* hullOut)
//{
//	//Hull* hull = nullptr;
//
//	if (recursionDepth == 0)
//		return hull;
//
//	size_t left, right, top, bottom;
//	left = right = top = bottom = 0;
//	
//	for(int i = 0; i < pointSize; ++i)
//	{
//		if (points[i].x < points[left].x)
//			left = i;
//
//		if (points[i].x > points[right].x)
//			right = i;
//	}
//
//	hull = new Hull(*left);
//	hull->InsertNext(*right);
//
//	if (recursionDepth == 1)
//		return hull;
//
//	size_t A = hull, B = hull + 1;
//	//Hull *A = hull, *B = hull->Next;
//	std::vector<HullPoint> topSet, bottomSet;
//	for (int i = 0; i < pointSize; ++i)
//	{
//		if (points[i] == points[A] || points[i] == points[B])
//			continue;
//
//		HullPoint point(*it, *A, *B);
//		float left = vectorMath::sign(points[i], points[A], points[B]);
//		//TODO: CHECK (CW) vs (CCW)
//		if (left > 0.f)
//			topSet.push_back(point);
//		else
//			bottomSet.push_back(point);
//	}
//
//	i_HullSet(A, B, topSet, recursionDepth);
//	i_HullSet(B, A, bottomSet, recursionDepth);
//
//	return hull;
//}

std::ostream & operator<<(std::ostream & os, const sf::Vector2f & v)
{
	return os /*<< /*<< "x: "*/ << v.x << ":"
		/*<< "y: "*/ << v.y;
}
