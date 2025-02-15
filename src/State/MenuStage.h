#pragma once

#include "../StateMachine/StateMachine.h"
#include "../StateMachine/State.h"
#include "../StateMachine/AssetManager.h" 



#include "../App.h"

#include "../State/GameState.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <iostream>

class MenuStage :
    public Engine::State
{
public:
    MenuStage(std::shared_ptr<Context>& context);
    ~MenuStage();
	void init() override;
    void pause() override;
    void resume() override;
    void processEvents() override;
    void update(const sf::Time& dt) override;
    void draw() override;


	sf::Sprite background, buttonPlay;
	sf::Text title, testingEvent;

private:
	std::shared_ptr<Context> m_context;
};
