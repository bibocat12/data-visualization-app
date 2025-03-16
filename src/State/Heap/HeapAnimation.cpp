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


void HeapMainState::changeBColor(int index, int index1, int index2, sf::Color from, sf::Color to)
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

void HeapMainState::changeWColor(int index, int index1, int index2, sf::Color from, sf::Color to)
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

void HeapMainState::deleteAllFrames()
{
	b_frames.clear();
	w_frames.clear();
	breakpoints.clear();
	numFrames = 0;
	currentFrameIndex = 0;
	isPlaying = false;
}

void HeapMainState::initCreateFrames(std::vector<int> elements)
{
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	auto arrs = heap.create(elements);
	initNode();
	initEdge();

	codePanel.setText("current = head", 0);
	codePanel.setText("while k > 0", 1);
	codePanel.setText("    current = current->next", 2);
	codePanel.setText("    k--", 3);
	codePanel.setText("insert v after current", 4);

	breakpoints.push_back(0);
	int firstIndex = static_cast<int>(b_frames.size());
	int lastIndex = firstIndex + 60 - 1;
	for (int i = 0; i < 60; i++)
	{
		Engine::Frame b_frame, w_frame;
		for (int j = 0; j < (int)arrs[0].size(); j++) {
			b_nodes[j].setString(std::to_string(arrs[0][j].second));
			w_nodes[j].setString(std::to_string(arrs[0][j].second));
			b_nodes[j].setRadius(RADIUS * static_cast<float>(i + 1) / 60);
			w_nodes[j].setRadius(RADIUS * static_cast<float>(i + 1) / 60);
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
			b_frame.addNode("1bnodes" + std::to_string(arrs[0][j].first), b_nodes[j]);
			w_frame.addNode("1wnodes" + std::to_string(arrs[0][j].first), w_nodes[j]);
			b_frame.addEdge("2bedges" + std::to_string(arrs[0][j].first), b_edges[j]);
			w_frame.addEdge("2wedges" + std::to_string(arrs[0][j].first), w_edges[j]);
		}
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	for (int i = 1; i < (int)arrs[0].size(); i++)
		connectTwoNodes(i, firstIndex, lastIndex, 1);

	breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);
	
	//Heapify
	std::vector<std::pair<int, int>> prev;
	for (int i = 1; i < (int)arrs.size(); i++) {
		for (int j = 0; j < (int)arrs[i].size() - 1; j += 2) {
			std::pair<int, int> cur = arrs[i][j];
			std::pair<int, int> child = arrs[i][j + 1];
			int firstIndex = static_cast<int>(b_frames.size());
			int lastIndex = firstIndex + 60 - 1;
			b_nodes[cur.first].setString(std::to_string(cur.second));
			w_nodes[cur.first].setString(std::to_string(cur.second));
			b_nodes[child.first].setString(std::to_string(child.second));
			w_nodes[child.first].setString(std::to_string(child.second));

			for (int i = 0; i < 60; i++)
			{
				Engine::Frame b_frame, w_frame;

				codePanel.setLineColor(1, LavenderSoft);
				codePanel.setLineColor(2, LavenderSoft);

				b_frame.init(b_frames[b_frames.size() - 1]);
				w_frame.init(w_frames[w_frames.size() - 1]);
				b_frame.addPanel("3bcodePanel", codePanel);
				w_frame.addPanel("3wcodePanel", codePanel);
				for(auto x:prev) {
					b_frame.addNode("1bnodes" + std::to_string(x.first), b_nodes[x.first]);
					w_frame.addNode("1wnodes" + std::to_string(x.first), w_nodes[x.first]);
				}

				b_frames.push_back(b_frame);
				w_frames.push_back(w_frame);
			}
			swapTwoNodes(cur.first, child.first, firstIndex, lastIndex, 1);
			breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);
			prev.push_back(cur);
			prev.push_back(child);
		}
	}

	//end
	aniSlider.setNumPart(static_cast<int>(b_frames.size()));
	aniSlider.setBreakpoints(breakpoints);
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = static_cast<int>(b_frames.size());
	currentFrameIndex = 0;
}


void HeapMainState::initInsertFrames(int value)
{
	std::vector<int> allElements = heap.getAllElements();
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	std::vector<std::pair<int, int>> pars = heap.insertKey(value);
	initNode();
	initEdge();

	for (int i = 0; i < (int)allElements.size(); i++)
	{
		b_nodes[i].setString(std::to_string(allElements[i]));
		w_nodes[i].setString(std::to_string(allElements[i]));
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		b_frame.addEdge("2bedges" + std::to_string(i), b_edges[i]);
		w_frame.addEdge("2wedges" + std::to_string(i), w_edges[i]);
	}
	
	codePanel.setText("current = head", 0);
	codePanel.setText("while k > 0", 1);
	codePanel.setText("    current = current->next", 2);
	codePanel.setText("    k--", 3);
	codePanel.setText("insert v after current", 4);

	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);


	for (int i = 0; i < 60; i++)
	{
		Engine::Frame b_frame, w_frame;
		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());
		codePanel.setLineColor(1, sf::Color::Red);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}

	int firstIndex = static_cast<int>(b_frames.size());
	int lastIndex = firstIndex + 60 - 1;

	int id = heap.Size() - 1;
	//add new node
	b_nodes[id].setString(std::to_string(value));
	w_nodes[id].setString(std::to_string(value));
	for (int i = 0; i < 60; i++)
	{
		Engine::Frame b_frame, w_frame;
		
		codePanel.setLineColor(1, LavenderSoft);
		codePanel.setLineColor(2, LavenderSoft);
		if (id == 0) {
			b_nodes[id].setFillColor(sf::Color::Red);
			w_nodes[id].setFillColor(Orange);
			if (i == 59) {
				b_nodes[id].setFillColor(sf::Color::White);
				w_nodes[id].setFillColor(sf::Color::White);
			}
		}

		b_frame.init(b_frames[b_frames.size() - 1]);
		w_frame.init(w_frames[w_frames.size() - 1]);
		b_frame.addNode("1bnodes" + std::to_string(id), b_nodes[id]);
		w_frame.addNode("1wnodes" + std::to_string(id), w_nodes[id]);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);

		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	if (id) {
		connectTwoNodes(id, firstIndex, lastIndex, (int) pars.size() == 1);
	}
	breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);

	//swap nodes
	for (int h = 1; h < (int) pars.size(); h++) {
		std::pair<int, int> par = pars[h];
		int firstIndex = static_cast<int>(b_frames.size());
		int lastIndex = firstIndex + 60 - 1;
		b_nodes[par.first].setString(std::to_string(par.second));
		w_nodes[par.first].setString(std::to_string(par.second));
		for (int i = 0; i < 60; i++)
		{
			Engine::Frame b_frame, w_frame;

			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(2, LavenderSoft);

			b_frame.init(b_frames[b_frames.size() - 1]);
			w_frame.init(w_frames[w_frames.size() - 1]);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);
			for (int pre_h = 0; pre_h < h - 1; pre_h++) {
				b_frame.addNode("1bnodes" + std::to_string(pars[pre_h].first), b_nodes[pars[pre_h].first]);
				w_frame.addNode("1wnodes" + std::to_string(pars[pre_h].first), w_nodes[pars[pre_h].first]);
			}

			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		swapTwoNodes(id, heap.parent(id), firstIndex, lastIndex, 1);
		breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);
		id = par.first;
	}
	
	aniSlider.setNumPart(static_cast<int>(b_frames.size()));
	aniSlider.setBreakpoints(breakpoints);
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = static_cast<int>(b_frames.size());
	currentFrameIndex = 0;
}

void HeapMainState::initUpdateFrames(int id, int newV)
{
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	std::vector<int> allElements = heap.getAllElements();
	bool isLess = heap.isLessThanParent(id, newV);
	auto arrs = heap.update(id, newV);
	initNode();
	initEdge();

	for (int i = 0; i < (int)allElements.size(); i++)
	{
		b_nodes[i].setString(std::to_string(allElements[i]));
		w_nodes[i].setString(std::to_string(allElements[i]));
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		b_frame.addEdge("2bedges" + std::to_string(i), b_edges[i]);
		w_frame.addEdge("2wedges" + std::to_string(i), w_edges[i]);
	}

	codePanel.setText("current = head", 0);
	codePanel.setText("while k > 0", 1);
	codePanel.setText("    current = current->next", 2);
	codePanel.setText("    k--", 3);
	codePanel.setText("insert v after current", 4);

	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);


	for (int i = 0; i < 60; i++)
	{
		Engine::Frame b_frame, w_frame;
		b_frame.init(b_frames.back());
		w_frame.init(w_frames.back());
		codePanel.setLineColor(1, sf::Color::Red);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}

	//Change node 
	for (int i = 0; i < 60; i++)
	{
		Engine::Frame b_frame, w_frame;

		codePanel.setLineColor(1, LavenderSoft);
		codePanel.setLineColor(2, LavenderSoft);
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
			}
			b_nodes[id].setRadius(static_cast<float>(RADIUS * static_cast<float>(i - 29) / 30));
			w_nodes[id].setRadius(static_cast<float>(RADIUS * static_cast<float>(i - 29) / 30));
			if (i == 59 && (int)arrs.size() == 1) {
				b_nodes[id].setFillColor(sf::Color::White);
				w_nodes[id].setFillColor(sf::Color::White);
			}
		}

		b_frame.init(b_frames[b_frames.size() - 1]);
		w_frame.init(w_frames[w_frames.size() - 1]);
		b_frame.addNode("1bnodes" + std::to_string(id), b_nodes[id]);
		w_frame.addNode("1wnodes" + std::to_string(id), w_nodes[id]);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);

		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);

	/*b_frame.addNode("1bnodes" + std::to_string(id), b_nodes[id]);
	w_frame.addNode("1wnodes" + std::to_string(id), w_nodes[id]);
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);*/

	//swap
	std::vector<std::pair<int, int>> prev;
	std::pair<int, int> cur, child;
	for (int i = 0; i < (int)arrs.size() - 1; i = i + 1 + (!isLess)) {
		int firstIndex = static_cast<int>(b_frames.size());
		int lastIndex = firstIndex + 60 - 1;

		cur = arrs[i];
		if (!isLess) {
			b_nodes[cur.first].setString(std::to_string(cur.second));
			w_nodes[cur.first].setString(std::to_string(cur.second));
			child = arrs[i + 1];
			b_nodes[child.first].setString(std::to_string(child.second));
			w_nodes[child.first].setString(std::to_string(child.second));
		}
		else {
			if (i + 1 < arrs.size()) {
				std::pair<int, int> par = arrs[i + 1];
				b_nodes[par.first].setString(std::to_string(par.second));
				w_nodes[par.first].setString(std::to_string(par.second));
			}
			prev.push_back(cur);
		}

		for (int i = 0; i < 60; i++)
		{
			Engine::Frame b_frame, w_frame;

			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(2, LavenderSoft);

			b_frame.init(b_frames[b_frames.size() - 1]);
			w_frame.init(w_frames[w_frames.size() - 1]);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);
			for (auto x : prev) {
				b_frame.addNode("1bnodes" + std::to_string(x.first), b_nodes[x.first]);
				w_frame.addNode("1wnodes" + std::to_string(x.first), w_nodes[x.first]);
			}

			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		if (isLess) {
			swapTwoNodes(cur.first, heap.parent(cur.first), firstIndex, lastIndex, 1);
		}
		else {
			swapTwoNodes(cur.first, child.first, firstIndex, lastIndex, 1);
			prev.push_back(cur);
			prev.push_back(child);
		}
		breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);
	}


	//end
	aniSlider.setNumPart(static_cast<int>(b_frames.size()));
	aniSlider.setBreakpoints(breakpoints);
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = static_cast<int>(b_frames.size());
	currentFrameIndex = 0;
}

void HeapMainState::initDeleteFrames(int id)
{
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;
	std::vector<int> allElements = heap.getAllElements();
	initNode();
	initEdge();
	auto arrs = heap.deleteKey(id);

	for (int i = 0; i < (int)allElements.size(); i++)
	{
		b_nodes[i].setString(std::to_string(allElements[i]));
		w_nodes[i].setString(std::to_string(allElements[i]));
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		b_frame.addEdge("2bedges" + std::to_string(i), b_edges[i]);
		w_frame.addEdge("2wedges" + std::to_string(i), w_edges[i]);
	}

	codePanel.setText("current = head", 0);
	codePanel.setText("while k > 0", 1);
	codePanel.setText("    current = current->next", 2);
	codePanel.setText("    k--", 3);
	codePanel.setText("insert v after current", 4);

	b_frame.addPanel("3bcodePanel", codePanel);
	w_frame.addPanel("3wcodePanel", codePanel);
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);

	// move the delete node to the root
	for (int h = 1; h < (int)arrs[0].size(); h++) {
		std::pair<int, int> child = arrs[0][h - 1];
		std::pair<int, int> par = arrs[0][h];
		int firstIndex = static_cast<int>(b_frames.size());
		int lastIndex = firstIndex + 60 - 1;
		b_nodes[par.first].setString(std::to_string(par.second));
		w_nodes[par.first].setString(std::to_string(par.second));
		for (int i = 0; i < 60; i++)
		{
			Engine::Frame b_frame, w_frame;

			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(2, LavenderSoft);

			b_frame.init(b_frames[b_frames.size() - 1]);
			w_frame.init(w_frames[w_frames.size() - 1]);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);
			for (int pre_h = 0; pre_h < h - 1; pre_h++) {
				b_frame.addNode("1bnodes" + std::to_string(arrs[0][pre_h].first), b_nodes[arrs[0][pre_h].first]);
				w_frame.addNode("1wnodes" + std::to_string(arrs[0][pre_h].first), w_nodes[arrs[0][pre_h].first]);
			}

			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		swapTwoNodes(child.first, par.first, firstIndex, lastIndex, 1);
		breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);
	}

	for (int i = 0; i < (int) arrs[0].size(); i++) {
		b_frame.addNode("1bnodes" + std::to_string(arrs[0][i].first), b_nodes[arrs[0][i].first]);
		w_frame.addNode("1wnodes" + std::to_string(arrs[0][i].first), w_nodes[arrs[0][i].first]);
	}
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);

	//delete the node 
	for (int i = 0; i < 60; i++)
	{
		Engine::Frame b_frame, w_frame;
		codePanel.setLineColor(1, LavenderSoft);
		codePanel.setLineColor(2, LavenderSoft);
		b_nodes[0].setFillColor(sf::Color::Red);
		w_nodes[0].setFillColor(Orange);
	
		b_nodes[0].setRadius(static_cast<float>(RADIUS - RADIUS * static_cast<float>(i + 1) / 60));
		w_nodes[0].setRadius(static_cast<float>(RADIUS - RADIUS * static_cast<float>(i + 1) / 60));
		if (i == 59) {
			b_nodes[0].setCharacterSize(0);
			w_nodes[0].setCharacterSize(0);
		}

		b_frame.init(b_frames[b_frames.size() - 1]);
		w_frame.init(w_frames[w_frames.size() - 1]);
		b_frame.addNode("1bnodes" + std::to_string(0), b_nodes[0]);
		w_frame.addNode("1wnodes" + std::to_string(0), w_nodes[0]);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);

		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);

	// move the last node
	int firstIndex = static_cast<int>(b_frames.size());
	int lastIndex = firstIndex + 60 - 1;
	for (int i = 0; i < 60; i++)
	{
		Engine::Frame b_frame, w_frame;

		codePanel.setLineColor(1, LavenderSoft);
		codePanel.setLineColor(2, LavenderSoft);

		b_frame.init(b_frames[b_frames.size() - 1]);
		w_frame.init(w_frames[w_frames.size() - 1]);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);

		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	deleteEdge(heap.Size(), firstIndex, lastIndex, 1);
	swapTwoNodes(heap.Size(), 0, firstIndex, lastIndex, 1);
	breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);
	b_nodes[heap.Size()].setRadius(0);
	w_nodes[heap.Size()].setRadius(0);
	b_nodes[heap.Size()].setCharacterSize(0);
	w_nodes[heap.Size()].setCharacterSize(0);

	//heapify
	if ((int)arrs[1].size() > 1) {
		b_nodes[0].setFillColor(sf::Color::Red);
		w_nodes[0].setFillColor(Orange);
		b_nodes[0].setRadius(RADIUS);
		w_nodes[0].setRadius(RADIUS);
		b_nodes[0].setCharacterSize(20);
		w_nodes[0].setCharacterSize(20);
		b_frame.addNode("1bnodes" + std::to_string(0), b_nodes[0]);
		w_frame.addNode("1wnodes" + std::to_string(0), w_nodes[0]);
		b_frame.addNode("1bnodes" + std::to_string(heap.Size()), b_nodes[heap.Size()]);
		w_frame.addNode("1wnodes" + std::to_string(heap.Size()), w_nodes[heap.Size()]);
		b_frame.addEdge("2bedges" + std::to_string(heap.Size()), b_edges[heap.Size()]);
		w_frame.addEdge("2wedges" + std::to_string(heap.Size()), w_edges[heap.Size()]);
		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}

	std::vector<std::pair<int, int>> prev;
	for (int h = 0; h < (int)arrs[1].size() - 1; h += 2) {
		std::pair<int, int> cur = arrs[1][h];
		std::pair<int, int> child = arrs[1][h + 1];
		int firstIndex = static_cast<int>(b_frames.size());
		int lastIndex = firstIndex + 60 - 1;
		b_nodes[cur.first].setString(std::to_string(cur.second));
		w_nodes[cur.first].setString(std::to_string(cur.second));
		b_nodes[child.first].setString(std::to_string(child.second));
		w_nodes[child.first].setString(std::to_string(child.second));

		for (int i = 0; i < 60; i++)
		{
			Engine::Frame b_frame, w_frame;

			codePanel.setLineColor(1, LavenderSoft);
			codePanel.setLineColor(2, LavenderSoft);

			b_frame.init(b_frames[b_frames.size() - 1]);
			w_frame.init(w_frames[w_frames.size() - 1]);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);
			for (auto x : prev) {
				b_frame.addNode("1bnodes" + std::to_string(x.first), b_nodes[x.first]);
				w_frame.addNode("1wnodes" + std::to_string(x.first), w_nodes[x.first]);
			}

			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}
		swapTwoNodes(cur.first, child.first, firstIndex, lastIndex, 1);
		breakpoints.push_back(static_cast<int>(b_frames.size()) - 1);
		prev.push_back(cur);
		prev.push_back(child);
	}

	// end
	aniSlider.setNumPart(static_cast<int>(b_frames.size()));
	aniSlider.setBreakpoints(breakpoints);
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = static_cast<int>(b_frames.size());
	currentFrameIndex = 0;
}

void HeapMainState::updateFrames()
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


