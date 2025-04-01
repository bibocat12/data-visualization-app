#include "HeapMainState.h"

void HeapMainState::connectTwoNodes(int index, int index1, int index2, bool isEnd)
{
	sf::Vector2f start, end;

	if (index % 2 == 1) { // left child
		//find center of the node
		sf::Vector2f center = b_nodes[index].getPosition();
		start = sf::Vector2f(center.x + cos(DEG_TO_RAD(30)) * RADIUS, center.y - sin(DEG_TO_RAD(30)) * RADIUS);

		//find center of parent
		center = b_nodes[heap.parent(index)].getPosition();
		end = sf::Vector2f(center.x - cos(DEG_TO_RAD(30)) * RADIUS, center.y + sin(DEG_TO_RAD(30)) * RADIUS);
	}
	else { // right child

		//find center of the node
		sf::Vector2f center = b_nodes[index].getPosition();
		start = sf::Vector2f(center.x - cos(DEG_TO_RAD(30)) * RADIUS, center.y - sin(DEG_TO_RAD(30)) * RADIUS);

		//find center of parent
		center = b_nodes[heap.parent(index)].getPosition();
		end = sf::Vector2f(center.x + cos(DEG_TO_RAD(30)) * RADIUS, center.y + sin(DEG_TO_RAD(30)) * RADIUS);
	}

	float _tan = abs(end.y - start.y) / abs(end.x - start.x);

	for (int i = index1; i <= index2; i++)
	{
		sf::Vector2f posEndEdge;
		if (index % 2 == 1) {
			posEndEdge.x = start.x + abs(end.x - start.x) * static_cast<float>(i - index1 + 1) / (index2 - index1 + 1);
		}
		else {
			posEndEdge.x = start.x - abs(end.x - start.x) * static_cast<float>(i - index1 + 1) / (index2 - index1 + 1);
		}
		posEndEdge.y = start.y - abs(posEndEdge.x - start.x) * _tan;

		b_edges[index].setStart(start);
		w_edges[index].setStart(start);
		b_edges[index].setEnd(posEndEdge);
		w_edges[index].setEnd(posEndEdge);

		b_nodes[index].setFillColor(sf::Color::Red);
		w_nodes[index].setFillColor(Orange);
		b_nodes[index].setRadius(RADIUS * static_cast<float>(i - index1 + 1) / (index2 - index1 + 1));
		w_nodes[index].setRadius(RADIUS * static_cast<float>(i - index1 + 1) / (index2 - index1 + 1));
		if (i == index2 && isEnd) {
			b_nodes[index].setFillColor(sf::Color::White);
			w_nodes[index].setFillColor(sf::Color::White);
		}

		b_frames[i].addEdge("2bedges" + std::to_string(index), b_edges[index]);
		w_frames[i].addEdge("2wedges" + std::to_string(index), w_edges[index]);
		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
		w_frames[i].addNode("1wnodes" + std::to_string(index), w_nodes[index]);
	}
}

void HeapMainState::deleteEdge(int index, int index1, int index2, bool isEnd)
{
	sf::Vector2f start, end;

	if (index % 2 == 1) { // left child
		//find center of the node
		sf::Vector2f center = b_nodes[index].getPosition();
		start = sf::Vector2f(center.x + cos(DEG_TO_RAD(30)) * RADIUS, center.y - sin(DEG_TO_RAD(30)) * RADIUS);

		//find center of parent
		center = b_nodes[heap.parent(index)].getPosition();
		end = sf::Vector2f(center.x - cos(DEG_TO_RAD(30)) * RADIUS, center.y + sin(DEG_TO_RAD(30)) * RADIUS);
	}
	else { // right child
		//find center of the node
		sf::Vector2f center = b_nodes[index].getPosition();
		start = sf::Vector2f(center.x - cos(DEG_TO_RAD(30)) * RADIUS, center.y - sin(DEG_TO_RAD(30)) * RADIUS);

		//find center of parent
		center = b_nodes[heap.parent(index)].getPosition();
		end = sf::Vector2f(center.x + cos(DEG_TO_RAD(30)) * RADIUS, center.y + sin(DEG_TO_RAD(30)) * RADIUS);
	}

	float _tan = abs(end.y - start.y) / abs(end.x - start.x);

	for (int i = index1; i <= index2; i++)
	{
		sf::Vector2f posEndEdge;
		if (index % 2 == 1) {
			posEndEdge.x = start.x + abs(end.x - start.x) * static_cast<float> (i - index1 + 1) / (index2 - index1 + 1);
		}
		else {
			posEndEdge.x = start.x - abs(end.x - start.x) * static_cast<float> (i - index1 + 1) / (index2 - index1 + 1);
		}
		posEndEdge.y = start.y - abs(posEndEdge.x - start.x) * _tan;

		b_edges[index].setStart(posEndEdge);
		b_edges[index].setEnd(end);
		w_edges[index].setStart(posEndEdge);
		w_edges[index].setEnd(end);

		if (i == index2) {
			b_edges[index].setThickness(0);
			w_edges[index].setThickness(0);
		}

		b_frames[i].addEdge("2bedges" + std::to_string(index), b_edges[index]);
		w_frames[i].addEdge("2wedges" + std::to_string(index), w_edges[index]);
	}
}

void HeapMainState::swapTwoNodes(int node1, int node2, int index1, int index2, bool isEnd)
{
	int index = std::max(node1, node2);
	int par = std::min(node1, node2);
	sf::Vector2f start, end;
	start = b_nodes[index].getPosition();
	end = b_nodes[par].getPosition();

	for (int i = index1; i <= index2; i++) {
		sf::Vector2f childPos, parPos;
		float t = static_cast<float>(i - index1 + 1) / (index2 - index1 + 1);
		childPos = start + t * (end - start);
		parPos = end + t * (start - end);

		b_nodes[index].setPosition(childPos);
		w_nodes[index].setPosition(childPos);
		b_nodes[par].setPosition(parPos);
		w_nodes[par].setPosition(parPos);

		b_nodes[node1].setFillColor(sf::Color::Red);
		w_nodes[node1].setFillColor(Orange);
		b_nodes[node2].setTextColor(sf::Color::Red);
		w_nodes[node2].setTextColor(Orange);
		if (i == index2 && isEnd) {
			b_nodes[node1].setFillColor(sf::Color::White);
			w_nodes[node1].setFillColor(sf::Color::White);
			b_nodes[node2].setTextColor(sf::Color::Black);
			w_nodes[node2].setTextColor(sf::Color::Black);
		}

		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
		w_frames[i].addNode("1wnodes" + std::to_string(index), w_nodes[index]);
		b_frames[i].addNode("1bnodes" + std::to_string(par), b_nodes[par]);
		w_frames[i].addNode("1wnodes" + std::to_string(par), w_nodes[par]);
	}

	auto tmp = b_nodes[node1];
	tmp.setPosition(b_nodes[node1].getPosition());
	tmp.setString(b_nodes[node1].getString());
	b_nodes[node1].setPosition(b_nodes[node2].getPosition());
	b_nodes[node1].setString(b_nodes[node2].getString());
	b_nodes[node2].setPosition(tmp.getPosition());
	b_nodes[node2].setString(tmp.getString());

	tmp = w_nodes[node1];
	tmp.setPosition(w_nodes[node1].getPosition());
	tmp.setString(w_nodes[node1].getString());
	w_nodes[node1].setPosition(w_nodes[node2].getPosition());
	w_nodes[node1].setString(w_nodes[node2].getString());
	w_nodes[node2].setPosition(tmp.getPosition());
	w_nodes[node2].setString(tmp.getString());
}

void HeapMainState::deleteAllFrames()
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

void HeapMainState::setCodePanelColor(int frameIndex)
{
	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, codePanelColor[frameIndex][i]);
	}
}

void HeapMainState::initPreHeap(const std::vector<int>& nums)
{
	Engine::Frame b_frame, w_frame;
	for (int j = 0; j < (int)nums.size(); j++) {
		b_nodes[j].setString(std::to_string(nums[j]));
		w_nodes[j].setString(std::to_string(nums[j]));
		b_frame.addNode("1bnodes" + std::to_string(j), b_nodes[j]);
		w_frame.addNode("1wnodes" + std::to_string(j), w_nodes[j]);
		if (j) {
			b_frame.addEdge("2bedges" + std::to_string(j), b_edges[j]);
			w_frame.addEdge("2wedges" + std::to_string(j), w_edges[j]);
		}
	}
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);
}

void HeapMainState::preInitCreateFrames(bool isInitState)
{
	isSelectedCreateFrames = true;
	isSelectedInsertFrames = false;
	isSelectedDeleteFrames = false;
	isSelectedUpdateFrames = false;
	isSelectedExtractFrames = false;

	breakpoints.clear();
	createArrs = heap.create(createNums);
	initNode();
	initEdge();
	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	codePanel.setText("for (i = 0; i < a.size(); i++)", 0);
	codePanel.setText("    node[i] = a[i]", 1);
	codePanel.setText("for (i = a.size() / 2 - 1; i >= 0; i--)", 2);
	codePanel.setText("    heapify(i)", 3);

	// calculate number of frames
	breakpoints.push_back(0);
	numFrames += 60;
	breakpoints.push_back(numFrames);
	// Heapify
	for (int i = 1; i < (int)createArrs.size(); i++) {
		for (int j = 0; j < (int)createArrs[i].size() - 1; j += 2) {
			numFrames += 60;
			breakpoints.push_back(numFrames);
		}
	}

	aniSlider.setNumPart(numFrames);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void HeapMainState::initCreateFrames(bool isInitState)
{
	auto elements = createNums;
	deleteAllFrames();

	if (currentFrameIndex < 60) {
		for (int i = 0; i < 60; i++)
		{
			Engine::Frame b_frame, w_frame;
			for (int j = 0; j < (int)createArrs[0].size(); j++) {
				b_nodes[j].setString(std::to_string(createArrs[0][j].second));
				w_nodes[j].setString(std::to_string(createArrs[0][j].second));
				b_nodes[j].setTextUnder(std::to_string(createArrs[0][j].first));
				w_nodes[j].setTextUnder(std::to_string(createArrs[0][j].first));
				float t = static_cast<float>(i + 1) / 60;
				b_nodes[j].setRadius(RADIUS * t);
				w_nodes[j].setRadius(RADIUS * t);
				codePanelColor[i][0] = sf::Color::Red;
				codePanelColor[i][1] = sf::Color::Red;
				if (i == 59 && j == (int)createArrs[0].size() - 1) {
					codePanelColor[i][0] = LavenderSoft;
					codePanelColor[i][1] = LavenderSoft;
				}
				if (j == 0) {
					if (i < 59) {
						b_nodes[j].setFillColor(sf::Color::Red);
						w_nodes[j].setFillColor(Orange);
					}
					else {
						b_nodes[j].setFillColor(sf::Color::White);
						w_nodes[j].setFillColor(sf::Color::White);
					}
				}

				b_frame.addNode("1bnodes" + std::to_string(createArrs[0][j].first), b_nodes[j]);
				w_frame.addNode("1wnodes" + std::to_string(createArrs[0][j].first), w_nodes[j]);
				b_frame.addEdge("2bedges" + std::to_string(createArrs[0][j].first), b_edges[j]);
				w_frame.addEdge("2wedges" + std::to_string(createArrs[0][j].first), w_edges[j]);
			}
			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		for (int i = 1; i < (int)createArrs[0].size(); i++)
			connectTwoNodes(i, 0, 59, 1);
	}
	else {
		int preFrames = 60;
		bool ok = 0;
		for (int i = 1; i < (int)createArrs.size(); i++) {
			for (int j = 0; j < (int)createArrs[i].size() - 1; j += 2) {
				preFrames += 60;
				if (preFrames > currentFrameIndex) {
					//this one
					int firstIndex = static_cast<int>(b_frames.size());
					int lastIndex = firstIndex + 60 - 1;
					std::pair<int, int> cur = createArrs[i][j];
					std::pair<int, int> child = createArrs[i][j + 1];
					b_nodes[cur.first].setString(std::to_string(cur.second));
					w_nodes[cur.first].setString(std::to_string(cur.second));

					b_nodes[child.first].setString(std::to_string(child.second));
					w_nodes[child.first].setString(std::to_string(child.second));

					for (int k = 0; k < 60; k++)
					{
						initPreHeap(elements);
						codePanelColor[k][2] = sf::Color::Red;
						codePanelColor[k][3] = sf::Color::Red;
						if (k == 59 && i == (int)createArrs.size() - 1) {
							codePanelColor[k][2] = LavenderSoft;
							codePanelColor[k][3] = LavenderSoft;
						}
					}
					swapTwoNodes(cur.first, child.first, firstIndex, lastIndex, 1);

					ok = 1;
					break;
				}
				std::swap(elements[createArrs[i][j].first], elements[createArrs[i][j + 1].first]);
			}

			if (ok) {
				return;
			}
		}
	}

}

void HeapMainState::preInitInsertFrames(int value)
{
	isSelectedCreateFrames = false;
	isSelectedInsertFrames = true;
	isSelectedDeleteFrames = false;
	isSelectedUpdateFrames = false;
	isSelectedExtractFrames = false;

	breakpoints.clear();
	heapElements = heap.getAllElements();
	insertArrs = heap.insertKey(value);
	initNode();
	initEdge();

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	codePanel.setText("node[size++] = newValue", 0);
	codePanel.setText("while (i > 0 && node[i] < node[parent(i)])", 1);
	codePanel.setText("    swap(node[i], node[parent(i)])", 2);
	codePanel.setText("    i = parent(i)", 3);

	breakpoints.push_back(0);
	numFrames += 60;
	breakpoints.push_back(numFrames);
	for (int h = 1; h < (int)insertArrs.size(); h++) {
		numFrames += 60;
		breakpoints.push_back(numFrames);
	}

	aniSlider.setNumPart(numFrames);
	aniSlider.setPart(0);
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void HeapMainState::initInsertFrames(int value)
{
	deleteAllFrames();
	auto elements = heapElements;
	elements.push_back(value);

	int id = heap.Size() - 1;
	if (currentFrameIndex < 60) {
		//add new node
		b_nodes[id].setString(std::to_string(value));
		w_nodes[id].setString(std::to_string(value));
		b_nodes[id].setTextUnder(std::to_string(id));
		w_nodes[id].setTextUnder(std::to_string(id));
		for (int i = 0; i < 60; i++)
		{
			Engine::Frame b_frame, w_frame;
			if (id == 0) {
				b_nodes[id].setFillColor(sf::Color::Red);
				w_nodes[id].setFillColor(Orange);
				if (i == 59) {
					b_nodes[id].setFillColor(sf::Color::White);
					w_nodes[id].setFillColor(sf::Color::White);
				}
			}
			codePanelColor[i][0] = sf::Color::Red;
			if (i == 59) {
				codePanelColor[i][0] = LavenderSoft;
			}

			initPreHeap(heapElements);
			b_frames[i].addNode("1bnodes" + std::to_string(id), b_nodes[id]);
			w_frames[i].addNode("1wnodes" + std::to_string(id), w_nodes[id]);

		}
		if (id) {
			connectTwoNodes(id, 0, 59, 1);
		}
	}
	else {
		//swap nodes
		int preFrames = 60;
		for (int h = 1; h < (int)insertArrs.size(); h++) {
			std::pair<int, int> par = insertArrs[h];
			preFrames += 60;
			if (preFrames > currentFrameIndex) {
				for (int i = 0; i < 60; i++)
				{
					codePanelColor[i][1] = sf::Color::Red;
					codePanelColor[i][2] = sf::Color::Red;
					codePanelColor[i][3] = sf::Color::Red;
					if (h == (int)insertArrs.size() - 1 && i == 59) {
						codePanelColor[i][1] = LavenderSoft;
						codePanelColor[i][2] = LavenderSoft;
						codePanelColor[i][3] = LavenderSoft;
					}

					initPreHeap(elements);

				}
				swapTwoNodes(id, heap.parent(id), 0, 59, 1);
				break;
			}
			id = par.first;
			std::swap(elements[insertArrs[h - 1].first], elements[insertArrs[h].first]);
		}
	}
}

void HeapMainState::preInitUpdateFrames(int id, int newV)
{
	isSelectedCreateFrames = false;
	isSelectedInsertFrames = false;
	isSelectedDeleteFrames = false;
	isSelectedUpdateFrames = true;
	isSelectedExtractFrames = false;

	breakpoints.clear();
	heapElements = heap.getAllElements();
	isLess = heap.isLessThanParent(id, newV);
	updateArrs = heap.update(id, newV);
	initNode();
	initEdge();

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	codePanel.setText("node[id] = newValue", 0);
	codePanel.setText("while(id > 0 && node[id] < node[parent(id)])", 1);
	codePanel.setText("    swap(node[id], node[parent(id)]", 2);
	codePanel.setText("    id = parent(id)", 3);
	codePanel.setText("heapify(id)", 4);

	breakpoints.push_back(0);
	// change node
	numFrames += 60;
	breakpoints.push_back(numFrames);
	// swap
	for (int i = 0; i < (int)updateArrs.size() - 1; i = i + 1 + (!isLess)) {
		numFrames += 60;
		breakpoints.push_back(numFrames);
	}

	aniSlider.setNumPart(numFrames);
	aniSlider.setPart(0);
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void HeapMainState::initUpdateFrames(int id, int newV)
{
	deleteAllFrames();
	//initNode();
	auto elements = heapElements;

	int preFrames = 0;
	//Change node 
	preFrames += 60;
	if (preFrames > currentFrameIndex) {
		for (int i = 0; i < 60; i++)
		{
			initPreHeap(elements);
			codePanelColor[i][0] = sf::Color::Red;
			b_nodes[id].setFillColor(sf::Color::Red);
			w_nodes[id].setFillColor(Orange);

			if (i < 30) {
				b_nodes[id].setRadius(static_cast<float>(RADIUS - RADIUS * static_cast<float>(i + 1) / 30));
				w_nodes[id].setRadius(static_cast<float>(RADIUS - RADIUS * static_cast<float>(i + 1) / 30));
			}
			else {
				if (i == 30) {
					b_nodes[id].setString(std::to_string(newV));
					w_nodes[id].setString(std::to_string(newV));
					elements[id] = newV;
				}
				b_nodes[id].setRadius(static_cast<float>(RADIUS * static_cast<float>(i - 29) / 30));
				w_nodes[id].setRadius(static_cast<float>(RADIUS * static_cast<float>(i - 29) / 30));
				if (i == 59 && (int)updateArrs.size() == 1) {
					b_nodes[id].setFillColor(sf::Color::White);
					w_nodes[id].setFillColor(sf::Color::White);
				}
				if (i == 59) {
					codePanelColor[i][0] = LavenderSoft;
				}
			}

			b_frames[i].addNode("1bnodes" + std::to_string(id), b_nodes[id]);
			w_frames[i].addNode("1wnodes" + std::to_string(id), w_nodes[id]);
		}
		return;
	}
	elements[id] = newV;

	//swap
	std::pair<int, int> cur, child;
	for (int i = 0; i < (int)updateArrs.size() - 1; i = i + 1 + (!isLess)) {
		cur = updateArrs[i];
		if (!isLess) {
			child = updateArrs[i + 1];
		}
		preFrames += 60;
		if (preFrames > currentFrameIndex) {
			for (int j = 0; j < 60; j++) {
				if (isLess) {
					codePanelColor[j][1] = sf::Color::Red;
					codePanelColor[j][2] = sf::Color::Red;
					codePanelColor[j][3] = sf::Color::Red;
					if (j == 59 && i + 1 >= (int)updateArrs.size() - 1) {
						codePanelColor[j][1] = LavenderSoft;
						codePanelColor[j][2] = LavenderSoft;
						codePanelColor[j][3] = LavenderSoft;
					}
				}
				else {
					codePanelColor[j][4] = sf::Color::Red;
					if (j == 59 && i + 2 >= (int)updateArrs.size() - 1) {
						codePanelColor[j][4] = LavenderSoft;
					}
				}

				initPreHeap(elements);
			}
			if (isLess) {
				swapTwoNodes(cur.first, heap.parent(cur.first), 0, 59, 1);
			}
			else {
				swapTwoNodes(cur.first, child.first, 0, 59, 1);
			}
			return;
		}
		if (isLess) {
			std::swap(elements[cur.first], elements[heap.parent(cur.first)]);
		}
		else {
			std::swap(elements[cur.first], elements[child.first]);
		}
	}
}

void HeapMainState::preInitDeleteFrames(int id)
{
	isSelectedCreateFrames = false;
	isSelectedInsertFrames = false;
	isSelectedDeleteFrames = true;
	isSelectedUpdateFrames = false;
	isSelectedExtractFrames = false;

	breakpoints.clear();
	heapElements = heap.getAllElements();
	deleteArrs = heap.deleteKey(id);
	initNode();
	initEdge();

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	codePanel.setText("while (id > 0)", 0);
	codePanel.setText("    swap(node[id], node[parent(id)]", 1);
	codePanel.setText("    id = parent(id)", 2);
	codePanel.setText("// extract root", 3);
	codePanel.setText("node[0] = node[size--]", 4);
	codePanel.setText("heapify(0)", 5);

	breakpoints.push_back(0);
	// move the delete node to the root 
	for (int h = 1; h < (int)deleteArrs[0].size(); h++) {
		numFrames += 60;
		breakpoints.push_back(numFrames);
	}
	// delete the node
	numFrames += 60;
	breakpoints.push_back(numFrames);
	// move the last node
	numFrames += 60;
	breakpoints.push_back(numFrames);
	// heapify
	for (int h = 0; h < (int)deleteArrs[1].size() - 1; h += 2) {
		numFrames += 60;
		breakpoints.push_back(numFrames);
	}

	aniSlider.setNumPart(numFrames);
	aniSlider.setPart(0);
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void HeapMainState::initDeleteFrames(int id)
{
	deleteAllFrames();
	auto elements = heapElements;
	initNode(elements.size());
	initEdge(elements.size());

	int preFrames = 0;
	// move the delete node to the root
	for (int h = 1; h < (int)deleteArrs[0].size(); h++) {
		std::pair<int, int> child = deleteArrs[0][h - 1];
		std::pair<int, int> par = deleteArrs[0][h];

		preFrames += 60;
		if (preFrames > currentFrameIndex) {
			for (int i = 0; i < 60; i++)
			{
				codePanelColor[i][0] = sf::Color::Red;
				codePanelColor[i][1] = sf::Color::Red;
				codePanelColor[i][2] = sf::Color::Red;
				if (i == 59 && h == (int)deleteArrs[0].size() - 1) {
					codePanelColor[i][0] = LavenderSoft;
					codePanelColor[i][1] = LavenderSoft;
					codePanelColor[i][2] = LavenderSoft;
				}

				initPreHeap(elements);
			}
			swapTwoNodes(child.first, par.first, 0, 59, 1);
			return;
		}
		std::swap(elements[child.first], elements[par.first]);
	}

	//delete the node 
	preFrames += 60;
	if (preFrames > currentFrameIndex) {
		for (int i = 0; i < 60; i++)
		{
			codePanelColor[i][4] = sf::Color::Red;
			b_nodes[0].setFillColor(sf::Color::Red);
			w_nodes[0].setFillColor(Orange);

			b_nodes[0].setRadius(static_cast<float>(RADIUS - RADIUS * static_cast<float>(i + 1) / 60));
			w_nodes[0].setRadius(static_cast<float>(RADIUS - RADIUS * static_cast<float>(i + 1) / 60));
			if (i == 59) {
				b_nodes[0].setCharacterSize(0);
				w_nodes[0].setCharacterSize(0);
				codePanelColor[i][4] = LavenderSoft;
			}

			initPreHeap(elements);
			b_frames[i].addNode("1bnodes" + std::to_string(0), b_nodes[0]);
			w_frames[i].addNode("1wnodes" + std::to_string(0), w_nodes[0]);
		}
		return;
	}
	b_nodes[0].setRadius(0);
	w_nodes[0].setRadius(0);
	b_nodes[0].setCharacterSize(0);
	w_nodes[0].setCharacterSize(0);

	// move the last node
	preFrames += 60;
	if (preFrames > currentFrameIndex) {
		for (int i = 0; i < 60; i++)
		{
			codePanelColor[i][4] = sf::Color::Red;
			if (i == 59) {
				codePanelColor[i][4] = LavenderSoft;
			}
			initPreHeap(elements);
			if (i == 0) {
				b_nodes[heap.Size()].setTextUnder("");
				w_nodes[heap.Size()].setTextUnder("");
				b_frames[i].addNode("1bnodes" + std::to_string(heap.Size()), b_nodes[heap.Size()]);
				w_frames[i].addNode("1wnodes" + std::to_string(heap.Size()), w_nodes[heap.Size()]);
			}
		}
		deleteEdge(heap.Size(), 0, 59, 1);
		swapTwoNodes(heap.Size(), 0, 0, 59, 1);
		return;
	}
	std::swap(elements[heap.Size()], elements[0]);
	b_nodes[0].setRadius(RADIUS);
	w_nodes[0].setRadius(RADIUS);
	b_nodes[0].setCharacterSize(20);
	w_nodes[0].setCharacterSize(20);
	b_nodes[heap.Size()].setTextUnder("");
	w_nodes[heap.Size()].setTextUnder("");
	b_nodes[heap.Size()].setRadius(0);
	w_nodes[heap.Size()].setRadius(0);
	b_nodes[heap.Size()].setCharacterSize(0);
	w_nodes[heap.Size()].setCharacterSize(0);
	b_edges[heap.Size()].setThickness(0);
	w_edges[heap.Size()].setThickness(0);

	//heapify
	for (int h = 0; h < (int)deleteArrs[1].size() - 1; h += 2) {
		std::pair<int, int> cur = deleteArrs[1][h];
		std::pair<int, int> child = deleteArrs[1][h + 1];

		preFrames += 60;
		if (preFrames > currentFrameIndex) {
			for (int i = 0; i < 60; i++) {
				codePanelColor[i][5] = sf::Color::Red;
				if (i == 59 && h + 2 >= (int)deleteArrs[1].size() - 1) {
					codePanelColor[i][5] = LavenderSoft;
				}

				initPreHeap(elements);
			}
			swapTwoNodes(cur.first, child.first, 0, 59, 1);
			return;
		}
		std::swap(elements[cur.first], elements[child.first]);
	}

}

void HeapMainState::preInitExtractFrames()
{
	isSelectedCreateFrames = false;
	isSelectedInsertFrames = false;
	isSelectedDeleteFrames = false;
	isSelectedUpdateFrames = false;
	isSelectedExtractFrames = true;

	breakpoints.clear();
	heapElements = heap.getAllElements();
	extractArrs = heap.extractMin();
	initNode();
	initEdge();

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
	numFrames = 0;
	currentFrameIndex = 0;
	prevFrameIndex = 0;

	codePanel.setText("node[0] = node[size--]", 0);
	codePanel.setText("// heapify", 1);
	codePanel.setText("while(node[i] > node[minChild(i)])", 2);
	codePanel.setText("    swap(node[i], node[minChild(i)])", 3);
	codePanel.setText("    i = minChild(i)", 4);

	breakpoints.push_back(0);
	// delete the node
	numFrames += 60;
	breakpoints.push_back(numFrames);
	// move the last node
	numFrames += 60;
	breakpoints.push_back(numFrames);
	// heapify
	for (int h = 0; h < (int)extractArrs.size() - 1; h += 2) {
		numFrames += 60;
		breakpoints.push_back(numFrames);
	}

	aniSlider.setNumPart(numFrames);
	aniSlider.setPart(0);
	aniSlider.setBreakpoints(breakpoints);
	currentFrameIndex = 0;
	isPlaying = true;
	isPaused = false;
	isEnd = false;
}

void HeapMainState::initExtractFrames()
{
	deleteAllFrames();
	auto elements = heapElements;
	initNode(elements.size());
	initEdge(elements.size());

	int preFrames = 0;
	//delete the node 
	preFrames += 60;
	if (preFrames > currentFrameIndex) {
		for (int i = 0; i < 60; i++)
		{
			codePanelColor[i][0] = sf::Color::Red;
			b_nodes[0].setFillColor(sf::Color::Red);
			w_nodes[0].setFillColor(Orange);

			b_nodes[0].setRadius(static_cast<float>(RADIUS - RADIUS * static_cast<float>(i + 1) / 60));
			w_nodes[0].setRadius(static_cast<float>(RADIUS - RADIUS * static_cast<float>(i + 1) / 60));
			if (i == 59) {
				b_nodes[0].setCharacterSize(0);
				w_nodes[0].setCharacterSize(0);
				codePanelColor[i][0] = LavenderSoft;
			}

			initPreHeap(elements);
			b_frames[i].addNode("1bnodes" + std::to_string(0), b_nodes[0]);
			w_frames[i].addNode("1wnodes" + std::to_string(0), w_nodes[0]);
		}
		return;
	}
	b_nodes[0].setRadius(0);
	w_nodes[0].setRadius(0);
	b_nodes[0].setCharacterSize(0);
	w_nodes[0].setCharacterSize(0);

	// move the last node
	preFrames += 60;
	if (preFrames > currentFrameIndex) {
		for (int i = 0; i < 60; i++)
		{
			codePanelColor[i][0] = sf::Color::Red;
			if (i == 59) {
				codePanelColor[i][0] = LavenderSoft;
			}

			initPreHeap(elements);
			if (i == 0) {
				b_nodes[heap.Size()].setTextUnder("");
				w_nodes[heap.Size()].setTextUnder("");
				b_frames[i].addNode("1bnodes" + std::to_string(heap.Size()), b_nodes[heap.Size()]);
				w_frames[i].addNode("1wnodes" + std::to_string(heap.Size()), w_nodes[heap.Size()]);
			}
		}
		deleteEdge(heap.Size(), 0, 59, 1);
		swapTwoNodes(heap.Size(), 0, 0, 59, 1);
		return;
	}
	std::swap(elements[heap.Size()], elements[0]);
	b_nodes[0].setRadius(RADIUS);
	w_nodes[0].setRadius(RADIUS);
	b_nodes[0].setCharacterSize(20);
	w_nodes[0].setCharacterSize(20);
	b_nodes[heap.Size()].setTextUnder("");
	w_nodes[heap.Size()].setTextUnder("");
	b_nodes[heap.Size()].setRadius(0);
	w_nodes[heap.Size()].setRadius(0);
	b_nodes[heap.Size()].setCharacterSize(0);
	w_nodes[heap.Size()].setCharacterSize(0);
	b_edges[heap.Size()].setThickness(0);
	w_edges[heap.Size()].setThickness(0);

	//heapify
	for (int h = 0; h < (int)extractArrs.size() - 1; h += 2) {
		std::pair<int, int> cur = extractArrs[h];
		std::pair<int, int> child = extractArrs[h + 1];

		preFrames += 60;
		if (preFrames > currentFrameIndex) {
			for (int i = 0; i < 60; i++) {
				codePanelColor[i][2] = sf::Color::Red;
				codePanelColor[i][3] = sf::Color::Red;
				codePanelColor[i][4] = sf::Color::Red;
				if (i == 59 && h + 2 >= (int)extractArrs.size() - 1) {
					codePanelColor[i][2] = LavenderSoft;
					codePanelColor[i][3] = LavenderSoft;
					codePanelColor[i][4] = LavenderSoft;
				}

				initPreHeap(elements);
			}
			swapTwoNodes(cur.first, child.first, 0, 59, 1);
			return;
		}
		std::swap(elements[cur.first], elements[child.first]);
	}
}

void HeapMainState::updateFrames()
{
	if (numFrames == 0) return;
	if (numFrames > 0) currentFrameIndex = std::min(currentFrameIndex, numFrames - 1);
	if (currentFrameIndex == 0 || aniSlider.getBreakpoints(prevFrameIndex) != aniSlider.getBreakpoints(currentFrameIndex)) {
		if (isSelectedCreateFrames) {
			initCreateFrames();
		}
		if (isSelectedInsertFrames) {
			initInsertFrames(insertValue);
		}
		if (isSelectedDeleteFrames) {
			initDeleteFrames(deleteId);
		}
		if (isSelectedExtractFrames) {
			initExtractFrames();
		}
		if (isSelectedUpdateFrames) {
			initUpdateFrames(updateId, updateValue);
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
				setCodePanelColor(59);
				if (*m_context->themeType == 0)
					currentFrame = b_frames.back();
				else
					currentFrame = w_frames.back();

			}
		}
	}
}