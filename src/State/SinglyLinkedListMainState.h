#pragma once


#include "../StateMachine/State.h"
#include "../StateMachine/StateMachine.h"
#include "../StateMachine/AssetManager.h"
#include "../StateMachine/DEFINITION.h"
#include "../StateMachine/Frame.h"


#include "../GUI/Button.h"
#include "../GUI/Node.h"
#include "../GUI/Textbox.h"

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
	void handleStartButtonEvents( const sf::Event event);
	void handleRandomButtonEvents(sf::Event event);
	void handleInsertButtonEvents(sf::Event event);
	void handleDeleteButtonEvents(sf::Event event);
	void handleSearchButtonEvents(sf::Event event);
	void handleBackButtonEvents(sf::Event event);

	int numFrames = 0;
	int currentFrameIndex = 0;
	std::vector<Engine::Frame> frames;
	bool isShowing = false;
	bool isPlaying = false;
	Engine::Frame currentFrame;
	Engine::Frame staticFrame;

	SinglyLinkedList LinkedList;
	SinglyLinkedList LinkedList2;

	void initRandomFrames();
	void initInsertFrames();

	void updateFrames();


	sf::Sprite background;

	Button startButton;
	Button randomButton;
	Button insertButton;
	Button deleteButton;
	Button searchButton;
	Button backButton;

	std::vector<Engine::Frame> m_frames;

	Node node[18];

private:
	std::shared_ptr<Context> m_context;
};

