#include "AVLMainState.h"



void AVLMainState::initNode(std::vector<int>& elements, std::vector<int>& depth)
{
	// Init nodes
	int numNodes = elements.size();
	if (numNodes <= LIMIT_NODE_MIN)
	{
		RADIUS = MAX_RADIUS;
		DISTANCE_X = MAX_DISTANCE_X;
		DISTANCE_Y = MAX_DISTANCE_Y;
	}
	else
		if (numNodes <= LIMIT_NODE_MED)
		{
			RADIUS = MED_RADIUS;
			DISTANCE_X = MED_DISTANCE_X;
			DISTANCE_Y = MED_DISTANCE_Y;
		}
		else if (numNodes <= LIMIT_NODE_MAX)
		{
			RADIUS = MIN_RADIUS;
			DISTANCE_X = MIN_DISTANCE_X;
			DISTANCE_Y = MIN_DISTANCE_Y;
		}
		else
	{
			RADIUS = SM_RADIUS;
			DISTANCE_X = SM_DISTANCE_X;
			DISTANCE_Y = SM_DISTANCE_Y;
	}

	PADDING_X = SCREEN_WIDTH / 2.0 - numNodes / 2.0 * DISTANCE_X;
	PADDING_Y = 100;
	
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] == -1)
			continue;
		sf::Vector2f pos;
		pos.x = PADDING_X + (i) * DISTANCE_X;
		pos.y = PADDING_Y + depth[i] * DISTANCE_Y;
		b_nodes[i] = Node();
		b_nodes[i].setFillColor(B_NODE_COLOR);
		b_nodes[i].setOutlineColor(B_NODE_OUTLINE_COLOR);
		b_nodes[i].setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		b_nodes[i].setOutlineThickness(-3);
		b_nodes[i].setRadius(RADIUS);
		b_nodes[i].setCharacterSize(RADIUS);
		b_nodes[i].setString(std::to_string(elements[i]));
		b_nodes[i].setTextUnder(std::to_string(depth[i]), 15, sf::Color::Black);
		b_nodes[i].setTextColor(sf::Color::Black);
		b_nodes[i].setPosition(pos);
		
		w_nodes[i] = Node();
		w_nodes[i].setFillColor(W_NODE_COLOR);
		w_nodes[i].setOutlineColor(W_NODE_OUTLINE_COLOR);
		w_nodes[i].setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		w_nodes[i].setCharacterSize(RADIUS);
		w_nodes[i].setTextColor(sf::Color::Black);
		w_nodes[i].setOutlineThickness(-3);
		w_nodes[i].setCharacterSize(RADIUS);
		w_nodes[i].setTextUnder(std::to_string(depth[i]), 15, sf::Color::Black);
		w_nodes[i].setRadius(RADIUS);
		w_nodes[i].setString(std::to_string(elements[i]));
		w_nodes[i].setPosition(pos);


	}

}

void AVLMainState::resetNodePosRad()
{
	// Reset node position and radius
	for (int i = 0; i < 100; i++)
	{
		b_nodes[i].setRadius(0);
		w_nodes[i].setRadius(0);
	}
}

void AVLMainState::initEdge(std::vector<int>& parent)
{
	// Init edges
	for (int i = 0; i < parent.size(); i++)
	{
		if (parent[i] != -1)
		{
			sf::Vector2f pos1 = b_nodes[i].getPosition();
			sf::Vector2f pos2 = b_nodes[parent[i]].getPosition();
			b_edges[i] = Edge();
			b_edges[i].setColor(B_NODE_OUTLINE_COLOR);
			b_edges[i].setThickness(3);
			b_edges[i].setStart(pos1);
			b_edges[i].setEnd(pos2);

			w_edges[i] = Edge();
			w_edges[i].setColor(W_NODE_OUTLINE_COLOR);
			w_edges[i].setThickness(3);
			w_edges[i].setStart(pos1);
			w_edges[i].setEnd(pos2);
		}
	}
}

void AVLMainState::changeBNode(int index, int index1, int index2, Node from, Node to)
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

		if (from.getPosition() != to.getPosition())
		{
			std::cerr << "from: " << from.getPosition().x << " " << from.getPosition().y << std::endl;
			std::cerr << "to: " << to.getPosition().x << " " << to.getPosition().y << std::endl;
			std::cerr << "pos: " << pos.x << " " << pos.y << std::endl;
		}

		b_nodes[index].setFillColor(color);
		b_nodes[index].setPosition(pos);
		b_nodes[index].setOutlineColor(colorOutline);
		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
	}
}

void AVLMainState::changeWNode(int index, int index1, int index2, Node from, Node to)
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

void AVLMainState::changeBEdge(int index, int index1, int index2, Edge from, Edge to)
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

void AVLMainState::changeWEdge(int index, int index1, int index2, Edge from, Edge to)
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


void AVLMainState::deleteAllFrames()
{
	// Clear all frames
	b_frames.clear();
	w_frames.clear();
	breakpoints.clear();
}

void AVLMainState::initEmptyFrames(int count)
{
	// Clear all frames
	deleteAllFrames();
	isFrameActive.clear();
	// Init frames
	Engine::Frame b_frame, w_frame;
	breakpoints.push_back(0);
	for (int i = 0; i < count; i++)
	{
		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
			isFrameActive.push_back(false);
		}
		breakpoints.push_back(b_frames.size());
	}

	aniSlider.setNumPart(b_frames.size());
	aniSlider.setBreakpoints(breakpoints);
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	currentFrameIndex = 0;

}



void AVLMainState::initCreateFrames(std::vector<int> elements)
{
	// Clear all frames
	deleteAllFrames();
	// Init frames
	Engine::Frame b_frame, w_frame;
	avl.clear();

	avl.create(elements);

	std::vector<int> inorder = avl.getAllElements();
	std::vector<int> inorderDepth = avl.getInorderDepth();
	std::vector<int> parent = avl.getParent();

	int numNodes = elements.size();
	initNode(inorder, inorderDepth);
	initEdge(parent);

	// Add nodes and edges to frames
	for (int i = 0; i < (int)elements.size(); i++)
	{
		w_frame.addNode("1wnode" + std::to_string(i), w_nodes[i]);
		b_frame.addNode("1bnode" + std::to_string(i), b_nodes[i]);
		if (parent[i] != -1)
		{
			w_frame.addEdge("1wedge" + std::to_string(i), w_edges[i]);
			b_frame.addEdge("1bedge" + std::to_string(i), b_edges[i]);
		}


	}
	// Add code panel to frames
	codePanel.setText("current = head", 0);
	codePanel.setText("while k > 0", 1);
	codePanel.setText("    current = current->next", 2);
	codePanel.setText("    k--", 3);
	codePanel.setText("insert v after current", 4);
	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);
	for (int step = 0; step < 60; step++)
	{
		w_frames.push_back(w_frame);
		b_frames.push_back(b_frame);
	}
;
	Node node;
	for (int i = 0; i < (int)elements.size(); i++)
	{
		node = w_nodes[i];
		node.setFillColor(W_NODE_COLOR_TRANS);
		node.setOutlineColor(W_NODE_OUTLINE_COLOR_TRANS);
		changeBNode(i, 0, 59, node, b_nodes[i]);
		node = b_nodes[i];
		node.setFillColor(B_NODE_COLOR_TRANS);
		node.setOutlineColor(B_NODE_OUTLINE_COLOR_TRANS);
		changeWNode(i, 0, 59, node, w_nodes[i]);

	}

	breakpoints.push_back(0);
	breakpoints.push_back(b_frames.size());
	aniSlider.setNumPart(b_frames.size());
	aniSlider.setBreakpoints(breakpoints);

	isPlaying = true;
	isPaused = false;
	isEnd = false;
	currentFrameIndex = 0;
	numFrames = b_frames.size();

	aniSlider.setNumPart(b_frames.size());

}
void AVLMainState::initInsertFrames()
{
	deleteAllFrames();
	std::vector<std::string> codeLines = {
		"insert v",
		"case:",
		"    rotateLL",
		"    rotateLR",
		"    rotateRL",
		"    rotateRR",
		"",
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);
	int currBreakpoint = aniSlider.getBreakpoints(currentFrameIndex) / 60;
	std::string operation = snapshots[currBreakpoint].operation;
	if (operation == "find" || operation.find("check") != std::string::npos)
	{
		Engine::Frame b_frame, w_frame;
		std::vector<int> inorder = snapshots[currBreakpoint].inorder;
		std::vector<int> inorderDepth = snapshots[currBreakpoint].inorderDepth;
		std::vector<int> parent = snapshots[currBreakpoint].parent;
		initNode(inorder, inorderDepth);
		initEdge(parent);
		int order = snapshots[currBreakpoint].order;
		codePanel.setLineColor(0, sf::Color::Red);
		w_frame.addPanel("3wcodePanel", codePanel);
		b_frame.addPanel("3bcodePanel", codePanel);
		if (operation.find("check") != std::string::npos)
		{
			w_nodes[order].setTextUnder(std::to_string(std::stoi(operation.substr(5))), 15, sf::Color::Red);
			b_nodes[order].setTextUnder(std::to_string(std::stoi(operation.substr(5))), 15, sf::Color::Red);
		}
		for (int i = 0; i < inorder.size(); i++)
		{
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			if (parent[i] != -1)
			{
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
			}
		}
		for (int step = 0; step < 60; step++)
		{
			w_frames.push_back(w_frame);
			b_frames.push_back(b_frame);
		}
		Node node = w_nodes[order];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeBNode(order, 0, 59, b_nodes[order], node);
		node = b_nodes[order];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeWNode(order, 0, 59, w_nodes[order], node);
		codePanel.setLineColor(0, sf::Color::Red);
	}
	else
	{
		Engine::Frame b_frame, w_frame;

		codePanel.setLineColor(0, sf::Color::Red);
		w_frame.addPanel("3wcodePanel", codePanel);
		b_frame.addPanel("3bcodePanel", codePanel);

		if(snapshots[currBreakpoint].inorder.size() != snapshots[currBreakpoint - 1].inorder.size())
			return;
		std::vector<int> preparent = snapshots[currBreakpoint - 1].parent;
		std::vector<int> preinorder = snapshots[currBreakpoint - 1].inorder;
		std::vector<int> preinorderDepth = snapshots[currBreakpoint - 1].inorderDepth;
		std::vector<int> parent = snapshots[currBreakpoint].parent;
		std::vector<int> inorder = snapshots[currBreakpoint].inorder;
		std::vector<int> inorderDepth = snapshots[currBreakpoint].inorderDepth;
		int numNodes = preinorder.size();
		initNode(preinorder, preinorderDepth);
		initEdge(preparent);

		for (int i = 0; i < preinorder.size(); i++) {
			preb_nodes[i] = b_nodes[i];
			prew_nodes[i] = w_nodes[i];
			preb_edges[i] = b_edges[i];
			prew_edges[i] = w_edges[i];
		}

		initNode(inorder, inorderDepth);
		initEdge(parent);
		for (int i = 0; i < numNodes; i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (parent[i] != -1)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}

		for (int i = 0; i < 60; i++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		int firstIndex = b_frames.size() - 60;
		int lastIndex = b_frames.size() - 1;

		int x = -1, y = 0;
		for (int i = 0; i < numNodes; i++)
		{
			
			if (prew_nodes[i].getPosition() != b_nodes[i].getPosition())
			{
				changeBNode(i, 0, 59, preb_nodes[i], b_nodes[i]);
				changeWNode(i, 0, 59, prew_nodes[i], w_nodes[i]);
			}

			if (parent[i] == -1 && preparent[i] == -1)
				continue;
			if (parent[i] != -1 && preparent[i] != -1)
			{
				changeBEdge(i, 0, 59, preb_edges[i], b_edges[i]);
				changeWEdge(i, 0, 59, prew_edges[i], w_edges[i]);
			}
			else if (parent[i] != -1)
				x = i;
			else
				y = i;
		}
		if (x != -1)
		{
			changeBEdge(x, 0, 59, preb_edges[y], b_edges[x]);
			changeWEdge(x, 0, 59, prew_edges[y], w_edges[x]);
		}
	}
}
void AVLMainState::initDeleteFrames(int value)
{
	deleteAllFrames();

	// Set up the code panel text for deletion.
	std::vector<std::string> codeLines = {
		"delete v",
		"replace v with successor",
		"case:",
		"    rotateLL",
		"    rotateLR",
		"    rotateRL",
		"    rotateRR",
	};


	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);


	// Obtain the snapshots from the AVL tree deletion.
	// 
	// (Assuming removeSnapshots is updated to call removeSnapshot internally.)

	std::vector<int> inorder = avl.getAllElements();
	std::vector<int> inorderDepth = avl.getInorderDepth();
	std::vector<int> parent = avl.getParent();

	std::vector<std::string> operations;

	int numNodes = inorder.size();
	initNode(inorder, inorderDepth);
	initEdge(parent);


	int indexValue = -1;;
	Engine::Frame b_frame, w_frame;
	for (int i = 0; i < inorder.size(); i++)
	{	
		if (inorder[i] == value)
			indexValue = i;
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		if (parent[i] != -1)
		{
			w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
		}
		preb_edges[i] = b_edges[i];
		prew_edges[i] = w_edges[i];
		preb_nodes[i] = b_nodes[i];
		prew_nodes[i] = w_nodes[i];
	}

	for (int step = 0; step < 60; step++)
	{
		w_frames.push_back(w_frame);
		b_frames.push_back(b_frame);
	}


	std::vector<int> path = avl.searchPath(value);
	std::vector<AVLTree::TreeSnapshot> snapshots = avl.removeSnapshots(value);

	std::vector<int> preparent = parent;

	bool isRemoved = false;
	// For each snapshot, create animation frames.
	for (size_t i = 0; i < snapshots.size(); i++) {
		Engine::Frame b_frame, w_frame;
		std::vector<int> inorder = snapshots[i].inorder;
		std::vector<int> inorderDepth = snapshots[i].inorderDepth;
		std::vector<int> parent = snapshots[i].parent;
		std::string op = snapshots[i].operation;
		int current = snapshots[i].order;
		std::string operation = snapshots[i].operation;
		if (inorder.size() != numNodes) {
			inorder.insert(inorder.begin() + indexValue, -1);
			inorderDepth.insert(inorderDepth.begin() + indexValue, -2);
			parent.insert(parent.begin() + indexValue, -1);
			for (int i = 0; i < inorder.size(); i++)
			{
				if (inorder[i] == -1)
					continue;
				if (parent[i] >= indexValue)
					parent[i]++;
			}
			isRemoved = true;
			
		}

		// Reinitialize the node positions and edges based on the snapshot.
		initNode(inorder, inorderDepth);
		initEdge(parent);

		codePanel.setText(operation, 0);

		// Add nodes and edges to the current frames.
		for (size_t j = 0; j < inorder.size(); j++) {
			if (inorder[j] == -1)
			{

				continue;
			}
			w_frame.addNode("1wnodes" + std::to_string(j), w_nodes[j]);
			b_frame.addNode("1bnodes" + std::to_string(j), b_nodes[j]);
			if (parent[j] != -1) {
				w_frame.addEdge("1wedges" + std::to_string(j), w_edges[j]);
				b_frame.addEdge("1bedges" + std::to_string(j), b_edges[j]);
			}
		}



		// Highlight the code panel based on the snapshot's operation.
		if (op.find("check") != std::string::npos)
			codePanel.setLineColor(2, sf::Color::Red);
		else
			if (operations.empty() == false) {
				if (operations.back() == "rotateRL" || operation == "rotateRL")
					codePanel.setLineColor(4, sf::Color::Red);
				else if (operation == "rotateLR" || operations.back() == "rotateLR")
					codePanel.setLineColor(3, sf::Color::Red);
				else if (operation == "rotateRR")
					codePanel.setLineColor(5, sf::Color::Red);
				else if (operation == "rotateLL")
					codePanel.setLineColor(2, sf::Color::Red);
			}
		else
			codePanel.setLineColor(0, sf::Color::Red);


		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);

	//	// Add several identical frames for smooth animation (e.g. 60 steps).


		int firstIndex = b_frames.size();
		int lastIndex = b_frames.size() + 59;

		for (int step = 0; step < 60; step++) {
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
	//	std::cerr << operation << " " << current << std::endl;
		if (operation == "find")
		{
			Node node;
			if (current >= indexValue && isRemoved == true)
				current++;
			node = w_nodes[current];
			node.setFillColor(W_NODE_COLOR_HOVER);
			changeWNode(current, firstIndex, lastIndex, w_nodes[current], node);
			node = b_nodes[current];
			node.setFillColor(B_NODE_COLOR_HOVER);
			changeBNode(current, firstIndex, lastIndex, b_nodes[current], node);
			breakpoints.push_back(b_frames.size() - 1);
			for (int i = 0; i < (int)inorder.size(); i++)
			{
				preb_edges[i] = b_edges[i];
				prew_edges[i] = w_edges[i];
				preb_nodes[i] = b_nodes[i];
				prew_nodes[i] = w_nodes[i];
			}
			preparent = parent;
			codePanel.setLineColor(1, LavenderSoft);
			continue;
		}
		else if (operation.find("check") != std::string::npos)
		{
			int number = std::stoi(operation.substr(5));
			if (current >= indexValue && isRemoved == true)
				current++;
			b_nodes[current].setTextUnder(std::to_string(number), 15, sf::Color::Red);
			w_nodes[current].setTextUnder(std::to_string(number), 15, sf::Color::Red);
			Node node;
			node = w_nodes[current];
			node.setFillColor(W_NODE_COLOR_HOVER);
			changeWNode(current, firstIndex, lastIndex, w_nodes[current], node);
			node = b_nodes[current];
			node.setFillColor(B_NODE_COLOR_HOVER);
			changeBNode(current, firstIndex, lastIndex, b_nodes[current], node);
			breakpoints.push_back(b_frames.size() - 1);
			b_nodes[current].setTextUnder("", 15, sf::Color::Black);
			w_nodes[current].setTextUnder("", 15, sf::Color::Black);
			for (int i = 0; i < (int)inorder.size(); i++)
			{
				preb_edges[i] = b_edges[i];
				prew_edges[i] = w_edges[i];
				preb_nodes[i] = b_nodes[i];
				prew_nodes[i] = w_nodes[i];
			}
			preparent = parent;
			codePanel.setLineColor(1, LavenderSoft);
			continue;
		}
		else
		{
			int x = -1, y = 0;
			for (int i = 0; i < numNodes; i++)
			{
				if (inorder[i] == -1)
					continue;
				changeBNode(i, firstIndex, lastIndex, preb_nodes[i], b_nodes[i]);
				changeWNode(i, firstIndex, lastIndex, prew_nodes[i], w_nodes[i]);
				if (parent[i] == -1 && preparent[i] == -1)
					continue;
				if (parent[i] != -1 && preparent[i] != -1)
				{
					changeBEdge(i, firstIndex, lastIndex, preb_edges[i], b_edges[i]);
					changeWEdge(i, firstIndex, lastIndex, prew_edges[i], w_edges[i]);
				}
				else if (parent[i] != -1)
					x = i;
				else
					y = i;
			}
			if (x != -1)
			{
				changeBEdge(x, firstIndex, lastIndex, preb_edges[y], b_edges[x]);
				changeWEdge(x, firstIndex, lastIndex, prew_edges[y], w_edges[x]);
			}
		}
		
		breakpoints.push_back(b_frames.size() - 1);
		preparent = parent;
		for (int i = 0; i < numNodes; i++)
		{
			preb_edges[i] = b_edges[i];
			prew_edges[i] = w_edges[i];
			preb_nodes[i] = b_nodes[i];
			prew_nodes[i] = w_nodes[i];
		}
		// Optionally, reset the code panel colors after each snapshot.
		codePanel.setLineColor(0, LavenderSoft);
		codePanel.setLineColor(1, LavenderSoft);
		codePanel.setLineColor(2, LavenderSoft);
		codePanel.setLineColor(3, LavenderSoft);
		codePanel.setLineColor(4, LavenderSoft);
		codePanel.setLineColor(5, LavenderSoft);
		operations.push_back(operation);
	}

	// Finalize animation slider and playback settings.
	aniSlider.setNumPart(b_frames.size());
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
	numFrames = b_frames.size();
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}
void AVLMainState::initSearchFrames(int value)
{
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	avl.search(value);
	std::vector<int> inorder = avl.getAllElements();
	std::vector<int> inorderDepth = avl.getInorderDepth();
	std::vector<int> parent = avl.getParent();
	int numNodes = inorder.size();
	initNode(inorder, inorderDepth);
	initEdge(parent);
	// Add nodes and edges to frames

	for (int i = 0; i < (int)inorder.size(); i++)
	{
		w_frame.addNode("1wnode" + std::to_string(i), w_nodes[i]);
		b_frame.addNode("1bnode" + std::to_string(i), b_nodes[i]);
		if (parent[i] != -1)
		{
			w_frame.addEdge("1wedge" + std::to_string(i), w_edges[i]);
			b_frame.addEdge("1bedge" + std::to_string(i), b_edges[i]);
		}
	}

	// Add code panel to frames
	codePanel.setText("current = head", 0);
	codePanel.setText("while current->value != value", 1);
	codePanel.setText("    if current->value < value", 2);
	codePanel.setText("        current = current->right", 3);
	codePanel.setText("    else", 4);
	codePanel.setText("        current = current->left", 5);
	codePanel.setText("return current", 6);
	codePanel.setLineColor(1, sf::Color::Red);

	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);
	for (int step = 0; step < 60; step++)
	{
		w_frames.push_back(w_frame);
		b_frames.push_back(b_frame);
	}
	codePanel.setLineColor(1, LavenderSoft);

	std::vector<int> path = avl.searchPath(value);
	Node node;
	for (int i = 0; i < (int)path.size(); i++)
	{
		int firstIndex = b_frames.size();
		int lastIndex = b_frames.size() + 59;
		node = w_nodes[path[i]];
		node.setFillColor(W_NODE_COLOR_HOVER);
		node = b_nodes[path[i]];
		node.setFillColor(B_NODE_COLOR_HOVER);
		Panel codePanel2 = codePanel;
		Panel codePanel3 = codePanel;
		codePanel2.setLineColor(1, sf::Color::Red);
		if(i != 0)
			if (inorder[path[i]] < value)
			{
				codePanel3.setLineColor(2, sf::Color::Red);
				codePanel3.setLineColor(3, sf::Color::Red);
			}
			else if (value < inorder[path[i]])
			{
				codePanel3.setLineColor(4, sf::Color::Red);
				codePanel3.setLineColor(5, sf::Color::Red);
			}
			else
			{
				codePanel3.setLineColor(6, sf::Color::Red);
			}

		Engine::Frame b_frame, w_frame;
		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());

		for (int step = 0; step < 60; step++)
		{
			if (step < 30)
			{
				b_frame.addPanel("3bcodePanel", codePanel2);
				w_frame.addPanel("3wcodePanel", codePanel2);
			}
			else
			{
				b_frame.addPanel("3bcodePanel", codePanel3);
				w_frame.addPanel("3wcodePanel", codePanel3);
			}
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		node = w_nodes[path[i]];
		node.setFillColor(W_NODE_COLOR_HOVER);

		changeBNode(path[i], firstIndex, lastIndex, node, b_nodes[path[i]]);
		node = b_nodes[path[i]];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeWNode(path[i], firstIndex, lastIndex, node, w_nodes[path[i]]);
		breakpoints.push_back(b_frames.size() - 1);

		if (inorder[path[i]] == value)
		{
	
			for (int step = 0; step <= 60; step++)
			{
				b_frames.push_back(b_frames.back());
				w_frames.push_back(w_frames.back());
			}

			node = b_nodes[path[i]];
			node.setFillColor(sf::Color::Green);
			changeBNode(path[i], b_frames.size() - 61, b_frames.size() - 1, b_nodes[path[i]], node);
			Node node = w_nodes[path[i]];
			node.setFillColor(sf::Color::Green);
			changeWNode(path[i], w_frames.size() - 61, w_frames.size() - 1, w_nodes[path[i]], node);
			breakpoints.push_back(b_frames.size() - 1);
			break;
		}
	}
	numFrames = b_frames.size();

}
void AVLMainState::initInorderFrames()
{
	deleteAllFrames();
	std::vector<std::string> codeLines = {
		"record inorder traversal",
		"inorder(node -> left)",
		"visit the current node",
		"inorder(node -> right)",
		"",
		"",
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);
	inorderSnapshot = avl.recordInorder();
	int numNodes = inorderSnapshot.size();
	int currBreakpoint = aniSlider.getBreakpoints(currentFrameIndex)/60;
	Engine::Frame b_frame, w_frame;
	std::vector<int> inorder = avl.getAllElements();
	std::vector<int> inorderDepth = avl.getInorderDepth();
	std::vector<int> parent = avl.getParent();
	std::string operations;
	initNode(inorder, inorderDepth);
	initEdge(parent);
	std::map<int, int> index;
	for (int i = 0; i < inorder.size(); i++)
	{
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (parent[i] != -1)
		{
			b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
			w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
		}
	}

	for (int i = 0; i < currBreakpoint; i++)
	{
		int x = inorderSnapshot[i];
		if (index.find(inorderSnapshot[i]) == index.end())
		{
			Node node = w_nodes[x];
			node.setFillColor(W_NODE_COLOR_HOVER);
			w_frame.addNode("1wnodes" + std::to_string(x), node);
			node = b_nodes[x];
			node.setFillColor(B_NODE_COLOR_HOVER);
			b_frame.addNode("1bnodes" + std::to_string(x), node);
			if (parent[x] != -1)
			{
				w_frame.addEdge("1wedges" + std::to_string(x), w_edges[x]);
				b_frame.addEdge("1bedges" + std::to_string(x), b_edges[x]);
			}
			operations = "inorder";

		}
		else
		{
			Node node = w_nodes[x];
			node.setFillColor(sf::Color::Green);
			w_frame.addNode("1wnodes" + std::to_string(x), node);
			node = b_nodes[x];
			node.setFillColor(sf::Color::Green);

			b_frame.addNode("1bnodes" + std::to_string(x), node);
			if (parent[x] != -1)
			{
				w_frame.addEdge("1wedges" + std::to_string(x), w_edges[x]);
				b_frame.addEdge("1bedges" + std::to_string(x), b_edges[x]);
			}
			operations = "visit";

		}
		index[x] = 1;
	}
	int current = inorderSnapshot[currBreakpoint];
	if(operations == "inorder" && index[current] == 0)
		codePanel.setLineColor(1, sf::Color::Red);
	else if (operations == "visit" && index[current] == 0)
		codePanel.setLineColor(3, sf::Color::Red);
	else if(operations == "")
		codePanel.setLineColor(0, sf::Color::Red);
	else
		codePanel.setLineColor(2, sf::Color::Red);
	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);


	for (int i = 0; i < 60; i++)
	{
		w_frames.push_back(w_frame);
		b_frames.push_back(b_frame);
	}
	
	if (index[current] == 1)
	{
		Node node;
		node = w_nodes[current];
		node.setFillColor(sf::Color::Green);
		changeWNode(current, 0, 59, w_nodes[current], node);
		node = b_nodes[current];
		node.setFillColor(sf::Color::Green);
		changeBNode(current, 0, 59, b_nodes[current], node);
	}
	else
	{
		Node node;
		node = w_nodes[current];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(current, 0, 59, w_nodes[current], node);
		node = b_nodes[current];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(current, 0, 59, b_nodes[current], node);
	}
	codePanel.setLineColor(0, LavenderSoft);
	codePanel.setLineColor(1, LavenderSoft);
	codePanel.setLineColor(2, LavenderSoft);
	codePanel.setLineColor(3, LavenderSoft);

}

void AVLMainState::createInorderFrames()
{
	currentState = "inorder";
	deleteAllFrames();
	std::vector<int> inorderSnapshot = avl.recordInorder();
	int numNodes = inorderSnapshot.size();
	

	for(int i = 0;i < numNodes;i++)
		breakpoints.push_back(i*60);
	breakpoints.push_back(numNodes * 60 - 1);
	aniSlider.setNumPart(numNodes * 60);
	std::cerr << "Num Part: " << numNodes * 60 << std::endl;
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = numNodes * 60;
}

void AVLMainState::createInsertFrames(int value)
{
	currentState = "insert";
	deleteAllFrames();
	snapshots = avl.insertSnapshots(value);
	int numNodes = snapshots.size();
	for (int i = 0; i < numNodes; i++)
		breakpoints.push_back(i * 60);
	breakpoints.push_back(numNodes * 60 - 1);
	aniSlider.setNumPart(numNodes * 60);
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = numNodes * 60;
}




void AVLMainState::updateFrames()
{
	if (numFrames == 0) return;
	if (numFrames > 0) currentFrameIndex = std::min(currentFrameIndex, numFrames - 1);
	if (currentFrameIndex == 0 || aniSlider.getBreakpoints(prevFrameIndex) != aniSlider.getBreakpoints(currentFrameIndex)) {
		if (currentState == "inorder") {
			initInorderFrames();
		}
		if (currentState == "insert")
		{
			initInsertFrames();
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
				if (currentState == "inorder")
				{
					b_currentFrame = b_frames[currentFrameIndex - aniSlider.getBreakpoints(currentFrameIndex)];
					w_currentFrame = w_frames[currentFrameIndex - aniSlider.getBreakpoints(currentFrameIndex)];
				}
				else
				{
					b_currentFrame = b_frames[currentFrameIndex];
					w_currentFrame = w_frames[currentFrameIndex];
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

Engine::Frame AVLMainState::handleInorderFrame(int index)
{
	return Engine::Frame();
}

