#include <iostream>

#include <SFML/Graphics.hpp>

#include "Space2D.h"
#include "CollisionDetection.h"

void main(int argc, const char* argv[])
{
	bool debug = false;

	for (int i = 1; i < argc; ++i)
	{
		/*if (strcmp(argv[i], "--mode") == 0)
		{
			++i;
			if (strcmp(argv[i], "cpu") == 0)
				mode = planeWorld::MT_CPU;
			else if (strcmp(argv[i], "gpu") == 0)
				mode = planeWorld::MT_GPU;
		}
		else if (strcmp(argv[i], "--threads") == 0)
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
		}
		else*/ if (strcmp(argv[i], "--debug") == 0)
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

	sf::RenderWindow window(vm, "Space Simulation", sf::Style::Titlebar | sf::Style::Close | sf::Style::Default, settings);
	window.setFramerateLimit(60);

	//Space2D spaaace;
	//spaaace.physxTick = .016f;

	//spaaace.setRenderWindow(&window);
	//spaaace.setWorldDimensions(300, 1000);
	///*spaaace.setNumberOfThreads(threads);
	//spaaace.setMutlithreadingMode(mode);
	//spaaace.setOpenCLPlatformAndDevice(platformId, deviceId);*/
	//spaaace.setDebugMode(debug);
	//spaaace.Run();

	CollisionDetection cd;
	cd.setDebugMode(true);
	cd.physxTick = 0.016f;
	cd.setRenderWindow(&window);
	cd.StartDemo(300, sf::Vector2i(500, 500));
}