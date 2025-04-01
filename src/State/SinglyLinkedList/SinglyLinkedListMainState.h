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


#include "SinglyLinkedList.h"


#include "../../App.h"
#include "../MenuState.h"


#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>




class SinglyLinkedListMainState : public Engine::State
{

public:

	const float EDGE_Y = 410;
	const float NODE_Y = 400;
	const float PADDING_X = 80;
	const float DISTANCE_X = 80;
	const float RADIUS = 20;
	const float CHARACTER_SIZE = 20;

	const sf::Color B_NODE_COLOR = sf::Color::White;
	const sf::Color B_NODE_COLOR_HOVER = sf::Color::Yellow;
	const sf::Color W_NODE_COLOR = sf::Color::White;
	const sf::Color W_NODE_COLOR_HOVER = Orange;


	SinglyLinkedListMainState(std::shared_ptr<Context>& context);
	~SinglyLinkedListMainState();
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
	int prevFrameIndex = 0;
	bool isShowing = false;
	bool isPaused = false;
	bool isPlaying = false;
	bool isEnd = false;

	int kInsert = 0;
	int vInsert = 0;
	int kDelete = 0;
	int vDelete = 0;
	int kSearch = 0;
	int kUpdate = 0;
	int oldVUpdate = 0;
	int newVUpdate = 0;
	std::vector<int> breakpoints;

	Engine::Frame currentFrame;
	Engine::Frame b_currentFrame;
	Engine::Frame w_currentFrame;
	std::vector<Engine::Frame> b_frames;
	std::vector<Engine::Frame> w_frames;

	int speed = 1;
	std::string currentState = "no";

	sf::Color codePanelColor[60][7];
	
	void initCreateFrames();
	void initInsertFrames();
	void initDeleteFrames();
	void initUpdateFrames();
	void initSearchFrames();

	void createCreateFrames(const std::vector<int>& nums);
	void createInsertFrames(int k, int v);
	void createDeleteFrame(int v);
	void createSearchFrames(int num);
	void createUpdateFrames(int oldV, int newV);

	void deleteAllFrames();

	void setCodePanelColor(int frameIndex);



	Node b_nodes[100];
	Edge b_edges[100];
	Node w_nodes[100];
	Edge w_edges[100];
	Node preb_nodes[100];
	Edge preb_edges[100];
	Node prew_nodes[100];
	Edge prew_edges[100];



	void initNode(std::vector<int>& getAllElements);
	void initEdge(std::vector<int>& getAllElements);
	void changeBNode(int index, int index1, int index2, Node from, Node to);
	void changeWNode(int index, int index1, int index2, Node from, Node to);
	void changeBEdge(int index, int index1, int index2, Edge from, Edge to);
	void changeWEdge(int index, int index1, int index2, Edge from, Edge to);

	SinglyLinkedList LinkedList;

	sf::Text warningText;
	bool isWarning = false;


	void updateFrames();


	sf::Sprite background;


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

	Textbox insertTextboxK;
	Textbox insertTextboxV;
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
	int checkNumber(std::string str);
private:
	sf::Vector2f labelSize;
	float checkpointY;
};