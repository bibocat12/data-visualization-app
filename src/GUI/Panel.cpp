#include "Panel.h"

Panel::Panel(sf::Vector2f pos, sf::Vector2f labelSize, sf::Color _textColor, sf::Color _panelColor, sf::Font& _font, int charSize) {
	this->pos = pos;
	this->labelSize = labelSize;
	textColor = _textColor;
	panelColor = _panelColor;
	font = _font;
	this->charSize = charSize;
}

void Panel::add(std::string text) {
	Label label = Label(text, charSize, labelSize, panelColor, textColor, font);
	if (panel.empty() == true) {
		label.setPosition(pos);
	}
	else {
		label.setPosition(sf::Vector2f{ pos.x, pos.y + labelSize.y * (int)panel.size() });
	}
	panel.push_back(label);
}

void Panel::setText(std::string text, int lineIndex) {
	panel[lineIndex].setText(text);
}

void Panel::setTextColor(sf::Color color) {
	for (int i = 0; i < (int)panel.size(); i++) {
		panel[i].setTextColor(color);
	}
}

void Panel::draw(sf::RenderWindow& window) {
	for (int i = 0; i < (int)panel.size(); i++) {
		panel[i].drawTo(window);
	}
}

