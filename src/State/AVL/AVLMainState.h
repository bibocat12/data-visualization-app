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

#include "AVLTree.h"
#include "../../App.h"
#include "../MenuState.h"

#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>


class AVLMainState : public Engine::State {
public:
    // Constants
    const float MAX_RADIUS = 30;
    const float MED_RADIUS = 20;
    const float MIN_RADIUS = 15;
    const float SM_RADIUS = 10;


    const float MAX_DISTANCE_X = 50;
    const float MED_DISTANCE_X = 30;
    const float MIN_DISTANCE_X = 20;
    const float SM_DISTANCE_X = 20;


    const float MAX_DISTANCE_Y = 80;
    const float MED_DISTANCE_Y = 70;
    const float MIN_DISTANCE_Y = 60;
    const float SM_DISTANCE_Y = 50;
    float RADIUS = 25;
    float PADDING_X = 380;
    float PADDING_Y = 20;

    float DISTANCE_X = 40;
    float DISTANCE_Y = 80;

    const int LIMIT_NODE_MIN = 30;
    const int LIMIT_NODE_MED = 50;
    const int LIMIT_NODE_MAX = 70;



    const sf::Color B_NODE_COLOR = sf::Color::White;
    const sf::Color B_NODE_COLOR_TRANS = sf::Color(255, 255, 255, 0);
    const sf::Color B_NODE_COLOR_HOVER = sf::Color::Yellow;
    const sf::Color B_NODE_OUTLINE_COLOR = sf::Color::Red;
    const sf::Color B_NODE_OUTLINE_COLOR_TRANS = sf::Color(255, 0, 0, 0);
    const sf::Color W_NODE_COLOR = sf::Color::White;
    const sf::Color W_NODE_COLOR_TRANS = sf::Color(255, 255, 255, 0);
    const sf::Color W_NODE_COLOR_HOVER = Orange;
    const sf::Color W_NODE_OUTLINE_COLOR = Orange;
    const sf::Color W_NODE_OUTLINE_COLOR_TRANS = sf::Color(255, 165, 0, 0);



    // Constructor & Destructor
    AVLMainState(std::shared_ptr<Context>& context);
    ~AVLMainState();

    // Core Functions
    void init() override;
    void pause() override;
    void resume() override;
    void processEvents() override;
    void update(const sf::Time& dt) override;
    void draw() override;

    // Event Handlers
    void handleButtonEvents(const sf::Event& event);
    void handleCreateButtonEvents(const sf::Event& event);
    void handleInsertButtonEvents(const sf::Event& event);
    void handleDeleteButtonEvents(const sf::Event& event);
    void handleSearchButtonEvents(const sf::Event& event);
    void handleInorderButtonEvents(const sf::Event& event);

    void handleHomeButtonEvents(const sf::Event& event);
    void handleThemeButtonEvents(const sf::Event& event);
    void handleAniSliderEvents(const sf::Event& event);
    void handleSpeedSliderEvents(const sf::Event& event);

    // Frame Control
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


    // Node & Edge Data
    Node b_nodes[100];
    Edge b_edges[100];
    Node w_nodes[100];
    Edge w_edges[100];

    Node preb_nodes[100];
    Node prew_nodes[100];
    Edge preb_edges[100];
    Edge prew_edges[100];

    AVLTree avl;

    // Node Manipulation
    void initNode(std::vector<int>& elements, std::vector<int>& depth);
    void resetNodePosRad();
    void initEdge(std::vector<int>& parent);
    void changeBNode(int index, int index1, int index2, Node from, Node to);
    void changeWNode(int index, int index1, int index2, Node from, Node to);
    void changeBEdge(int index, int index1, int index2, Edge from, Edge to);
    void changeWEdge(int index, int index1, int index2, Edge from, Edge to);
    void connectTwoNodes(int index, int index1, int index2, bool isEnd);

    // Frame Initialization

    sf::Color codePanelColor[60][9];
    std::string currentState = "no";

    void deleteAllFrames();
	void initEmptyFrames(int count);
    void initCreateFrames(std::vector<int> elements);
    void initInsertFrames();

	int deleteValue = 0;
    void initDeleteFrames(int deleteValue);
	void initSearchFrames();
    std::vector<int> searchPath;
    int ValueFind = 0;
=========
    void initDeleteFrames(int value);

	void initSearchFrames(int value);
>>>>>>>>> Temporary merge branch 2
	void initInorderFrames();

    void createInorderFrames();
	void createInsertFrames(int value);
	void createDeleteFrames(int value);
	void createSearchFrames(int value);

	void setCodePanelColor(int frameIndex);


    void updateFrames();

    Engine::Frame handleInorderFrame(int index);

    // UI Elements
    sf::Sprite background;
    std::vector<Engine::Frame> b_frames;
    std::vector<Engine::Frame> w_frames;
	std::vector<bool> isFrameActive;
	std::vector<int> inorderSnapshot;
	std::vector<AVLTree::TreeSnapshot> snapshots;
    int speed = 1;

    // UI Initialization
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

    // Buttons
    ImageButton themeButton;
    ImageButton homeButton;

    Button createButton;
    Button insertButton;
    Button searchButton;
    Button deleteButton;
    Button inorderButton;

    bool isSelectedInsertButton = false;
    bool isSelectedDeleteButton = false;
    bool isSelectedSearchButton = false;
    bool isSelectedCreateButton = false;
    bool isSelectedInorderButton = false;

    // UI Panels & Sliders
    Panel codePanel;
    Slider aniSlider;
    Slider speedSlider;

    // Playback Controls
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

    // Input Fields
    Textbox insertTextbox;
    Textbox deleteTextbox;
    Textbox searchTextbox;
    Textbox createTextbox;

    ImageButton randomUpdateButton;

public:
    // UI Initialization
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