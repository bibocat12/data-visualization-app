#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Node
{
public:
	Node();
	~Node();

	sf::CircleShape shape;
	sf::Text text;
	sf::Vector2f position;
	sf::Color fillColor;
	sf::Color outlineColor;


	void setFont(sf::Font& font);
	void setFillColor(sf::Color color);
	void setCharacterSize(int size);
	void setPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	bool isMouseOver(sf::RenderWindow& window);
	void handleHover(sf::RenderWindow& window);
	void setRadius(float radius);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(float thickness);
	void setString(std::string str);

	

private:
	

	
};

