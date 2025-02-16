#include "Button.h"


Button::Button(char* st, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
	text.setString(st);
	text.setColor(textColor);
	text.setCharacterSize(charSize);

	button.setSize(size);
	button.setFillColor(bgColor);
}

void Button::setFront(sf::Font &font){
	text.setFont(font);
}

void Button::setBackColor(sf::Color color) {
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
	text.setColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
	button.setPosition(pos);

	float xPos = (pos.x + button.getGlobalBounds().width / 3) - (text.getGlobalBounds().width / 2);
	float yPos = (pos.y + button.getGlobalBounds().height / 3) - (text.getGlobalBounds().height / 2);
	text.setPosition({ xPos, yPos });
}

void Button::drawTo(sf::RenderWindow& window){
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window){
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float buttonPosX = button.getPosition().x;
	float buttonPosY = button.getPosition().y;

	float buttonxPosWidth = button.getPosition().x + button.getGlobalBounds().width;
	float buttonyPosHeight = button.getPosition().y + button.getGlobalBounds().height;

	if (buttonPosX < mouseX && mouseX < buttonxPosWidth && buttonPosY < mouseY && mouseY < buttonyPosHeight) {
		return true;
	}
	return false;
}

void Button::handleHover(sf::RenderWindow& window) {
	if (isMouseOver(window)) {
		setBackColor(sf::Color::White);
	}
	else {
		setBackColor(sf::Color::Green);
	}
}


