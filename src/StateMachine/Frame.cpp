#include "Frame.h"

#include "Frame.h"

void Engine::Frame::init(Frame frame)
{
	buttonMap = frame.buttonMap;
	nodeMap = frame.nodeMap;
}

void Engine::Frame::addButton(std::string name, std::shared_ptr<Button> button)
{
    buttonMap[name] = button;
}

void Engine::Frame::addNode(std::string name, std::shared_ptr<Node> node)
{
    nodeMap[name] = node;
}

std::shared_ptr<Button> Engine::Frame::getButton(std::string name)
{
    auto it = buttonMap.find(name);
    if (it != buttonMap.end())
    {
        return it->second;  
    }
    return nullptr;
}

std::shared_ptr<Node> Engine::Frame::getNode(std::string name)
{
    auto it = nodeMap.find(name);
    if (it != nodeMap.end())
    {
        return it->second;
    }
    return nullptr;
}

void Engine::Frame::drawAll(sf::RenderWindow& window)
{
    for (auto& pair : buttonMap)
    {
        pair.second->drawTo(window);
    }
    for (auto& pair : nodeMap)
    {
        pair.second->drawTo(window);
    }
}


