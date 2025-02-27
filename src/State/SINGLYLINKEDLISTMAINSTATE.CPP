#include "SinglyLinkedListMainState.h"


void SinglyLinkedListMainState::switchTheme() {
	*m_context->themeType ^= 1;
	if (*m_context->themeType == 1) { // dark mode
		backgroundColor = LightBlack;
		textColor = sf::Color::White;
		normalButtonColor = Orange;
		hoverButtonColor = LightOrangeYellow;
		themeButton.setBackground(m_context->assetManager->getTexture("LightTheme"));

		// change text color
		createButton.setTextColor(textColor);
		insertButton.setTextColor(textColor);
		deleteButton.setTextColor(textColor);
		updateButton.setTextColor(textColor);
		searchButton.setTextColor(textColor);
		speedSlider.setTextColor(textColor);
		title.setFillColor(textColor);
		for (int i = 0; i < (int)codePanel.size(); i++) {
			codePanel[i].setTextColor(textColor);
		}
	}
	else if (*m_context->themeType == 0) { // light mode
		backgroundColor = SuperLightPink;
		textColor = sf::Color::Black;
		normalButtonColor = LightBlue;
		hoverButtonColor = MediumBlue;
		themeButton.setBackground(m_context->assetManager->getTexture("DarkTheme"));

		// change text color
		createButton.setTextColor(textColor);
		insertButton.setTextColor(textColor);
		deleteButton.setTextColor(textColor);
		updateButton.setTextColor(textColor);
		searchButton.setTextColor(textColor);
		speedSlider.setTextColor(textColor);
		title.setFillColor(textColor);
		for (int i = 0; i < (int)codePanel.size(); i++) {
			codePanel[i].setTextColor(textColor);
		}
	}
}

Label SinglyLinkedListMainState::initPanel(char* st, sf::Vector2f pos, sf::Color backColor){
	Label label = Label(st, 18, panelSize, LavenderSoft, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"));
	label.setPosition(pos);
	return label;
}

void SinglyLinkedListMainState::initButton(Button& button, char* text, sf::Vector2f pos) {
	button = Button(text, buttonSize, 20, normalButtonColor, textColor);
	button.setFont(m_context->assetManager->getFont("Oswald"));
	button.setPosition(pos);
}

SinglyLinkedListMainState::SinglyLinkedListMainState(std::shared_ptr<Context>& context) : m_context(context)
{

	// Init theme
	*m_context->themeType ^= 1;
	themeButton = ImageButton(m_context->assetManager->getTexture("LightTheme"), 1.0f, 1.0f);
	switchTheme();
	themeButton.setPosition(sf::Vector2f{ 1450, 30 });

	// Init title
	title.setCharacterSize(34);
	title.setFont(m_context->assetManager->getFont("Oswald"));
	title.setString("SINGLY LINKED LIST");
	homeButton = ImageButton(m_context->assetManager->getTexture("HomeButton"), 1.0f, 1.0f);
	homeButton.setPosition(sf::Vector2f{ (SCREEN_WIDTH - title.getGlobalBounds().width) / 2 - homeButton.getGlobalBounds().width - 15, 10 });

	title.setFillColor(textColor);
	title.setPosition((SCREEN_WIDTH - title.getGlobalBounds().width) / 2, homeButton.getPosition().y + (homeButton.getGlobalBounds().height - title.getCharacterSize()) / 2);

	// Init button
	buttonSize.x = 120;
	buttonSize.y = 40;
	float checkpointY = 650;
	float firstButtonY = checkpointY + 30;
	initButton(createButton, "Create", sf::Vector2f{ 10, firstButtonY });
	initButton(insertButton, "Insert", sf::Vector2f{ 10, firstButtonY + buttonSize.y});
	initButton(deleteButton, "Delete", sf::Vector2f{ 10, firstButtonY + 2 * buttonSize.y});
	initButton(updateButton, "Update", sf::Vector2f{ 10, firstButtonY + 3 * buttonSize.y });
	initButton(searchButton, "Search", sf::Vector2f{ 10, firstButtonY + 4 * buttonSize.y });
	
	// Init code panel
	int numLine = 7;
    panelSize = sf::Vector2f(500, static_cast<float>((SCREEN_HEIGHT - 20 - checkpointY) / numLine));
	codePanel.push_back(initPanel("insert v", sf::Vector2f{ SCREEN_WIDTH - 10 - panelSize.x,  checkpointY}, normalButtonColor));
	codePanel.push_back(initPanel("for i", sf::Vector2f{ SCREEN_WIDTH - 10 - panelSize.x,  checkpointY + panelSize.y}, normalButtonColor));
	codePanel.push_back(initPanel("", sf::Vector2f{ SCREEN_WIDTH - 10 - panelSize.x,  checkpointY + 2 * panelSize.y }, normalButtonColor));
	codePanel.push_back(initPanel("", sf::Vector2f{ SCREEN_WIDTH - 10 - panelSize.x,  checkpointY + 3 * panelSize.y }, normalButtonColor));
	codePanel.push_back(initPanel("", sf::Vector2f{ SCREEN_WIDTH - 10 - panelSize.x,  checkpointY + 4 * panelSize.y }, normalButtonColor));
	codePanel.push_back(initPanel("", sf::Vector2f{ SCREEN_WIDTH - 10 - panelSize.x,  checkpointY + 5 * panelSize.y }, normalButtonColor));
	codePanel.push_back(initPanel("", sf::Vector2f{ SCREEN_WIDTH - 10 - panelSize.x,  checkpointY + 6 * panelSize.y }, normalButtonColor));

	
	// Init Animation slider
	aniSlider = Slider(sf::Vector2f{ buttonSize.x + 50, checkpointY }, sf::Vector2f{ SCREEN_WIDTH - 10 - panelSize.x - buttonSize.x - 100, 20.f }, sf::Vector2f{ 20, 20 });
	aniSlider.setColor(LightGray, RoyalBlue, Gold);



	playButton = ImageButton(m_context->assetManager->getTexture("Play"), 1.0f, 1.0f);
	playButton.setPosition(sf::Vector2f{aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - playButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15});
	
	previousButton = ImageButton(m_context->assetManager->getTexture("Previous"), 1.0f, 1.0f);
	previousButton.setPosition(sf::Vector2f{ playButton.getPosition().x - previousButton.getGlobalBounds().width, playButton.getPosition().y});

	rewindButton = ImageButton(m_context->assetManager->getTexture("Rewind"), 1.0f, 1.0f);
	rewindButton.setPosition(sf::Vector2f{ previousButton.getPosition().x - rewindButton.getGlobalBounds().width, playButton.getPosition().y });

	nextButton = ImageButton(m_context->assetManager->getTexture("Next"), 1.0f, 1.0f);
	nextButton.setPosition(sf::Vector2f{ playButton.getPosition().x + playButton.getGlobalBounds().width, playButton.getPosition().y });
	
	forwardButton = ImageButton(m_context->assetManager->getTexture("Forward"), 1.0f, 1.0f);
	forwardButton.setPosition(sf::Vector2f{ nextButton.getPosition().x + nextButton.getGlobalBounds().width, playButton.getPosition().y });

	replayButton = ImageButton(m_context->assetManager->getTexture("Replay"), 1.0f, 1.0f);
	replayButton.setPosition(sf::Vector2f{-1000, -1000});

	pauseButton = ImageButton(m_context->assetManager->getTexture("Pause"), 1.0f, 1.0f);
	pauseButton.setPosition(sf::Vector2f{ -1000, -1000 });
	
	// Init speed slider
	speedSlider = Slider(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - 300) / 2, playButton.getPosition().y + playButton.getGlobalBounds().height + 15}, sf::Vector2f{300, 15.f}, sf::Vector2f{20, 20});
	speedSlider.setColor(LightGray, NavyBlue, GoldenOrange);
	speedSlider.setNumPart(6);
	speedSlider.setText("1.0x", "1.0x", 20, m_context->assetManager->getFont("Neon"), textColor);
}

SinglyLinkedListMainState::~SinglyLinkedListMainState()
{
}

void SinglyLinkedListMainState::init()
{



}

void SinglyLinkedListMainState::pause()
{

}

void SinglyLinkedListMainState::resume()
{

}

void SinglyLinkedListMainState::processEvents()
{
	sf::Event event;

	while (m_context->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->window->close();
			return;
		}

		createButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
		insertButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
		deleteButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
		updateButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
		searchButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);

		if (aniSlider.getPartIndex() == aniSlider.getNumPart()) {
			pauseButton.setPosition(sf::Vector2f({ -1000, 1000 }));
			playButton.setPosition(sf::Vector2f({ -1000, 1000 }));
			replayButton.setPosition(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - replayButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15});
		}
		else {
			pauseButton.setPosition(sf::Vector2f({ -1000, 1000 }));
			replayButton.setPosition(sf::Vector2f({ -1000, 1000 }));
			playButton.setPosition(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - playButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15});
		}
		
		if (event.type == sf::Event::MouseButtonPressed)
		{	
			if (homeButton.isMouseOverCircle(*m_context->window))
			{
				m_context->stateMachine->removeState();
			}
			if (themeButton.isMouseOver(*m_context->window)) {
				switchTheme();
			}

			if (nextButton.isMouseOverCircle(*m_context->window)) {
				aniSlider.setPart(aniSlider.getPartIndex() + 1);
			}

			if (previousButton.isMouseOverCircle(*m_context->window)) {
				aniSlider.setPart(aniSlider.getPartIndex() - 1);
			}

			if (forwardButton.isMouseOverCircle(*m_context->window)) {
				aniSlider.setPart(aniSlider.getNumPart());
			}

			if (rewindButton.isMouseOverCircle(*m_context->window)) {
				aniSlider.setPart(0);
			}

			if (replayButton.isMouseOverCircle(*m_context->window)) {
				aniSlider.setPart(0);
			}
	

		}
		aniSlider.handleEvent(event);
		speedSlider.handleEvent(event);
		std::string st = "1.0x";
		st[0] = char(speedSlider.getPartIndex() + 1 + '0');
		speedSlider.setMaxText(st);

	}
}

void SinglyLinkedListMainState::update(const sf::Time& dt)
{

}

void SinglyLinkedListMainState::draw()
{
	m_context->window->clear(backgroundColor);
	m_context->window->draw(title);
	createButton.drawTo(*m_context->window);

	insertButton.drawTo(*m_context->window);
	deleteButton.drawTo(*m_context->window);
	updateButton.drawTo(*m_context->window);
	searchButton.drawTo(*m_context->window);


	themeButton.drawTo(*m_context->window);
	homeButton.drawTo(*m_context->window);
	for (int i = 0; i < (int)codePanel.size(); i++) {
		codePanel[i].drawTo(*m_context->window);
	}

	aniSlider.draw(*m_context->window);
	speedSlider.draw(*m_context->window);

	playButton.drawTo(*m_context->window);
	previousButton.drawTo(*m_context->window);
	nextButton.drawTo(*m_context->window);
	rewindButton.drawTo(*m_context->window);
	forwardButton.drawTo(*m_context->window);
	replayButton.drawTo(*m_context->window);
	pauseButton.drawTo(*m_context->window);
  
	updateFrames();


	m_context->window->display();

}


void SinglyLinkedListMainState::handleButtonEvents( const  sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (createButton.isMouseOver(*m_context->window))
		{
			handleCreateButtonEvents(event);
		}
		else if (insertButton.isMouseOver(*m_context->window))
		{
			handleInsertButtonEvents(event);
		}
		else if (deleteButton.isMouseOver(*m_context->window))
		{
			handleDeleteButtonEvents(event);
		}
		else if (searchButton.isMouseOver(*m_context->window))
		{
			handleSearchButtonEvents(event);
		}

		
	}
}

void SinglyLinkedListMainState::handleCreateButtonEvents(const sf::Event event)
{
	 
}

void SinglyLinkedListMainState::handleRandomButtonEvents(sf::Event event)
{
	std::cout << "Random Button:";
	int n;
	std::cin >> n;
	std::vector<int> allElements;
	for (int i = 0; i < n; i++) {
		allElements.push_back(rand() % 100);
	}


	LinkedList.init(allElements);

	for (int x : LinkedList.getAllElements())
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;

	initRandomFrames();

}

void SinglyLinkedListMainState::handleInsertButtonEvents(sf::Event event)
{
}

void SinglyLinkedListMainState::handleDeleteButtonEvents(sf::Event event)
{
}

void SinglyLinkedListMainState::handleSearchButtonEvents(sf::Event event)
{
}

void SinglyLinkedListMainState::handleBackButtonEvents(sf::Event event)
{
}

void SinglyLinkedListMainState::handleStartButtonEvents(sf::Event event)
{
}



void SinglyLinkedListMainState::initRandomFrames()
{
	int timeRepeat = 0;
	
	std::vector<int> allElements;
	allElements = LinkedList.getAllElements();
	Engine::Frame previousframe;
	for (int i = 0; i < allElements.size(); i++) {
		Engine::Frame frame;
		std::shared_ptr<Node> node = std::make_shared<Node>();
		node->setString(std::to_string(allElements[i]));
		node->setFillColor(sf::Color::Green);
		node->setOutlineColor(sf::Color::Black);
		node->setOutlineThickness(2);
		node->setRadius(20);
		node->setPosition(sf::Vector2f(500 + i * 80, 30));
		if(i != 0)
			frame.init(previousframe);
		frame.addNode(std::to_string(allElements[i]), std::move(node));
		previousframe = frame;
		for (int j = 0; j < 100; j++)
			frames.push_back(frame);
		frames.push_back(frame);
	}

	numFrames = frames.size();
	isPlaying = true;
	currentFrameIndex = 0;

}

void SinglyLinkedListMainState::initInsertFrames()
{
}

void SinglyLinkedListMainState::updateFrames()
{
	if (isPlaying)
	{
		if (numFrames > 0)
		{
			if (currentFrameIndex < numFrames)
			{
				currentFrame = frames[currentFrameIndex];
				currentFrameIndex++;
			}
			else
			{
				currentFrame = frames[currentFrameIndex - 1];
				isPlaying = false;
			}
		}
	}
	currentFrame.drawAll(*m_context->window);

}


