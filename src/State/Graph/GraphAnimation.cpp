#include "GraphMainState.h"

void GraphMainState::deleteAllFrames() {
	frames.clear();
	breakpoints.clear();
	numFrames = 0;
	currentFrameIndex = 0;
	isPlaying = false;
	Engine::Frame frame;
	currentFrame = frame;
	aniSlider.setNumPart(0);
	aniSlider.setBreakpoints(breakpoints);
	aniSlider.setPart(0);

	for (int i = 0; i < 7; i++) {
		codePanel.setLineColor(i, LavenderSoft);
		codePanel.setText("", i);
	}
}

void GraphMainState::selectEdge(int edgeIndex, bool isSelected, int index1, int index2)
{
	int u = fGraph.edges[edgeIndex].from;
	int v = fGraph.edges[edgeIndex].to;
	fGraph.nodes[u].node.setFillColor(Orange);
	fGraph.nodes[v].node.setFillColor(Orange);

	for (int i = index1; i <= index2; i++) {
		if (((i - index1 + 1) / 10) == 6) {
			if (isSelected) {
				fGraph.edges[edgeIndex].edge.setColor(Orange);
			}
			else {
				fGraph.edges[edgeIndex].edge.setColor(textColor);
			}
		}
		else if (((i - index1 + 1) / 10) % 2 == 1) {
			fGraph.edges[edgeIndex].edge.setColor(textColor);
		}
		else if (((i - index1 + 1) / 10) % 2 == 0) {
			fGraph.edges[edgeIndex].edge.setColor(Orange);
		}

		frames[i].addNode("1nodes" + std::to_string(u), fGraph.nodes[u].node);
		frames[i].addNode("1nodes" + std::to_string(v), fGraph.nodes[v].node);
		frames[i].addEdge("2edges" + std::to_string(edgeIndex), fGraph.edges[edgeIndex].edge);
	}
}

void GraphMainState::initMstFrames()
{
	deleteAllFrames();
	Engine::Frame frame;
	auto arrs = graph.kruskal();

	codePanel.setText("sort edges by increasing weight", 0);
	codePanel.setText("for ([u, v, w]:edges)", 1);
	codePanel.setText("if (dsu.sameSet(u, v) == false)", 2);
	codePanel.setText("    dsu.Union(u, v) // add the edge to MST", 3);
	codePanel.setText("else continue", 4);
	
	breakpoints.push_back(0);

	for (int i = 0; i < (int) fGraph.nodes.size(); i++)
	{
		frame.addNode("1nodes" + std::to_string(i), fGraph.nodes[i].node);
	}
	for (int i = 0; i < (int)fGraph.edges.size(); i++) {
		frame.addEdge("2edges" + std::to_string(i), fGraph.edges[i].edge);
	}
	codePanel.setLineColor(0, sf::Color::Red);
	frame.addPanel("3codePanel", codePanel);
	frames.push_back(frame);
	codePanel.setLineColor(0, LavenderSoft);
	
	for (int k = 0; k < (int) arrs.size();k++) {
		int firstIndex = static_cast<int>(frames.size());
		int lastIndex = firstIndex + 60 - 1;

		auto edge = fGraph.edges[arrs[k].first];
		for (int i = 0; i < 60; i++) {
			frame.init(frames[frames.size() - 1]);
			if (i < 20) {
				codePanel.setLineColor(2, sf::Color::Red);
				if (i == 19) {
					codePanel.setLineColor(2, LavenderSoft);
				}
			}
			else {
				if (arrs[k].second) {
					codePanel.setLineColor(3, sf::Color::Red);
					if (i == 59) {
						codePanel.setLineColor(3, LavenderSoft);
					}
				}
				else {
					codePanel.setLineColor(4, sf::Color::Red);
					if (i == 59) {
						codePanel.setLineColor(4, LavenderSoft);
					}
				}
			}
			frame.addPanel("3codePanel", codePanel);
			frames.push_back(frame);
		}

		selectEdge(arrs[k].first, arrs[k].second, firstIndex, lastIndex);
		breakpoints.push_back((int)frames.size());
	}
	
	aniSlider.setNumPart(static_cast<int>(frames.size()));
	aniSlider.setBreakpoints(breakpoints);
	isPlaying = true;
	isPaused = false;
	isEnd = false;
	numFrames = static_cast<int>(frames.size());
	currentFrameIndex = 0;
}

void GraphMainState::updateFrames()
{
	numFrames = frames.size();
	speed = speedSlider.getPartIndex() + 1;
	if (isPlaying)
	{

		if (numFrames > 0)
		{
			//std::cerr << currentFrameIndex << std::endl;
			if (currentFrameIndex < numFrames - 1)
			{
				isEnd = false;
				currentFrame = frames[currentFrameIndex];
				if (isPaused == false)
					currentFrameIndex += speed;
			}
			else
			{
				isEnd = true;
				isPaused = true;
				currentFrameIndex = numFrames - 1;
				aniSlider.setPart(currentFrameIndex + 1);
				currentFrame = frames.back();

			}
		}
	}
}

