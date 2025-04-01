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
#include "../../GUI/ForceGraph.h"

#include "Graph.h"
#include "../../App.h"
#include "../MenuState.h"

#include <vector>
#include <array>;
#include <fstream>
#include <cstdlib>
#include <string>

class GraphMainState : public Engine::State {
public:
	GraphMainState(std::shared_ptr<Context>& context);
	~GraphMainState();
	void init() override;
	void pause() override;
	void resume() override;
	void processEvents() override;
	void update(const sf::Time& dt) override;
	void draw() override;

	void handleButtonEvents(const sf::Event& event);

	void handleSettingsButtonEvents(const sf::Event event);
	void handleCreateButtonEvents(sf::Event event);
	void handleInputButtonEvents(sf::Event event);
	void handleMstButtonEvents(sf::Event event);
	void handleShortestPathButtonEvents(sf::Event event);
	void handleHomeButtonEvents(sf::Event event);
	void handleThemeButtonEvents(sf::Event event);
	void handleAniSliderEvents(sf::Event event);
	void handleSpeedSliderEvents(sf::Event event);
	void setDirected(bool directed);
	void setFixed(bool fixed);
	void hideObject();
	sf::Vector2f randomNodePosition();

	int numFrames = 0;
	int currentFrameIndex = 0;
	int prevFrameIndex = 0;
	bool isShowing = false;
	bool isPaused = false;
	bool isPlaying = false;
	bool isEnd = false;

	std::vector<int> breakpoints;

	Engine::Frame currentFrame;
	Engine::Frame nextFrame;
	Engine::Frame staticFrame;

private:
public:

	const float RADIUS = 20;
	Graph graph;
	ForceGraph fGraph;
	Edge tmpEdge;
	Node nodes[100];
	Edge edges[100];

	void initPreGraph();
	void deleteAllFrames();
	void selectEdge(int edgeIndex, bool isSelected, int index1, int index2);
	void moveTo(int from, int edgeIndex, int index1, int index2);
	void preInitMstFrames();
	void initMstFrames();
	void preInitShortestPathFrames(int s);
	void initShortestPathFrames(int s);
	std::vector<std::pair<int, bool>> mstArrs;

	void updateFrames();
	std::vector<Engine::Frame> frames;
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

	Button settingsButton;
	Button createButton;
	Button inputButton;
	Button mstButton;
	Button shortestPathButton;
	Button directedButton;
	Button undirectedButton;
	Button fixedButton;
	Button unfixedButton;

	bool isSelectedSettingsButton = false;
	bool isSelectedCreateButton = false;
	bool isSelectedInputButton = false;
	bool isSelectedMstButton = false;
	bool isSelectedShortestPathButton = false;
	bool isDirected = false;
	bool isFixed = false;

	bool isSelectedMstFrames = false;

	bool isSelectedShortestPathFrames = false;
	int source;
	std::vector<std::array<int, 3>> spArrs;

	void deleteOldFrames();
	void setCodePanelColor(int frameIndex);
	sf::Color codePanelColor[60][7];
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

	Textbox createTextboxN;
	Textbox createTextboxE;
	Textbox shortestPathTextbox;
	const int numMatrix = 13;
	Textbox inputTextbox[13];
	ImageButton randomButton1;

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