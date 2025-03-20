#pragma once

#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"
#include "../GUI/Node.h"
#include "../GUI/Edge.h"
#include "../GUI/Panel.h"

#include <stack>
#include <map>
#include <unordered_map>
#include <string>

namespace Engine
{
    class Frame {
    public:
        Frame() = default;

        void init(const Frame& frame);


        void addButton(const std::string& name, const Button& button);
        void addNode(const std::string& name, const Node& node);
        void addEdge(const std::string& name, const Edge& edge);
		void addText(const std::string& name, const sf::Text& text);
		void addPanel(const std::string& name, const Panel& panel);


        Button& getButton(const std::string& name);
        Node& getNode(const std::string& name);
        Edge& getEdge(const std::string& name);
		sf::Text& getText(const std::string& name);
		Panel& getPanel(const std::string& name);


        void drawAll(sf::RenderWindow& window);

    private:
        std::unordered_map<std::string, Button> buttonMap;
        std::unordered_map<std::string, Node> nodeMap;
        std::unordered_map<std::string, Edge> edgeMap;
		std::unordered_map<std::string, sf::Text> textMap;
		std::unordered_map<std::string, Panel> panelMap;
    };

}
