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
		sf::Vector2f pos;
		if (index % 2 == 1) {
			pos.x = start.x + abs(end.x - start.x) / (index2 - index1 + 1) * (i - index1);
		}
		else {
			pos.x = start.x - abs(end.x - start.x) / (index2 - index1 + 1) * (i - index1);
		}
		pos.y = start.y - abs(pos.x - start.x) * _tan;

		sf::Vector2f posEndEdge;
		if (index % 2 == 1) {
			posEndEdge.x = start.x + abs(end.x - start.x) / (index2 - index1 + 1) * (i - index1 + 1);
		}
		else {
			posEndEdge.x = start.x - abs(end.x - start.x) / (index2 - index1 + 1) * (i - index1 + 1);
		}
		posEndEdge.y = start.y - abs(posEndEdge.x - start.x) * _tan;

		b_edges[index].setStart(start);
		w_edges[index].setStart(start);
		b_edges[index].setEnd(posEndEdge);
		w_edges[index].setEnd(posEndEdge);

		b_nodes[index].setFillColor(sf::Color::Red);
		w_nodes[index].setFillColor(Orange);
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

void HeapMainState::swapTwoNodes(int index, int index1, int index2, bool isEnd)
{
	int par = heap.parent(index);
	sf::Vector2f start, end;
	start = b_nodes[index].getPosition();
	end = b_nodes[par].getPosition();

	for (int i = index1; i <= index2; i++) {
		sf::Vector2f childPos, parPos;
		if (index % 2 == 1) {
			childPos = sf::Vector2f(start.x + abs(end.x - start.x) / (index2 - index1 + 1) * (i - index1 + 1), start.y - abs(end.y - start.y) / (index2 - index1) * (i - index1 + 1));
			parPos = sf::Vector2f(end.x - abs(end.x - start.x) / (index2 - index1 + 1) * (i - index1 + 1), end.y + abs(end.y - start.y) / (index2 - index1) * (i - index1 + 1));
		}
		else {
			childPos = sf::Vector2f(start.x - abs(end.x - start.x) / (index2 - index1 + 1) * (i - index1 + 1), start.y - abs(end.y - start.y) / (index2 - index1) * (i - index1 + 1));
			parPos = sf::Vector2f(end.x + abs(end.x - start.x) / (index2 - index1 + 1) * (i - index1 + 1), end.y + abs(end.y - start.y) / (index2 - index1) * (i - index1 + 1));
		}
		b_nodes[index].setPosition(childPos);
		w_nodes[index].setPosition(childPos);
		b_nodes[par].setPosition(parPos);
		w_nodes[par].setPosition(parPos);
		b_nodes[index].setFillColor(sf::Color::Red);
		w_nodes[index].setFillColor(Orange);
		b_nodes[par].setTextColor(sf::Color::Red);
		w_nodes[par].setTextColor(Orange);
		if (i == index2 && isEnd) {
			b_nodes[index].setFillColor(sf::Color::White);
			w_nodes[index].setFillColor(sf::Color::White);
			b_nodes[par].setTextColor(sf::Color::Black);
			w_nodes[par].setTextColor(sf::Color::Black);
		}

		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
		w_frames[i].addNode("1wnodes" + std::to_string(index), w_nodes[index]);
		b_frames[i].addNode("1bnodes" + std::to_string(par), b_nodes[par]);
		w_frames[i].addNode("1wnodes" + std::to_string(par), w_nodes[par]);
	}

	auto tmp = b_nodes[index];
	tmp.setPosition(b_nodes[index].getPosition());
	tmp.setString(b_nodes[index].getString());
	b_nodes[index].setPosition(b_nodes[par].getPosition());
	b_nodes[index].setString(b_nodes[par].getString());
	b_nodes[par].setPosition(tmp.getPosition());
	b_nodes[par].setString(tmp.getString());

	tmp = w_nodes[index];
	tmp.setPosition(w_nodes[index].getPosition());
	tmp.setString(w_nodes[index].getString());
	w_nodes[index].setPosition(w_nodes[par].getPosition());
	w_nodes[index].setString(w_nodes[par].getString());
	w_nodes[par].setPosition(tmp.getPosition());
	w_nodes[par].setString(tmp.getString());
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

void HeapMainState::initRandomFrames(std::vector<int> elements)
{
	int timeRepeat = 0;
	deleteAllFrames();
	heap.removeAll();

	for (int x : elements)
		heap.insertKey(x);

	codePanel.setText("for x in elements", 0);
	codePanel.setText("    insert(x)", 1);
	codePanel.setText("return", 2);

	std::vector<int> allElements;
	std::cerr << "NumElements: " << elements.size() << std::endl;
	allElements = heap.getAllElements();
	initNode();
	initEdge();
	breakpoints.push_back(0);


	for (int i = 0;i < 60;i++)
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
	breakpoints.push_back(b_frames.size());

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

		//moveNodeEdge(i, firstIndex, lastIndex, sf::Vector2f(PADDING_X + (i - 1) * DISTANCE_X, 400), sf::Vector2f(PADDING_X + i * DISTANCE_X, 400));
		breakpoints.push_back(b_frames.size() - 1);
	}
	aniSlider.setNumPart(b_frames.size());
	aniSlider.setBreakpoints(breakpoints);
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = b_frames.size();
	std::cerr << "NumFrames: " << numFrames << std::endl;
	currentFrameIndex = 0;

}


void HeapMainState::initInsertFrames(int value)
{
	std::vector<int> allElements = heap.getAllElements();
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;

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

	initNode();
	initEdge();

	int firstIndex = static_cast<int>(b_frames.size());
	int lastIndex = firstIndex + 60 - 1;

	int id = heap.Size();
	std::vector<std::pair<int, int>> pars = heap.insertKey(value);
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
		swapTwoNodes(id, firstIndex, lastIndex, 1);
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

void HeapMainState::updateFrames()
{
	numFrames = b_frames.size();
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
					currentFrameIndex++;


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


