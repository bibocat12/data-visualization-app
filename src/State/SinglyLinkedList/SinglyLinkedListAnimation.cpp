#include "../../../header/State/SinglyLinkedList/SinglyLinkedListMainState.h"

void SinglyLinkedListMainState::initNode(std::vector<int>& getAllElements)
{
	int numElements = getAllElements.size();

	for (int i = 0; i < numElements; i++)
	{

		w_nodes[i] = Node();
		w_nodes[i].setRadius(20);
		w_nodes[i].setOutlineThickness(-2);
		w_nodes[i].setOutlineColor(Orange);
		w_nodes[i].setFillColor(sf::Color::White);

		w_nodes[i].setPosition(sf::Vector2f(PADDING_X + i * DISTANCE_X, NODE_Y));
		w_nodes[i].setString(std::to_string(getAllElements[i]));
		w_nodes[i].setCharacterSize(CHARACTER_SIZE);
		w_nodes[i].setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		w_nodes[i].setTextColor(sf::Color::Black);


		b_nodes[i] = w_nodes[i];

		
		b_nodes[i].setFillColor(B_NODE_COLOR);
		b_nodes[i].setOutlineColor(sf::Color::Red);
		b_nodes[i].setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		b_nodes[i].setPosition(sf::Vector2f(PADDING_X + i * DISTANCE_X, NODE_Y));
		b_nodes[i].setCharacterSize(RADIUS);
		b_nodes[i].setString(std::to_string(getAllElements[i]));
		b_nodes[i].setTextColor(sf::Color::Black);
		b_nodes[i].setString(std::to_string(getAllElements[i]));
		b_nodes[i].setTextColor(sf::Color::Black);

		



	}
}

void SinglyLinkedListMainState::initEdge(std::vector<int>& getAllElements)
{
	int numElements = getAllElements.size();
	for (int i = 1; i < numElements; i++)
	{
		if (i == 0) continue;
		sf::Vector2f end = b_nodes[i].getPosition();
		end.x -= RADIUS;
		b_edges[i].setThickness(3);
		b_edges[i].setColor(sf::Color::Red);
		b_edges[i].setStart(b_nodes[i - 1].getPosition());
		b_edges[i].setEnd(end);

		w_edges[i].setThickness(3);
		w_edges[i].setColor(Orange);
		w_edges[i].setStart(b_nodes[i - 1].getPosition());
		w_edges[i].setEnd(end);

		w_edges[i].setDirected(true);
		b_edges[i].setDirected(true);
	}
}

void SinglyLinkedListMainState::deleteAllFrames()
{
	b_frames.clear();
	w_frames.clear();
	for(int i = 0;i < 60;i++)
		for (int j = 0; j < 9; j++)
			codePanelColor[i][j] = LavenderSoft;
}

void SinglyLinkedListMainState::setCodePanelColor(int frameIndex)
{
	for (int i = 0; i < 7; i++)
	{
		codePanel.setLineColor(i, codePanelColor[frameIndex][i]);
	}
}

void SinglyLinkedListMainState::changeBNode(int index, int index1, int index2, Node from, Node to)
{
	float step = (index2 - index1);
	float vR = (to.getFillColor().r - from.getFillColor().r) / step;
	float vG = (to.getFillColor().g - from.getFillColor().g) / step;
	float vB = (to.getFillColor().b - from.getFillColor().b) / step;
	float vA = (to.getFillColor().a - from.getFillColor().a) / step;
	float vX = (to.getPosition().x - from.getPosition().x) / step;
	float vY = (to.getPosition().y - from.getPosition().y) / step;
	float vROutline = (to.getOutlineColor().r - from.getOutlineColor().r) / step;
	float vGOutline = (to.getOutlineColor().g - from.getOutlineColor().g) / step;
	float vBOutline = (to.getOutlineColor().b - from.getOutlineColor().b) / step;
	float vAOutline = (to.getOutlineColor().a - from.getOutlineColor().a) / step;



	for (int i = index1; i <= index2; i++)
	{

		sf::Color color;
		color.r = from.getFillColor().r + vR * (i - index1);
		color.g = from.getFillColor().g + vG * (i - index1);
		color.b = from.getFillColor().b + vB * (i - index1);
		sf::Vector2f pos;
		pos.x = from.getPosition().x + vX * (i - index1);
		pos.y = from.getPosition().y + vY * (i - index1);
		sf::Color colorOutline;
		colorOutline.r = from.getOutlineColor().r + vROutline * (i - index1);
		colorOutline.g = from.getOutlineColor().g + vGOutline * (i - index1);
		colorOutline.b = from.getOutlineColor().b + vBOutline * (i - index1);
		colorOutline.a = from.getOutlineColor().a + vAOutline * (i - index1);


		b_nodes[index].setFillColor(color);
		b_nodes[index].setPosition(pos);
		b_nodes[index].setOutlineColor(colorOutline);
		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
	}
}

void SinglyLinkedListMainState::changeWNode(int index, int index1, int index2, Node from, Node to)
{
	float step = (index2 - index1);
	float vR = (to.getFillColor().r - from.getFillColor().r) / step;
	float vG = (to.getFillColor().g - from.getFillColor().g) / step;
	float vB = (to.getFillColor().b - from.getFillColor().b) / step;
	float vA = (to.getFillColor().a - from.getFillColor().a) / step;
	float vX = (to.getPosition().x - from.getPosition().x) / step;
	float vY = (to.getPosition().y - from.getPosition().y) / step;
	float vROutline = (to.getOutlineColor().r - from.getOutlineColor().r) / step;
	float vGOutline = (to.getOutlineColor().g - from.getOutlineColor().g) / step;
	float vBOutline = (to.getOutlineColor().b - from.getOutlineColor().b) / step;
	float vAOutline = (to.getOutlineColor().a - from.getOutlineColor().a) / step;
	for (int i = index1; i <= index2; i++)
	{
		sf::Color color;
		color.r = from.getFillColor().r + vR * (i - index1);
		color.g = from.getFillColor().g + vG * (i - index1);
		color.b = from.getFillColor().b + vB * (i - index1);
		color.a = from.getFillColor().a + vA * (i - index1);
		sf::Vector2f pos;
		pos.x = from.getPosition().x + vX * (i - index1);
		pos.y = from.getPosition().y + vY * (i - index1);
		sf::Color colorOutline;
		colorOutline.r = from.getOutlineColor().r + vROutline * (i - index1);
		colorOutline.g = from.getOutlineColor().g + vGOutline * (i - index1);
		colorOutline.b = from.getOutlineColor().b + vBOutline * (i - index1);
		colorOutline.a = from.getOutlineColor().a + vAOutline * (i - index1);
		w_nodes[index].setFillColor(color);
		w_nodes[index].setPosition(pos);
		w_nodes[index].setOutlineColor(colorOutline);
		w_frames[i].addNode("1wnodes" + std::to_string(index), w_nodes[index]);
	}
}

void SinglyLinkedListMainState::changeBEdge(int index, int index1, int index2, Edge from, Edge to)
{
	float step = (index2 - index1);

	float vStartX = (to.getStart().x - from.getStart().x) / step;
	float vStartY = (to.getStart().y - from.getStart().y) / step;
	float vEndX = (to.getEnd().x - from.getEnd().x) / step;
	float vEndY = (to.getEnd().y - from.getEnd().y) / step;
	for (int i = index1; i <= index2; i++)
	{


		sf::Vector2f start;
		start.x = from.getStart().x + vStartX * (i - index1);
		start.y = from.getStart().y + vStartY * (i - index1);
		sf::Vector2f end;
		end.x = from.getEnd().x + vEndX * (i - index1);
		end.y = from.getEnd().y + vEndY * (i - index1);

		b_edges[index].setStart(start);
		b_edges[index].setEnd(end);
		b_frames[i].addEdge("1bedges" + std::to_string(index), b_edges[index]);
	}
}

void SinglyLinkedListMainState::changeWEdge(int index, int index1, int index2, Edge from, Edge to)
{
	float step = (index2 - index1);
	float vStartX = (to.getStart().x - from.getStart().x) / step;
	float vStartY = (to.getStart().y - from.getStart().y) / step;
	float vEndX = (to.getEnd().x - from.getEnd().x) / step;
	float vEndY = (to.getEnd().y - from.getEnd().y) / step;
	for (int i = index1; i <= index2; i++)
	{
		sf::Color color;
		sf::Vector2f start;
		start.x = from.getStart().x + vStartX * (i - index1);
		start.y = from.getStart().y + vStartY * (i - index1);
		sf::Vector2f end;
		end.x = from.getEnd().x + vEndX * (i - index1);
		end.y = from.getEnd().y + vEndY * (i - index1);

		w_edges[index].setStart(start);
		w_edges[index].setEnd(end);
		w_frames[i].addEdge("1wedges" + std::to_string(index), w_edges[index]);
	}
}



void SinglyLinkedListMainState::initCreateFrames()
{
	std::vector<int> allElements = LinkedList.getAllElements();
	int numElements = allElements.size();
	int curBreakpoint = currentFrameIndex / 60;
	std::vector<std::string> codeLines = {
		"create linked list",
		"for each element in the list",
		"    insert element",
		"end"
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);

	deleteAllFrames();
	Engine::Frame b_frame, w_frame;

	initNode(allElements);
	initEdge(allElements);
	std::cerr << "curBreakpoint: " << currentFrameIndex << std::endl;
	for (int i = 0; i < curBreakpoint; i++)
	{
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if(i > 0)
		{
			b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
			w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
		}
	}

	for (int step = 0; step < 60; step++)
	{
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}

	Node node = b_nodes[curBreakpoint];
	node.setPosition(b_nodes[curBreakpoint].getPosition() - sf::Vector2f(RADIUS, 0));
	changeBNode(curBreakpoint, 1, 59, node, b_nodes[curBreakpoint]);
	node = w_nodes[curBreakpoint];
	node.setPosition(w_nodes[curBreakpoint].getPosition() - sf::Vector2f(RADIUS, 0));
	changeWNode(curBreakpoint, 1, 59, node, w_nodes[curBreakpoint]);

	if (curBreakpoint == 0)
		return;
	Edge edge = b_edges[curBreakpoint];
	edge.setEnd(b_nodes[curBreakpoint].getPosition() - sf::Vector2f(2*RADIUS , 0));
	changeBEdge(curBreakpoint, 1, 59, edge, b_edges[curBreakpoint]);
	edge = w_edges[curBreakpoint];
	edge.setEnd(w_nodes[curBreakpoint].getPosition() - sf::Vector2f(2 * RADIUS, 0));
	changeWEdge(curBreakpoint, 1, 59, edge, w_edges[curBreakpoint]);

}
void SinglyLinkedListMainState::initInsertFrames()
{
	std::vector<int> allElements = LinkedList.getAllElements();
	int numElements = allElements.size();
	int curBreakpoint = currentFrameIndex / 60;
	std::vector<std::string> codeLines = {
		"while k > 0 && node != nullptr",
		"    node = node -> next",
		"insert element",
		"end"
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);

	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	int v;
	if(kInsert != -1)
		v = vInsert;

	std::cerr << "kInsert" <<kInsert << std::endl;
	allElements.erase(allElements.begin() + kInsert);
	initNode(allElements);
	initEdge(allElements);
	
	std::cerr << "curBreakpoint: " << currentFrameIndex << std::endl;
	for (int i = 0; i < allElements.size(); i++)
	{
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (i > 0)
		{
			b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
			w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
		}
	}
	for (int step = 0; step < 60; step++)
	{
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}

	if (curBreakpoint < kInsert)
	{
		for(int i = 0;i < 60;i++)
			if(i < 30)
				codePanelColor[i][0] = sf::Color::Red;
			else
				codePanelColor[i][1] = sf::Color::Red;
		Node node = b_nodes[curBreakpoint];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(curBreakpoint, 0, 59, b_nodes[curBreakpoint], node);
		node = w_nodes[curBreakpoint];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(curBreakpoint, 0, 59, w_nodes[curBreakpoint], node);

		return;
	}
	else
	{
		for (int i = 0; i < 60; i++)
			if (i < 30)
				codePanelColor[i][0] = sf::Color::Red;
			else
				codePanelColor[i][2] = sf::Color::Red;

		for (int i = allElements.size() - 1; i >= kInsert; i--)
		{
			preb_nodes[i+1] = b_nodes[i];
			prew_nodes[i+1] = w_nodes[i];
			if(i > 0)
			{
				preb_edges[i+1] = b_edges[i];
				prew_edges[i+1] = w_edges[i];
				
			}
			b_nodes[i + 1] = b_nodes[i];
			w_nodes[i + 1] = w_nodes[i];
			if (i > 0)
			{
				b_edges[i + 1] = b_edges[i];
				w_edges[i + 1] = w_edges[i];
			}
		}
		allElements.insert(allElements.begin() + kInsert, v);
		initNode(allElements);
		initEdge(allElements);


		w_nodes[kInsert] = Node();
		w_nodes[kInsert].setRadius(RADIUS);
		w_nodes[kInsert].setOutlineThickness(-2);
		w_nodes[kInsert].setFillColor(W_NODE_COLOR);
		w_nodes[kInsert].setOutlineColor(sf::Color::Red);
		w_nodes[kInsert].setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		w_nodes[kInsert].setPosition(sf::Vector2f(PADDING_X + kInsert * DISTANCE_X, NODE_Y));
		w_nodes[kInsert].setCharacterSize(RADIUS);
		w_nodes[kInsert].setString(std::to_string(v));
		w_nodes[kInsert].setTextColor(sf::Color::Black);

		b_nodes[kInsert] = w_nodes[kInsert];
		b_nodes[kInsert].setOutlineColor(Orange);
		b_nodes[kInsert].setFillColor(sf::Color::White);
		b_nodes[kInsert].setPosition(sf::Vector2f(PADDING_X + kInsert * DISTANCE_X, NODE_Y));
		b_nodes[kInsert].setString(std::to_string(v));
		b_nodes[kInsert].setCharacterSize(CHARACTER_SIZE);
		b_nodes[kInsert].setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		b_nodes[kInsert].setTextColor(sf::Color::Black);
		preb_nodes[kInsert] = b_nodes[kInsert];
		preb_nodes[kInsert].setPosition(b_nodes[kInsert].getPosition() + sf::Vector2f(0, DISTANCE_X * 2));
		prew_nodes[kInsert] = w_nodes[kInsert];
		prew_nodes[kInsert].setPosition(w_nodes[kInsert].getPosition() + sf::Vector2f(0, DISTANCE_X * 2));
		if (kInsert > 0)
		{
			preb_edges[kInsert] = b_edges[kInsert];
			prew_edges[kInsert] = w_edges[kInsert];
			preb_edges[kInsert].setStart(b_nodes[kInsert - 1].getPosition());
			preb_edges[kInsert].setEnd(b_nodes[kInsert].getPosition() + sf::Vector2f(0, DISTANCE_X * 2));
			prew_edges[kInsert].setStart(w_nodes[kInsert - 1].getPosition());
			prew_edges[kInsert].setEnd(w_nodes[kInsert].getPosition() + sf::Vector2f(0, DISTANCE_X * 2));
		}
		if (kInsert != allElements.size())
		{
			preb_edges[kInsert + 1] = b_edges[kInsert + 1];
			prew_edges[kInsert + 1] = w_edges[kInsert + 1];
			preb_edges[kInsert + 1].setStart(b_nodes[kInsert ].getPosition());
			preb_edges[kInsert + 1].setEnd(b_nodes[kInsert + 1].getPosition() - sf::Vector2f(DISTANCE_X, 0));
			prew_edges[kInsert + 1].setStart(w_nodes[kInsert].getPosition());
			prew_edges[kInsert + 1].setEnd(w_nodes[kInsert + 1].getPosition() - sf::Vector2f(DISTANCE_X, 0));
		}

		for (int i = kInsert; i < allElements.size(); i++)
		{
			changeBNode(i, 0, 59, preb_nodes[i], b_nodes[i]);
			changeWNode(i, 0, 59, prew_nodes[i], w_nodes[i]);
			if (i > 0)
			{
				changeBEdge(i, 0, 59, preb_edges[i], b_edges[i]);
				changeWEdge(i, 0, 59, prew_edges[i], w_edges[i]);
			}
		}


	}



}
void SinglyLinkedListMainState::initDeleteFrames()
{

	std::vector<std::string> codeLines = {
	"node = head",
	"while node != nullptr",
	"    if node->val == v then delete",
	"    node = node -> next",
	"end"
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);

	std::vector<int> newElements = LinkedList.getAllElements();
	std::vector<int> oldElements = newElements;


	if (kDelete == -1)
	{
		int curBreakpoint = currentFrameIndex / 60;
		deleteAllFrames();
		Engine::Frame b_frame, w_frame;
		initNode(oldElements);
		initEdge(oldElements);

		for (int i = 0; i < oldElements.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (i > 0)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}

		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
			if(step < 30)
				codePanelColor[step][1] = sf::Color::Red;
			else
				codePanelColor[step][3] = sf::Color::Red;

			if (curBreakpoint == oldElements.size() - 1)
			{
				if(step < 20)
					codePanelColor[step][1] = sf::Color::Red;
				else if (step < 40)
					codePanelColor[step][3] = sf::Color::Red;
				else
					codePanelColor[step][4] = sf::Color::Red;
			}
		}

		Node node = b_nodes[curBreakpoint];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(curBreakpoint, 0, 59, b_nodes[curBreakpoint], node);
		node = w_nodes[curBreakpoint];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(curBreakpoint, 0, 59, w_nodes[curBreakpoint], node);
		return;

	}
	oldElements.insert(oldElements.begin() + kDelete, vDelete);

	int curBreakpoint = currentFrameIndex / 60;



	deleteAllFrames();
	Engine::Frame b_frame, w_frame;

	initNode(oldElements);
	initEdge(oldElements);



	if (curBreakpoint < kDelete)
	{
		for (int i = 0; i < oldElements.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (i > 0)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}
		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
			if (step < 30)
				codePanelColor[step][1] = sf::Color::Red;
			else
				codePanelColor[step][3] = sf::Color::Red;
		}
		Node node = b_nodes[curBreakpoint];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(curBreakpoint, 0, 59, b_nodes[curBreakpoint], node);
		node = w_nodes[curBreakpoint];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(curBreakpoint, 0, 59, w_nodes[curBreakpoint], node);

		return;
	}
	else
	{

		for(int i = 0;i < 60;i++)
			if (i < 30)
				codePanelColor[i][1] = sf::Color::Red;
			else
				codePanelColor[i][2] = sf::Color::Red;

		for (int i = kDelete; i < oldElements.size(); i++)
		{
			preb_nodes[i ] = b_nodes[i + 1];
			prew_nodes[i] = w_nodes[i + 1];
			if (i > 0)
			{
				preb_edges[i] = b_edges[i + 1];
				prew_edges[i] = w_edges[i + 1];
			}
		}



		initNode(newElements);
		initEdge(newElements);

		for (int i = 0; i < newElements.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (i > 0)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}
		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);

		}


		for (int i = kDelete; i < newElements.size(); i++)
		{
			changeBNode(i, 0, 59, preb_nodes[i], b_nodes[i]);
			changeWNode(i, 0, 59, prew_nodes[i], w_nodes[i]);
			if (i - 1 > 0)
			{
				changeBEdge(i, 0, 59, preb_edges[i], b_edges[i]);
				changeWEdge(i, 0, 59, prew_edges[i], w_edges[i]);
			}
		}
	}
}
void SinglyLinkedListMainState::initUpdateFrames()
{
	std::vector<int> allElements = LinkedList.getAllElements();
	int numElements = allElements.size();
	int curBreakpoint = currentFrameIndex / 60;
	std::vector<std::string> codeLines = {
		"node = head",
		"while node != nullptr",
		"    if node->val == oldV",
		"		node->val = newV",
		"    node = node -> next",
		"end"
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	
	initNode(allElements);
	initEdge(allElements);
	if (kUpdate == -1)
	{
		for (int i = 0; i < allElements.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (i > 0)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}
		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
			if (step < 30)
				codePanelColor[step][1] = sf::Color::Red;
			else
				codePanelColor[step][4] = sf::Color::Red;
		}
		Node node = b_nodes[curBreakpoint];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(curBreakpoint, 0, 59, b_nodes[curBreakpoint], node);
		node = w_nodes[curBreakpoint];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(curBreakpoint, 0, 59, w_nodes[curBreakpoint], node);
		return;
	}

	allElements[kUpdate] = oldVUpdate;
	initNode(allElements);
	initEdge(allElements);

	for (int i = 0; i < allElements.size(); i++)
	{
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (i > 0)
		{
			b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
			w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
		}
	}
	for (int step = 0; step < 60; step++)
	{
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
		if (step < 30)
			codePanelColor[step][1] = sf::Color::Red;
		else
			codePanelColor[step][4] = sf::Color::Red;
	}
	if (curBreakpoint < kUpdate)
	{
		Node node = b_nodes[curBreakpoint];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(curBreakpoint, 0, 59, b_nodes[curBreakpoint], node);
		node = w_nodes[curBreakpoint];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(curBreakpoint, 0, 59, w_nodes[curBreakpoint], node);
		return;
	}
	else
	{
		for (int i = 0; i < 60; i++)
			if (i < 20)
				codePanelColor[i][1] = sf::Color::Red;
			else if (i < 40)
				codePanelColor[i][2] = sf::Color::Red;
			else
				codePanelColor[i][3] = sf::Color::Red;
		allElements[kUpdate] = newVUpdate;
		initNode(allElements);
		initEdge(allElements);

		for (int i = 0; i < allElements.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (i > 0)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}
		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		Node node = b_nodes[kUpdate];
		node.setFillColor(sf::Color::Green);
		changeBNode(kUpdate, 0, 59, b_nodes[kUpdate], node);
		node = w_nodes[kUpdate];
		node.setFillColor(sf::Color::Green);
		changeWNode(kUpdate, 0, 59, w_nodes[kUpdate], node);

	}
}
void SinglyLinkedListMainState::initSearchFrames()
{
	std::vector<int> allElements = LinkedList.getAllElements();
	int curBreakpoint = currentFrameIndex / 60;
	deleteAllFrames();
	initNode(allElements);
	initEdge(allElements);
	std::vector<std::string> codeLines = {
		"node = head",
		"while node != nullptr",
		"    if node->val == v then return true",
		"    node = node -> next",
		"return false"
	};
	if (kSearch == -1)
	{
		for (int i = 0; i < codeLines.size(); i++)
			codePanel.setText(codeLines[i], i);
		deleteAllFrames();
		Engine::Frame b_frame, w_frame;
		for (int i = 0; i < allElements.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (i > 0)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}
		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);

			if (curBreakpoint == allElements.size() - 1)
			{
				if (step < 20)
					codePanelColor[step][1] = sf::Color::Red;
				else if (step < 40)
					codePanelColor[step][3] = sf::Color::Red;
				else
					codePanelColor[step][4] = sf::Color::Red;
			}
			else 			if (step < 30)
				codePanelColor[step][1] = sf::Color::Red;
			else
				codePanelColor[step][3] = sf::Color::Red;
		}
		Node node = b_nodes[curBreakpoint];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(curBreakpoint, 0, 59, b_nodes[curBreakpoint], node);
		node = w_nodes[curBreakpoint];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(curBreakpoint, 0, 59, w_nodes[curBreakpoint], node);
		return;
	}
	

	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);
	Engine::Frame b_frame, w_frame;
	for (int i = 0; i < allElements.size(); i++)
	{
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (i > 0)
		{
			b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
			w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
		}
	}

	if (curBreakpoint == kSearch)
	{
		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);

			if (step < 30)
				codePanelColor[step][1] = sf::Color::Red;
			else
				codePanelColor[step][2] = sf::Color::Red;
		}
		Node node = b_nodes[curBreakpoint];
		node.setFillColor(sf::Color::Green);
		changeBNode(curBreakpoint, 0, 59, b_nodes[curBreakpoint], node);
		node = w_nodes[curBreakpoint];
		node.setFillColor(sf::Color::Green);
		changeWNode(curBreakpoint, 0, 59, w_nodes[curBreakpoint], node);
		return;
	}
	for (int step = 0; step < 60; step++)
	{
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	if (step < 30)
			codePanelColor[step][1] = sf::Color::Red;
		else
			codePanelColor[step][3] = sf::Color::Red;
	}

	Node node = b_nodes[curBreakpoint];
	node.setFillColor(B_NODE_COLOR_HOVER);
	changeBNode(curBreakpoint, 0, 59, b_nodes[curBreakpoint], node);
	node = w_nodes[curBreakpoint];
	node.setFillColor(W_NODE_COLOR_HOVER);
	changeWNode(curBreakpoint, 0, 59, w_nodes[curBreakpoint], node);
	std::cerr << "k search " << kSearch << std::endl;
}


void SinglyLinkedListMainState::createCreateFrames(const std::vector<int>& nums)
{
	currentState = "create";
	deleteAllFrames();
	breakpoints.clear();
	LinkedList.removeAll();
	if (nums.size() == 0)
	{
		
	}
	for (int x : nums) {
		LinkedList.insert(x);
	}
	std::vector<int> allElements;
	for (int i = 0; i < nums.size(); i++)
	{
		allElements.push_back(nums[i]);
		if(i != 0)
		breakpoints.push_back(i * 60);
		else
			breakpoints.push_back(0);
	}
	breakpoints.push_back(nums.size() * 60 - 1);

	aniSlider.setNumPart(allElements.size() * 60);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = allElements.size() * 60;


}
void SinglyLinkedListMainState::createInsertFrames(int k, int v)
{
	currentState = "insert";
	deleteAllFrames();
	breakpoints.clear();
	LinkedList.insert(k, v);
	std::vector<int> allElements = LinkedList.getAllElements();
	int numElements = allElements.size();
	kInsert = k;
	vInsert = v;
	std::cerr << "k INSERT " << kInsert << std::endl;
	for (int i = 0; i <= kInsert; i++)
	{
		breakpoints.push_back(i * 60);

	}

	breakpoints.push_back((kInsert+1) * 60 - 1);
	aniSlider.setNumPart((kInsert+1) * 60);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = (kInsert+1) * 60;
	
}
void SinglyLinkedListMainState::createDeleteFrame(int v)
{
	currentState = "delete";
	deleteAllFrames();
	breakpoints.clear();

	kDelete = LinkedList.search(v);
	if (kDelete == -1) {
		kDelete = -1;
		std::vector<int> allElements = LinkedList.getAllElements();
		for(int i = 0;i < allElements.size();i++)
			breakpoints.push_back(i * 60);
		breakpoints.push_back(allElements.size() * 60 - 1);
		aniSlider.setNumPart(allElements.size() * 60);
		aniSlider.setBreakpoints(breakpoints);
		aniSlider.setPart(0);
		currentFrameIndex = 0;
		isPlaying = true;
		isPaused = false;
		isEnd = false;
		numFrames = allElements.size() * 60;
		return;
	}

	vDelete = v;
	LinkedList.deleteElement(v);

	std::vector<int> allElements = LinkedList.getAllElements();
	int numElements = allElements.size();

	for (int i = 0; i <= kDelete; i++)
	{
		breakpoints.push_back(i * 60);
	}
	breakpoints.push_back((kDelete + 1) * 60 - 1);

	aniSlider.setNumPart((kDelete + 1) * 60);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);

	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = (kDelete + 1) * 60;
}
void SinglyLinkedListMainState::createSearchFrames(int num)
{
	currentState = "search";
	deleteAllFrames();
	breakpoints.clear();

	kSearch = LinkedList.search(num);
	if (kSearch == -1) {
		std::vector<int> allElements = LinkedList.getAllElements();
		for (int i = 0; i < allElements.size(); i++)
			breakpoints.push_back(i * 60);
		breakpoints.push_back(allElements.size() * 60 - 1);
		aniSlider.setNumPart(allElements.size() * 60);
		aniSlider.setBreakpoints(breakpoints);
		aniSlider.setPart(0);
		currentFrameIndex = 0;
		isPlaying = true;
		isPaused = false;
		isEnd = false;
		numFrames = allElements.size() * 60;
		return;
	}

	std::vector<int> allElements = LinkedList.getAllElements();
	int numElements = allElements.size();

	for (int i = 0; i <= kSearch; i++)
	{
		breakpoints.push_back(i * 60);
	}
	breakpoints.push_back(kSearch * 60 + 60 - 1);

	aniSlider.setNumPart(kSearch * 60 + 60);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);

	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = (kSearch+1) * 60 ;


}
void SinglyLinkedListMainState::createUpdateFrames(int oldV, int newV)
{
	currentState = "update";
	deleteAllFrames();
	breakpoints.clear();
	kUpdate = LinkedList.search(oldV);
	oldVUpdate = oldV;
	newVUpdate = newV;
	if (kUpdate == -1) {
		std::vector<int> allElements = LinkedList.getAllElements();
		for (int i = 0; i < allElements.size(); i++)
			breakpoints.push_back(i * 60);
		breakpoints.push_back(allElements.size() * 60 - 1);
		aniSlider.setNumPart(allElements.size() * 60);
		aniSlider.setBreakpoints(breakpoints);
		aniSlider.setPart(0);
		currentFrameIndex = 0;
		isPlaying = true;
		isPaused = false;
		isEnd = false;
		numFrames = allElements.size() * 60;
		return;
	}
	LinkedList.update(oldV, newV);
	std::vector<int> allElements = LinkedList.getAllElements();
	int numElements = allElements.size();
	for (int i = 0; i <= kUpdate; i++)
	{
		breakpoints.push_back(i * 60);
	}
	breakpoints.push_back((kUpdate + 1) * 60 - 1);
	aniSlider.setNumPart((kUpdate + 1) * 60);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = (kUpdate + 1) * 60;
}


void SinglyLinkedListMainState::updateFrames()
{
	if (numFrames == 0) return;
	if (numFrames > 0) currentFrameIndex = std::min(currentFrameIndex, numFrames - 1);
	if (currentFrameIndex == 0 || aniSlider.getBreakpoints(prevFrameIndex) != aniSlider.getBreakpoints(currentFrameIndex)) {
		if (currentState == "create")
		{
			initCreateFrames();	
		}	
		if (currentState == "insert")
		{
			initInsertFrames();
		}
		if (currentState == "delete")
		{
			initDeleteFrames();
		}
		if (currentState == "search")
		{
			initSearchFrames();
		}
		if (currentState == "update")
		{
			initUpdateFrames();
		}

	}

	prevFrameIndex = currentFrameIndex;
	if (isPlaying)
	{

		if (numFrames > 0)
		{
			if (currentFrameIndex < numFrames - 1)
			{
				isEnd = false;
				if (1)
				{
					int curFrame = currentFrameIndex - aniSlider.getBreakpoints(currentFrameIndex);
					b_currentFrame = b_frames[curFrame];
					w_currentFrame = w_frames[curFrame];
					setCodePanelColor(curFrame);
				}

				if (*m_context->themeType == 0)
					currentFrame = b_currentFrame;
				else
					currentFrame = w_currentFrame;

				if (isPaused == false) {

					currentFrameIndex += speed;
					currentFrameIndex = std::min(numFrames - 1, currentFrameIndex);
				}
			}
			else
			{
				isEnd = true;
				isPaused = true;
				currentFrameIndex = numFrames - 1;
				aniSlider.setPart(currentFrameIndex + 1);
				if (*m_context->themeType == 0)
					currentFrame = b_frames.back();
				else
					currentFrame = w_frames.back();

			}
		}
	}
}