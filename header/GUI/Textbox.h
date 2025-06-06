#ifndef TEXTBOX_H  
#define TEXTBOX_H  

#include <SFML/Graphics.hpp>  
#include <iostream>  
#include <sstream>  
#include <cmath>

#include "../StateMachine/DEFINITION.h"

#define DELETE_KEY 8  
#define ENTER_KEY 13  
#define ESCAPE_KEY 27  


class Textbox {
public:
	Textbox() {}
	Textbox(int size, sf::Color color, bool sel);
	void setConstText(std::string text);
	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void setBox(sf::Vector2f size, sf::Color boxColor);
	void setLimit(bool ToF);
	void setLimit(bool ToF, int lim);
	void setSelected(bool sel);
	std::string getText();
	int getNum();
	void drawTo(sf::RenderWindow& window);
	void typedOnNum(sf::Event event, sf::RenderWindow& window);
	void typedOnMatrix(sf::Event event, sf::RenderWindow& window);
	void typedOnAlpha(sf::Event event, sf::RenderWindow& window);
	bool isMouseOver(sf::RenderWindow& window);
	void insertNum(int num);
	void insertText(std::string st);
	void setInvisible();
	void setVisible();
	void reset();
	void setLimNum(int num);
	sf::Vector2f getPositon() const;
	sf::FloatRect getGlobalBounds() const;
	void setLineBoundingBox(sf::Color color);
private:
	sf::Text textbox;
	sf::RectangleShape boundingBox, line;
	std::ostringstream text;
	sf::Vector2f pos;
	bool hasLineBoundingBox = false;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;
	int limNum;
	std::string constText;

	void inputLogic(int charTyped);
	void deleteLastChar();

private:
	sf::Clock clock;
	bool showCursor = false;

public:
	void handleCursor();
};

#endif // TEXTBOX_H