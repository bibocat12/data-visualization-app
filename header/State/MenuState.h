#pragma once

#include "../StateMachine/StateMachine.h"
#include "../StateMachine/State.h"
#include "../StateMachine/AssetManager.h" 


#include "../App.h"


#include <SFML/Graphics.hpp>

#include "../Utils.h"
#include "../GUI/Button.h"
#include "../GUI/ImageButton.h"
#include "../GUI/Label.h"

#include "SinglyLinkedList/SinglyLinkedListMainState.h"
#include "Trie/TrieMainState.h"
#include "Heap/HeapMainState.h"
#include "AVL/AVLMainState.h"
#include "Graph/GraphMainState.h"
#include "Tree234/Tree234MainState.h"

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

    sf::Sprite background;
    sf::Text title, testingEvent;

private:
    std::shared_ptr<Context> m_context;

private:
    sf::Color backgroundColor;
    sf::Color textColor;
    sf::Color normalButtonColor;
    sf::Color hoverButtonColor;
    std::vector<std::pair<Button, ImageButton >> buttons;
    sf::Vector2f buttonSize;
    ImageButton themeButton;
    int themeType;

public:
    std::pair<Button, ImageButton> initButton(char* text, sf::Texture& image, sf::Vector2f pos);
    void switchTheme();
};