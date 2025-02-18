#pragma once

#include "../StateMachine/StateMachine.h"
#include "../StateMachine/State.h"
#include "../StateMachine/AssetManager.h" 



#include "../App.h"

#include "../State/GameState.h"

#include <SFML/Graphics.hpp>

#include "../GUI/Button.h"

#include <memory>
#include <stack>
#include <iostream>

class MenuState :
    public Engine::State
{
public:
    MenuState(std::shared_ptr<Context>& context);
    ~MenuState();
	void init() override;
    void pause() override;
    void resume() override;
    void processEvents() override;
    void update(const sf::Time& dt) override;
    void draw() override;


	sf::Sprite background;
	sf::Text title, testingEvent;

    Button buttonPlay{"Singly Linked List", sf::Vector2f(200, 100), 24, sf::Color::Green, sf::Color::Black};

private:
	std::shared_ptr<Context> m_context;
};
