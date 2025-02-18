#include "Frame.h"

void Engine::Frame::addButton(std::string name, std::unique_ptr<Button> button)
{
    buttonMap.insert(std::make_pair(name, std::move(button)));
}

void Engine::Frame::addNode(std::string name, std::unique_ptr<Node> node)
{
    nodeMap.insert(std::make_pair(name, std::move(node)));
}

std::unique_ptr<Button> Engine::Frame::getButton(std::string name)
{
    auto it = buttonMap.find(name);
    if (it != buttonMap.end())
    {
        return std::make_unique<Button>(*it->second);
    }
    return nullptr;
}

Node Engine::Frame::getNode(std::string name)
{
    auto it = nodeMap.find(name);
    if (it != nodeMap.end())
    {
        return *(it->second);
    }
    return Node();
}

void Engine::Frame::drawAll(sf::RenderWindow& window)
{
    //for (auto& pair : buttonMap)
    //{
    //    pair.second->drawTo(window);
    //}
    //for (auto& pair : nodeMap)
    //{
    //    pair.second->drawTo(window);
    //}
}
