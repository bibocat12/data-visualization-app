#pragma once

#include "../StateMachine/StateMachine.h"
#include "../StateMachine/State.h"
#include "../StateMachine/AssetManager.h" 



#include "../App.h"

#include "../State/GameState.h"

#include <SFML/Graphics.hpp>

#include "../GUI/Button.h"
#include "../GUI/ImageButton.h"
#include "../GUI/Label.h"

#include <memory>
#include <stack>
#include <iostream>
#include <vector>

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
    std::pair<Button, ImageButton> initButton(char* text, sf::Texture image, sf::Vector2f pos);

	sf::Sprite background;
	sf::Text title, testingEvent;

    std::vector<std::pair<Button, ImageButton >> buttons;
private:
	std::shared_ptr<Context> m_context;
};
