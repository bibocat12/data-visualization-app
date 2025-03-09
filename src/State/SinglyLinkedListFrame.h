#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "SinglyLinkedList.h"

#include "../StateMachine/Frame.h"
#include "../StateMachine/Context.h"

class SinglyLinkedListFrame
{

public:

	SinglyLinkedListFrame();
	SinglyLinkedListFrame(std::shared_ptr<Context>& context);
	~SinglyLinkedListFrame();

	const float NODE_Y = 400;
	const float EDGE_Y = 400;
	const float PADDING_X = 80;
	const float DISTANCE_X = 60;
	const float RADIUS = 20;
	const float CHARACTER_SIZE = 20;

	const sf::Color B_NODE_COLOR = sf::Color::White;
	const sf::Color W_NODE_COLOR = sf::Color::White;



	////


	SinglyLinkedList LinkedList;

	void initContext(std::shared_ptr<Context>& context);
	void initNode();
	void initEdge();
	void initCodePanel();

	void setLinkedList(SinglyLinkedList& list);

	std::vector<Engine::Frame> b_frames;
	std::vector<Engine::Frame> w_frames;
	std::vector<int> breakpoints;

	void deleteAllFrames();

	void moveNodeEdge(int index, int index1, int index2, sf::Vector2f start, sf::Vector2f end);
	void moveNode(int index, int index1, int index2, sf::Vector2f start, sf::Vector2f end);
	void moveEdge(int index, int index1, int index2, 
		sf::Vector2f start1, sf::Vector2f start2, 
		sf::Vector2f end1, sf::Vector2f end2);
	
	void changeBColor(int index, int index1, int index2, sf::Color from, sf::Color to);
	void changeWColor(int index, int index1, int index2, sf::Color from, sf::Color to);
	void changeBEdge(int index, int index1, int index2, sf::Color from, sf::Color to);

	std::vector<Engine::Frame> getBFrames();
	std::vector<Engine::Frame> getWFrames();
	std::vector<int> getBreakpoints();

	void initCreateFrames();
	void initInsertFrames(int k, int v);
	void initDeleteFrames(int k);
	void initUpdateFrames(int oldV, int newV);
	void initSearchFrames(int num);

	
private:
	std::shared_ptr<Context> m_context;
	Node b_nodes[21];
	Edge b_edges[21];
	Node w_nodes[21];
	Edge w_edges[21];
	Panel codePanel;


};

