#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::setFont(sf::Font& font)
{
	text.setFont(font);
}

void Node::setFillColor(sf::Color color)
{
	shape.setFillColor(color);
	fillColor = color;
}

void Node::setCharacterSize(int size)
{
	text.setCharacterSize(size);
}	

void Node::setPosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
	text.setPosition(pos);
}

void Node::drawTo(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}

bool Node::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;
	float nodePosX = shape.getPosition().x;
	float nodePosY = shape.getPosition().y;
	float nodePosXWidth = shape.getPosition().x + shape.getGlobalBounds().width;
	float nodePosYHeight = shape.getPosition().y + shape.getGlobalBounds().height;
	if (nodePosX < mouseX && mouseX < nodePosXWidth && nodePosY < mouseY && mouseY < nodePosYHeight)
	{
		return true;
	}
	return false;
}

void Node::handleHover(sf::RenderWindow& window)
{
	if (isMouseOver(window))
	{
		setFillColor(sf::Color::White);
	}
	else
	{
		setFillColor(sf::Color::Green);
	}
}

void Node::setRadius(float radius)
{
	shape.setRadius(radius);
}

void Node::setOutlineColor(sf::Color color)
{
	shape.setOutlineColor(color);
	outlineColor = color;
}	

void Node::setOutlineThickness(float thickness)
{
	shape.setOutlineThickness(thickness);
}

void Node::setString(std::string str)
{
	text.setString(str);
}


