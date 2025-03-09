#pragma once
#include "AssetManager.h"

struct Context {
	std::unique_ptr<Engine::StateMachine> stateMachine;
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Engine::AssetManager> assetManager;
	std::unique_ptr<int> themeType;
	Context()
	{
		stateMachine = std::make_unique<Engine::StateMachine>();
		window = std::make_unique<sf::RenderWindow>();
		assetManager = std::make_unique<Engine::AssetManager>();
		themeType = std::make_unique<int>();
	};
};