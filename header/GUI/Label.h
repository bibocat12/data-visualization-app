#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>
#include <string>

class Label{
public:
	Label() {};
	Label(std::string st, int charSize, sf::Vector2f size, sf::Color backColor, sf::Color textColor, sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void setFont(sf::Font& font);
	void setBackColor(sf::Color color);
	sf::Color getBackColor();
	void setTextColor(sf::Color color);
	void drawTo(sf::RenderWindow& window);
	void setText(std::string st);
	void setSize(sf::Vector2f size);
private:
	sf::RectangleShape shape;
	sf::Text text;
};

#endif // LABEL_H