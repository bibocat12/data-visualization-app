#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>
#include <string>

class Label{
public:
	Label() {};
	Label(char* st, int charSize, sf::Color textColor, sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	
private:
	sf::Text text;
};

#endif // LABEL_H

