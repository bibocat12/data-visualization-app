#include "ForceGraph.h"
#include <cmath>

ForceGraph::ForceGraph() :
    nodeRadius(0), edgeThickness(0), font(*(new sf::Font()))
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
    nodes.push_back({node, sf::Vector2f(0, 0), false, false});
    nodes.back().node.setRadius(nodeRadius);
    nodes.back().node.setPosition(pos);
    nodes.back().node.setCharacterSize(20);
    nodes.back().node.setOutlineColor(color);
    nodes.back().node.setTextColor(color);
    nodes.back().node.initTextUnder(color, 20);
    nodes.back().node.setOutlineThickness(-3);
    nodes.back().node.setFont(font);
    nodes.back().node.setString(text);
    nodes.back().node.setFillColor(sf::Color::Transparent);
}


void ForceGraph::addEdge(int from, int to, int weight, bool directed) {
    Edge edge;
    edges.push_back({edge, from - 1, to - 1, weight});
    edges.back().edge.setThickness(edgeThickness);
    edges.back().edge.setFont(font);
    edges.back().edge.setDirected(directed);
    edges.back().edge.setColor(color);
    if(weight) edges.back().edge.setWeight(weight);
}

void ForceGraph::setFixed(bool isFixed) {
    for (int i = 0; i < (int)nodes.size(); i++) {
        nodes[i].fixed = isFixed;
    }
}

void ForceGraph::setColor(sf::Color color, bool changeFillColor)
{
    this->color = color;
    for (int i = 0; i < (int)nodes.size(); i++) {
        if (changeFillColor == true) nodes[i].node.setFillColor(sf::Color::Transparent);
        nodes[i].node.setOutlineColor(color);
        nodes[i].node.setTextColor(color);
        nodes[i].node.initTextUnder(color, 20);
    }
    for (int i = 0; i < (int)edges.size(); i++) {
        if(changeFillColor) edges[i].edge.setColor(color);
    }
}

void ForceGraph::applyForces(float dt, float optimalEdgeLength) {
    const float area = SCREEN_WIDTH * (600 - 90); // Assuming SCREEN_WIDTH and 600 as the height
    const float k = optimalEdgeLength; // Optimal distance between nodes
    const float damping = 0.85f; // Increased damping factor
    const float repulsionStrength = 0.1f; // Reduced repulsion strength
    const float attractionStrength = 0.1f; // Increased attraction strength
    const float velocityThreshold = 2.5f; // Threshold for stopping nodes

    // Calculate repulsive forces
    for (size_t i = 0; i < nodes.size(); i++) {
        nodes[i].velocity = sf::Vector2f(0, 0); // Reset velocity

        for (size_t j = 0; j < nodes.size(); j++) {
            if (i == j) continue;

            sf::Vector2f diff = nodes[i].node.position - nodes[j].node.position;
            float distance = static_cast<float>(std::sqrt(diff.x * diff.x + diff.y * diff.y)) + 1e-6f;
            if (distance < 0.01f) distance = 0.01f; // Prevent division by zero

            sf::Vector2f repulsiveForce = (diff / distance) * (repulsionStrength * k * k / distance);
            nodes[i].velocity += repulsiveForce;
        }
    }

    // Calculate attractive forces
    for (const auto& edge : edges) {
        sf::Vector2f diff = nodes[edge.to].node.position - nodes[edge.from].node.position;
        float distance = static_cast<float>(std::sqrt(diff.x * diff.x + diff.y * diff.y)) + 1e-6f;
        if (distance < 0.01f) distance = 0.01f; // Prevent division by zero

        sf::Vector2f attractiveForce = (diff / distance) * (attractionStrength * distance * distance / k);
        nodes[edge.from].velocity += attractiveForce;
        nodes[edge.to].velocity -= attractiveForce;
    }

    // Update positions
    for (auto& node : nodes) {
        if (!node.fixed && !node.dragging) {
            node.velocity *= damping; // Apply damping
            node.node.position += node.velocity * dt;

            // Boundary checks
            if (node.node.position.x < 0) {
                node.node.position.x = 0;
                node.velocity.x = 0;
            }
            if (node.node.position.y < 90) {
                node.node.position.y = 90;
                node.velocity.y = 0;
            }
            if (node.node.position.x > SCREEN_WIDTH) {
                node.node.position.x = SCREEN_WIDTH;
                node.velocity.x = 0;
            }
            if (node.node.position.y > 600) {
                node.node.position.y = 600;
                node.velocity.y = 0;
            }

            // Stop nodes if velocity is below threshold
            if (std::abs(node.velocity.x) < velocityThreshold && std::abs(node.velocity.y) < velocityThreshold) {
                node.velocity = sf::Vector2f(0, 0);
            }
        }

        if (node.dragging) {
            node.velocity = sf::Vector2f(0, 0); // Reset velocity if dragging
        }
    }
}

void ForceGraph::update(float dt) {
    applyForces(dt, idealEdgeLength);
}

void ForceGraph::draw(sf::RenderWindow& window) {
    // Draw edges
    for (auto& edge : edges) {
        sf::Vector2f start = nodes[edge.from].node.position;
        sf::Vector2f end = nodes[edge.to].node.position;
        sf::Vector2f dir = end - start;  
        float d = std::sqrt(dir.x * dir.x + dir.y * dir.y);  
        sf::Vector2f unitDir = dir / d;  

        edge.edge.setStart(start + unitDir * nodeRadius);
        edge.edge.setEnd(end - unitDir * nodeRadius);
        edge.edge.drawTo(window);
    }

    // Draw nodes
    for (auto& node : nodes) {
        node.node.setPosition(node.node.position);
        node.node.drawTo(window);
    }
}

int ForceGraph::getNodeAtPosition(sf::Vector2f pos) {
    for (size_t i = 0; i < nodes.size(); i++) {
        sf::Vector2f diff = nodes[i].node.position - pos;
        if (std::sqrt(diff.x * diff.x + diff.y * diff.y) < 15)
            return static_cast<int>(i);
    }
    return -1;
}

void ForceGraph::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        selectedNode = -1;
        for (int i = 0; i < (int)nodes.size(); i++) {
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
    for (int i = 0; i < (int)edges.size(); i++) {
        edges[i].edge.setDirected(isDirected);
    }
}

void ForceGraph::reset()
{
    nodes.clear();
    edges.clear();
}

