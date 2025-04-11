#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button() {}
	Button(std::string st, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor);
	void setFont(sf::Font& font);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void setLowTextPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	bool isMouseOver(sf::RenderWindow& window);
	void handleHover(sf::RenderWindow& window, sf::Color normalColor, sf::Color hoverColor);
	void setText(std::string str);
	sf::Vector2f getPositon() const;
	sf::FloatRect getGlobalBounds() const;
	void setSize(sf::Vector2f size);
private:
	sf::RectangleShape button; 
	sf::Text text;
};

#endif // BUTTON_H