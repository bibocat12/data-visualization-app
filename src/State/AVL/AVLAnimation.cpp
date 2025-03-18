#include "AVLMainState.h"



void AVLMainState::initNode(std::vector<int>& elements, std::vector<int>& depth)
{
	// Init nodes
	int numNodes = elements.size();
	if(numNodes <= LIMIT_NODE_MIN)
		RADIUS = MAX_RADIUS;
	else
		RADIUS = MIN_RADIUS;
	if (numNodes <= LIMIT_NODE_MIN)
		DISTANCE_X = MAX_DISTANCE_X;
	else
		DISTANCE_X = MIN_DISTANCE_X;

	PADDING_X = SCREEN_WIDTH / 2.0 - numNodes / 2.0 * DISTANCE_X;
	PADDING_Y = 100;
	
	for (int i = 0; i < elements.size(); i++)
	{
		sf::Vector2f pos;
		pos.x = PADDING_X + (i) * DISTANCE_X;
		pos.y = PADDING_Y + depth[i] * DISTANCE_Y;
		std::cerr << elements[i] << " " << depth[i] << std::endl;
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
	breakpoints.push_back(b_frames.size() - 1);

	isPlaying = true;
	isPaused = false;
	isEnd = false;
	currentFrameIndex = 0;

	aniSlider.setNumPart(b_frames.size());

}
void AVLMainState::initInsertFrames(int value)
{
	bool isFound = false;
	codePanel.setText("insert v", 0);
	codePanel.setText("case: ", 1);
	codePanel.setText("    RotateLL", 2);
	codePanel.setText("    RotateLR", 3);
	codePanel.setText("    RotateRL", 4);
	codePanel.setText("    RotateRR", 5);
	codePanel.setText("return current", 6);
	codePanel.setLineColor(0, sf::Color::Red);
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


		Engine::Frame b_frame, w_frame;
		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());

		for (int step = 0; step < 60; step++)
		{
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
			isFound = true;
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
	}
	if (isFound == true)
	{
		aniSlider.setNumPart(b_frames.size());
		aniSlider.setBreakpoints(breakpoints);
		currentFrameIndex = 0;
		isPlaying = true;
		isPaused = false;
		isEnd = false;
		return;
	}

	codePanel.setText("insert v", 0);
	codePanel.setText("case: ", 1);
	codePanel.setText("    RotateLL", 2);
	codePanel.setText("    RotateLR", 3);
	codePanel.setText("    RotateRL", 4);
	codePanel.setText("    RotateRR", 5);
	codePanel.setText("return current", 6);
	codePanel.setLineColor(0, LavenderSoft);

	Engine::Frame b_frame, w_frame;
	std::vector<AVLTree::TreeSnapshot> snapshots = avl.insertSnapshots(value);
	std::vector<int> preparent;
	std::vector<std::string> operations;
	for (int i = 0; i < (int)snapshots.size(); i++)
	{
		Engine::Frame b_frame, w_frame;
		std::vector<int> inorder = snapshots[i].inorder;
		std::vector<int> inorderDepth = snapshots[i].inorderDepth;
		std::vector<int> parent = snapshots[i].parent;
		std::string operation = snapshots[i].operation;
		int current = snapshots[i].order;


		initNode(inorder, inorderDepth);
		initEdge(parent);
		// Add nodes and edges to frames

		for (int i = 0; i < (int)inorder.size(); i++)
		{
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			if (parent[i] != -1)
			{
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
			}
		}
		// Add code panel to frames



		int firstIndex = b_frames.size();
		int lastIndex = b_frames.size() + 59;
		

		int numNodes = inorder.size();
        if (operation.find("check") != std::string::npos)
		{
			codePanel.setLineColor(1, sf::Color::Red);
			int number = std::stoi(operation.substr(5));
			std::vector<int> height = snapshots[i].height;
			b_nodes[current].setTextUnder(std::to_string(number), 15, sf::Color::Red);
			w_nodes[current].setTextUnder(std::to_string(number), 15, sf::Color::Red);

			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);

			for (int step = 0; step < 60; step++)
			{
				w_frames.push_back(w_frame);
				b_frames.push_back(b_frame);
			}
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
			operations.push_back(operation);
			codePanel.setLineColor(1, LavenderSoft);
			continue;
		}
		
		if (operations.back() == "rotateRL" || operation == "rotateRL")
			codePanel.setLineColor(4, sf::Color::Red);
		else if (operation == "rotateLR" || operations.back() == "rotateLR")
			codePanel.setLineColor(3, sf::Color::Red);
		else if (operation == "rotateRR")
			codePanel.setLineColor(5, sf::Color::Red);
		else if (operation == "rotateLL")
			codePanel.setLineColor(2, sf::Color::Red);


		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);
		
		firstIndex = b_frames.size();
		lastIndex = firstIndex + 59;
		for (int step = 0; step < 60; step++)
		{
			w_frames.push_back(w_frame);
			b_frames.push_back(b_frame);
		}
		if (i != 0)
		{
			int x = -1, y = 0;
			for (int i = 0; i < numNodes; i++)
			{
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

		for (int i = 0; i < numNodes; i++)
		{
			preb_nodes[i] = b_nodes[i];
			prew_nodes[i] = w_nodes[i];
			if (parent[i] != -1)
				preb_edges[i] = b_edges[i];
			if (parent[i] != -1)
				prew_edges[i] = w_edges[i];
		}
		preparent = parent;

		codePanel.setLineColor(1, LavenderSoft);
		codePanel.setLineColor(2, LavenderSoft);
		codePanel.setLineColor(3, LavenderSoft);
		codePanel.setLineColor(4, LavenderSoft);
		codePanel.setLineColor(5, LavenderSoft);
		operations.push_back(operation);
		breakpoints.push_back(b_frames.size() - 1);
	}
	isPlaying = true;
	isPaused = false;
	isEnd = false;

	aniSlider.setNumPart(b_frames.size());
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
}
void AVLMainState::initDeleteFrames(int value)
{
	deleteAllFrames();

	// Set up the code panel text for deletion.
	std::vector<std::string> codeLines = {
		"current = head",
		"while current->value != value",
		"    if current->value < value",
		"        current = current->right",
		"    else",
		"        current = current->left",
		"return current"
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);


	// Obtain the snapshots from the AVL tree deletion.
	// 
	// (Assuming removeSnapshots is updated to call removeSnapshot internally.)


	
	std::vector<int> inorder = avl.getAllElements();
	std::vector<int> inorderDepth = avl.getInorderDepth();
	std::vector<int> parent = avl.getParent();

	int numNodes = inorder.size();
	initNode(inorder, inorderDepth);
	initEdge(parent);
	int x;
	for (int i = 0; i < inorder.size(); i++)
	{
		if (inorder[i] == value)
			x = i;
		
		w_frame.addNode("1wnode" + std::to_string(i), w_nodes[i]);
		b_frame.addNode("1bnode" + std::to_string(i), b_nodes[i]);
		if (parent[i] != -1)
		{
			w_frame.addEdge("1wedge" + std::to_string(i), w_edges[i]);
			b_frame.addEdge("1bedge" + std::to_string(i), b_edges[i]);
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



	// For each snapshot, create animation frames.
	for (size_t i = 0; i < snapshots.size(); i++) {
		Engine::Frame b_frame, w_frame;
		std::vector<int> inorder = snapshots[i].inorder;
		std::vector<int> inorderDepth = snapshots[i].inorderDepth;
		std::vector<int> parent = snapshots[i].parent;
		std::string op = snapshots[i].operation;
		int current = snapshots[i].order;

		// Reinitialize the node positions and edges based on the snapshot.
		initNode(inorder, inorderDepth);
		initEdge(parent);

		

		// Add nodes and edges to the current frames.
		for (size_t j = 0; j < inorder.size(); j++) {
			w_frame.addNode("1wnode" + std::to_string(j), w_nodes[j]);
			b_frame.addNode("1bnode" + std::to_string(j), b_nodes[j]);
			if (parent[j] != -1) {
				w_frame.addEdge("1wedge" + std::to_string(j), w_edges[j]);
				b_frame.addEdge("1bedge" + std::to_string(j), b_edges[j]);
			}
		}



		// Highlight the code panel based on the snapshot's operation.
		if (op.find("check") != std::string::npos)
			codePanel.setLineColor(1, sf::Color::Red);
		else if (op == "rotateLL")
			codePanel.setLineColor(2, sf::Color::Red);
		else if (op == "rotateLR")
			codePanel.setLineColor(3, sf::Color::Red);
		else if (op == "rotateRL")
			codePanel.setLineColor(4, sf::Color::Red);
		else if (op == "rotateRR")
			codePanel.setLineColor(5, sf::Color::Red);
		else
			codePanel.setLineColor(0, sf::Color::Red);

		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);

		// Add several identical frames for smooth animation (e.g. 60 steps).


		int firstIndex = b_frames.size();
		int lastIndex = b_frames.size() + 59;

		for (int step = 0; step < 60; step++) {
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}


		

		breakpoints.push_back(b_frames.size() - 1);

		// Optionally, reset the code panel colors after each snapshot.
		codePanel.setLineColor(0, LavenderSoft);
		codePanel.setLineColor(1, LavenderSoft);
		codePanel.setLineColor(2, LavenderSoft);
		codePanel.setLineColor(3, LavenderSoft);
		codePanel.setLineColor(4, LavenderSoft);
		codePanel.setLineColor(5, LavenderSoft);
	}

	// Finalize animation slider and playback settings.
	aniSlider.setNumPart(b_frames.size());
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
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

}

void AVLMainState::initInorderFrames()
{

}

void AVLMainState::updateFrames()
{
	numFrames = b_frames.size();
	speed = speedSlider.getPartIndex() + 1;
	if (isPlaying)
	{

		if (numFrames > 0)
		{
			//std::cerr << currentFrameIndex << std::endl;
			if (currentFrameIndex < numFrames - 1)
			{
				isEnd = false;
				b_currentFrame = b_frames[currentFrameIndex];
				w_currentFrame = w_frames[currentFrameIndex];

				if (*m_context->themeType == 0)
					currentFrame = b_currentFrame;
				else
					currentFrame = w_currentFrame;

				if (isPaused == false)
					currentFrameIndex += speed;


			}
			else
			{
				isEnd = true;
				isPaused = true;
				currentFrameIndex = numFrames - 1;
				aniSlider.setPart(currentFrameIndex);
				if (*m_context->themeType == 0)
					currentFrame = b_frames.back();
				else
					currentFrame = w_frames.back();

			}
		}
	}
}

