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
	void setBreakpoints(std::vector<int> breakpoints);
	int getPartIndex();
	int getPartIndexMouse(float x);
	int getNumPart();
	void setTextColor(sf::Color color);
	void setPart(int index);
	bool isMouseOverWindow(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPositon() const;
	sf::FloatRect getGlobalBounds() const;

private:
	sf::RectangleShape bar;
	sf::RectangleShape curBar;
	sf::RectangleShape knob;
	std::vector<sf::RectangleShape> breakpointsLine;
	sf::Text minText;
	sf::Text maxText;
	std::vector<float> partX;
	std::vector<int> breakpoints;

	int currentPartIndex = 0;


	bool isPressed = false;
	bool isDragging = false;
	sf::Vector2f offset;


	static constexpr float density = 2.f / 10.f;
};

#endif // SLIDER_H