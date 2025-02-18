#include "Textbox.h"

Textbox::Textbox(int size, sf::Color color, bool sel) {
	textbox.setCharacterSize(size);
	textbox.setColor(color);
	isSelected = sel;

	if (isSelected) {
		textbox.setString("|");
	}
	else {
		textbox.setString("");
	}
}

void Textbox::setFont(sf::Font& font){
	textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f pos){
	textbox.setPosition(pos);
	boundingBox.setPosition(pos);
}

void Textbox::setSizeBox(sf::Vector2f size)
{
	boundingBox.setSize(size);
	boundingBox.setFillColor(sf::Color::White);
	boundingBox.setPosition(textbox.getPosition());
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setOutlineThickness(2);
}

void Textbox::setLimit(bool ToF) {
	hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim){
	hasLimit = ToF;
	limit = lim - 1;
}

void Textbox::setSelected(bool sel){
	isSelected = sel;
	if (isSelected == false) {
		std::string T = text.str();
		std::string newT = "";
		for (int i = 0; i < (int) T.size(); i++) {
			newT += T[i];
		}
		textbox.setString(newT);
	}
}

std::string Textbox::getText(){
	return text.str();
}

void Textbox::drawTo(sf::RenderWindow& window) {
	window.draw(boundingBox);
	window.draw(textbox);
	
}

void Textbox::typedOn(sf::Event input) {
	
	if (isSelected) {
		
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (hasLimit) {
				if (text.str().length() <= limit) {
					inputLogic(charTyped);
				}
				else if (text.str().length() > limit && charTyped == DELETE_KEY) {
					deleteLastChar();
				}
			}
			else {
				inputLogic(charTyped);
			}
		}
	}
}

bool Textbox::isMouseOver(sf::RenderWindow& window)
{
	
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;
	if (boundingBox.getGlobalBounds().contains(mouseX, mouseY))
	{
		return true;
		
	}
	
	return false;
}

void Textbox::inputLogic(int charTyped){
	if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if(charTyped == DELETE_KEY){
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	
	textbox.setString(text.str() + "|");
}

void Textbox::deleteLastChar(){
	std::string T = text.str();
	std::string newT = "";
	for (int i = 0; i < (int) T.size() - 1; i++) {
		newT += T[i];
	}

	text.str("");
	text << newT;
	textbox.setString(text.str());
}



