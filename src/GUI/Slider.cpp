
#include "Slider.h"

Slider::Slider(sf::Vector2f pos, sf::Vector2f barSize, sf::Vector2f knobBarSize) {
	bar.setPosition(pos);
	bar.setSize(barSize);
	curBar.setPosition(pos);

	knob.setSize(knobBarSize);
	knob.setPosition(sf::Vector2f{ pos.x, pos.y - (knobBarSize.y - barSize.y) / 2 });
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
	float sizePart = bar.getGlobalBounds().width / num;
	partX.push_back(bar.getPosition().x);
	for (int i = 1; i <= num; i++) {
		partX.push_back(static_cast<float>(bar.getPosition().x + sizePart * i));
	}
}

int Slider::getPartIndex() {
	for (int i = 0; i < (int)partX.size(); i++) {
		if (knob.getPosition().x <= partX[i]) return i;
	}
	return getNumPart();
}

int Slider::getPartIndexMouse(float x) {
	if (x <= partX[0] + density * (partX[1] - partX[0])) return 0;
	for (int i = 1; i < (int)partX.size(); i++) {
		if (x <= partX[i]) return i;
	}
	return getNumPart();
}

int Slider::getNumPart() {
	return (int)partX.size() - 1;
}

void Slider::setTextColor(sf::Color color) {
	minText.setColor(color);
	maxText.setColor(color);
}

void Slider::setPart(int index) {
	if (index < 0) index = 0;
	if (index >= (int)partX.size()) index = (int)partX.size() - 1;

	curBar.setSize(sf::Vector2f{ partX[index] - bar.getPosition().x, bar.getGlobalBounds().height });
	if (index == 0) {
		knob.setPosition(sf::Vector2f{ bar.getPosition().x, bar.getPosition().y - (knob.getGlobalBounds().height - bar.getGlobalBounds().height) / 2 });
	}
	else {
		knob.setPosition(sf::Vector2f{ partX[index] - knob.getGlobalBounds().width, bar.getPosition().y - (knob.getGlobalBounds().height - bar.getGlobalBounds().height) / 2 });
	}
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
			setPart(getPartIndex());
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
}

sf::Vector2f Slider::getPositon() const {
	return bar.getPosition();
}


sf::FloatRect Slider::getGlobalBounds() const {
	return bar.getGlobalBounds();
}
