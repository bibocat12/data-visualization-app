#ifndef PANEL_H
#define PANEL_H

#include "Label.h"
#include "../StateMachine/DEFINITION.h"

#include <iostream>
#include <vector>

class Panel{
public:
	Panel(){}
	Panel(sf::Vector2f pos, sf::Vector2f labelSize, sf::Color _textColor, sf::Color _panelColor, sf::Font& _font, int charSize);
	void add(std::string text);
	void setText(std::string text, int lineIndex);
	void setLineColor(int lineIndex, sf::Color color);
	sf::Color getLineColor(int lineIndex);
	void setTextColor(sf::Color color);
	void draw(sf::RenderWindow& window);

private:
	std::vector<Label> panel;
	sf::Vector2f labelSize;
	sf::Vector2f pos;
	sf::Color textColor;
	sf::Color panelColor;
	sf::Font font;
	int charSize;
};

#endif // PANEL_H

