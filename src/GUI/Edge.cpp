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

sf::Color Edge::getColor()
{
	return line.getFillColor();
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
		float length = thickness;
		sf::VertexArray triangle(sf::Triangles, 3);
		float angle = atan2(end.y - start.y, end.x - start.x);
		sf::Vector2f direction = sf::Vector2f(cos(angle), sin(angle));
		sf::Vector2f normal = sf::Vector2f(-direction.y, direction.x);
		sf::Vector2f p1 = end; 
		sf::Vector2f p2 = end - direction * length + normal * (length*2 );
		sf::Vector2f p3 = end - direction * length - normal * (length*2 );
		
		triangle[0].position = p1;
		triangle[1].position = p2;
		triangle[2].position = p3;
		triangle[0].color = color;
		triangle[1].color = color;
		triangle[2].color = color;

		window.draw(triangle);
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
