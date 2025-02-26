#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

class ImageButton {
public:
	ImageButton() {}
	ImageButton(const sf::Texture& normalTexture, float scaleX, float scaleY);
	void setBackground(const sf::Texture& texture);
	void setPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	bool isMouseOver(sf::RenderWindow& window);
	bool ImageButton::isMouseOverCircle(sf::RenderWindow& window);
	void ImageButton::handleHover(sf::RenderWindow& window, const sf::Texture& normalTexture, const sf::Texture& pressedTexture);

private:
	sf::Sprite button;
};

#endif // IMAGEBUTTON_H