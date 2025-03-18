#include "Label.h"

Label::Label(std::string st, int charSize, sf::Vector2f size, sf::Color backColor, sf::Color textColor, sf::Font& font) {
	text.setString(st);
	text.setColor(textColor);
	text.setCharacterSize(charSize);
	text.setFont(font);

	shape.setFillColor(backColor);
	shape.setSize(size);
}

void Label::setPosition(sf::Vector2f pos) {
	shape.setPosition(pos);

	float xPos = pos.x + 10;
	float yPos = pos.y + (shape.getGlobalBounds().height - text.getCharacterSize()) / 2;
	text.setPosition(sf::Vector2f{ xPos, yPos });
}

void Label::setFont(sf::Font& font){
	text.setFont(font);
}

void Label::setBackColor(sf::Color color){
	shape.setFillColor(color);
}

sf::Color Label::getBackColor()
{
	return shape.getFillColor();
}

void Label::setTextColor(sf::Color color){
	text.setColor(color);
}

void Label::drawTo(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(text);
}

void Label::setText(std::string st){
	text.setString(st);
}

void Label::setSize(sf::Vector2f size)
{
	shape.setSize(size);
}
