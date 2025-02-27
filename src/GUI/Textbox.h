#ifndef TEXTBOX_H  
#define TEXTBOX_H  

#include <SFML/Graphics.hpp>  
#include <iostream>  
#include <sstream>  

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
	void typedOnNum(sf::Event event);
	void typedOnAlpha(sf::Event event);
	bool isMouseOver(sf::RenderWindow& window);
	void setInvisible();
	void setVisible();
	void reset();
	sf::Vector2f getPositon() const;
	sf::FloatRect getGlobalBounds() const;



private:
	sf::Text textbox;
	sf::RectangleShape boundingBox;
	std::ostringstream text;
	sf::Vector2f pos;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;
	std::string constText;

	void inputLogic(int charTyped);
	void deleteLastChar();
};

#endif // TEXTBOX_H