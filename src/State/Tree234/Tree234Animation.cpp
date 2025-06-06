#include "../../../header/State/Tree234/Tree234MainState.h"

void Tree234MainState::setCodePanelColor(int frameIndex)
{
	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, codePanelColor[frameIndex][i]);
	}
}

void Tree234MainState::deleteAllFrames()
{
	b_frames.clear();
	w_frames.clear();
	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
	}
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 7; j++) {
			codePanelColor[i][j] = LavenderSoft;
		}
	}
}

void Tree234MainState::updateFrames()
{
	if (numFrames == 0) return;
	if (numFrames > 0) currentFrameIndex = std::min(currentFrameIndex, numFrames - 1);
	if (currentFrameIndex == 0 || aniSlider.getBreakpoints(prevFrameIndex) != aniSlider.getBreakpoints(currentFrameIndex)) {
		if (isSelectedCreateFrames) {
			initCreateFrames(createNums);
		}
		if (isSelectedInsertFrames) {
			initInsertFrames(insertValue);
		}
		if (isSelectedDeleteFrames) {
			initDeleteFrames(deleteValue);
		}
		if (isSelectedSearchFrames) {
			initSearchFrames(searchValue);
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
				int curFrame = currentFrameIndex - aniSlider.getBreakpoints(currentFrameIndex);
				b_currentFrame = b_frames[curFrame];
				w_currentFrame = w_frames[curFrame];
				setCodePanelColor(curFrame);

				if (*m_context->themeType == 0)
					currentFrame = w_currentFrame;
				else
					currentFrame = b_currentFrame;

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
				setCodePanelColor(59);
				if (*m_context->themeType == 0)
					currentFrame = w_frames.back();
				else
					currentFrame = b_frames.back();

			}
		}
	}
}

void Tree234MainState::initPreTree(Tree234::Node* root)
{
	std::queue<std::pair<Tree234::Node*, int>> q;
	q.push({ root, 0 });
	for (int i = 0; i < maxDepth; i++) {
		nodes[i].clear();
	}

	while (!q.empty()) {
		auto u = q.front().first;
		int du = q.front().second;
		q.pop();

		nodes[du].push_back(u);
		for (auto v : u->children) {
			q.push({ v, du + 1 });
		}
	}

	totNode = 0;
	totEdge = 0;
	for (int i = 0; i < maxDepth; i++) {
		float len = 0;
		for (auto node : nodes[i]) {
			len += static_cast<float>(node->keys.size()) * SIDE;
			len += spaceX;
		}
		if(len > 0) len -= spaceX;
		float firX = (SCREEN_WIDTH - len) / 2.f;

		float curPos = firX;
		for (auto &node : nodes[i]) {
			node->nodes.clear();
			for (auto x : node->keys) {
				initNode(b_nodes[totNode], 1);
				initNode(w_nodes[totNode], 0);
				node->nodes.push_back(totNode);
				b_nodes[totNode].setPosition(sf::Vector2f(curPos + SIDE / 2.f, NodePos.y + (spaceY + SIDE) * i));
				w_nodes[totNode].setPosition(sf::Vector2f(curPos + SIDE / 2.f, NodePos.y + (spaceY + SIDE) * i));
				b_nodes[totNode].setString(std::to_string(x));
				w_nodes[totNode].setString(std::to_string(x));
				curPos += SIDE;
				totNode++;
			}
			curPos += spaceX;
		}
	}

	for (int i = 0; i < maxDepth; i++) {
		for (auto& node : nodes[i]) {
			if (node == nullptr) continue;
			for (auto& child : node->children) {
				if (child == nullptr) continue;
				initEdge(b_edges[totEdge], 1);
				initEdge(w_edges[totEdge], 0);
				child->edge = totEdge;
				setEdgePos(node, child, totEdge);
				totEdge++;
			}
		}
	}
}

void Tree234MainState::initTreeFrames()
{
	Engine::Frame b_frame, w_frame;
	for (int i = 0; i < totNode; i++) {
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
	}
	for (int i = 0; i < totEdge; i++) {
		b_frame.addEdge("2bedges" + std::to_string(i), b_edges[i]);
		w_frame.addEdge("2wedges" + std::to_string(i), w_edges[i]);
	}
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);
}

void Tree234MainState::merge(Tree234::Node* child, Tree234::Node* sibling, int index1, int index2)
{
	sf::Vector2f diff = (b_nodes[child->nodes.back()].getPosition() - b_nodes[sibling->nodes.front()].getPosition()) + sf::Vector2f(SIDE, 0);
	std::queue<Tree234::Node*> q;
	q.push(sibling);
	for (auto nodeId : sibling->nodes) {
		moveNode(nodeId, diff, index1, index2);
	}
	while (!q.empty()) {
		auto u = q.front();
		q.pop();

		for (auto v : u->children) {
			q.push(v);
			moveNodeWithEdge(v, u, diff + sf::Vector2f(spaceX, 0), index1, index2);
		}
	}
}

void Tree234MainState::split(Tree234::Node* root, int index1, int index2)
{
	for (int i = index1; i <= index2; i++) {
		float t = static_cast<float>(i - index1 + 1) / (index2 - index1 + 1);
		std::queue<Tree234::Node*> q;
		q.push(root);

		while (!q.empty()) {
			auto u = q.front();
			q.pop();

			for (auto v : u->children) {
				for (auto nodeId : v->nodes) {
					b_nodes[nodeId].setPosition(sf::Vector2f(b_nodes[nodeId].getPosition().x, b_nodes[u->nodes.front()].getPosition().y + t * (SIDE + spaceY)));
					w_nodes[nodeId].setPosition(sf::Vector2f(b_nodes[nodeId].getPosition().x, b_nodes[u->nodes.front()].getPosition().y + t * (SIDE + spaceY)));
				}
				setEdgePos(u, v, v->edge);
				q.push(v);
			}
		}


		initTreeFrames();
	}
}

void Tree234MainState::setSpacing(int nodeId)
{
	for (int i = 0; i < maxDepth; i++) {
		float len = 0;
		for (auto node : nodes[i]) {
			for (int x : node->nodes) {
				len += b_nodes[x].getGlobalBounds().width;
			}
			len += spaceX;
		}
		if (len > 0) len -= spaceX;
		float firX = (SCREEN_WIDTH - len) / 2.f;

		float curPos = firX;
		for (auto& node : nodes[i]) {
			for (auto x : node->nodes) {
				float curSide = b_nodes[x].getGlobalBounds().width;
				b_nodes[x].setPosition(sf::Vector2f(curPos + curSide / 2.f, NodePos.y + (spaceY + SIDE) * i));
				w_nodes[x].setPosition(sf::Vector2f(curPos + curSide / 2.f, NodePos.y + (spaceY + SIDE) * i));
				curPos += curSide;
			}
			curPos += spaceX;
		}
	}

	for (int i = 0; i < maxDepth; i++) {
		for (auto& node : nodes[i]) {
			if (node == nullptr) continue;
			for (auto& child : node->children) {
				if (child == nullptr) continue;
				setEdgePos(node, child, child->edge);
			}
		}
	}
}

void Tree234MainState::appearNode(int nodeId, int index1, int index2)
{
	for (int i = index1; i <= index2; i++) {
		b_nodes[nodeId].setFillColor(Orange);
		w_nodes[nodeId].setFillColor(sf::Color::Red);
		if (i == index2) {
			b_nodes[nodeId].setFillColor(sf::Color::White);
			w_nodes[nodeId].setFillColor(sf::Color::White);
		}
		
		float t = static_cast<float> (i - index1 + 1) / (index2 - index1 + 1);
		b_nodes[nodeId].setSide(SIDE * t);
		w_nodes[nodeId].setSide(SIDE * t);
		setSpacing(nodeId);
		initTreeFrames();
	}
}

void Tree234MainState::markNode(int nodeId, int index1, int index2)
{
	for (int i = index1; i <= index2; i++) {
		b_nodes[nodeId].setFillColor(Orange);
		w_nodes[nodeId].setFillColor(sf::Color::Red);
		if (i == index2) {
			b_nodes[nodeId].setFillColor(sf::Color::White);
			w_nodes[nodeId].setFillColor(sf::Color::White);
		}

		initTreeFrames();
	}
}

void Tree234MainState::removeNode(int nodeId, int index1, int index2)
{
	for (int i = index1; i <= index2; i++) {
		b_nodes[nodeId].setFillColor(Orange);
		w_nodes[nodeId].setFillColor(sf::Color::Red);
		if (i == index2) {
			b_nodes[nodeId].setFillColor(sf::Color::White);
			w_nodes[nodeId].setFillColor(sf::Color::White);
		}

		float t = 1.f - static_cast<float> (i - index1 + 1) / (index2 - index1 + 1);
		b_nodes[nodeId].setSide(SIDE * t);
		w_nodes[nodeId].setSide(SIDE * t);
		if (i - index1 + 1 == (index2 - index1 + 1) / 2) {
			b_nodes[nodeId].setString("");
			w_nodes[nodeId].setString("");
		}
		setSpacing(nodeId);
		initTreeFrames();
	}
}

void Tree234MainState::deleteEdge(int edgeId, int index1, int index2)
{
	sf::Vector2f start = b_edges[edgeId].getStart();
	sf::Vector2f end = b_edges[edgeId].getEnd();

	for (int i = index1; i <= index2; i++) {
		float t = 1.0f - static_cast<float>(i - index1 + 1) / (index2 - index1 + 1);
		sf::Vector2f newEnd = start + t * (end - start);  
		b_edges[edgeId].setEnd(newEnd);
		w_edges[edgeId].setEnd(newEnd);

		b_frames[i].addEdge("2bedges" + std::to_string(edgeId), b_edges[edgeId]);
		w_frames[i].addEdge("2wedges" + std::to_string(edgeId), w_edges[edgeId]);
	}
}

void Tree234MainState::connectEdge(int edgeId, int index1, int index2)
{
	sf::Vector2f start = b_edges[edgeId].getStart();
	sf::Vector2f end = b_edges[edgeId].getEnd();

	for (int i = index1; i <= index2; i++) {
		float t = static_cast<float>(i - index1 + 1) / (index2 - index1 + 1);
		sf::Vector2f newEnd = start + t * (end - start);
		b_edges[edgeId].setEnd(newEnd);
		w_edges[edgeId].setEnd(newEnd);

		b_frames[i].addEdge("2bedges" + std::to_string(edgeId), b_edges[edgeId]);
		w_frames[i].addEdge("2wedges" + std::to_string(edgeId), w_edges[edgeId]);
	}
}

void Tree234MainState::moveEdge(int edgeId, sf::Vector2f diff, int index1, int index2)
{
	sf::Vector2f oldEnd = b_edges[edgeId].getEnd();
	sf::Vector2f pos = oldEnd + diff;
	for (int i = index1; i <= index2; i++) {
		float t = static_cast<float> (i - index1 + 1) / (index2 - index1 + 1);
		sf::Vector2f newEnd = oldEnd + t * (pos - oldEnd);
		b_edges[edgeId].setEnd(newEnd);
		w_edges[edgeId].setEnd(newEnd);
		b_edges[edgeId].setColor(Orange);
		w_edges[edgeId].setColor(sf::Color::Red);
		if (i == index2) {
			b_edges[edgeId].setColor(sf::Color::White);
			w_edges[edgeId].setColor(sf::Color::Black);
		}

		b_frames[i].addEdge("2bedges" + std::to_string(edgeId), b_edges[edgeId]);
		w_frames[i].addEdge("2wedges" + std::to_string(edgeId), w_edges[edgeId]);
	}
}

void Tree234MainState::moveNode(int nodeId, sf::Vector2f diff, int index1, int index2)
{
	sf::Vector2f oldPos = b_nodes[nodeId].getPosition();
	sf::Vector2f pos = oldPos + diff;
	for (int i = index1; i <= index2; i++) {
		float t = static_cast<float> (i - index1 + 1) / (index2 - index1 + 1);
		sf::Vector2f newPos = oldPos + t * (pos - oldPos);
		b_nodes[nodeId].setPosition(newPos);
		w_nodes[nodeId].setPosition(newPos);
		b_nodes[nodeId].setFillColor(Orange);
		w_nodes[nodeId].setFillColor(sf::Color::Red);
		if (i == index2) {
			b_nodes[nodeId].setFillColor(sf::Color::White);
			w_nodes[nodeId].setFillColor(sf::Color::White);
		}

		b_frames[i].addNode("1bnodes" + std::to_string(nodeId), b_nodes[nodeId]);
		w_frames[i].addNode("1wnodes" + std::to_string(nodeId), w_nodes[nodeId]);
	}
}

void Tree234MainState::moveNodeWithEdge(Tree234::Node* cur, Tree234::Node* par, sf::Vector2f diff, int index1, int index2)
{
	moveEdge(cur->edge, diff, index1, index2);
	std::vector<sf::Vector2f> oldPos;
	for (auto nodeId : cur->nodes) {
		oldPos.push_back(b_nodes[nodeId].getPosition());
	}
	for (int i = index1; i <= index2; i++) {
		for (int j = 0; j < cur->nodes.size(); j++) {
			int nodeId = cur->nodes[j];
			sf::Vector2f pos = oldPos[j] + diff;
			float t = static_cast<float> (i - index1 + 1) / (index2 - index1 + 1);
			sf::Vector2f newPos = oldPos[j] + t * (pos - oldPos[j]);
			b_nodes[nodeId].setPosition(newPos);
			w_nodes[nodeId].setPosition(newPos);
			b_nodes[nodeId].setFillColor(Orange);
			w_nodes[nodeId].setFillColor(sf::Color::Red);
			if (i == index2) {
				b_nodes[nodeId].setFillColor(sf::Color::White);
				w_nodes[nodeId].setFillColor(sf::Color::White);
			}

			b_frames[i].addNode("1bnodes" + std::to_string(nodeId), b_nodes[nodeId]);
			w_frames[i].addNode("1wnodes" + std::to_string(nodeId), w_nodes[nodeId]);
		}
		setEdgePos(par, cur, cur->edge);
		b_frames[i].addEdge("2bedges" + std::to_string(cur->edge), b_edges[cur->edge]);
		w_frames[i].addEdge("2wedges" + std::to_string(cur->edge), w_edges[cur->edge]);
	}
}

void Tree234MainState::preInitCreateFrames(std::vector<int> &nums)
{
	isSelectedCreateFrames = true;
	isSelectedInsertFrames = false;
	isSelectedDeleteFrames = false;
	isSelectedSearchFrames = false;

	breakpoints.clear();

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	// calculate number of frames
	tree234.create(nums);
	breakpoints.push_back(0);
	initPreTree(tree234.snapshots.back());
	numFrames += 60;
	breakpoints.push_back(numFrames);

	//end
	aniSlider.setNumPart(numFrames);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void Tree234MainState::initCreateFrames(std::vector<int> &nums)
{
	deleteAllFrames();
	int preFrames = 0;

	preFrames += 60;
	if (preFrames > currentFrameIndex) {
		for (int i = 0; i < 60; i++) {
			float t = static_cast<float>(i + 1) / 60;
			SIDE = baseSide * t;
			spaceX = baseSpaceX * t;
			spaceY = baseSpaceY * t;
			initPreTree(tree234.snapshots.back());
			initTreeFrames();
		}
		return;
	}
}

void Tree234MainState::preInitInsertFrames(int value)
{
	isSelectedCreateFrames = false;
	isSelectedInsertFrames = true;
	isSelectedDeleteFrames = false;
	isSelectedSearchFrames = false;

	breakpoints.clear();

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	codePanel.setText("if (node->keys.size() == 3) // isFull ", 0);
	codePanel.setText("    split(node)", 1);
	codePanel.setText("if (node->children.empty()) // isLeaf", 2);
	codePanel.setText("    node->keys.insert(key); return", 3);
	codePanel.setText("next = node->keys.upper_bound(key) - 1", 4);
	codePanel.setText("insert(node->children[next], key)", 5);

	// calculate number of frames
	breakpoints.push_back(0);
	tree234.insert(value);
	for (int i = 1; i < tree234.snapshots.size(); i++) {
		numFrames += 60;
		breakpoints.push_back(numFrames);
	}

	//end
	aniSlider.setNumPart(numFrames);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void Tree234MainState::initInsertFrames(int value)
{
	deleteAllFrames();
	int preFrames = 0;

	initPreTree(tree234.snapshots[0]);
	for (int i = 1; i < tree234.snapshots.size(); i++) {
		preFrames += 60;
		if (preFrames > currentFrameIndex) {
			std::string type = tree234.typeSnapshots[i];
			if (type == "splitRoot") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][0] = sf::Color::Red;
					codePanelColor[j][1] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][0] = LavenderSoft;
						codePanelColor[j][1] = LavenderSoft;
					}
				}

;				for (int i = 0; i < 5; i++) {
					initTreeFrames();
				}
				initPreTree(tree234.snapshots[i]);
				split(tree234.operatedNodes[i][0], 5, 59);
			} 
			else if (type == "splitChild") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][0] = sf::Color::Red;
					codePanelColor[j][1] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][0] = LavenderSoft;
						codePanelColor[j][1] = LavenderSoft;
					}
				}

				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 30; j++) {
					initTreeFrames();
				}
				int idx = 0;
				while (idx < tree234.operatedNodes[i][1]->keys.size() && tree234.operatedNodes[i][1]->keys[idx] < tree234.operatedNodes[i][0]->keys[1]) {
					idx++;
				}
				deleteEdge(tree234.operatedNodes[i][0]->edge, 0, 29);
				sf::Vector2f posA = b_nodes[tree234.operatedNodes[i][0]->nodes[1]].getPosition();
				initPreTree(tree234.snapshots[i]);
				sf::Vector2f posB = b_nodes[tree234.operatedNodes[i][1]->nodes[idx]].getPosition();
				initPreTree(tree234.snapshots[i - 1]);
				sf::Vector2f diff = posB - posA;
				moveNode(tree234.operatedNodes[i][0]->nodes[1], diff, 0, 29);
				initPreTree(tree234.snapshots[i]);
				split(tree234.operatedNodes[i][1], 30, 59);
			}
			else if(type == "") {
				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 5; j++) {
					initTreeFrames();
				}
				initPreTree(tree234.snapshots[i]);
				for (int j = 5; j < 60; j++) {
					initTreeFrames();
				}
			}
			else if (type == "insert") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][2] = sf::Color::Red;
					codePanelColor[j][3] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][2] = LavenderSoft;
						codePanelColor[j][3] = LavenderSoft;
					}
				}

				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 5; j++) {
					initTreeFrames();
				}
				initPreTree(tree234.snapshots[i]);
				int idx = 0;
				while (idx < tree234.operatedNodes[i][0]->keys.size() && tree234.operatedNodes[i][0]->keys[idx] < value) {
					idx++;
				}
				appearNode(tree234.operatedNodes[i][0]->nodes[idx], 5, 59);
			}
			
			return;
		}
	}
}

void Tree234MainState::preInitSearchFrames(int value)
{
	isSelectedCreateFrames = false;
	isSelectedInsertFrames = false;
	isSelectedDeleteFrames = false;
	isSelectedSearchFrames = true;

	breakpoints.clear();

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	codePanel.setText("if (!node || node->isLeaf()) return false", 0);
	codePanel.setText("idx = 0", 1);
	codePanel.setText("while (key < keys in node->keys) idx++", 2);
	codePanel.setText("if (idx < node->keys.size() && ", 3);
	codePanel.setText("    key == node->keys[idx]) return true", 4);
	codePanel.setText("return search(node->children[idx])", 5);

	// calculate number of frames
	breakpoints.push_back(0);
	auto cur = tree234.snapshots.back();
	initPreTree(tree234.snapshots.back());
	while (1) {
		numFrames += 60;
		breakpoints.push_back(numFrames);
		int idx = 0;
		while (idx < cur->keys.size() && cur->keys[idx] < value) {
			idx++;
		}
		if (idx < cur->keys.size() && cur->keys[idx] == value) break;
		if (cur->isLeaf()) break;

		cur = cur->children[idx];
	}

	//end
	aniSlider.setNumPart(numFrames);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void Tree234MainState::initSearchFrames(int value)
{
	deleteAllFrames();
	int preFrames = 0;
	
	auto cur = tree234.snapshots.back();
	while (1) {
		preFrames += 60;
		int idx = 0;
		while (idx < cur->keys.size() && cur->keys[idx] < value) {
			idx++;
		}
		if (idx < cur->keys.size() && cur->keys[idx] == value) {
			if (preFrames > currentFrameIndex) {
				for (int i = 0; i < 60; i++) {
					b_nodes[cur->nodes[idx]].setFillColor(Orange);
					w_nodes[cur->nodes[idx]].setFillColor(sf::Color::Red);
					/*codePanel.setLineColor(3, sf::Color::Red);
					codePanel.setLineColor(4, sf::Color::Red);*/
					codePanelColor[i][3] = sf::Color::Red;
					codePanelColor[i][4] = sf::Color::Red;
					if (i == 59) {
						b_nodes[cur->nodes[idx]].setFillColor(sf::Color::White);
						w_nodes[cur->nodes[idx]].setFillColor(sf::Color::White);
						/*codePanel.setLineColor(3, LavenderSoft);
						codePanel.setLineColor(4, LavenderSoft);*/
						codePanelColor[i][3] = LavenderSoft;
						codePanelColor[i][4] = LavenderSoft;
					}
					initTreeFrames();
					//b_frames[i].addPanel("3bcodePanel", codePanel);
					//w_frames[i].addPanel("3wcodePanel", codePanel);
				}
				return;
			}
		}

		if (preFrames > currentFrameIndex) {
			for (int i = 0; i < 60; i++) {
				for (auto nodeId : cur->nodes) {
					b_nodes[nodeId].setTextColor(Orange);
					w_nodes[nodeId].setTextColor(sf::Color::Red);
					if (i == 59) {
						b_nodes[nodeId].setTextColor(sf::Color::Black);
						w_nodes[nodeId].setTextColor(sf::Color::Black);
					}
				}
				if (cur->isLeaf()) {
					//codePanel.setLineColor(0, sf::Color::Red);
					codePanelColor[i][0] = sf::Color::Red;
					if (i == 59) {
						//codePanel.setLineColor(0, LavenderSoft);
						codePanelColor[i][0] = LavenderSoft;
					}
				}
				else {
					if (i < 40) {
						//codePanel.setLineColor(1, sf::Color::Red);
						//codePanel.setLineColor(2, sf::Color::Red);
						codePanelColor[i][1] = sf::Color::Red;
						codePanelColor[i][2] = sf::Color::Red;
						if (i == 39) {
							//codePanel.setLineColor(1, LavenderSoft);
							//codePanel.setLineColor(2, LavenderSoft);
							codePanelColor[i][1] = LavenderSoft;
							codePanelColor[i][2] = LavenderSoft;
						}
					}
					else {
						//codePanel.setLineColor(5, sf::Color::Red);
						codePanelColor[i][5] = sf::Color::Red;
						if (i == 59) {
							//codePanel.setLineColor(5, LavenderSoft);
							codePanelColor[i][5] = LavenderSoft;
						}
					}
				}
				initTreeFrames();
				/*b_frames[i].addPanel("3bcodePanel", codePanel);
				w_frames[i].addPanel("3wcodePanel", codePanel);*/
			}
			return;
		}
		if (cur->isLeaf()) {
			break;
		}
		cur = cur->children[idx];
	}
}

void Tree234MainState::preInitDeleteFrames(int value)
{
	isSelectedCreateFrames = false;
	isSelectedInsertFrames = false;
	isSelectedDeleteFrames = true;
	isSelectedSearchFrames = false;

	breakpoints.clear();

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	codePanel.setText("if (key in node && node->isLeaf) erase(key)", 0);
	codePanel.setText("if (key in node)", 1);
	codePanel.setText("    replace key with predecessor/successor", 2);
	codePanel.setText("if (key not in node) remove(child, key)", 3);
	codePanel.setText("if (child->keys.size() < 2)  ", 4);
	codePanel.setText("    fill child or merge with sibling", 5);
	codePanel.setText("remove(child, key)", 6);

	// calculate number of frames
	breakpoints.push_back(0);
	tree234.remove(value);
	for (int i = 1; i < tree234.snapshots.size(); i++) {
		if (tree234.typeSnapshots[i] == "skip") continue;
		numFrames += 60;
		breakpoints.push_back(numFrames);
	}

	//end
	aniSlider.setNumPart(numFrames);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void Tree234MainState::initDeleteFrames(int value)
{
	deleteAllFrames();
	int preFrames = 0;

	for (int i = 1; i < tree234.snapshots.size(); i++) {
		if (tree234.typeSnapshots[i] == "skip") continue;
		preFrames += 60;
		if (preFrames > currentFrameIndex) {
			if (tree234.typeSnapshots[i] == "") {
				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 5; j++) {
					initTreeFrames();
				}
				initPreTree(tree234.snapshots[i]);
				for (int j = 5; j < 60; j++) {
					initTreeFrames();
				}
			}
			else if (tree234.typeSnapshots[i] == "movePrevEdges") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i]);
				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 60; j++) {
					initTreeFrames();
				}
				for (auto child : tree234.operatedNodes[i][0]->children) {
					moveEdge(child->edge, sf::Vector2f(SIDE, 0), 0, 59);
				}

			}
			else if (tree234.typeSnapshots[i] == "moveNextEdges") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i]);
				for (int j = 0; j < 60; j++) {
					initTreeFrames();
				}
				for (auto child : tree234.operatedNodes[i][0]->children) {
					moveEdge(child->edge, sf::Vector2f(-SIDE, 0), 0, 59);
				}
			}
			else if (tree234.typeSnapshots[i] == "extraPrevKeys") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 5; j++) {
					initTreeFrames();
				}
				initPreTree(tree234.snapshots[i]);
				appearNode(tree234.operatedNodes[i][0]->nodes.front(), 5, 59);
			}
			else if (tree234.typeSnapshots[i] == "extraNextKeys") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 5; j++) {
					initTreeFrames();
				}
				initPreTree(tree234.snapshots[i]);
				appearNode(tree234.operatedNodes[i][0]->nodes.back(), 5, 59);
			}
			else if (tree234.typeSnapshots[i] == "moveNextNodes") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i]);
				for (int j = 0; j < 60; j++) {
					initTreeFrames();
				}
				int nodeId = tree234.operatedNodes[i][1]->nodes.front();
				int nodeId2 = tree234.operatedNodes[i][0]->nodes[tree234.idxes[i]];
				moveNode(nodeId, b_nodes[nodeId2].getPosition() - b_nodes[nodeId].getPosition(), 0, 59);
			}
			else if (tree234.typeSnapshots[i] == "movePrevNodes") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i]);
				for (int j = 0; j < 60; j++) {
					initTreeFrames();
				}
				int nodeId = tree234.operatedNodes[i][1]->nodes.back();
				int nodeId2 = tree234.operatedNodes[i][0]->nodes[tree234.idxes[i]];
				moveNode(nodeId, b_nodes[nodeId2].getPosition() - b_nodes[nodeId].getPosition(), 0, 59);
			}
			else if (tree234.typeSnapshots[i] == "remove") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i - 1]);
				removeNode(tree234.operatedNodes[i][0]->nodes[tree234.idxes[i]], 0, 59);
				if (tree234.operatedNodes[i].size() == 2 && tree234.operatedNodes[i][1]->nodes.size() == 1) {
					deleteEdge(tree234.operatedNodes[i][1]->edge, 0, 59);
				
				}
			}
			else if (tree234.typeSnapshots[i] == "push_backNode") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 5; j++) {
					initTreeFrames();
				}
				initPreTree(tree234.snapshots[i]);
				appearNode(tree234.operatedNodes[i][0]->nodes.back(), 5, 59);
			}
			else if (tree234.typeSnapshots[i] == "mergeSibling") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][4] = sf::Color::Red;
					codePanelColor[j][5] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][4] = LavenderSoft;
						codePanelColor[j][5] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i - 1]);
				for (int j = 0; j < 60; j++) {
					initTreeFrames();
				}
				deleteEdge(tree234.operatedNodes[i][1]->edge, 0, 59);
				merge(tree234.operatedNodes[i][0], tree234.operatedNodes[i][1], 0, 59);
			}
			else if (tree234.typeSnapshots[i] == "removeLeaf") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][0] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][0] = LavenderSoft;
					}
				}
				initPreTree(tree234.snapshots[i - 1]);
				removeNode(tree234.operatedNodes[i][0]->nodes[tree234.idxes[i]], 0, 59);
				if (tree234.operatedNodes[i].size() == 2 && tree234.operatedNodes[i][1]->nodes.size() == 1) {
					deleteEdge(tree234.operatedNodes[i][1]->edge, 0, 59);
				}
			} 
			else if (tree234.typeSnapshots[i] == "replace") {
				for (int j = 0; j < 59; j++) {
					codePanelColor[j][1] = sf::Color::Red;
					codePanelColor[j][2] = sf::Color::Red;
					if (j == 59) {
						codePanelColor[j][1] = LavenderSoft;
						codePanelColor[j][2] = LavenderSoft;
					}
				}

				initPreTree(tree234.snapshots[i - 1]);
				markNode(tree234.operatedNodes[i][0]->nodes[tree234.idxes[i]], 0, 29);
				initPreTree(tree234.snapshots[i]);
				markNode(tree234.operatedNodes[i][0]->nodes[tree234.idxes[i]], 30, 59);
			}
			return;
		}
	}
}
