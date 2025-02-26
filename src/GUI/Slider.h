#ifndef SLIDER_H
#define SLIDER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <SFML\Graphics.hpp>


class Slider {
public:
	Slider() {}
	Slider(sf::Vector2f pos, sf::Vector2f barSize, sf::Vector2f knobBarSize);
	void setColor(sf::Color barColor, sf::Color curBarColor, sf::Color knobColor);
	void setText(std::string minSt, std::string maxSt, int size, sf::Font& font, sf::Color color);
	void setMaxText(std::string maxSt);
	void setNumPart(int num);
	int getPartIndex();
	int getNumPart();
	void setTextColor(sf::Color color);
	void setPart(int index);
	void handleEvent(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPositon() const;
	sf::FloatRect getGlobalBounds() const;

private:
	sf::RectangleShape bar;
	sf::RectangleShape curBar;
	sf::RectangleShape knob;
	sf::Text minText;
	sf::Text maxText;
	std::vector<float> partX;
	static constexpr float density = 4.f / 10.f;
};

#endif // SLIDER_H

