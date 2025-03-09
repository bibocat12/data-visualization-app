#include "SinglyLinkedListFrame.h"
//
//
SinglyLinkedListFrame::SinglyLinkedListFrame()
{
}

SinglyLinkedListFrame::SinglyLinkedListFrame(std::shared_ptr<Context>& context)
{
	m_context = context;
	//initNode();
}

SinglyLinkedListFrame::~SinglyLinkedListFrame()
{
}

void SinglyLinkedListFrame::initContext(std::shared_ptr<Context>& context)
{
	m_context = context;
}

void SinglyLinkedListFrame::initNode()
{
	for (int i = 0; i < 21; i++)
	{
		Node node;

		node.setFillColor(sf::Color::White);			// set color for node in white theme
		node.setOutlineColor(sf::Color::Red);
		node.setOutlineThickness(-5);
		node.setRadius(RADIUS);
		node.setPosition(sf::Vector2f(PADDING_X + i * DISTANCE_X, NODE_Y));
		node.setCharacterSize(20);
		node.setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		node.setTextColor(sf::Color::Black);


		b_nodes[i] = node;

		node.setFillColor(sf::Color::White);			// set color for node in black theme
		node.setOutlineColor(Orange);
		w_nodes[i] = node;
	}
}

void SinglyLinkedListFrame::initEdge()
{
	for (int i = 0; i < 21; i++)
	{
		Edge edge;
		edge.setColor(sf::Color::Black);			// set color for edge in white theme
		edge.setThickness(5);
		edge.setStart(sf::Vector2f(PADDING_X + i * DISTANCE_X, EDGE_Y ));
		edge.setEnd(sf::Vector2f(PADDING_X + (i + 1) * DISTANCE_X - RADIUS , EDGE_Y));
		edge.setDirected(true);
		b_edges[i] = edge;
		edge.setColor(sf::Color::White);			// set color for edge in black theme
		edge.setThickness(5);
		edge.setStart(sf::Vector2f(PADDING_X + i * DISTANCE_X, EDGE_Y));
		edge.setEnd(sf::Vector2f(PADDING_X + (i + 1) * DISTANCE_X - RADIUS , EDGE_Y));

		w_edges[i] = edge;
	}
}

void SinglyLinkedListFrame::initCodePanel()
{
	int numLine = 7;
	float checkpointY = 650;
	sf::Color textColor = sf::Color::White;
	sf::Vector2f labelSize = sf::Vector2f(500, static_cast<float>((SCREEN_HEIGHT - 20 - checkpointY) / numLine));
	codePanel = Panel(sf::Vector2f{ SCREEN_WIDTH - 10 - labelSize.x,  checkpointY }, labelSize, textColor, LavenderSoft, m_context->assetManager->getFont("JetBrainsMono-Regular"), 18);
	codePanel.add("insert v");
	codePanel.add("for i");
	codePanel.add("");
	codePanel.add("");
	codePanel.add("");
	codePanel.add("");
	codePanel.add("");
}

void SinglyLinkedListFrame::setLinkedList(SinglyLinkedList& list)
{
	LinkedList = list;
}

void SinglyLinkedListFrame::deleteAllFrames()
{
	b_frames.clear();
	w_frames.clear();
	breakpoints.clear();
}

void SinglyLinkedListFrame::moveNodeEdge(int index, int index1, int index2, sf::Vector2f start, sf::Vector2f end)
{
	for (int i = index1; i <= index2; i++)
	{
		sf::Vector2f pos;
		pos.x = start.x + (i - index1) * (end.x - start.x) / (index2 - index1);
		pos.y = start.y + (i - index1) * (end.y - start.y) / (index2 - index1);
		sf::Vector2f posEndEdge;
		posEndEdge.x = start.x + (i - index1) * (end.x - start.x) / (index2 - index1) - RADIUS;
		posEndEdge.y = EDGE_Y;
		b_nodes[index].setPosition(pos);
		w_nodes[index].setPosition(pos);
		b_edges[index].setStart(sf::Vector2f(start.x, EDGE_Y));
		w_edges[index].setStart(sf::Vector2f(start.x, EDGE_Y));
		b_edges[index].setEnd(posEndEdge);
		w_edges[index].setEnd(posEndEdge);
		b_frames[i].init(b_frames[i - 1]);
		w_frames[i].init(w_frames[i - 1]);
		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
		w_frames[i].addNode("1wnodes" + std::to_string(index), w_nodes[index]);
		b_frames[i].addEdge("2bedges" + std::to_string(index), b_edges[index]);
		w_frames[i].addEdge("2wedges" + std::to_string(index), w_edges[index]);
	}
}

void SinglyLinkedListFrame::moveNode(int index, int index1, int index2, sf::Vector2f start, sf::Vector2f end)
{
	for (int i = index1; i <= index2; i++)
	{
		sf::Vector2f pos;
		pos.x = start.x + (i - index1) * (end.x - start.x) / (index2 - index1);
		pos.y = start.y + (i - index1) * (end.y - start.y) / (index2 - index1);
		b_nodes[index].setPosition(pos);
		w_nodes[index].setPosition(pos);

		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
		w_frames[i].addNode("1wnodes" + std::to_string(index), w_nodes[index]);
	}
}

void SinglyLinkedListFrame::moveEdge(int index, int index1, int index2, 
	sf::Vector2f start1, sf::Vector2f start2, 
	sf::Vector2f end1, sf::Vector2f end2)
{
	for (int i = index1; i <= index2; i++)
	{
		sf::Vector2f posStart;
		sf::Vector2f posEnd;
		posStart.x = start1.x + (i - index1) * (start2.x - start1.x) / (index2 - index1);
		posStart.y = start1.y + (i - index1) * (start2.y - start1.y) / (index2 - index1);
		posEnd.x = end1.x + (i - index1) * (end2.x - end1.x) / (index2 - index1);
		posEnd.y = end1.y + (i - index1) * (end2.y - end1.y) / (index2 - index1);
		b_edges[index].setStart(posStart);
		b_edges[index].setEnd(posEnd);
		w_edges[index].setStart(posStart);
		w_edges[index].setEnd(posEnd);

		b_frames[i].addEdge("2bedges" + std::to_string(index), b_edges[index]);
		w_frames[i].addEdge("2wedges" + std::to_string(index), w_edges[index]);


	}
}



void SinglyLinkedListFrame::changeBColor(int index, int index1, int index2, sf::Color from, sf::Color to)
{
	float step = (index2 - index1);
	float vR = (to.r - from.r) / step;
	float vG = (to.g - from.g) / step;
	float vB = (to.b - from.b) / step;
	for (int i = index1; i <= index2; i++)
	{
		sf::Color color;
		color.r = from.r + vR * (i - index1);
		color.g = from.g + vG * (i - index1);
		color.b = from.b + vB * (i - index1);
		b_nodes[index].setTextColor(color);
		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
	}
}

void SinglyLinkedListFrame::changeWColor(int index, int index1, int index2, sf::Color from, sf::Color to)
{
	float step = (index2 - index1);
	float vR = (to.r - from.r) / step;
	float vG = (to.g - from.g) / step;
	float vB = (to.b - from.b) / step;
	for (int i = index1; i <= index2; i++)
	{
		sf::Color color;
		color.r = from.r + vR * (i - index1);
		color.g = from.g + vG * (i - index1);
		color.b = from.b + vB * (i - index1);
		w_nodes[index].setTextColor(color);
		w_frames[i].addNode("1wnodes" + std::to_string(index), w_nodes[index]);
	}
}

std::vector<Engine::Frame> SinglyLinkedListFrame::getBFrames()
{
	return b_frames;
}

std::vector<Engine::Frame> SinglyLinkedListFrame::getWFrames()
{
	return w_frames;
}

std::vector<int> SinglyLinkedListFrame::getBreakpoints()
{
	return breakpoints;
}



void SinglyLinkedListFrame::initCreateFrames()
{
	deleteAllFrames();
	initCodePanel();
	codePanel.setText("for x in elements", 0);
	codePanel.setText("    insert(x)", 1);
	codePanel.setText("return", 2);
	std::vector<int> allElements;
	allElements = LinkedList.getAllElements();
	for(int x: allElements)
		std::cerr << x << " ";
	initNode();
	initEdge();
	for (int i = 0; i < allElements.size(); i++)
	{
		b_nodes[i].setString(std::to_string(allElements[i]));
		w_nodes[i].setString(std::to_string(allElements[i]));
	}

	breakpoints.push_back(0);
	for (int i = 0; i < 60; i++)
	{
		Engine::Frame b_frame, w_frame;
		b_nodes[0].setString(std::to_string(allElements[0]));
		w_nodes[0].setString(std::to_string(allElements[0]));
		b_frame.addNode("1bnodes0", b_nodes[0]);
		w_frame.addNode("1swnodes0", w_nodes[0]);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	for (int i = 1; i < allElements.size(); i++)
	{
		int firstIndex = b_frames.size();
		int lastIndex = b_frames.size() + 60 - 1;
		for (int j = 0; j < 60; j++)
		{
			Engine::Frame b_frame, w_frame;
			b_nodes[i].setString(std::to_string(allElements[i]));
			w_nodes[i].setString(std::to_string(allElements[i]));
			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(2, LavenderSoft);
			b_frame.init(b_frames[b_frames.size() - 1]);
			w_frame.init(w_frames[w_frames.size() - 1]);
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		moveNodeEdge(i, firstIndex, lastIndex, sf::Vector2f(PADDING_X + (i - 1) * DISTANCE_X, NODE_Y), sf::Vector2f(PADDING_X + i * DISTANCE_X, NODE_Y));
		breakpoints.push_back(b_frames.size() - 1);
	}

}
void SinglyLinkedListFrame::initInsertFrames(int k, int v)
{
	std::vector<int> allElements = LinkedList.getAllElements();
	int size = allElements.size();
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	initNode();
	initEdge();
	initCodePanel();
	
	for (int i = 0; i < size; i++)
	{
		b_nodes[i].setString(std::to_string(allElements[i]));
		w_nodes[i].setString(std::to_string(allElements[i]));
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (i < size - 1)
		{
			b_frame.addEdge("2bedges" + std::to_string(i), b_edges[i]);
			w_frame.addEdge("2wedges" + std::to_string(i), w_edges[i]);
		}
	}
	codePanel.setText("current = head", 0);
	codePanel.setText("while k > 0 and current != NULL", 1);
	codePanel.setText("    current = current->next", 2);
	codePanel.setText("    k--", 3);
	codePanel.setText("newNode = new Node(v)", 4);
	codePanel.setText("newNode->next = current->next", 5);
	codePanel.setText("current->next = newNode", 6);
	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);
	for (int i = 0; i < std::min(k, (int)allElements.size()); i++)
	{
		int x = allElements[i];
		int firstIndex = b_frames.size();
		int lastIndex = firstIndex + 120 - 1;
		for (int step = 0; step < 120; step++)
		{
			Engine::Frame b_frame, w_frame;
			b_frame.init(b_frames.back());
			w_frame.init(w_frames.back());
			codePanel.setLineColor(0, LavenderSoft);
			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(2, LavenderSoft);
			codePanel.setLineColor(3, LavenderSoft);
			codePanel.setLineColor(4, LavenderSoft);
			codePanel.setLineColor(5, LavenderSoft);
			codePanel.setLineColor(6, LavenderSoft);
			if (step <= 60)
				codePanel.setLineColor(1, sf::Color::Red);
			else
			{
				codePanel.setLineColor(2, sf::Color::Red);
				codePanel.setLineColor(3, sf::Color::Red);
			}
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);

			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		changeBColor(i, firstIndex, lastIndex, sf::Color::Black, sf::Color::Blue);
		changeWColor(i, firstIndex, lastIndex, sf::Color::Black, sf::Color::Blue);
		breakpoints.push_back(b_frames.size() - 1);
	}

	Node& b_newNode = b_nodes[20];
	Node & w_newNode = w_nodes[20];
	b_newNode.setString(std::to_string(v));
	w_newNode.setString(std::to_string(v));
	b_newNode.setFillColor(sf::Color::White);
	w_newNode.setFillColor(sf::Color::White);
	b_newNode.setOutlineColor(sf::Color::Red);
	w_newNode.setOutlineColor(Orange);
	b_newNode.setOutlineThickness(-5);
	w_newNode.setOutlineThickness(-5);
	b_newNode.setRadius(RADIUS);
	w_newNode.setRadius(RADIUS);
	b_newNode.setPosition(sf::Vector2f(PADDING_X + k * DISTANCE_X, NODE_Y + DISTANCE_X ));
	w_newNode.setPosition(sf::Vector2f(PADDING_X + k * DISTANCE_X, NODE_Y + DISTANCE_X));
	b_newNode.setCharacterSize(20);
	w_newNode.setCharacterSize(20);
	b_newNode.setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
	w_newNode.setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
	b_newNode.setTextColor(sf::Color::Black);
	w_newNode.setTextColor(sf::Color::Black);

	codePanel.setLineColor(0, LavenderSoft);
	codePanel.setLineColor(1, LavenderSoft);
	codePanel.setLineColor(2, LavenderSoft);
	codePanel.setLineColor(3, LavenderSoft);
	codePanel.setLineColor(4, LavenderSoft);
	codePanel.setLineColor(5, LavenderSoft);
	codePanel.setLineColor(6, LavenderSoft);
	codePanel.setLineColor(4, sf::Color::Red);
	for (int step = 0; step < 30; step++)
	{
		Engine::Frame b_frame, w_frame;

		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());

		b_frame.addNode("1bnodes20", b_newNode);
		w_frame.addNode("1wnodes20", w_newNode);

		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);

		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);

	}
	codePanel.setLineColor(4, LavenderSoft);
	codePanel.setLineColor(5, sf::Color::Red);
	codePanel.setLineColor(6, sf::Color::Red);


	b_edges[20].setStart(sf::Vector2f(PADDING_X + k * DISTANCE_X, EDGE_Y + DISTANCE_X));
	b_edges[20].setEnd(sf::Vector2f(PADDING_X + k * DISTANCE_X, EDGE_Y + RADIUS));
	w_edges[20].setStart(sf::Vector2f(PADDING_X + k * DISTANCE_X, EDGE_Y + DISTANCE_X));
	w_edges[20].setEnd(sf::Vector2f(PADDING_X + k * DISTANCE_X, EDGE_Y + RADIUS));

	sf::Vector2f startEdge1 = sf::Vector2f(PADDING_X + (k-1) * DISTANCE_X, EDGE_Y);
	sf::Vector2f endEdge1 = sf::Vector2f(PADDING_X + k * DISTANCE_X - RADIUS , EDGE_Y + DISTANCE_X);
	if (k > 0)
	{
		b_edges[k - 1].setStart(startEdge1);
		b_edges[k - 1].setEnd(endEdge1);
		w_edges[k - 1].setStart(startEdge1);
		w_edges[k - 1].setEnd(endEdge1);
	}


	for (int step = 0; step < 30; step++)
	{
		Engine::Frame b_frame, w_frame;
		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());
		if(k > 0)
		{
			b_frame.addEdge("2bedges" + std::to_string(k-1), b_edges[k-1]);
			w_frame.addEdge("2wedges" + std::to_string(k-1), w_edges[k-1]);
		}	
		if (k != size) {
			b_frame.addEdge("2bedges20", b_edges[20]);
			w_frame.addEdge("2wedges20", w_edges[20]);
		}
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	int firstIndex = b_frames.size();
	int lastIndex = b_frames.size() + 60 - 1;
	for (int step = 0; step < 60; step++)
	{
		Engine::Frame b_frame, w_frame;
		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());

		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}

	for (int j = k; j < size; j++)
		moveNode(j, firstIndex, lastIndex, sf::Vector2f(PADDING_X + (j) * DISTANCE_X, NODE_Y), sf::Vector2f(PADDING_X + (j+1) * DISTANCE_X, NODE_Y));

	for (int j = k; j < size - 1; j++)
	{
		sf::Vector2f startEdge1 = sf::Vector2f(PADDING_X + (j ) * DISTANCE_X, EDGE_Y);
		
		sf::Vector2f startEdge2 = sf::Vector2f(PADDING_X + (j + 1) * DISTANCE_X, EDGE_Y);
		sf::Vector2f endEdge1 =   sf::Vector2f(PADDING_X + (j + 1) * DISTANCE_X - RADIUS, EDGE_Y);
		sf::Vector2f endEdge2 =   sf::Vector2f(PADDING_X + (j + 2) * DISTANCE_X - RADIUS, EDGE_Y);
		moveEdge(j, firstIndex, lastIndex, startEdge1, startEdge2, endEdge1, endEdge2);
	}
	if(k != size)
	moveEdge(20, firstIndex, lastIndex, 
		sf::Vector2f(PADDING_X + k * DISTANCE_X, EDGE_Y + DISTANCE_X), sf::Vector2f(PADDING_X + k * DISTANCE_X, EDGE_Y),
		sf::Vector2f(PADDING_X + k * DISTANCE_X, EDGE_Y + RADIUS), sf::Vector2f(PADDING_X + (k+1) * DISTANCE_X - RADIUS, EDGE_Y)
	);
	
	if (k > 0)
	{
		
		sf::Vector2f posStart, posEnd;
		posEnd.x = PADDING_X + k * DISTANCE_X - RADIUS;
		posEnd.y = EDGE_Y;

		posStart.x = PADDING_X + (k - 1) * DISTANCE_X;
		posStart.y = EDGE_Y;

		moveEdge(k - 1, firstIndex, lastIndex, startEdge1, startEdge1, endEdge1, posEnd);
	}
	moveNode(20, firstIndex, lastIndex, 
		sf::Vector2f(PADDING_X + k * DISTANCE_X, NODE_Y + DISTANCE_X), sf::Vector2f(PADDING_X + k * DISTANCE_X, NODE_Y));
	breakpoints.push_back(b_frames.size() - 1);
}

void SinglyLinkedListFrame::initDeleteFrames(int v)
{
	std::vector<int> allElements = LinkedList.getAllElements();
	int size = allElements.size();
	int deleteIndex = -1;
	for (int i = 0; i < size; i++)
	{
		if (allElements[i] == v)
		{
			deleteIndex = i;
			break;
		}
	}
	if (deleteIndex == -1)
		return;

	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	initNode();
	initEdge();
	initCodePanel();
	for (int i = 0; i < size; i++)
	{
		b_nodes[i].setString(std::to_string(allElements[i]));
		w_nodes[i].setString(std::to_string(allElements[i]));
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (i < size - 1)
		{
			b_frame.addEdge("2bedges" + std::to_string(i), b_edges[i]);
			w_frame.addEdge("2wedges" + std::to_string(i), w_edges[i]);
		}
	}
	codePanel.setText("current = head", 0);
	codePanel.setText("while(current != NULL and current->data != v)", 1);
	codePanel.setText("    prev = current", 2);
	codePanel.setText("    current = current->next", 3);
	codePanel.setText("if(current != NULL)", 4);
	codePanel.setText("    prev->next = current->next", 5);
	codePanel.setText("    delete current", 6);
	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);

	for (int i = 0; i < std::min(deleteIndex, size); i++)
	{
		int firstIndex = b_frames.size();
		int lastIndex = firstIndex + 120 - 1;
		for (int step = 0; step < 120; step++)
		{
			Engine::Frame b_frame, w_frame;
			b_frame.init(b_frames.back());
			w_frame.init(w_frames.back());
			codePanel.setLineColor(0, LavenderSoft);
			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(2, LavenderSoft);
			codePanel.setLineColor(3, LavenderSoft);
			codePanel.setLineColor(4, LavenderSoft);
			codePanel.setLineColor(5, LavenderSoft);
			codePanel.setLineColor(6, LavenderSoft);
			if (step <= 60)
				codePanel.setLineColor(1, sf::Color::Red);
			else
			{
				codePanel.setLineColor(2, sf::Color::Red);
				codePanel.setLineColor(3, sf::Color::Red);
			}
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		changeBColor(i, b_frames.size() - 120, b_frames.size() - 1, sf::Color::Black, sf::Color::Blue);
		changeWColor(i, w_frames.size() - 120, w_frames.size() - 1, sf::Color::Black, sf::Color::Blue);
		breakpoints.push_back(b_frames.size() - 1);
	}

	int deletionStart = b_frames.size();
	int deletionEnd = deletionStart + 30 - 1;
	for (int step = 0; step < 30; step++)
	{
		Engine::Frame b_frame, w_frame;
		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());
		sf::Vector2f startPos = b_nodes[deleteIndex].getPosition();
		sf::Vector2f endPos = startPos; endPos.y += DISTANCE_X;
		sf::Vector2f newPos;
		newPos.x = startPos.x;
		newPos.y = startPos.y + (endPos.y - startPos.y) * step / 30.0f;
		b_nodes[deleteIndex].setPosition(newPos);
		w_nodes[deleteIndex].setPosition(newPos);
		b_frame.addNode("1bnodes" + std::to_string(deleteIndex), b_nodes[deleteIndex]);
		w_frame.addNode("1wnodes" + std::to_string(deleteIndex), w_nodes[deleteIndex]);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}

	int shiftStart = b_frames.size();
	int shiftEnd = shiftStart + 60 - 1;
	
	for (int step = 0; step < 60; step++)
	{
		Engine::Frame b_frame, w_frame;
		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	for (int j = deleteIndex + 1; j < size; j++)
	{
		moveNode(j, shiftStart, shiftEnd,
			sf::Vector2f(PADDING_X + j * DISTANCE_X, NODE_Y),
			sf::Vector2f(PADDING_X + (j - 1) * DISTANCE_X, NODE_Y));
	}

	for (int j = deleteIndex; j < size - 1; j++)
	{
		sf::Vector2f startEdge1 = sf::Vector2f(PADDING_X + j * DISTANCE_X, EDGE_Y);
		sf::Vector2f startEdge2 = sf::Vector2f(PADDING_X + (j - 1) * DISTANCE_X, EDGE_Y);
		sf::Vector2f endEdge1 = sf::Vector2f(PADDING_X + (j + 1) * DISTANCE_X - RADIUS, EDGE_Y);
		sf::Vector2f endEdge2 = sf::Vector2f(PADDING_X + j * DISTANCE_X - RADIUS, EDGE_Y);
		moveEdge(j, shiftStart, shiftEnd, startEdge1, startEdge2, endEdge1, endEdge2);
	}


	if (deleteIndex > 0)
	{
		sf::Vector2f posStart(PADDING_X + (deleteIndex - 1) * DISTANCE_X, EDGE_Y);
		sf::Vector2f posEnd(PADDING_X + deleteIndex * DISTANCE_X - RADIUS, EDGE_Y);
		moveEdge(deleteIndex - 1, shiftStart, shiftEnd, posStart, posStart, posEnd, posEnd);
	}
	breakpoints.push_back(b_frames.size() - 1);
}

void SinglyLinkedListFrame::initUpdateFrames(int oldV, int newV)
{
	std::vector<int> allElements;
	allElements = LinkedList.getAllElements();
	deleteAllFrames();
	initCodePanel();
	initNode();
	initEdge();
	int size = allElements.size();
	Engine::Frame b_frame, w_frame;
	for (int i = 0; i < allElements.size(); i++)
	{
		int x = allElements[i];
		b_nodes[i].setString(std::to_string(allElements[i]));
		w_nodes[i].setString(std::to_string(allElements[i]));
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (i < size - 1)
		{
			b_frame.addEdge("2bedges" + std::to_string(i), b_edges[i]);
			w_frame.addEdge("2wedges" + std::to_string(i), w_edges[i]);
		}
	}

	codePanel.setText("current = head", 0);
	codePanel.setText("while current != NULL", 1);
	codePanel.setText("    if current->data == x", 2);
	codePanel.setText("        current->data = v", 3);
	codePanel.setText("    current = current->next", 4);


	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);

	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);

	for (int i = 0; i < allElements.size(); i++)
	{
		int x = allElements[i];
		int firstIndex = b_frames.size();
		int lastIndex = firstIndex + 120 - 1;
		for (int i = 0; i < 60; i++)
		{
			Engine::Frame b_frame, w_frame;
			b_frame.init(b_frames.back());
			w_frame.init(w_frames.back());
			codePanel.setLineColor(0, LavenderSoft);
			codePanel.setLineColor(1, sf::Color::Red);
			codePanel.setLineColor(2, LavenderSoft);
			codePanel.setLineColor(3, LavenderSoft);
			codePanel.setLineColor(4, LavenderSoft);
			codePanel.setLineColor(5, LavenderSoft);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		changeBColor(i, firstIndex, lastIndex - 90, sf::Color::Black, sf::Color::Blue);
		changeWColor(i, firstIndex, lastIndex - 90, sf::Color::Black, sf::Color::Blue);
		changeBColor(i, lastIndex - 90 + 1, lastIndex - 60, sf::Color::Blue, sf::Color::Blue);
		changeWColor(i, lastIndex - 90 + 1, lastIndex - 60, sf::Color::Blue, sf::Color::Blue);
		if (x == oldV)
		{
			int firstIndex = b_frames.size();
			int lastIndex = b_frames.size() + 60 - 1;
			for (int step = 0; step < 60; step++)
			{
				Engine::Frame b_frame, w_frame;
				b_frame.init(b_frames.back());
				w_frame.init(w_frames.back());
				b_nodes[i].setString(std::to_string(newV));
				w_nodes[i].setString(std::to_string(newV));
				codePanel.setLineColor(1, LavenderSoft);
				codePanel.setLineColor(2, sf::Color::Red);
				codePanel.setLineColor(3, sf::Color::Red);
				codePanel.setLineColor(4, LavenderSoft);
				codePanel.setLineColor(5, LavenderSoft);
				b_frame.addPanel("3bcodePanel", codePanel);
				w_frame.addPanel("3wcodePanel", codePanel);
				b_frames.push_back(b_frame);
				w_frames.push_back(w_frame);
			}
			changeBColor(i, firstIndex, lastIndex, sf::Color::Red, sf::Color::Green);
			changeWColor(i, firstIndex, lastIndex, sf::Color::Red, sf::Color::Green);
			breakpoints.push_back(b_frames.size() - 1);
			break;
		}

		for (int i = 0; i < 60; i++)
		{
			Engine::Frame b_frame, w_frame;
			b_frame.init(b_frames.back());
			w_frame.init(w_frames.back());
			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(4, sf::Color::Red);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		breakpoints.push_back(b_frames.size() - 1);

	}
}



void SinglyLinkedListFrame::initSearchFrames(int num)
{
	std::vector<int> allElements = LinkedList.getAllElements();
	deleteAllFrames();
	initCodePanel();
	initNode();
	initEdge();
	Engine::Frame b_frame, w_frame;

	codePanel.setText("current = head", 0);
	codePanel.setText("while current != NULL and current->data != " + std::to_string(num), 1);
	codePanel.setText("    current = current->next", 2);
	codePanel.setText("if current == NULL", 3);
	codePanel.setText("    return false", 4);
	codePanel.setText("return true", 5);

	initNode();
	initEdge();

	codePanel.setLineColor(1, sf::Color::Red);
	for (int i = 0; i < allElements.size(); i++)
	{
		int x = allElements[i];
		b_nodes[i].setString(std::to_string(x));
		w_nodes[i].setString(std::to_string(x));
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (i > 0)
		{
			b_frame.addEdge("2bedges" + std::to_string(i - 1), b_edges[i - 1]);
			w_frame.addEdge("2wedges" + std::to_string(i - 1), w_edges[i - 1]);
		}
	}

	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);
	bool isFound = false;

	for (int i = 0; i < allElements.size(); i++)
	{
		int first = b_frames.size();
		int last = first + 120 - 1;

		for (int step = 0; step < 60; step++)
		{
			Engine::Frame b_frame, w_frame;

			b_frame.init(b_frames.back());
			w_frame.init(w_frames.back());

			codePanel.setLineColor(1, sf::Color::Red);
			codePanel.setLineColor(2, LavenderSoft);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);


			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}

		changeBColor(i, first, last - 90, sf::Color::Black, sf::Color::Blue);
		changeWColor(i, first, last - 90, sf::Color::Black, sf::Color::Blue);
		changeBColor(i, last - 90 + 1, last - 60, sf::Color::Blue, sf::Color::Blue);
		changeWColor(i, last - 90 + 1, last - 60, sf::Color::Blue, sf::Color::Blue);


		if (allElements[i] == num)
		{
			int firstIndex = b_frames.size();
			int lastIndex = b_frames.size() + 60 - 1;
			for (int step = 0; step < 60; step++)
			{
				Engine::Frame b_frame, w_frame;
				b_frame.init(b_frames.back());
				w_frame.init(w_frames.back());
				codePanel.setLineColor(1, LavenderSoft);
				codePanel.setLineColor(2, LavenderSoft);
				codePanel.setLineColor(5, sf::Color::Red);
				b_frame.addPanel("3bcodePanel", codePanel);
				w_frame.addPanel("3wcodePanel", codePanel);


				b_frames.push_back(b_frame);
				w_frames.push_back(w_frame);
			}
			changeBColor(i, firstIndex, lastIndex, sf::Color::Red, sf::Color::Green);
			changeWColor(i, firstIndex, lastIndex, sf::Color::Red, sf::Color::Green);
			breakpoints.push_back(b_frames.size() - 1);
			isFound = true;
			break;
		}

		for (int step = 0; step < 60; step++)
		{
			Engine::Frame b_frame, w_frame;
			b_frame.init(b_frames.back());
			w_frame.init(w_frames.back());

			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(2, sf::Color::Red);

			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);

			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		changeBColor(i, last - 60 + 1, last, sf::Color::Blue, sf::Color::Red);
		changeWColor(i, last - 60 + 1, last, sf::Color::Blue, sf::Color::Red);
		breakpoints.push_back(b_frames.size() - 1);
	}

	if (isFound == false)
	{

		codePanel.setLineColor(2, LavenderSoft);
		codePanel.setLineColor(3, sf::Color::Red);
		codePanel.setLineColor(4, sf::Color::Red);

		b_frames.back().addPanel("3bcodePanel", codePanel);
		w_frames.back().addPanel("3wcodePanel", codePanel);
	}
}