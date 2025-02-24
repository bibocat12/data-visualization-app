#pragma once

#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"
#include "../GUI/Node.h"

#include <memory>
#include <stack>
#include <map>
#include <string>


namespace Engine
{
    class Frame {
    public:
        Frame() = default;

		void init(Frame frame);

        void addButton(std::string name, std::shared_ptr<Button> button);
        void addNode(std::string name, std::shared_ptr<Node> node);

        std::shared_ptr<Button> getButton(std::string name);
        std::shared_ptr<Node> getNode(std::string name);

        void drawAll(sf::RenderWindow& window);

    private:
        std::map<std::string, std::shared_ptr<Button>> buttonMap;
        std::map<std::string, std::shared_ptr<Node>> nodeMap;
    };

}

