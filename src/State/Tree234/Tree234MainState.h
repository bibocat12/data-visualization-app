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

#include "Tree234.h"

#include "../../App.h"
#include "../MenuState.h"

#include <vector>
#include <queue>
#include <array>
#include <fstream>
#include <cstdlib>
#include <string>

class Tree234MainState : public Engine::State {
public:
	const float baseSide = 40;
	const float baseSpaceX = 40;
	const float baseSpaceY = 40;
	float SIDE = 40;
	float spaceX = 40;
	float spaceY = 40;

	Tree234MainState(std::shared_ptr<Context>& context);
	~Tree234MainState();
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
	void handleHomeButtonEvents(sf::Event event);
	void handleSearchButtonEvents(sf::Event event);
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


public:
	Node b_nodes[80];
	Node w_nodes[80];
	Edge b_edges[80];
	Edge w_edges[80];

	Tree234 tree234;
	const int maxDepth = 10;
	std::array<std::vector<Tree234::Node*>, 10> nodes;

	
	sf::Vector2f middlePoint(std::vector<int> &nodes);
	void setEdgePos(Tree234::Node *par, Tree234::Node* cur, int id);
	void initNode(Node &node, bool isDark);
	void initEdge(Edge &edge, bool isDark);

	//Animation
	sf::Vector2f NodePos;
	void setCodePanelColor(int frameIndex);
	void deleteAllFrames();
	void updateFrames();
	void initPreTree(Tree234::Node* root);
	void initTreeFrames();
	void split(Tree234::Node* root, int index1, int index2);
	void appearNode(int nodeId, int index1, int index2);
	void deleteEdge(int edgeId, int index1, int index2);
	void connectEdge(int edgeId, int index1, int index2);
	void moveEdge(int edgeId, sf::Vector2f diff, int index1, int index2);
	void moveNode(int nodeId, sf::Vector2f diff, int index1, int index2);
	void preInitCreateFrames(std::vector<int> &nums);
	void initCreateFrames(std::vector<int> &nums);
	void preInitInsertFrames(int value);
	void initInsertFrames(int value);
	void preInitSearchFrames(int value);
	void initSearchFrames(int value);
	void preInitDeleteFrames(int value);
	void initDeleteFrames(int value);


	std::vector<Engine::Frame> b_frames;
	std::vector<Engine::Frame> w_frames;
	int speed = 1;
	int totNode = 0;
	int totEdge = 1;

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
	Button searchButton;

	bool isSelectedInsertButton = false;
	bool isSelectedDeleteButton = false;
	bool isSelectedCreateButton = false;
	bool isSelectedSearchButton = false;

	bool isSelectedCreateFrames = false;
	std::vector<int> createNums;

	bool isSelectedInsertFrames = false;
	int insertValue;

	bool isSelectedDeleteFrames = false;
	int deleteValue;

	bool isSelectedSearchFrames = false;
	int searchValue;

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
	Textbox searchTextbox;

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