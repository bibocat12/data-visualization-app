#include "Label.h"

Label::Label(char* st, int charSize, sf::Color textColor, sf::Font& font){
	text.setString(st);
	text.setColor(textColor);
	text.setCharacterSize(charSize);
	text.setFont(font);
}

void Label::setPosition(sf::Vector2f pos) {
	text.setPosition(pos);
}

void Label::drawTo(sf::RenderWindow& window) {
	window.draw(text);
}
