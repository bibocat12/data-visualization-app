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

	std::vector<Engine::Frame> m_frames;

private:
	std::shared_ptr<Context> m_context;

private:
	sf::Text title;
	sf::Color backgroundColor;
	sf::Color textColor;
	sf::Color normalButtonColor;
	sf::Color hoverButtonColor;
	sf::Vector2f buttonSize;
	sf::Vector2f panelSize;

	ImageButton themeButton;
	ImageButton homeButton;
	Button createButton;
	Button insertButton;
	Button deleteButton;
	Button updateButton;
	Button searchButton;
	std::vector<Label> codePanel;

	Slider aniSlider;
	Slider speedSlider;
	ImageButton playButton;
	ImageButton replayButton;
	ImageButton pauseButton;
	ImageButton nextButton;
	ImageButton previousButton;
	ImageButton rewindButton;
	ImageButton forwardButton;

public:
	void initButton(Button& button, char* text, sf::Vector2f pos);
	void switchTheme();
	Label initPanel(char* st, sf::Vector2f pos, sf::Color backColor);
};

