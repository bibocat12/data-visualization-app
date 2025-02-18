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
	class Frame
	{
	public:
		Frame() {}
		~Frame() {}

		void addButton(std::string name, std::unique_ptr<Button> button);
		void addNode(std::string name, std::unique_ptr<Node> node);

		std::unique_ptr<Button> getButton(std::string name);
		Node getNode(std::string name);

		void drawAll(sf::RenderWindow& window);


	private:

		std::map<std::string, std::unique_ptr<Button>> buttonMap;
		std::map<std::string, std::unique_ptr<Node>> nodeMap;
	};
}

