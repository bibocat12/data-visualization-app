#include "ForceGraph.h"
#include <cmath>
#include <array>

ForceGraph::ForceGraph() :
    nodeRadius(0), edgeThickness(0), font(*(new sf::Font())), numNodes(0), numEdges(0)
{
}

void ForceGraph::init(float nodeRadius, float edgeThickness, sf::Font& font, sf::Color color)
{
    this->nodeRadius = nodeRadius;
    this->edgeThickness = edgeThickness;
    this->font = font;
    this->color = color;
}

void ForceGraph::addNode(sf::Vector2f pos, const std::string& text) {
    Node node;
    nodes[numNodes] = { node, sf::Vector2f(0, 0), false, false };
    nodes[numNodes].node.setRadius(nodeRadius);
    nodes[numNodes].node.setPosition(pos);
    nodes[numNodes].node.setCharacterSize(20);
    nodes[numNodes].node.setTextColor(color);
    nodes[numNodes].node.setOutlineThickness(-3);
    nodes[numNodes].node.setOutlineColor(color);
    nodes[numNodes].node.initTextUnder(color, 20);
    nodes[numNodes].node.setFont(font);
    nodes[numNodes].node.setString(text);
    nodes[numNodes].node.setFillColor(sf::Color::Transparent);
    numNodes++;
}

void ForceGraph::addEdge(int from, int to, int weight, bool directed) {
    Edge edge;
    edges[numEdges] = { edge, from - 1, to - 1, weight };
    edges[numEdges].edge.setThickness(edgeThickness);
    edges[numEdges].edge.setFont(font);
    edges[numEdges].edge.setDirected(directed);
    edges[numEdges].edge.setColor(color);
    if (weight) edges[numEdges].edge.setWeight(weight);
    numEdges++;
}

void ForceGraph::setFixed(bool isFixed) {
    for (int i = 0; i < numNodes; i++) {
        nodes[i].fixed = isFixed;
    }
}

void ForceGraph::setColor(sf::Color _color, bool changeFillColor)
{
    color = _color;
    for (int i = 0; i < numNodes; i++) {
        if (changeFillColor == true) {
            nodes[i].node.setFillColor(sf::Color::Transparent);
            nodes[i].node.initTextUnder(color, 20);
        }
        nodes[i].node.setOutlineColor(color);
        nodes[i].node.setTextColor(color);
    }
    for (int i = 0; i < numEdges; i++) {
        if (changeFillColor || edges[i].edge.getColor() == sf::Color::White || edges[i].edge.getColor() == sf::Color::Black) edges[i].edge.setColor(color);
    }
}

void ForceGraph::applyForces(float dt, float optimalEdgeLength) {
    const float area = SCREEN_WIDTH * (600 - 90);
    const float k = optimalEdgeLength; // optimal distance between nodes
    const float damping = 0.85f; // damping factor
    const float repulsionStrength = 0.1f; // reduced repulsion strength
    const float attractionStrength = 0.1f; // increased attraction strength
    const float velocityThreshold = 2.5f; // threshold for stopping nodes

    // calculate repulsive forces
    for (int i = 0; i < numNodes; i++) {
        nodes[i].velocity = sf::Vector2f(0, 0);

        for (int j = 0; j < numNodes; j++) {
            if (i == j) continue;

            sf::Vector2f diff = nodes[i].node.position - nodes[j].node.position;
            float distance = static_cast<float>(std::sqrt(diff.x * diff.x + diff.y * diff.y)) + 1e-6f;
            if (distance < 0.01f) distance = 0.01f; // prevent division by zero

            sf::Vector2f repulsiveForce = (diff / distance) * (repulsionStrength * k * k / distance);
            nodes[i].velocity += repulsiveForce;
        }
    }

    // calculate attractive forces
    for (int i = 0; i < numEdges; i++) {
        sf::Vector2f diff = nodes[edges[i].to].node.position - nodes[edges[i].from].node.position;
        float distance = static_cast<float>(std::sqrt(diff.x * diff.x + diff.y * diff.y)) + 1e-6f;
        if (distance < 0.01f) distance = 0.01f; // prevent division by zero

        sf::Vector2f attractiveForce = (diff / distance) * (attractionStrength * distance * distance / k);
        nodes[edges[i].from].velocity += attractiveForce;
        nodes[edges[i].to].velocity -= attractiveForce;
    }

    // update positions
    for (int i = 0; i < numNodes; i++) {
        if (!nodes[i].fixed && !nodes[i].dragging) {
            nodes[i].velocity *= damping;
            nodes[i].node.position += nodes[i].velocity * dt;

            if (nodes[i].node.position.x < 0) {
                nodes[i].node.position.x = 0;
                nodes[i].velocity.x = 0;
            }
            if (nodes[i].node.position.y < 90) {
                nodes[i].node.position.y = 90;
                nodes[i].velocity.y = 0;
            }
            if (nodes[i].node.position.x > SCREEN_WIDTH) {
                nodes[i].node.position.x = SCREEN_WIDTH;
                nodes[i].velocity.x = 0;
            }
            if (nodes[i].node.position.y > 600) {
                nodes[i].node.position.y = 600;
                nodes[i].velocity.y = 0;
            }

            // stop nodes if velocity is below threshold
            if (std::abs(nodes[i].velocity.x) < velocityThreshold && std::abs(nodes[i].velocity.y) < velocityThreshold) {
                nodes[i].velocity = sf::Vector2f(0, 0);
            }
        }

        if (nodes[i].dragging) {
            nodes[i].velocity = sf::Vector2f(0, 0);
        }
    }
}

void ForceGraph::update(float dt) {
    applyForces(dt, idealEdgeLength);
    for (int i = 0; i < numNodes; i++) {
        nodes[i].node.setTextUnder(nodes[i].node.getStringUnder());
    }
}

void ForceGraph::draw(sf::RenderWindow& window) {
    for (int i = 0; i < numEdges; i++) {
        sf::Vector2f start = nodes[edges[i].from].node.position;
        sf::Vector2f end = nodes[edges[i].to].node.position;
        sf::Vector2f dir = end - start;
        float d = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        sf::Vector2f unitDir = dir / d;

        edges[i].edge.setStart(start + unitDir * nodeRadius);
        edges[i].edge.setEnd(end - unitDir * nodeRadius);
        edges[i].edge.drawTo(window);
    }

    for (int i = 0; i < numNodes; i++) {
        nodes[i].node.setPosition(nodes[i].node.position);
        nodes[i].node.drawTo(window);
    }
}

int ForceGraph::getNodeAtPosition(sf::Vector2f pos) {
    for (int i = 0; i < numNodes; i++) {
        sf::Vector2f diff = nodes[i].node.position - pos;
        if (std::sqrt(diff.x * diff.x + diff.y * diff.y) < 15)
            return i;
    }
    return -1;
}

void ForceGraph::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        selectedNode = -1;
        for (int i = 0; i < numNodes; i++) {
            if (nodes[i].node.isMouseOver(window)) {
                selectedNode = i;
                break;
            }
        }
        if (selectedNode != -1) nodes[selectedNode].dragging = true;
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (selectedNode != -1) nodes[selectedNode].dragging = false;
        selectedNode = -1;
    }

    if (event.type == sf::Event::MouseMoved && selectedNode != -1) {
        nodes[selectedNode].node.position = sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
        nodes[selectedNode].velocity = sf::Vector2f(0, 0);
    }
}

void ForceGraph::setDirected(bool isDirected)
{
    for (int i = 0; i < numEdges; i++) {
        edges[i].edge.setDirected(isDirected);
    }
}

void ForceGraph::reset()
{
    numNodes = 0;
    numEdges = 0;
}
