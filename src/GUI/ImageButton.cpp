#include "../../header/GUI/ImageButton.h"


ImageButton::ImageButton(const sf::Texture& normalTexture, float scaleX, float scaleY) {
	button.setTexture(normalTexture);
	button.setScale(scaleX, scaleY);
}

void ImageButton::setBackground(const sf::Texture& texture) {
	button.setTexture(texture);
}

void ImageButton::setPosition(sf::Vector2f pos) {
	button.setPosition(pos);
}

void ImageButton::drawTo(sf::RenderWindow& window) {
	window.draw(button);
}

sf::Vector2f ImageButton::getPosition() const{
	return button.getPosition();
}

sf::FloatRect ImageButton::getGlobalBounds() const{
	return button.getGlobalBounds();
}

bool ImageButton::isMouseOver(sf::RenderWindow& window) {
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

bool ImageButton::isMouseOverCircle(sf::RenderWindow& window) {
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;
	float radius = button.getGlobalBounds().width / 2;

	float dx = mouseX - (button.getPosition().x + radius);
	float dy = mouseY - (button.getPosition().y + radius);
	return (dx * dx + dy * dy) <= (radius * radius);
}

void ImageButton::handleHover(sf::RenderWindow& window, const sf::Texture& normalTexture, const sf::Texture& pressedTexture) {
	if (isMouseOver(window)) {
		setBackground(pressedTexture);
	}
	else {
		setBackground(normalTexture);
	}
}

