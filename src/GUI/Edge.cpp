#include "Edge.h"

Edge::Edge()
{
	setColor(sf::Color::Black);
	setThickness(2);
	isDirected = false;
	isWeight = false;
	thickness = 2;
}

Edge::~Edge()
{
}

void Edge::setStart(sf::Vector2f start)
{
	this->start = start;
}

void Edge::setEnd(sf::Vector2f end)
{
	this->end = end;
}

void Edge::setDirected(bool isDirected)
{
	this->isDirected = isDirected;
}

void Edge::setColor(sf::Color color)
{
	this->color = color;
	line.setFillColor(color);
}

void Edge::setThickness(float thickness)
{
	this->thickness = thickness;
}

void Edge::setFont(sf::Font& font)
{
	this->font = font;
}

void Edge::setWeight(int weight)
{
	this->weight = weight;
	isWeight = true;
	text.setString(std::to_string(weight));
}

void Edge::drawTo(sf::RenderWindow& window)
{
	line.setPosition(start);
	float length = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
	line.setSize(sf::Vector2f(length, thickness));
	line.setOrigin(0, thickness / 2);
	line.setRotation(atan2(end.y - start.y, end.x - start.x) * 180 / 3.14159265);
	window.draw(line);
	if (isDirected)
	{
		sf::CircleShape arrow(5, 3);
		arrow.setFillColor(color);
		arrow.setPosition(end);
		arrow.setRotation(atan2(end.y - start.y, end.x - start.x) * 180 / 3.14159265);
		window.draw(arrow);
	}
	if (isWeight)
	{
		text.setFont(font);
		text.setCharacterSize(20);
		text.setFillColor(color);
		text.setPosition((start + end) / 2.f);
		window.draw(text);
	}

}
