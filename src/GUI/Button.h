#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button() {}
	Button(char* st, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor);
	void setFront(sf::Font& font);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	bool isMouseOver(sf::RenderWindow& window);
	void handleHover(sf::RenderWindow& window);

private:
	sf::RectangleShape button;
	sf::Text text;
};

#endif // BUTTON_H