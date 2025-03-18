#include "Button.h"


Button::Button(std::string st, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
	text.setString(st);
	text.setColor(textColor);
	text.setCharacterSize(charSize);

	button.setSize(size);
	button.setFillColor(bgColor);
}

void Button::setFont(sf::Font &font){
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

	float xPos = pos.x + (button.getGlobalBounds().width - text.getGlobalBounds().width) / 2;
	float yPos = pos.y + (button.getGlobalBounds().height - text.getCharacterSize()) / 2;
	text.setPosition(sf::Vector2f{ xPos, yPos });
}

void Button::setLowTextPosition(sf::Vector2f pos) {
	button.setPosition(pos);

	float xPos = pos.x + (button.getGlobalBounds().width - text.getGlobalBounds().width) / 2;
	float yPos = pos.y + button.getGlobalBounds().height - text.getCharacterSize() - 20;
	text.setPosition(sf::Vector2f{ xPos, yPos });
}

void Button::drawTo(sf::RenderWindow& window){
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window){
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Button::handleHover(sf::RenderWindow& window, sf::Color normalColor, sf::Color hoverColor) {
	if (isMouseOver(window)) {
		setBackColor(hoverColor);
	}
	else {
		setBackColor(normalColor);
	}
}

void Button::setText(std::string str)
{
	text.setString(str);
}

sf::Vector2f Button::getPositon() const {
	return button.getPosition();
}

sf::FloatRect Button::getGlobalBounds() const {
	return button.getGlobalBounds();
}

void Button::setSize(sf::Vector2f size)
{
	button.setSize(size);
}



