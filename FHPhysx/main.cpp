#include <iostream>

#include <SFML/Graphics.hpp>

#include "Particle2D.h"
#include "CollisionDetection.h"

enum MODE { MODE_MOONLANDER = 0, MODE_COLLISION };

void main(int argc, const char* argv[])
{
	bool debug = false;
	int triangles = 324;
	float gap = 50.0f;
	MODE mode = MODE_COLLISION;

	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "--mode") == 0)
		{
			++i;
			if (strcmp(argv[i], "particle") == 0)
				mode = MODE_MOONLANDER;
			else if (strcmp(argv[i], "collision") == 0)
				mode =	MODE_COLLISION;
		}
		else if (strcmp(argv[i], "--triangles") == 0)
		{
			triangles = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "--gap") == 0)
		{
			gap = float(atof(argv[++i]));
		}/*
		else if (strcmp(argv[i], "--platformId") == 0)
		{
			platformId = atoi(argv[++i]);
			if (debug)
				DEBUG(platformId);
		}
		else if (strcmp(argv[i], "--deviceId") == 0)
		{
			deviceId = atoi(argv[++i]);
			if (debug)
				DEBUG(deviceId);
		}*/
		else if (strcmp(argv[i], "--debug") == 0)
		{
			debug = true;
			std::cout << "DEBUG MODE ACTIVATED" << std::endl;
		}
	}

	sf::VideoMode vm;
	vm.width = 1280;
	vm.height = 720;
	vm.bitsPerPixel = 32;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(vm, "PHS Project", sf::Style::Titlebar | sf::Style::Close | sf::Style::Default, settings);
	window.setFramerateLimit(144);

	if (mode == MODE_MOONLANDER)
	{
		std::cout << "Particle2D started...\n";

		Particle2D particle;
		particle.physxTick = .016f;

		particle.setRenderWindow(&window);
		particle.setWorldDimensions(300, 1000);
		/*spaaace.setNumberOfThreads(threads);
		spaaace.setMutlithreadingMode(mode);
		spaaace.setOpenCLPlatformAndDevice(platformId, deviceId);*/
		particle.setDebugMode(debug);
		particle.Run();
	}
	else if (mode == MODE_COLLISION)
	{
		std::cout << "Collision Detection Demo started\n";

		CollisionDetection cd;
		cd.setDebugMode(true);
		cd.physxTick = 0.016f;
		cd.setRenderWindow(&window);
		cd.StartDemo(triangles, gap);
		//cd.StartDemo(100, sf::Vector2i(500, 500));
	}

	window.close();

	std::cout << "thx 4 using this physics project :)";
	//std::cin.ignore();
}