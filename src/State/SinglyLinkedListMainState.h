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


#include "SinglyLinkedList.h"

#include "../App.h"
#include "MenuState.h"

#include <vector>


class SinglyLinkedListMainState : public Engine::State 
{

public:
	SinglyLinkedListMainState(std::shared_ptr<Context>& context);
	~SinglyLinkedListMainState();
	void init() override;
	void pause() override;
	void resume() override;
	void processEvents() override;
	void update(const sf::Time& dt) override;
	void draw() override;

	void handleButtonEvents( const sf::Event& event);
	void handleCreateButtonEvents( const sf::Event event);
	void handleRandomButtonEvents(sf::Event event);
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
	std::vector<Engine::Frame> frames;
	bool isShowing = false;
	bool isPlaying = false;
	Engine::Frame currentFrame;
	Engine::Frame staticFrame;
  
  	Node node[18];

	SinglyLinkedList LinkedList;
	SinglyLinkedList LinkedList2;

	void initRandomFrames();
	void initInsertFrames();

	void updateFrames();


	sf::Sprite background;


	std::vector<Engine::Frame> m_frames;
  
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

	Textbox insertTextbox;
	Textbox deleteTextbox;
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

