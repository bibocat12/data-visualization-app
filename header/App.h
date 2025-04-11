#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <ctime>

#include "StateMachine/StateMachine.h"
#include "StateMachine/AssetManager.h"
#include "StateMachine/DEFINITION.h"
#include "StateMachine/Context.h"

#include "State/MenuState.h"


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
