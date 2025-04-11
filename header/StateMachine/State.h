#pragma once

#include <SFML/Graphics.hpp>

class StateMachine;
namespace Engine {
    class State {
    public:
        State() {};
        virtual ~State() {}

        virtual void pause() = 0;
        virtual void resume() = 0;

		virtual void init() = 0;
        virtual void processEvents() = 0;
        virtual void update(const sf::Time& dt) = 0;
        virtual void draw() = 0;

    };
    
}