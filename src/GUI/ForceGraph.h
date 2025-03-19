#ifndef FORCEGRAPH_H
#define FORCEGRAPH_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../GUI/Node.h"
#include "../GUI/Edge.h"
#include "../StateMachine/DEFINITION.h"

class ForceGraph {
public:
    ForceGraph();
    void init(float nodeRadius, float edgeThickness, sf::Font& font, sf::Color color);
    void addNode(sf::Vector2f pos, const std::string& text = "");
    void addEdge(int from, int to, int weight = 0, bool directed = false);
    void setFixed(bool isFixed);
    void setColor(sf::Color color, bool changeFillColor);
    void applyForces(float dt, float optimalEdgeLength);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    int getNodeAtPosition(sf::Vector2f pos);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void setDirected(bool isDirected);
    void reset();

private:
    struct forceNode {
        Node node;
        sf::Vector2f velocity;
        bool fixed = false;
        bool dragging = false;
    };

    struct forceEdge {
        Edge edge;
        int from;
        int to;
        int weight;
    };

public:
    std::vector<forceNode> nodes;
    std::vector<forceEdge> edges;
private:

    int selectedNode = -1;
    float idealEdgeLength = 200.0f;
    float nodeRadius;
    float edgeThickness;
    sf::Font& font;
    sf::Color color;
};

#endif // FORCEGRAPH_H

