
#include "Slider.h"

Slider::Slider(sf::Vector2f pos, sf::Vector2f barSize, sf::Vector2f knobBarSize) {
	bar.setPosition(pos);
	bar.setSize(barSize);
	curBar.setPosition(pos);


	knob.setSize(knobBarSize);
	//knob.setOrigin(sf::Vector2f{ knobBarSize.x , 0 });
	knob.setPosition(sf::Vector2f{ pos.x, pos.y - (knobBarSize.y - barSize.y) / 2.f });
	setNumPart(1);
}

void Slider::setColor(sf::Color barColor, sf::Color curBarColor, sf::Color knobColor) {
	bar.setFillColor(barColor);
	curBar.setFillColor(curBarColor);
	knob.setFillColor(knobColor);
}

void Slider::setText(std::string minSt, std::string maxSt, int size, sf::Font& font, sf::Color color) {
	minText.setString(minSt);
	maxText.setString(maxSt);

	minText.setFont(font);
	maxText.setFont(font);

	minText.setColor(color);
	maxText.setColor(color);

	minText.setCharacterSize(size);
	maxText.setCharacterSize(size);

	minText.setOrigin(sf::Vector2f{ 0, minText.getLocalBounds().height / 2 + minText.getLocalBounds().top });
	minText.setPosition(sf::Vector2f{ bar.getPosition().x - minText.getGlobalBounds().width - 10, bar.getPosition().y + bar.getGlobalBounds().height / 2 });
	maxText.setOrigin(sf::Vector2f{ 0, maxText.getLocalBounds().height / 2 + maxText.getLocalBounds().top });
	maxText.setPosition(sf::Vector2f{ bar.getGlobalBounds().width + bar.getPosition().x + 10, bar.getPosition().y + bar.getGlobalBounds().height / 2 });
}

void Slider::setMaxText(std::string maxSt) {
	maxText.setString(maxSt);
}

void Slider::setNumPart(int num) {
	partX.clear();
	float sizePart = bar.getGlobalBounds().width / static_cast<float> (num);
	partX.push_back(bar.getPosition().x);
	for (int i = 1; i <= num; i++) {
		partX.push_back(bar.getPosition().x + sizePart * static_cast<float> (i));
	}
}

void Slider::setBreakpoints(std::vector<int> breakpoints)
{
	this->breakpoints = breakpoints;
	breakpointsLine.clear();
	for (int i = 0; i < breakpoints.size(); i++) {
		sf::RectangleShape line;
		line.setSize(sf::Vector2f{ 1, bar.getGlobalBounds().height });
		line.setPosition(sf::Vector2f{ partX[breakpoints[i]], bar.getPosition().y });
		if (i == 0 || i == (int)breakpoints.size() - 1) {
			line.setFillColor(sf::Color::Transparent);
		}
		else line.setFillColor(sf::Color::Black);
		breakpointsLine.push_back(line);
	}
}

int Slider::getPartIndex() {
	return currentPartIndex;
	for (int i = 0; i < (int)partX.size(); i++) {

		if (knob.getPosition().x <= partX[i]) return i;
	}
	return getNumPart();
}

int Slider::getPartIndexMouse(float x) {
	if (x <= partX[0] + density * (partX[1] - partX[0])) return 0;
	for (int i = 1; i < (int)partX.size(); i++) {
		if (x <= partX[i])
		{
			currentPartIndex = i;
			return i;
		}
	}
	return getNumPart();
}

int Slider::getNumPart() {
	return (int)partX.size() - 1;
}

int Slider::getBreakpoints(int currentFrameIndex)
{
	for (int i = (int)breakpoints.size() - 1; i >= 0; i--) {
		if (breakpoints[i] <= currentFrameIndex) return breakpoints[i];
	}
	return 0;
}

void Slider::setTextColor(sf::Color color) {
	minText.setColor(color);
	maxText.setColor(color);
}

void Slider::setPart(int index) {
	if (index < 0) index = 0;
	if (index >= (int)partX.size()) index = (int)partX.size() - 1;
	currentPartIndex = index;
	curBar.setSize(sf::Vector2f{ partX[index] - bar.getPosition().x, bar.getGlobalBounds().height });

	if (index == 0) {
		knob.setPosition(sf::Vector2f{ bar.getPosition().x, bar.getPosition().y - (knob.getGlobalBounds().height - bar.getGlobalBounds().height) / 2.f });
	}
	else {
		knob.setPosition(sf::Vector2f{ partX[index] - knob.getGlobalBounds().width, bar.getPosition().y - (knob.getGlobalBounds().height - bar.getGlobalBounds().height) / 2.f });
	}
}

bool Slider::isMouseOverWindow(sf::RenderWindow& window)
{
	float mousePosX = sf::Mouse::getPosition(window).x;
	float mousePosY = sf::Mouse::getPosition(window).y;
	return bar.getGlobalBounds().contains(mousePosX, mousePosY) || knob.getGlobalBounds().contains(mousePosX, mousePosY);
}

void Slider::handleEvent(sf::Event event) {
	float sizePart = bar.getGlobalBounds().width / ((int)partX.size() - 1);

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && isPressed == false) {
		float mousePosX = event.mouseButton.x;
		float mousePosY = event.mouseButton.y;
		if (knob.getGlobalBounds().contains(mousePosX, mousePosY)) {
			isPressed = true;
			offset = sf::Vector2f{ mousePosX - knob.getPosition().x, mousePosY - knob.getPosition().y };
		}
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		isPressed = false;
		isDragging = false;
	}


	if (isPressed == true) {
		float mousePosX = event.mouseMove.x;
		float mousePosY = event.mouseMove.y;
		if (sf::Event::MouseMoved) {
			isDragging = true;
			knob.setPosition(sf::Vector2f{ mousePosX - offset.x, knob.getPosition().y });
			setPart(getPartIndexMouse(knob.getPosition().x));
		}
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		float mousePosX = event.mouseButton.x;
		float mousePosY = event.mouseButton.y;
		if (bar.getGlobalBounds().contains(mousePosX, mousePosY)) {
			setPart(getPartIndexMouse(mousePosX));

		}
	}

}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(bar);
	window.draw(curBar);

	window.draw(knob);
	window.draw(minText);
	window.draw(maxText);
	for (int i = 0; i < (int)breakpointsLine.size(); i++) {
		window.draw(breakpointsLine[i]);
	}
}

sf::Vector2f Slider::getPositon() const {
	return bar.getPosition();
}


sf::FloatRect Slider::getGlobalBounds() const {
	return bar.getGlobalBounds();
}