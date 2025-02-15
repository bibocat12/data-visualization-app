#pragma once

#include "../StateMachine/StateMachine.h"
#include "../StateMachine/State.h"
#include "../StateMachine/AssetManager.h" 
#include "../App.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <iostream>



class GameState :
    public Engine::State
{
public:
	GameState(std::shared_ptr<Context>& context);
	~GameState();
	void init() override;
	void pause() override;
	void resume() override;
	void processEvents() override;
	void update(const sf::Time& dt) override;
	void draw() override;

	sf::Sprite background;

private:
	std::shared_ptr<Context> m_context;

};

