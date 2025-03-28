#include "TrieMainState.h"

void TrieMainState::deleteAllFrames()
{
	b_frames.clear();
	w_frames.clear();
	breakpoints.clear();
	snapshots.clear();
}

void TrieMainState::initNode(Trie::TrieSnapshot& snapshot)
{
	std::vector<Trie::TrieNodeInfo> nodes = snapshot.nodesInfo;
	for (int i = 0; i < nodes.size(); i++)
	{
		int depth = nodes[i].depth;
		int orderDisplay = nodes[i].orderDisplay;
		int order = nodes[i].order;
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
			b_nodes[i].setTextUnder("1", 10, sf::Color::Red);

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
			w_nodes[i].setTextUnder("1", 10, sf::Color::Red);
	
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
			sf::Vector2f start;
			start.x = PADDING_X + nodes[parentOrder].orderDisplay * (DISTANCE_X);
			start.y = PADDING_Y + (depth - 1) * (DISTANCE_Y);
			sf::Vector2f end;
			end.x = PADDING_X + orderDisplay * (DISTANCE_X);
			end.y = PADDING_Y + depth * (DISTANCE_Y);
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


void TrieMainState::initCreateFrames(std::vector<std::string> words)
{
	// Clear all frames
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


void TrieMainState::updateFrames()
{
	if (numFrames == 0) return;
	if (numFrames > 0) currentFrameIndex = std::min(currentFrameIndex, numFrames - 1);
	if (currentFrameIndex == 0 || aniSlider.getBreakpoints(prevFrameIndex) != aniSlider.getBreakpoints(currentFrameIndex)) {
		//if (currentState == "inorder") {
		//	initInorderFrames();
		//}
		//if (currentState == "insert")
		//{
		//	initInsertFrames();
		//}
		//if (currentState == "delete")
		//{
		//	initDeleteFrames(deleteValue);
		//}
		//if (currentState == "search")
		//{
		//	initSearchFrames();
		//	std::cerr << currentFrameIndex << std::endl;
		//}

	}

	prevFrameIndex = currentFrameIndex;
	if (isPlaying)
	{

		if (numFrames > 0)
		{
			if (currentFrameIndex < numFrames - 1)
			{
				isEnd = false;
				if (currentState == "inorder" || currentState == "insert" || currentState == "delete" || currentState == "search")
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