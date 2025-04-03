#pragma once
#include "AssetManager.h"
#include <SFML/System.hpp> 

struct Context {
	std::unique_ptr<Engine::StateMachine> stateMachine;
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Engine::AssetManager> assetManager;
	std::unique_ptr<int> themeType;
	std::unique_ptr<sf::Time> TIME_PER_FRAME; 
	std::unique_ptr<std::vector<float>> timeScale;

	Context()
	{
		stateMachine = std::make_unique<Engine::StateMachine>();
		window = std::make_unique<sf::RenderWindow>();
		assetManager = std::make_unique<Engine::AssetManager>();
		themeType = std::make_unique<int>();

		TIME_PER_FRAME = std::make_unique<sf::Time>(sf::seconds(1.f / 60.f)); 
        timeScale = std::make_unique<std::vector<float>>(std::initializer_list<float>{0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4});
	};
};