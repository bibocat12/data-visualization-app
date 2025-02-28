#include "Textbox.h"

Textbox::Textbox(int size, sf::Color color, bool sel) {
	textbox.setCharacterSize(size);
	textbox.setColor(color);
	isSelected = sel;

	if (isSelected) {
		textbox.setString(constText + "|");
	}
	else {
		textbox.setString(constText + "");
	}
}

void Textbox::setConstText(std::string _text)
{
	constText = _text;
	text << _text;
}

void Textbox::setFont(sf::Font& font) {
	textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f pos) {
	this->pos = pos;
	boundingBox.setPosition(pos);
	textbox.setPosition(sf::Vector2f{ pos.x,  pos.y + (boundingBox.getGlobalBounds().height - textbox.getCharacterSize()) / 2 });
	setInvisible();
}

void Textbox::setBox(sf::Vector2f size, sf::Color boxColor)
{
	boundingBox.setSize(size);
	boundingBox.setFillColor(boxColor);
	boundingBox.setPosition(textbox.getPosition());
	//boundingBox.setOutlineColor(Gunmetal);
	//boundingBox.setOutlineThickness(2);
}

void Textbox::setLimit(bool ToF) {
	hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim) {
	hasLimit = ToF;
	limit = lim - 1;
}

void Textbox::setSelected(bool sel) {
	isSelected = sel;
	if (isSelected == false) {
		std::string T = text.str();
		std::string newT = "";
		for (int i = 0; i < (int)T.size(); i++) {
			newT += T[i];
		}
		textbox.setString(newT);
	}
	else {
		textbox.setString(text.str() + (showCursor ? "|":""));
	}
}

std::string Textbox::getText() {
	std::string ans = "";
	for (int i = (int)constText.size(); i < (int)text.str().size(); i++) {
		ans += text.str()[i];
	}
	return ans;
}

int Textbox::getNum()
{
	std::string st = getText();
	int ans = 0;
	for (auto ch : st) ans = ans * 10 + ch - '0';
	return ans;
}

void Textbox::drawTo(sf::RenderWindow& window) {
	window.draw(boundingBox);
	window.draw(textbox);
}

void Textbox::handleCursor() {
	float timeElapsed = clock.getElapsedTime().asSeconds();
	showCursor = fmod(timeElapsed, 0.5f * 2) < 0.5f;
	setSelected(isSelected);

}
void Textbox::typedOnNum(sf::Event event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		setSelected(isMouseOver(window));
	}

    if (event.type == sf::Event::TextEntered && isSelected) {
        int charTyped = event.text.unicode;

        if ((48 <= charTyped && charTyped <= 57 && !(text.str().length() == 0 && charTyped == 48)) || charTyped == DELETE_KEY || charTyped == ENTER_KEY || charTyped == ESCAPE_KEY) {
            if (hasLimit) {
                if (text.str().length() <= limit + constText.length()) {
                    inputLogic(charTyped);
                }
                else if (text.str().length() > limit + constText.length() && charTyped == DELETE_KEY) {
                    deleteLastChar();
                }
            }
            else {
                inputLogic(charTyped);
            }
        }
    }
}

void Textbox::typedOnAlpha(sf::Event event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		setSelected(isMouseOver(window));
	}

	if (event.type == sf::Event::TextEntered && isSelected) {
		int charTyped = event.text.unicode;
		if ((charTyped >= 65 && charTyped <= 90) || (charTyped >= 97 && charTyped <= 122) || charTyped == DELETE_KEY || charTyped == ENTER_KEY || charTyped == ESCAPE_KEY) {
			if (hasLimit) {
				if (text.str().length() <= limit + constText.length()) {
					inputLogic(charTyped);
				}
				else if (text.str().length() > limit + constText.length() && charTyped == DELETE_KEY) {
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
	if (boundingBox.getGlobalBounds().contains(mouseX, mouseY)) return true;
	return false;
}

void Textbox::insertNum(int num)
{
	reset();
	std::string st = std::to_string(num);
	for (char ch : st) {
		inputLogic(ch);
	}
}

void Textbox::setInvisible()
{
	textbox.setPosition(sf::Vector2f {-1000, 1000});
	boundingBox.setPosition(sf::Vector2f {-1000, 1000});
}

void Textbox::setVisible()
{
	boundingBox.setPosition(pos);
	textbox.setPosition(sf::Vector2f{ pos.x,  pos.y + (boundingBox.getGlobalBounds().height - textbox.getCharacterSize()) / 2 });
}

void Textbox::inputLogic(int charTyped) {
	if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > constText.length()) {
			deleteLastChar();
		}
	}
	else if (charTyped == ESCAPE_KEY) {
		setSelected(false);
	}

	if (isSelected) {
		textbox.setString(text.str() + (showCursor ? "|":""));
	}
	else {
		textbox.setString(text.str());
	}
}

void Textbox::deleteLastChar() {
	std::string T = text.str();
	std::string newT = "";
	for (int i = 0; i < (int)T.size() - 1; i++) {
		newT += T[i];
	}

	text.str(constText);
	text << newT;
	textbox.setString(text.str());
}

void Textbox::reset() {
	while (text.str().length() > constText.length()) {
		deleteLastChar();
	}
	setSelected(true);
}

sf::Vector2f Textbox::getPositon() const
{
	return pos;
}

sf::FloatRect Textbox::getGlobalBounds() const
{
	return boundingBox.getGlobalBounds();
}


