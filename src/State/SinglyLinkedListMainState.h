#pragma once


#include "../StateMachine/State.h"
#include "../StateMachine/StateMachine.h"
#include "../StateMachine/AssetManager.h"
#include "../StateMachine/DEFINITION.h"
#include "../StateMachine/Frame.h"


#include "../GUI/Button.h"
#include "../GUI/Node.h"
#include "../GUI/Textbox.h"

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


	sf::Sprite background;

	Button startButton;
	Button insertButton;
	Button deleteButton;
	Button searchButton;
	Button backButton;

	std::vector<Engine::Frame> m_frames;

private:
	std::shared_ptr<Context> m_context;
};

