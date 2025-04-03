#include "TrieMainState.h"

void TrieMainState::deleteAllFrames()
{
	b_frames.clear();
	w_frames.clear();
	//breakpoints.clear();
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 7; j++) {
			codePanelColor[i][j] = LavenderSoft;
		}
	}
}

void TrieMainState::initNode(Trie::TrieSnapshot& snapshot)
{
	std::vector<Trie::TrieNodeInfo> nodes = snapshot.nodesInfo;
	for (int i = nodes.size() - 1; i >= 0; i--)
	{
		totalChild[i] = 0;
		orderFinal[i] = nodes[i].orderDisplay;
	}
	PADDING_X = 1e9;
	RADIUS = MAX_RADIUS;
	for (int i = nodes.size() - 1; i >= 0; i--)
	{
		int par = nodes[i].parentOrder;

		PADDING_X = std::min((float)(SCREEN_WIDTH - nodes[i].orderDisplay * 1.0 * DISTANCE_X) / 2, PADDING_X);

		if (i != 0)
		{
			if (totalChild[par] == 0)
				orderFinal[par] -= nodes[par].orderDisplay;

			orderFinal[par] += (orderFinal[i]/std::max(totalChild[i],1.0f));
			totalChild[par] += 1;
			
		}
	}


	for (int i = 0; i < nodes.size(); i++)
	{
		
		int depth = nodes[i].depth;
		float orderDisplay = orderFinal[i];
		int order = nodes[i].order;

		if (totalChild[i] != 0)
			orderDisplay = orderFinal[i] / totalChild[i];

		sf::Vector2f pos;
		pos.x = PADDING_X + orderDisplay * (DISTANCE_X);
		pos.y = PADDING_Y + depth * (DISTANCE_Y);

		std::string str(1, nodes[i].character);
		b_nodes[i].setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		b_nodes[i].setCharacterSize(MAX_RADIUS);
		b_nodes[i].setTextColor(sf::Color::Black);	
		b_nodes[i].setFillColor(B_NODE_COLOR);
		b_nodes[i].setOutlineColor(B_NODE_OUTLINE_COLOR);
		b_nodes[i].setOutlineThickness(-5);
		b_nodes[i].setRadius(MAX_RADIUS);
		b_nodes[i].setString(str);
		b_nodes[i].setPosition(pos);

		if (nodes[i].isEndOfWord)
			b_nodes[i].setTextUnder("isEnd", 10, sf::Color::Red);
		else b_nodes[i].setTextUnder("", 10, sf::Color::Red);

		w_nodes[i].setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		w_nodes[i].setCharacterSize(MAX_RADIUS);
		w_nodes[i].setFillColor(W_NODE_COLOR);
		w_nodes[i].setOutlineColor(W_NODE_OUTLINE_COLOR);
		w_nodes[i].setOutlineThickness(-5);
		w_nodes[i].setRadius(MAX_RADIUS);
		w_nodes[i].setTextColor(sf::Color::Black);
		w_nodes[i].setString(str);
		w_nodes[i].setPosition(pos);
		if (nodes[i].isEndOfWord)
			w_nodes[i].setTextUnder("isEnd", 10, sf::Color::Red);
		else
			w_nodes[i].setTextUnder("", 10, sf::Color::Red);
	}
}

void TrieMainState::initEdge(Trie::TrieSnapshot& snapshot)
{
	std::vector<Trie::TrieNodeInfo> nodes = snapshot.nodesInfo;
	for (int i = 0; i < nodes.size(); i++)
	{
		int depth = nodes[i].depth;
		int order = nodes[i].order;
		int orderDisplay = nodes[i].orderDisplay;
		sf::Vector2f pos;
		pos.x = PADDING_X + order * (DISTANCE_X);
		pos.y = PADDING_Y + depth * (DISTANCE_Y);
		if (nodes[i].parentOrder != -1)
		{
			int parentOrder = nodes[i].parentOrder;
			sf::Vector2f start = b_nodes[parentOrder].getPosition();

			sf::Vector2f end = b_nodes[i].getPosition();

			b_edges[i].setColor(B_NODE_OUTLINE_COLOR);
			b_edges[i].setThickness(3);
			b_edges[i].setStart(start);
			b_edges[i].setEnd(end);

			w_edges[i] = Edge();
			w_edges[i].setColor(W_NODE_OUTLINE_COLOR);
			w_edges[i].setThickness(3);
			w_edges[i].setStart(start);
			w_edges[i].setEnd(end);
		}
	}
}

void TrieMainState::changeBNode(int index, int index1, int index2, Node from, Node to)
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

void TrieMainState::changeWNode(int index, int index1, int index2, Node from, Node to)
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

void TrieMainState::setCodePanelColor(int frameIndex)
{
	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, codePanelColor[frameIndex][i]);
	}
}


void TrieMainState::initCreateFrames(std::vector<std::string> words)
{
	// Clear all frames
	std::vector<std::string> codeLines = {
			"insert word",
	"if node not found",
	"  create node",
	"",
	"",
	"",
	""
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);
	deleteAllFrames();
	trie.clear();
	// Init frames
	Engine::Frame b_frame, w_frame;

	breakpoints.push_back(0);
	for (int i = 0; i < words.size(); i++)
	{
		trie.insert(words[i]);
	}

	Trie::TrieSnapshot snapshot = trie.getSnapshot();
	initNode(snapshot);
	initEdge(snapshot);
	for (int i = 0; i < snapshot.nodesInfo.size(); i++)
	{
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (snapshot.nodesInfo[i].parentOrder != -1)
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
	breakpoints.push_back(b_frames.size());
	aniSlider.setNumPart(b_frames.size());
	aniSlider.setBreakpoints(breakpoints);
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	currentFrameIndex = 0;
	numFrames = b_frames.size();
}

void TrieMainState::initInsertFrames()
{
	deleteAllFrames();
	std::vector<std::string> codeLines = {
		"if node -> children[c] == nullptr",
		"    node -> childen[c] = new Node:",
		"travel(node -> children[c])",
		"end",
		"",
		"",
		""
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);
	int currBreakpoint = aniSlider.getBreakpoints(currentFrameIndex) / 60;
	std::string operation = snapshots[currBreakpoint].operation;
	Trie::TrieSnapshot snapshot = snapshots[currBreakpoint];
	std::cerr << operation << std::endl;
	if (operation == "traverse" || operation == "mark_end" || operation == "already_exists" || operation == "end_insert")
	{
		initNode(snapshot);
		initEdge(snapshot);
		Engine::Frame b_frame, w_frame;
		for (int i = 0; i < snapshot.nodesInfo.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (snapshot.nodesInfo[i].parentOrder != -1)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}

		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
			if (operation == "mark_end" )
				codePanelColor[step][3] = sf::Color::Red;
			else
				codePanelColor[step][2] = sf::Color::Red;
		}
		if (snapshot.currentNodeOrder == -1)
			return;

		Node node = w_nodes[snapshot.currentNodeOrder];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(snapshot.currentNodeOrder, 0, 59, b_nodes[snapshot.currentNodeOrder], node);
		node = b_nodes[snapshot.currentNodeOrder];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(snapshot.currentNodeOrder, 0, 59, w_nodes[snapshot.currentNodeOrder], node);
	}
	else
	{
		Engine::Frame b_frame, w_frame;

		initNode(snapshot);
		initEdge(snapshot);
		
		for (int i = 0; i < snapshot.nodesInfo.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (snapshot.nodesInfo[i].parentOrder != -1)
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
				codePanelColor[step][0] = sf::Color::Red;
			else if (step < 60)
				codePanelColor[step][1] = sf::Color::Red;

		}

		std::cerr << "operation: " << operation << std::endl;
		int order = snapshot.currentNodeOrder;
		std::cerr << "order: " << order << std::endl;
		Node node = w_nodes[order];
		int par = snapshot.nodesInfo[order].parentOrder;
		sf::Vector2f pos1 = node.getPosition();
		sf::Vector2f pos2 = b_nodes[par].getPosition();
		node.setPosition((pos1 + pos2) / 2.0f);
		changeWNode(order, 0, 59, node, b_nodes[order]);
		node = b_nodes[order];
		node.setPosition((pos1 + pos2) / 2.0f);
		changeBNode(order, 0, 59, node, w_nodes[order]);


	}
}

void TrieMainState::initDeleteFrames(int deleteValue)
{
	deleteAllFrames();
	std::vector<std::string> codeLines = {
		"if node == nullptr",
		"    return",
		"travel(node -> children[c])",
		"if node has no children and not end of word",
		"    delete node",
		"else node -> isEnd = false",
		"end"
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);

	int currBreakpoint = aniSlider.getBreakpoints(currentFrameIndex) / 60;
	std::string operation = snapshots[currBreakpoint].operation;
	Trie::TrieSnapshot snapshot = snapshots[currBreakpoint];

	std::cerr << operation << std::endl;


		initNode(snapshot);
		initEdge(snapshot);

		Engine::Frame b_frame, w_frame;
		for (int i = 0; i < snapshot.nodesInfo.size(); i++) {
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (snapshot.nodesInfo[i].parentOrder != -1) {
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}

		for (int step = 0; step < 60; step++) {
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
			if (operation == "remove_unmark_end")
				codePanelColor[step][5] = sf::Color::Red;
			if (operation == "traverse")
				codePanelColor[step][2] = sf::Color::Red;
			if (operation == "remove_delete" || operation == "remove_delete_leaf")
				if (step < 30)
					codePanelColor[step][3] = sf::Color::Red;
				else
					codePanelColor[step][4] = sf::Color::Red;
			if (operation == "end_remove")
				codePanelColor[step][6] = sf::Color::Red;
			if (operation == "not_found")
				if (step < 30)
					codePanelColor[step][0] = sf::Color::Red;
				else
					codePanelColor[step][1] = sf::Color::Red;
		}

		if (snapshot.currentNodeOrder == -1)
			return;

		Node node = w_nodes[snapshot.currentNodeOrder];
		node.setFillColor(W_NODE_COLOR_HOVER);
		changeWNode(snapshot.currentNodeOrder, 0, 59, b_nodes[snapshot.currentNodeOrder], node);
		node = b_nodes[snapshot.currentNodeOrder];
		node.setFillColor(B_NODE_COLOR_HOVER);
		changeBNode(snapshot.currentNodeOrder, 0, 59, w_nodes[snapshot.currentNodeOrder], node);
	
}


void TrieMainState::initSearchFrames()
{
	deleteAllFrames();
	std::vector<std::string> codeLines = {
		"if node -> children[c] == nullptr ",
		"    return false",
		"if end of word",
		"    if node -> isEnd == true",
		"         return true",
		"    else return false",
		"return travel(node -> children[c])"
	};
	for (int i = 0; i < codeLines.size(); i++)
		codePanel.setText(codeLines[i], i);
	int currBreakpoint = aniSlider.getBreakpoints(currentFrameIndex) / 60;
	std::string operation = snapshots[currBreakpoint].operation;
	Trie::TrieSnapshot snapshot = snapshots[currBreakpoint];
	std::cerr << operation << std::endl;

		initNode(snapshot);
		initEdge(snapshot);
		Engine::Frame b_frame, w_frame;
		for (int i = 0; i < snapshot.nodesInfo.size(); i++)
		{
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			if (snapshot.nodesInfo[i].parentOrder != -1)
			{
				b_frame.addEdge("1bedges" + std::to_string(i), b_edges[i]);
				w_frame.addEdge("1wedges" + std::to_string(i), w_edges[i]);
			}
		}
		for (int step = 0; step < 60; step++)
		{
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
			if (operation == "traverse")
				codePanelColor[step][6] = sf::Color::Red;

			if (operation == "found_word")
				if(step < 20)
					codePanelColor[step][2] = sf::Color::Red;
				else if (step < 40)
					codePanelColor[step][3] = sf::Color::Red;
				else 
					codePanelColor[step][4] = sf::Color::Red;
	
			if (operation == "not_found_prefix")
				if (step < 30)
					codePanelColor[step][2] = sf::Color::Red;
				else if (step < 60)
					codePanelColor[step][5] = sf::Color::Red;

			if (operation == "not_found")
				if(step < 30)
					codePanelColor[step][0] = sf::Color::Red;
				else if (step < 60)
					codePanelColor[step][1] = sf::Color::Red;
		}
		if (snapshot.currentNodeOrder == -1)
			return;
		Node node = w_nodes[snapshot.currentNodeOrder];
		node.setFillColor(W_NODE_COLOR_HOVER);
		if(operation == "found_word")
			node.setFillColor(sf::Color::Green);
		else if (operation == "not_found_prefix")
			node.setFillColor(sf::Color::Red);
		changeWNode(snapshot.currentNodeOrder, 0, 59, b_nodes[snapshot.currentNodeOrder], node);
		node = b_nodes[snapshot.currentNodeOrder];
		node.setFillColor(B_NODE_COLOR_HOVER);
		if (operation == "found_word")
			node.setFillColor(sf::Color::Green);
		else if(operation == "not_found_prefix")
			node.setFillColor(sf::Color::Red);
		changeBNode(snapshot.currentNodeOrder, 0, 59, w_nodes[snapshot.currentNodeOrder], node);

}


void TrieMainState::createInsertFrames(std::string word)
{
	currentState = "insert";
	//deleteAllFrames();
	breakpoints.clear();
	snapshots = trie.insertSnapshots(word);
	std::cerr << "snapshots size: " << snapshots.size() << std::endl;
	int numNodes = snapshots.size();
	for (int i = 0; i < numNodes; i++)
		breakpoints.push_back(i * 60);
	breakpoints.push_back(numNodes * 60 - 1);
	aniSlider.setNumPart(numNodes * 60);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = numNodes * 60;
}

void TrieMainState::createDeleteFrames(std::string word)
{
	currentState = "delete";
	//deleteAllFrames();
	breakpoints.clear();
	snapshots = trie.removeSnapshots(word);
	std::cerr << "snapshots size: " << snapshots.size() << std::endl;
	int numNodes = snapshots.size();
	for (int i = 0; i < numNodes; i++)
		breakpoints.push_back(i * 60);
	breakpoints.push_back(numNodes * 60 - 1);
	aniSlider.setNumPart(numNodes * 60);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = numNodes * 60;
}

void TrieMainState::createSearchFrames(std::string word)
{
	currentState = "search";
	//deleteAllFrames();
	breakpoints.clear();
	snapshots = trie.searchSnapshots(word);
	std::cerr << "snapshots size: " << snapshots.size() << std::endl;
	int numNodes = snapshots.size();
	for (int i = 0; i < numNodes; i++)
		breakpoints.push_back(i * 60);
	breakpoints.push_back(numNodes * 60 - 1);
	aniSlider.setNumPart(numNodes * 60);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = numNodes * 60;
}

void TrieMainState::updateFrames()
{
	if (numFrames == 0) return;
	if (numFrames > 0) currentFrameIndex = std::min(currentFrameIndex, numFrames - 1);
	if (currentFrameIndex == 0 || aniSlider.getBreakpoints(prevFrameIndex) != aniSlider.getBreakpoints(currentFrameIndex)) {

		if (currentState == "insert")
		{
			initInsertFrames();
		}
		if (currentState == "delete")
		{
			initDeleteFrames(deleteValue);
		}
		if (currentState == "search")
		{
			initSearchFrames();
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
				if ( currentState == "insert" || currentState == "delete" || currentState == "search")
				{
					int curFrame = currentFrameIndex - aniSlider.getBreakpoints(currentFrameIndex);
					b_currentFrame = b_frames[curFrame];
					w_currentFrame = w_frames[curFrame];
					setCodePanelColor(curFrame);
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