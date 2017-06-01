#include <iostream>

#include <SFML/Graphics.hpp>

#include "Space2D.h"
#include "CollisionDetection.h"

enum MODE { MODE_MOONLANDER = 0, MODE_COLLISION };

void main(int argc, const char* argv[])
{
	bool debug = false;
	MODE mode = MODE_MOONLANDER;

	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "--mode") == 0)
		{
			++i;
			if (strcmp(argv[i], "moon") == 0)
				mode = MODE_MOONLANDER;
			else if (strcmp(argv[i], "collision") == 0)
				mode =	MODE_COLLISION;
		}
		/*else if (strcmp(argv[i], "--threads") == 0)
		{
			threads = atoi(argv[++i]);
			if (debug)
				DEBUG(threads);
		}
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
	vm.width = 720;
	vm.height = 720;
	vm.bitsPerPixel = 32;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(vm, "PHS Project", sf::Style::Titlebar | sf::Style::Close | sf::Style::Default, settings);
	window.setFramerateLimit(144);

	if (mode == MODE_MOONLANDER)
	{
		std::cout << "Moonlander started...\n";

		Space2D spaaace;
		spaaace.physxTick = .016f;

		spaaace.setRenderWindow(&window);
		spaaace.setWorldDimensions(300, 1000);
		/*spaaace.setNumberOfThreads(threads);
		spaaace.setMutlithreadingMode(mode);
		spaaace.setOpenCLPlatformAndDevice(platformId, deviceId);*/
		spaaace.setDebugMode(debug);
		spaaace.Run();
	}
	else if (mode == MODE_COLLISION)
	{
		std::cout << "Collision Detection Demo started\n";

		CollisionDetection cd;
		cd.setDebugMode(true);
		cd.physxTick = 0.016f;
		cd.setRenderWindow(&window);
		//cd.StartDemo(324, sf::Vector2i(500, 500));
		cd.StartDemo(100, sf::Vector2i(500, 500));
	}

	window.close();

	std::cout << "thx 4 using this physics project :)";
	//std::cin.ignore();
}