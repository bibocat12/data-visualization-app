#pragma once
#include <SFML/Graphics.hpp>
class Edge
{
public:
	Edge();
	~Edge();

	sf::RectangleShape line;


	void setStart(sf::Vector2f start);
	void setEnd(sf::Vector2f end);
	void setDirected(bool isDirected);
	void setColor(sf::Color color);
	void setThickness(float thickness);
	void setFont(sf::Font& font);
	sf::Color getColor();


	
	void setWeight(int weight);

	sf::Vector2f getStart() const { return start; };
	sf::Vector2f getEnd() const { return end; };

	void drawTo(sf::RenderWindow& window);

private:

	bool isDirected;
	bool isWeight;
	int weight;
	float thickness;
	sf::Text text;
	sf::Color color;
	sf::Vector2f start;
	sf::Vector2f end;
};

