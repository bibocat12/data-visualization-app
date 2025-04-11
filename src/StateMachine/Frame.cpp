#include "../../header/StateMachine/Frame.h"

namespace Engine
{
    void Frame::init(const Frame& frame)
    {
        buttonMap = frame.buttonMap;
        nodeMap = frame.nodeMap;
        edgeMap = frame.edgeMap;

        textMap = frame.textMap;
        panelMap = frame.panelMap;
    }

    void Frame::addButton(const std::string& name, const Button& button)
    {
        buttonMap[name] = button;
    }

    void Frame::addNode(const std::string& name, const Node& node)
    {
        nodeMap[name] = node;
    }

    void Frame::addEdge(const std::string& name, const Edge& edge)
    {
        edgeMap[name] = edge;
    }

    void Frame::addText(const std::string& name, const sf::Text& text)
    {
        textMap[name] = text;
    }

    void Frame::addPanel(const std::string& name, const Panel& panel)
    {
        panelMap[name] = panel;
    }

    Button& Frame::getButton(const std::string& name)
    {
        return buttonMap.at(name);
    }

    Node& Frame::getNode(const std::string& name)
    {
        return nodeMap.at(name);
    }

    Edge& Frame::getEdge(const std::string& name)
    {
        return edgeMap.at(name);
    }

    sf::Text& Frame::getText(const std::string& name)
    {
        return textMap.at(name);
    }

    Panel& Frame::getPanel(const std::string& name)
    {
        return panelMap.at(name);
    }

    void Frame::drawAll(sf::RenderWindow& window)
    {
        for (auto& button : buttonMap)
            button.second.drawTo(window);

        Edge* tmpEdge = nullptr;
        for (auto& edge : edgeMap) {
            if (edge.first.front() == '9') {
                tmpEdge = &edge.second;
            }
            edge.second.drawTo(window);
        }
        if (tmpEdge) {
            tmpEdge->drawTo(window);
        }

        for (auto& node : nodeMap)
            node.second.drawTo(window);

        for (auto& text : textMap)
            window.draw(text.second);

        for (auto& panel : panelMap)
            panel.second.draw(window);


    }
}