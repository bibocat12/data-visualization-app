#include "GraphMainState.h"

void GraphMainState::initPreGraph()
{
    Engine::Frame frame;
    for (int i = 0; i < (int)fGraph.numNodes; i++)
    {
        frame.addNode("1nodes" + std::to_string(i), fGraph.nodes[i].node);
    }
    for (int i = 0; i < (int)fGraph.numEdges; i++) {
        frame.addEdge("2edges" + std::to_string(i), fGraph.edges[i].edge);
    }
    frames.push_back(std::move(frame));

}

void GraphMainState::deleteAllFrames() {
    frames.clear();
    for (int i = 0; i < 7; i++) {
        codePanel.setLineColor(i, LavenderSoft);
    }
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 7; j++) {
            codePanelColor[i][j] = LavenderSoft;
        }
    }
}

void GraphMainState::selectEdge(int edgeIndex, bool isSelected, int index1, int index2)
{
    int u = fGraph.edges[edgeIndex].from;
    int v = fGraph.edges[edgeIndex].to;
    fGraph.nodes[u].node.setFillColor(Orange);
    fGraph.nodes[v].node.setFillColor(Orange);

    for (int i = index1; i <= index2; i++) {
        if (((i - index1 + 1) / 20) == 3) {
            if (isSelected) {
                fGraph.edges[edgeIndex].edge.setColor(Orange);
            }
            else {
                fGraph.edges[edgeIndex].edge.setColor(textColor);
            }
        }
        else if (((i - index1 + 1) / 20) % 2 == 1) {
            fGraph.edges[edgeIndex].edge.setColor(textColor);
        }
        else if (((i - index1 + 1) / 20) % 2 == 0) {
            fGraph.edges[edgeIndex].edge.setColor(Orange);
        }

        frames[i].addNode("1nodes" + std::to_string(u), fGraph.nodes[u].node);
        frames[i].addNode("1nodes" + std::to_string(v), fGraph.nodes[v].node);
        frames[i].addEdge("2edges" + std::to_string(edgeIndex), fGraph.edges[edgeIndex].edge);
    }
}

void GraphMainState::moveTo(int from, int edgeIndex, int index1, int index2)
{
    sf::Vector2f start = fGraph.edges[edgeIndex].edge.getStart();
    sf::Vector2f end = fGraph.edges[edgeIndex].edge.getEnd();
    if (fGraph.edges[edgeIndex].from == from) {
        std::swap(start, end);
    }
    tmpEdge.setColor(Orange);
    tmpEdge.setDirected(false);
    tmpEdge.setThickness(3.5f);
    for (int i = index1; i <= index2; i++) {
        float t = static_cast<float> (i - index1 + 1) / (index2 - index1);
        tmpEdge.setStart(start);
        tmpEdge.setEnd(start + t * (end - start));
        if (i < index2) frames[i].addEdge("9tmpedges999", tmpEdge);
        else {
            int from = fGraph.edges[edgeIndex].from;
            int to = fGraph.edges[edgeIndex].to;
            fGraph.nodes[from].node.setFillColor(Orange);
            fGraph.nodes[to].node.setFillColor(Orange);
            frames[i].addNode("1nodes" + std::to_string(from), fGraph.nodes[from].node);
            frames[i].addNode("1nodes" + std::to_string(to), fGraph.nodes[to].node);
            frames[i].addEdge("2edges" + std::to_string(edgeIndex), fGraph.edges[edgeIndex].edge);
        }
    }
}

void GraphMainState::preInitMstFrames()
{
    isSelectedMstFrames = true;
    isSelectedShortestPathFrames = false;

    for (auto& node : fGraph.nodes) {
        node.node.setTextUnder("");
    }
    breakpoints.clear();
    mstArrs = graph.kruskal();
    for (int i = 0; i < 7; i++) {
        codePanel.setLineColor(i, LavenderSoft);
        codePanel.setText("", i);
    }
    numFrames = 0;
    currentFrameIndex = 0;
    prevFrameIndex = 0;

    codePanel.setText("sort edges by increasing weight", 0);
    codePanel.setText("for ([u, v, w]:edges)", 1);
    codePanel.setText("if (dsu.sameSet(u, v) == false)", 2);
    codePanel.setText("    dsu.Union(u, v) // add the edge to MST", 3);
    codePanel.setText("else continue", 4);

    // calculate number of frames
    breakpoints.push_back(0);
    for (int k = 0; k < (int)mstArrs.size(); k++) {
        numFrames += 60;
        breakpoints.push_back(numFrames);
    }

    aniSlider.setNumPart(numFrames);
    aniSlider.setBreakpoints(breakpoints);
    aniSlider.setPart(0);
    currentFrameIndex = 0;
    isPlaying = true;
    isPaused = false;
    isEnd = false;
}

void GraphMainState::initMstFrames()
{
    deleteAllFrames();
    fGraph.setColor(textColor, true);
    int preFrames = 0;
    for (int k = 0; k < (int)mstArrs.size(); k++) {
        preFrames += 60;
        if (preFrames > currentFrameIndex) {
            auto edge = fGraph.edges[mstArrs[k].first];
            for (int pre_k = 0; pre_k < k; pre_k++) {
                int u = fGraph.edges[mstArrs[pre_k].first].from;
                int v = fGraph.edges[mstArrs[pre_k].first].to;
                fGraph.nodes[u].node.setFillColor(Orange);
                fGraph.nodes[v].node.setFillColor(Orange);
                if (mstArrs[pre_k].second) {
                    fGraph.edges[mstArrs[pre_k].first].edge.setColor(Orange);
                }
            }
            for (int i = 0; i < 60; i++) {
                if (i < 20) {
                    codePanelColor[i][2] = sf::Color::Red;
                    if (i == 19) {
                        codePanelColor[i][2] = LavenderSoft;
                    }
                }
                else {
                    if (mstArrs[k].second) {
                        codePanelColor[i][3] = sf::Color::Red;
                        if (i == 59) {
                            codePanelColor[i][3] = LavenderSoft;
                        }
                    }
                    else {
                        codePanelColor[i][4] = sf::Color::Red;
                        if (i == 59) {
                            codePanelColor[i][4] = LavenderSoft;
                        }
                    }
                }
                initPreGraph();
            }

            selectEdge(mstArrs[k].first, mstArrs[k].second, 0, 59);
            return;
        }
    }

}

void GraphMainState::preInitShortestPathFrames(int s)
{
    isSelectedMstFrames = false;
    isSelectedShortestPathFrames = true;

    spArrs = graph.dijkstra(s, (int)fGraph.numNodes);
    breakpoints.clear();
    for (int i = 0; i < 7; i++) {
        codePanel.setLineColor(i, LavenderSoft);
        codePanel.setText("", i);
    }
    numFrames = 0;
    currentFrameIndex = 0;
    prevFrameIndex = 0;

    codePanel.setText("pq.push({dist[source] = 0, source})", 0);
    codePanel.setText("while(!pq.empty())", 1);
    codePanel.setText("    u = pq.front().second; pq.pop()", 2);
    codePanel.setText("    for([v, w] adjacent to u) ", 3);
    codePanel.setText("    if(dist[v] > dist[u] + w)", 4);
    codePanel.setText("        dist[v] = dist[u] + w", 5);
    codePanel.setText("        pq.push({dist[v], v})", 6);

    // calculate number of frames 
    breakpoints.push_back(0);
    for (int i = 0; i < (int)spArrs.size(); i++) {
        numFrames += 60;
        breakpoints.push_back(numFrames);
    }

    aniSlider.setNumPart(numFrames);
    aniSlider.setBreakpoints(breakpoints);
    aniSlider.setPart(0);
    currentFrameIndex = 0;
    isPlaying = true;
    isPaused = false;
    isEnd = false;
}

void GraphMainState::initShortestPathFrames(int s)
{
    deleteAllFrames();
    fGraph.setColor(textColor, 1);
    for (auto& node : fGraph.nodes) {
        node.node.initTextUnder(Orange, 20);
        node.node.setTextUnder("");
    }

    int preFrames = 0;
    for (int i = 0; i < (int)spArrs.size(); i++) {
        preFrames += 60;
        auto cur = spArrs[i];
        if (preFrames > currentFrameIndex) {
            for (int j = 0; j < 60; j++) {
                for (int k = 0; k < (int)fGraph.numNodes; k++) {
                    fGraph.nodes[k].node.setTextUnder("1e9");
                }
                for (int pre_i = 0; pre_i < i; pre_i++) {
                    fGraph.nodes[spArrs[pre_i][1] - 1].node.setTextUnder(std::to_string(spArrs[pre_i][2]));
                    fGraph.nodes[spArrs[pre_i][1] - 1].node.setFillColor(Orange);
                }
                initPreGraph();

                if (i == 0) {
                    for (int k = 0; k < (int)fGraph.numNodes; k++) {
                        auto& node = fGraph.nodes[k];
                        codePanelColor[j][0] = sf::Color::Red;
                        if ((j / 10) % 2 == 0) {
                            node.node.setFillColor(Orange);
                        }
                        else {
                            if (k == cur[1] - 1 && j == 59) {
                                node.node.setFillColor(Orange);
                            }
                            else node.node.setFillColor(sf::Color::Transparent);
                        }
                        if (j == 59) {
                            codePanelColor[j][0] = LavenderSoft;
                        }
                        node.node.setTextUnder(k == cur[1] - 1 ? "0" : "1e9");
                        frames[j].addNode("1nodes" + std::to_string(k), fGraph.nodes[k].node);
                    }

                }
                else {
                    if (j < 10) {
                        codePanelColor[j][2] = sf::Color::Red;
                        if (j == 9) {
                            codePanelColor[j][2] = LavenderSoft;
                        }
                    }
                    else {
                        codePanelColor[j][4] = sf::Color::Red;
                        codePanelColor[j][5] = sf::Color::Red;
                        codePanelColor[j][6] = sf::Color::Red;
                        if (j == 59) {
                            fGraph.nodes[cur[1] - 1].node.setTextUnder(std::to_string(cur[2]));
                            frames[j].addNode("1nodes" + std::to_string(cur[1] - 1), fGraph.nodes[cur[1] - 1].node);
                            codePanelColor[j][4] = LavenderSoft;
                            codePanelColor[j][5] = LavenderSoft;
                            codePanelColor[j][6] = LavenderSoft;
                        }
                    }
                }

            }

            if (i != 0) {
                moveTo(cur[1] - 1, cur[0], 0, 59);
            }
            return;
        }
    }
}

void GraphMainState::updateFrames()
{
    if (numFrames == 0) return;
    if (numFrames > 0) currentFrameIndex = std::min(currentFrameIndex, numFrames - 1);
    if (currentFrameIndex == 0 || aniSlider.getBreakpoints(prevFrameIndex) != aniSlider.getBreakpoints(currentFrameIndex)) {
        if (isSelectedMstFrames) {
            initMstFrames();
        }
        if (isSelectedShortestPathFrames) {
            initShortestPathFrames(source);
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
                currentFrame = frames[curFrame];
                setCodePanelColor(curFrame);

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
                currentFrame = frames.back();
            }
        }
    }
}

void GraphMainState::deleteOldFrames()
{
    deleteAllFrames();
    numFrames = 0;
    isSelectedMstFrames = false;
    isSelectedShortestPathFrames = false;
    Engine::Frame frame;
    currentFrame = frame;
    breakpoints.clear();
    aniSlider.setNumPart(0);
    aniSlider.setPart(0);
    aniSlider.setBreakpoints(breakpoints);
}

void GraphMainState::setCodePanelColor(int frameIndex)
{
    for (int i = 0; i < 7; i++) {
        codePanel.setLineColor(i, codePanelColor[frameIndex][i]);
    }
}
