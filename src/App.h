#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

#include "StateMachine/StateMachine.h"
#include "StateMachine/AssetManager.h"
#include "StateMachine/DEFINITION.h"

struct Context
{
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
	}
};

#include "State/MenuState.h"
#include "State/SinglyLinkedListMainState.h"

class App
{
public:
	App();
	~App();
	void run();
private:
	sf::Clock m_clock;
	sf::Time m_dt;
	std::shared_ptr<Context> m_context;
public:
};

