#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::initTextUnder(sf::Color color, int size)
{
	textSizeUnder = size;
	textColorUnder = color;
}

void Node::setTextUnder(std::string s)
{
	textUnder.setString(s);
	textUnder.setCharacterSize(textSizeUnder);
	textUnder.setFillColor(textColorUnder);
	textUnder.setOrigin(textUnder.getGlobalBounds().width / 2, textUnder.getGlobalBounds().height / 2);
	textUnder.setPosition(shape.getPosition().x, shape.getPosition().y + shape.getRadius() * 1.25);

	isSetTextUnder = true;
}

void Node::setTextUnder(std::string s, int charSize, sf::Color color)
{
	textUnder.setString(s);
	textUnder.setCharacterSize(charSize);
	textUnder.setFillColor(color);
	textUnder.setOrigin(textUnder.getGlobalBounds().width / 2, textUnder.getGlobalBounds().height / 2);
	textUnder.setPosition(shape.getPosition().x, shape.getPosition().y + shape.getRadius() * 1.25);

	isSetTextUnder = true;
}

void Node::setFont(sf::Font& font)
{
	text.setFont(font);
	textUnder.setFont(font);
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
	this->position = pos;
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(pos);
	sf::FloatRect textBounds = text.getLocalBounds();
	sf::FloatRect shapeBounds = shape.getGlobalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	text.setPosition(shapeBounds.left + shapeBounds.width / 2.0f,
		shapeBounds.top + shapeBounds.height / 2.0f);
}

sf::Vector2f Node::getPosition()
{
	return position;
}

void Node::drawTo(sf::RenderWindow& window)
{
	this->setPosition(position);

	window.draw(shape);
	window.draw(text);
	if (isSetTextUnder)
		window.draw(textUnder); 

}

bool Node::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;
	float nodePosX = shape.getPosition().x;
	float nodePosY = shape.getPosition().y;
	float radius = shape.getRadius();

	float distance = std::sqrt((mouseX - nodePosX) * (mouseX - nodePosX) + (mouseY - nodePosY) * (mouseY - nodePosY));
	return distance <= radius;
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

void Node::setTextColor(sf::Color color)
{
	text.setFillColor(color);
}

std::string Node::getString()
{
	return text.getString();
}

sf::Color Node::getFillColor()
{
	return fillColor;
}

sf::Color Node::getOutlineColor()
{
	return outlineColor;
}

std::string Node::getStringUnder()
{
	return textUnder.getString();
}