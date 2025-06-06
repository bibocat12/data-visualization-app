#pragma once

#include "../../StateMachine/State.h"
#include "../../StateMachine/StateMachine.h"
#include "../../StateMachine/AssetManager.h"
#include "../../StateMachine/DEFINITION.h"
#include "../../StateMachine/Frame.h"


#include "../../GUI/Button.h"
#include "../../GUI/ImageButton.h"
#include "../../GUI/Node.h"
#include "../../GUI/Textbox.h"
#include "../../GUI/Label.h"
#include "../../GUI/Slider.h"
#include "../../GUI/Panel.h"
#include "../../GUI/portable-file-dialogs.h"
#include "../../GUI/Edge.h"

#include "Heap.h"

#include "../../App.h"
#include "../MenuState.h"

#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>


class HeapMainState : public Engine::State
{

public:
	const float RADIUS = 20;
	const float spaceX = 400;
	const float spaceY = 15;
	const float minSpaceX = 30;

	HeapMainState(std::shared_ptr<Context>& context);
	~HeapMainState();
	void init() override;
	void pause() override;
	void resume() override;
	void processEvents() override;
	void update(const sf::Time& dt) override;
	void draw() override;

	void handleButtonEvents(const sf::Event& event);

	void handleCreateButtonEvents(const sf::Event event);
	void handleInsertButtonEvents(sf::Event event);
	void handleDeleteButtonEvents(sf::Event event);
	void handleExtractButtonEvents(sf::Event event);
	void handleHomeButtonEvents(sf::Event event);
	void handleUpdateButtonEvents(sf::Event event);
	void handleThemeButtonEvents(sf::Event event);
	void handleAniSliderEvents(sf::Event event);
	void handleSpeedSliderEvents(sf::Event event);

	int numFrames = 0;
	int currentFrameIndex = 0;
	int prevFrameIndex = 0;
	bool isShowing = false;
	bool isPaused = false;
	bool isPlaying = false;
	bool isEnd = false;

	std::vector<int> breakpoints;

	Engine::Frame currentFrame;
	Engine::Frame b_currentFrame;
	Engine::Frame w_currentFrame;
	Engine::Frame b_nextFrame;
	Engine::Frame w_nextFrame;
	Engine::Frame staticFrame;
	
private:
	static constexpr int limNodes = 31;
	static constexpr int maxNodes = 64;

public:
	Node b_nodes[maxNodes];
	Edge b_edges[maxNodes];
	Node w_nodes[maxNodes];
	Edge w_edges[maxNodes];


	void initNode(int n = 0);
	void initEdge(int n = 0);

	MinHeap heap = MinHeap(maxNodes);

	void connectTwoNodes(int index, int index1, int index2, bool isEnd);
	void deleteEdge(int index, int index1, int index2, bool isEnd);
	void swapTwoNodes(int node1, int node2, int index1, int index2, bool isEnd);

	void deleteAllFrames();
	void setCodePanelColor(int frameIndex);
	void initPreHeap(const std::vector<int> &nums);
	void preInitCreateFrames(bool isInitState = false);
	void initCreateFrames(bool isInitState = false);
	void preInitInsertFrames(int value);
	void initInsertFrames(int value);
	void preInitUpdateFrames(int id, int newV);
	void initUpdateFrames(int id, int newV);
	void preInitDeleteFrames(int id);
	void initDeleteFrames(int id);
	void preInitExtractFrames();
	void initExtractFrames();

	void updateFrames();

	std::vector<Engine::Frame> b_frames;
	std::vector<Engine::Frame> w_frames;
	int speed = 1;

	void initButton(Button& button, std::string text, sf::Vector2f pos);
	void switchTheme();

private:
	std::shared_ptr<Context> m_context;

	sf::Text title;
	sf::Color backgroundColor;
	sf::Color textColor;
	sf::Color normalButtonColor;
	sf::Color hoverButtonColor;
	sf::Vector2f buttonSize;

	ImageButton themeButton;
	ImageButton homeButton;

	Button createButton;
	Button insertButton;
	Button deleteButton;
	Button updateButton;
	Button extractButton;

	bool isSelectedInsertButton = false;
	bool isSelectedDeleteButton = false;
	bool isSelectedExtractButton = false;
	bool isSelectedCreateButton = false;
	bool isSelectedUpdateButton = false;

	std::vector<int> heapElements;
	bool isSelectedCreateFrames = false;
	std::vector<int> createNums;
	std::vector<std::vector<std::pair<int, int>>> createArrs;
	bool isLess;

	bool isSelectedInsertFrames = false;
	int insertValue;
	std::vector<std::pair<int, int>> insertArrs;

	bool isSelectedDeleteFrames = false;
	int deleteId;
	std::vector<std::vector<std::pair<int, int>>> deleteArrs;

	bool isSelectedUpdateFrames = false;
	int updateId, updateValue;
	std::vector<std::pair<int, int>> updateArrs;

	std::vector<std::pair<int, int>> extractArrs;
	bool isSelectedExtractFrames = false;

	Panel codePanel;
	sf::Color codePanelColor[60][7];
	Slider aniSlider;
	Slider speedSlider;
	ImageButton playButton;
	ImageButton replayButton;
	ImageButton pauseButton;
	ImageButton nextButton;
	ImageButton previousButton;
	ImageButton rewindButton;
	ImageButton forwardButton;
	ImageButton randomButton;
	ImageButton okButton;
	ImageButton uploadFileButton;
	Label okButtonBackground;

	Textbox insertTextbox;
	Textbox deleteTextbox;
	Textbox createTextbox;
	Textbox updateTextboxX;
	Textbox updateTextboxV;
	ImageButton randomUpdateButton;

public:
	void initFunctionButton();
	void initCodePanel();
	void initTheme();
	void initTitle();
	void initAniSlider();
	void initSpeedSlider();

	void initTextbox(Textbox& textbox, int charSize, sf::Color textColor, sf::Font& font, sf::Vector2f pos);
private:
	sf::Vector2f labelSize;
	float checkpointY;
};