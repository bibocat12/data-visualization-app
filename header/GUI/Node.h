#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Node
{
public:
	Node();
	~Node();

	sf::CircleShape shape;
	sf::RectangleShape squareShape;
	bool isCircle = true;
	sf::Text text;
	sf::Vector2f position;
	sf::Color fillColor;
	sf::Color outlineColor;
	sf::Color textColorUnder;
	int textSizeUnder;
	sf::Text textUnder;
	std::string stringUnder;
	int charSizeUnder;
	bool isSetTextUnder = false;

	struct Data
	{
		std::string text;
		sf::Vector2f position;
		sf::Color fillColor;
		sf::Color outlineColor;
		int textSize;
		sf::Color textColorUnder;
		int textSizeUnder;
		std::string stringUnder;
		bool isSetTextUnder;
	};


	void setShape(bool isCircle);
	void initTextUnder(sf::Color color, int size);
	void setTextUnder(std::string s);
	void setTextUnder(std::string s, int charSize, sf::Color color);
	void setTextUnderPosition();
	std::string getTextUnderString();

	void setFont(sf::Font& font);
	void setFillColor(sf::Color color);
	void setCharacterSize(float size);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	
	void drawTo(sf::RenderWindow& window);
	bool isMouseOver(sf::RenderWindow& window);
	void handleHover(sf::RenderWindow& window);
	void setRadius(float radius);
	void setSide(float length);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(float thickness);
	void setString(std::string str);
	void setTextColor(sf::Color color);
	std::string getString();
	std::string getStringUnder();

	sf::Color getFillColor();
	sf::Color getOutlineColor();
private:



};