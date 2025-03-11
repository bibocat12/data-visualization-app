#pragma once

#include "../StateMachine/State.h"
#include "../StateMachine/StateMachine.h"
#include "../StateMachine/AssetManager.h"
#include "../StateMachine/DEFINITION.h"
#include "../StateMachine/Frame.h"


#include "../GUI/Button.h"
#include "../GUI/ImageButton.h"
#include "../GUI/Node.h"
#include "../GUI/Textbox.h"
#include "../GUI/Label.h"
#include "../GUI/Slider.h"
#include "../GUI/Panel.h"
#include "../GUI/portable-file-dialogs.h"
#include "../GUI/Edge.h"

#include "Heap.h"

#include "../App.h"
#include "MenuState.h"

#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>


class HeapMainState : public Engine::State
{

public:
	const float RADIUS = 25;
	const float spaceX = 380;
	const float spaceY = 20;
	const float minSpaceX = 65;

	const sf::Color B_NODE_COLOR = sf::Color::White;
	const sf::Color B_NODE_COLOR_HOVER = sf::Color::Yellow;
	const sf::Color W_NODE_COLOR = sf::Color::White;
	const sf::Color W_NODE_COLOR_HOVER = Orange;


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
	void handleSearchButtonEvents(sf::Event event);
	void handleHomeButtonEvents(sf::Event event);
	void handleUpdateButtonEvents(sf::Event event);
	void handleThemeButtonEvents(sf::Event event);
	void handleAniSliderEvents(sf::Event event);
	void handleSpeedSliderEvents(sf::Event event);

	int numFrames = 0;
	int currentFrameIndex = 0;
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
	static constexpr int maxNodes = 80;

public:
	Node b_nodes[maxNodes];
	Edge b_edges[maxNodes];
	Node w_nodes[maxNodes];
	Edge w_edges[maxNodes];


	void initNode();
	void initEdge();

	MinHeap heap = MinHeap(maxNodes);

	void connectTwoNodes(int index, int index1, int index2, bool isEnd);
	void swapTwoNodes(int index, int index1, int index2, bool isEnd);

	void changeBColor(int index, int index1, int index2, sf::Color from, sf::Color to);
	void changeWColor(int index, int index1, int index2, sf::Color from, sf::Color to);


	void deleteAllFrames();
	void initRandomFrames(std::vector<int> elements);
	void initInsertFrames(int value);
	void initUpdateFrames(int oldV, int newV);
	void initSearchFrames(int num);

	void updateFrames();


	sf::Sprite background;


	std::vector<Engine::Frame> b_frames;
	std::vector<Engine::Frame> w_frames;

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
	Button searchButton;

	bool isSelectedInsertButton = false;
	bool isSelectedDeleteButton = false;
	bool isSelectedSearchButton = false;
	bool isSelectedCreateButton = false;
	bool isSelectedUpdateButton = false;

	Panel codePanel;
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
	Textbox searchTextbox;
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

