#include "../../../header/State/Graph/GraphMainState.h"

void GraphMainState::switchTheme() {
	*m_context->themeType ^= 1;
	if (*m_context->themeType == 1) { // dark mode
		backgroundColor = LightBlack;
		textColor = sf::Color::White;
		normalButtonColor = Orange;
		hoverButtonColor = LightOrangeYellow;
		themeButton.setBackground(m_context->assetManager->getTexture("LightTheme"));

		// change text color
		createButton.setTextColor(textColor);
		settingsButton.setTextColor(textColor);
		inputButton.setTextColor(textColor);
		mstButton.setTextColor(textColor);
		shortestPathButton.setTextColor(textColor);
		directedButton.setTextColor(textColor);
		undirectedButton.setTextColor(textColor);
		fixedButton.setTextColor(textColor);
		unfixedButton.setTextColor(textColor);
		speedSlider.setTextColor(textColor);
		title.setFillColor(textColor);
		fGraph.setColor(textColor, 0);
		for (int i = 0; i < (int)frames.size(); i++) {
			for (int j = 0; j < (int)fGraph.numNodes; j++) {
				frames[i].getNode("1nodes" + std::to_string(j)).setOutlineColor(textColor);
				frames[i].getNode("1nodes" + std::to_string(j)).setTextColor(textColor);
			}
			for (int j = 0; j < (int)fGraph.numEdges; j++) {
				if (frames[i].getEdge("2edges" + std::to_string(j)).getColor() == sf::Color::Black) {
					frames[i].getEdge("2edges" + std::to_string(j)).setColor(sf::Color::White);
				}
			}
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
		settingsButton.setTextColor(textColor);
		inputButton.setTextColor(textColor);
		mstButton.setTextColor(textColor);
		shortestPathButton.setTextColor(textColor);
		directedButton.setTextColor(textColor);
		undirectedButton.setTextColor(textColor);
		fixedButton.setTextColor(textColor);
		unfixedButton.setTextColor(textColor);
		speedSlider.setTextColor(textColor);
		title.setFillColor(textColor);
		fGraph.setColor(textColor, 0);
		for (int i = 0; i < (int)frames.size(); i++) {
			for (int j = 0; j < (int)fGraph.numNodes; j++) {
				frames[i].getNode("1nodes" + std::to_string(j)).setOutlineColor(textColor);
				frames[i].getNode("1nodes" + std::to_string(j)).setTextColor(textColor);
			}
			for (int j = 0; j < (int)fGraph.numEdges; j++) {
				if (frames[i].getEdge("2edges" + std::to_string(j)).getColor() == sf::Color::White) {
					frames[i].getEdge("2edges" + std::to_string(j)).setColor(sf::Color::Black);
				}
			}
		}
	}
}

void GraphMainState::initFunctionButton() {
	buttonSize.x = 120;
	buttonSize.y = 40;
	checkpointY = 650;
	float firstButtonY = checkpointY + 30;
	initButton(settingsButton, "Settings", sf::Vector2f{ 10, firstButtonY });
	initButton(createButton, "Create", sf::Vector2f{ 10, firstButtonY + buttonSize.y });
	initButton(inputButton, "Input", sf::Vector2f{ 10, firstButtonY + 2 * buttonSize.y });
	initButton(mstButton, "MST", sf::Vector2f{ 10, firstButtonY + 3 * buttonSize.y });
	initButton(shortestPathButton, "Dijkstra", sf::Vector2f{ 10, firstButtonY + 4 * buttonSize.y });
	initButton(directedButton, "Directed", sf::Vector2f{ -1000, -1000 });
	initButton(undirectedButton, "Undirected", sf::Vector2f{ -1000, -1000 });
	initButton(fixedButton, "Fixed", sf::Vector2f{ -1000, -1000 });
	initButton(unfixedButton, "Unfixed", sf::Vector2f{ -1000, -1000 });

	directedButton.setSize(sf::Vector2f(100, 40));
	undirectedButton.setSize(sf::Vector2f(100, 40));
	fixedButton.setSize(sf::Vector2f(100, 40));
	unfixedButton.setSize(sf::Vector2f(100, 40));
	randomButton = ImageButton(m_context->assetManager->getTexture("Random"), 1.f, 1.f);
	randomButton1 = ImageButton(m_context->assetManager->getTexture("Random"), 1.f, 1.f);
	uploadFileButton = ImageButton(m_context->assetManager->getTexture("UploadFile"), 1.f, 1.f);
	okButton = ImageButton(m_context->assetManager->getTexture("Ok"), 1.f, 1.f);

	uploadFileButton.setPosition(sf::Vector2f{ -1000, -1000 });
	randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
	randomButton1.setPosition(sf::Vector2f{ -1000, -1000 });
	okButton.setPosition(sf::Vector2f{ -1000, -1000 });
	okButtonBackground = Label("", 0, sf::Vector2f{ 200, buttonSize.y }, DarkBeigeGrey, textColor, m_context->assetManager->getFont("arial"));
	okButtonBackground.setPosition(sf::Vector2f{ -1000, -1000 });

	initTextbox(createTextboxN, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + settingsButton.getPositon().x + settingsButton.getGlobalBounds().width, settingsButton.getPositon().y });
	createTextboxN.setConstText("N = ");
	createTextboxN.setLimit(true, 2);

	initTextbox(createTextboxE, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + settingsButton.getPositon().x + settingsButton.getGlobalBounds().width, createTextboxN.getPositon().y + createTextboxN.getGlobalBounds().height });
	createTextboxE.setConstText("E = ");
	createTextboxE.setLimit(true, 2);

	initTextbox(inputTextbox[numMatrix - 1], 15, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	inputTextbox[numMatrix - 1].setConstText(std::to_string(numMatrix) + "   ");
	inputTextbox[numMatrix - 1].setLimit(true, 38);
	inputTextbox[numMatrix - 1].setBox(sf::Vector2f(400, 30), BeigeGrey);
	inputTextbox[numMatrix - 1].setLineBoundingBox(DarkBeigeGrey);
	for (int i = numMatrix - 2; i >= 0; i--) {
		initTextbox(inputTextbox[i], 15, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{inputTextbox[i + 1].getPositon().x, inputTextbox[i + 1].getPositon().y - inputTextbox[i + 1].getGlobalBounds().height});
		inputTextbox[i].setConstText(std::to_string(i) + "   ");
		inputTextbox[i].setLimit(true, 38);
		inputTextbox[i].setBox(sf::Vector2f(400, 30), BeigeGrey);
		inputTextbox[i].setLineBoundingBox(DarkBeigeGrey);
	}

	initTextbox(shortestPathTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + settingsButton.getPositon().x + settingsButton.getGlobalBounds().width, settingsButton.getPositon().y });
	shortestPathTextbox.setConstText("s = ");
	shortestPathTextbox.setLimit(true, 2);
}

void GraphMainState::initCodePanel()
{
	int numLine = 7;
	labelSize = sf::Vector2f(500, static_cast<float>((SCREEN_HEIGHT - 20 - checkpointY) / numLine));
	codePanel = Panel(sf::Vector2f{ SCREEN_WIDTH - 10 - labelSize.x,  checkpointY }, labelSize, textColor, LavenderSoft, m_context->assetManager->getFont("JetBrainsMono-Regular"), 18);
	codePanel.add("insert v");
	codePanel.add("for i");
	codePanel.add("");
	codePanel.add("");
	codePanel.add("");
	codePanel.add("");
	codePanel.add("");
}

void GraphMainState::initTheme()
{
	*m_context->themeType ^= 1;
	themeButton = ImageButton(m_context->assetManager->getTexture("LightTheme"), 1.0f, 1.0f);
	switchTheme();
	themeButton.setPosition(sf::Vector2f{ 1450, 30 });
}

void GraphMainState::initTitle()
{
	title.setCharacterSize(34);
	title.setFont(m_context->assetManager->getFont("Oswald"));
	title.setString("Graph");
	homeButton = ImageButton(m_context->assetManager->getTexture("HomeButton"), 1.0f, 1.0f);
	homeButton.setPosition(sf::Vector2f{ (SCREEN_WIDTH - title.getGlobalBounds().width) / 2 - homeButton.getGlobalBounds().width - 15, 10 });

	title.setFillColor(textColor);
	title.setPosition((SCREEN_WIDTH - title.getGlobalBounds().width) / 2, homeButton.getPosition().y + (homeButton.getGlobalBounds().height - title.getCharacterSize()) / 2);

}

void GraphMainState::initSpeedSlider()
{
	speedSlider = Slider(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - 300) / 2, playButton.getPosition().y + playButton.getGlobalBounds().height + 15 }, sf::Vector2f{ 300, 15.f }, sf::Vector2f{ 20, 20 });
	speedSlider.setColor(LightGray, NavyBlue, GoldenOrange);
	speedSlider.setNumPart(7);
	speedSlider.setText("0.5x", "1.0x", 20, m_context->assetManager->getFont("Neon"), textColor);
	speedSlider.setPart(1);
}

void GraphMainState::initAniSlider()
{
	checkpointY = 650;
	aniSlider = Slider(sf::Vector2f{ buttonSize.x + 50, checkpointY }, sf::Vector2f{ SCREEN_WIDTH - 10 - labelSize.x - buttonSize.x - 100, 20.f }, sf::Vector2f{ 20, 20 });
	aniSlider.setColor(LightGray, RoyalBlue, Gold);

	playButton = ImageButton(m_context->assetManager->getTexture("Play"), 1.0f, 1.0f);
	playButton.setPosition(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - playButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15 });

	previousButton = ImageButton(m_context->assetManager->getTexture("Previous"), 1.0f, 1.0f);
	previousButton.setPosition(sf::Vector2f{ playButton.getPosition().x - previousButton.getGlobalBounds().width, playButton.getPosition().y });

	rewindButton = ImageButton(m_context->assetManager->getTexture("Rewind"), 1.0f, 1.0f);
	rewindButton.setPosition(sf::Vector2f{ previousButton.getPosition().x - rewindButton.getGlobalBounds().width, playButton.getPosition().y });

	nextButton = ImageButton(m_context->assetManager->getTexture("Next"), 1.0f, 1.0f);
	nextButton.setPosition(sf::Vector2f{ playButton.getPosition().x + playButton.getGlobalBounds().width, playButton.getPosition().y });

	forwardButton = ImageButton(m_context->assetManager->getTexture("Forward"), 1.0f, 1.0f);
	forwardButton.setPosition(sf::Vector2f{ nextButton.getPosition().x + nextButton.getGlobalBounds().width, playButton.getPosition().y });

	replayButton = ImageButton(m_context->assetManager->getTexture("Replay"), 1.0f, 1.0f);
	replayButton.setPosition(sf::Vector2f{ -1000, -1000 });

	pauseButton = ImageButton(m_context->assetManager->getTexture("Pause"), 1.0f, 1.0f);
	pauseButton.setPosition(sf::Vector2f{ -1000, -1000 });
}

void GraphMainState::initButton(Button& button, std::string text, sf::Vector2f pos) {
	button = Button(text, buttonSize, 20, normalButtonColor, textColor);
	button.setFont(m_context->assetManager->getFont("Oswald"));
	button.setPosition(pos);
}

GraphMainState::GraphMainState(std::shared_ptr<Context>& context) : m_context(context)
{

	// Init theme
	initTheme();

	// Init title
	initTitle();

	// Init button
	initFunctionButton();

	// Init code panel
	initCodePanel();

	// Init Animation slider
	initAniSlider();

	// Init speed slider
	initSpeedSlider();
	
	// Init graph
	fGraph.init(20, 3.5f, m_context->assetManager->getFont("JetBrainsMono-Regular"), textColor);
	setDirected(isDirected);
	setFixed(isFixed);
	graph.init();
}

GraphMainState::~GraphMainState()
{
	for (auto& frame : frames) frame.clear();
	frames.clear();
	breakpoints.clear();
	mstArrs.clear();
	spArrs.clear();
	graph.reset();
	fGraph.reset();
}

void GraphMainState::init()
{



}

void GraphMainState::pause()
{

}

void GraphMainState::resume()
{

}

void GraphMainState::processEvents()
{
	sf::Event event;

	while (m_context->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->window->close();
			return;
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space && !isSelectedInputButton)
			{
				if (isEnd == false)
					isPaused ^= 1;
			}

		}
		handleSpeedSliderEvents(event);
		handleButtonEvents(event);
		handleAniSliderEvents(event);
		fGraph.handleEvent(event, *m_context->window);
	}

	createTextboxN.handleCursor();
	createTextboxE.handleCursor();
	shortestPathTextbox.handleCursor();
	for (int i = 0; i < numMatrix; i++) {
		inputTextbox[i].handleCursor();
	}
}

void GraphMainState::update(const sf::Time& dt)
{

	pauseButton.setPosition(sf::Vector2f(-1000, -1000));
	playButton.setPosition(sf::Vector2f(-1000, -1000));
	replayButton.setPosition(sf::Vector2f(-1000, -1000));

	if (isEnd == true)
		replayButton.setPosition(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - replayButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15 });
	else if (isPaused == true)
		playButton.setPosition(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - playButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15 });
	else
		pauseButton.setPosition(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - pauseButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15 });



	if (isPaused == false && isPlaying == true)
		aniSlider.setPart(currentFrameIndex + 1);

	if (isPaused == true && isPlaying == true)
	{
		int part = aniSlider.getPartIndex();
		currentFrameIndex = part;

	}

	fGraph.update(dt.asSeconds());
	fGraph.setPositionBeforeDrawing();
	for (int i = 0; i < (int)frames.size(); i++) {
		for (int j = 0; j < (int)fGraph.numNodes; j++) {
			frames[i].getNode("1nodes" + std::to_string(j)).setPosition(fGraph.nodes[j].node.position);
			frames[i].getNode("1nodes" + std::to_string(j)).setTextUnderPosition();
		}
		for (int j = 0; j < (int)fGraph.numEdges; j++) {
			if (j == tmpEdgeIndex && isSelectedShortestPathFrames) {
				sf::Vector2f start = fGraph.edges[tmpEdgeIndex].edge.getStart();
				sf::Vector2f end = fGraph.edges[tmpEdgeIndex].edge.getEnd();
				float t = static_cast<float>(i + 1) / 59;
				tmpEdge.setStart(start);
				tmpEdge.setEnd(start + t * (end - start));
				frames[i].addEdge("9tmpedges999", tmpEdge);
			}
			frames[i].getEdge("2edges" + std::to_string(j)).setStart(fGraph.edges[j].edge.getStart());
			frames[i].getEdge("2edges" + std::to_string(j)).setEnd(fGraph.edges[j].edge.getEnd());
		}
	}
	updateFrames();
}

void GraphMainState::draw()
{

	m_context->window->clear(backgroundColor);
	m_context->window->draw(title);

	
	settingsButton.drawTo(*m_context->window);
	createButton.drawTo(*m_context->window);
	inputButton.drawTo(*m_context->window);
	mstButton.drawTo(*m_context->window);
	shortestPathButton.drawTo(*m_context->window);
	fixedButton.drawTo(*m_context->window);
	unfixedButton.drawTo(*m_context->window);
	directedButton.drawTo(*m_context->window);
	undirectedButton.drawTo(*m_context->window);


	themeButton.drawTo(*m_context->window);
	homeButton.drawTo(*m_context->window);

	aniSlider.draw(*m_context->window);
	speedSlider.draw(*m_context->window);

	playButton.drawTo(*m_context->window);
	previousButton.drawTo(*m_context->window);
	nextButton.drawTo(*m_context->window);
	rewindButton.drawTo(*m_context->window);
	forwardButton.drawTo(*m_context->window);
	replayButton.drawTo(*m_context->window);
	pauseButton.drawTo(*m_context->window);

	createTextboxN.drawTo(*m_context->window);
	createTextboxE.drawTo(*m_context->window);
	shortestPathTextbox.drawTo(*m_context->window);
	randomButton.drawTo(*m_context->window);
	randomButton1.drawTo(*m_context->window);
	okButtonBackground.drawTo(*m_context->window);
	okButton.drawTo(*m_context->window);
	for (int i = 0; i < numMatrix; i++) {
		inputTextbox[i].drawTo(*m_context->window);
	}
	uploadFileButton.drawTo(*m_context->window);

	if (isSelectedMstFrames || isSelectedShortestPathFrames) {
		codePanel.draw(*m_context->window);
	}
	if (isEnd || (!isSelectedMstFrames && !isSelectedShortestPathFrames)) {
		if(isSelectedMstFrames || isSelectedShortestPathFrames) codePanel.draw(*m_context->window);
		fGraph.draw(*m_context->window);
	}
	if (!isEnd) {
		currentFrame.drawAll(*m_context->window);
	}
	m_context->window->display();

}

void GraphMainState::initTextbox(Textbox& textbox, int charSize, sf::Color textColor, sf::Font& font, sf::Vector2f pos)
{
	textbox = Textbox(charSize, textColor, false);
	textbox.setFont(m_context->assetManager->getFont("JetBrainsMono-SemiBold"));
	textbox.setPosition(pos);
	textbox.setBox(sf::Vector2f{ 200, buttonSize.y }, BeigeGrey);
	textbox.setLimit(true, 9);
}

void GraphMainState::handleHomeButtonEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (homeButton.isMouseOverCircle(*m_context->window))
		{
			m_context->stateMachine->removeState();
		}
	}
}

void GraphMainState::handleThemeButtonEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (themeButton.isMouseOver(*m_context->window)) {
			switchTheme();
		}
	}
}

void GraphMainState::handleAniSliderEvents(sf::Event event)
{
	if (numFrames == 0) return;
	aniSlider.setNumPart(numFrames);

	if (isPlaying == false)
		return;

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (nextButton.isMouseOverCircle(*m_context->window)) {
			isPaused = true;
			for (int x : breakpoints)
				if (x > currentFrameIndex) {
					currentFrameIndex = x;
					break;
				}
			aniSlider.setPart(currentFrameIndex);
		}
		if (previousButton.isMouseOverCircle(*m_context->window)) {
			isPaused = true;
			for (int i = breakpoints.size() - 1; i >= 0; i--) {
				if (breakpoints[i] < currentFrameIndex) {
					currentFrameIndex = breakpoints[i];
					break;
				}
			}
			aniSlider.setPart(currentFrameIndex);

		}
		if (forwardButton.isMouseOverCircle(*m_context->window)) {
			isPaused = true;
			currentFrameIndex = numFrames - 1;
			aniSlider.setPart(numFrames);
		}
		if (rewindButton.isMouseOverCircle(*m_context->window)) {
			isPaused = true;
			currentFrameIndex = 0;
			aniSlider.setPart(0);
		}
		if (pauseButton.isMouseOverCircle(*m_context->window))
		{
			isPaused = true;
		}
		if (playButton.isMouseOverCircle(*m_context->window))
		{
			isPaused = false;
		}
		if (replayButton.isMouseOverCircle(*m_context->window))
		{
			isEnd = false;
			isPaused = false;
			currentFrameIndex = 0;
			aniSlider.setPart(0);
		}
		if (aniSlider.isMouseOverWindow(*m_context->window) == true)
		{
			isPaused = true;
			aniSlider.handleEvent(event);
			currentFrameIndex = aniSlider.getPartIndex();
			return;
		}
	}
	aniSlider.handleEvent(event);
	currentFrameIndex = aniSlider.getPartIndex();
}

void GraphMainState::handleSpeedSliderEvents(sf::Event event)
{
	speedSlider.handleEvent(event);
	std::string st;
	int curSpeed = speedSlider.getPartIndex();
	if (curSpeed == 0) st = "0.5x";
	if (curSpeed == 1) st = "1.0x";
	if (curSpeed == 2) st = "1.5x";
	if (curSpeed == 3) st = "2.0x";
	if (curSpeed == 4) st = "2.5x";
	if (curSpeed == 5) st = "3.0x";
	if (curSpeed == 6) st = "3.5x";
	if (curSpeed == 7) st = "4.0x";
	speedSlider.setMaxText(st);
	*m_context->TIME_PER_FRAME = sf::seconds(1.f / 60.f / m_context->timeScale->at(curSpeed));
}

void GraphMainState::setDirected(bool directed)
{
	isDirected = directed;
	if (isDirected) {
		directedButton.setBackColor(DarkBeigeGrey);
		undirectedButton.setBackColor(BeigeGrey);
	}
	else {
		directedButton.setBackColor(BeigeGrey);
		undirectedButton.setBackColor(DarkBeigeGrey);
		
	}
	graph.setDirected(isDirected);
	fGraph.setDirected(isDirected);
}

void GraphMainState::setFixed(bool fixed)
{
	isFixed = fixed;
	if (isFixed) {
		fixedButton.setBackColor(DarkBeigeGrey);
		unfixedButton.setBackColor(BeigeGrey);
	}
	else {
		fixedButton.setBackColor(BeigeGrey);
		unfixedButton.setBackColor(DarkBeigeGrey);
	}
	fGraph.setFixed(isFixed);
}

void GraphMainState::hideObject()
{
	okButton.setPosition(sf::Vector2f{ -1000, -1000 });
	okButtonBackground.setPosition(sf::Vector2f{ -1000, 1000 });
	directedButton.setPosition(sf::Vector2f{ -1000, -1000 });
	undirectedButton.setPosition(sf::Vector2f{ -1000, -1000 });
	fixedButton.setPosition(sf::Vector2f{ -1000, -1000 });
	unfixedButton.setPosition(sf::Vector2f{ -1000, -1000 });
}

sf::Vector2f GraphMainState::randomNodePosition()
{
	return sf::Vector2f(Utils::rand(500, 1000), Utils::rand(150, 450));
}

void GraphMainState::handleButtonEvents(const sf::Event& event)
{
	handleMstButtonEvents(event);
	handleSettingsButtonEvents(event);
	handleShortestPathButtonEvents(event);
	handleCreateButtonEvents(event);
	handleInputButtonEvents(event);
	handleHomeButtonEvents(event);
	handleThemeButtonEvents(event);
}

void GraphMainState::handleSettingsButtonEvents(const sf::Event event)
{
	settingsButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (settingsButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedSettingsButton ^= 1;
		isSelectedCreateButton = false;
		isSelectedInputButton = false;
		isSelectedMstButton = false;
		isSelectedShortestPathButton = false;
	}

	if (isSelectedSettingsButton) {
		hideObject();
		settingsButton.setBackColor(hoverButtonColor);

		fixedButton.setPosition(sf::Vector2f(5 + settingsButton.getPositon().x + settingsButton.getGlobalBounds().width, settingsButton.getPositon().y));
		unfixedButton.setPosition(sf::Vector2f(fixedButton.getPositon().x + fixedButton.getGlobalBounds().width, settingsButton.getPositon().y));
		directedButton.setPosition(sf::Vector2f(5 + settingsButton.getPositon().x + settingsButton.getGlobalBounds().width, fixedButton.getPositon().y + fixedButton.getGlobalBounds().height));
		undirectedButton.setPosition(sf::Vector2f(fixedButton.getPositon().x + fixedButton.getGlobalBounds().width, fixedButton.getPositon().y + fixedButton.getGlobalBounds().height));
		
		if (undirectedButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			setDirected(false);
		}

		if (directedButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			setDirected(true);
		}

		if (unfixedButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			setFixed(false);
		}

		if (fixedButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			setFixed(true);
		}
		
	}
	else {
		directedButton.setPosition(sf::Vector2f{ -1000, -1000 });
		undirectedButton.setPosition(sf::Vector2f{ -1000, -1000 });
		fixedButton.setPosition(sf::Vector2f{ -1000, -1000 });
		unfixedButton.setPosition(sf::Vector2f{ -1000, -1000 });
		if (!isSelectedSettingsButton && !isSelectedCreateButton && !isSelectedInputButton && !isSelectedMstButton && !isSelectedShortestPathButton) {
			hideObject();
		}
	}
}

void GraphMainState::handleCreateButtonEvents(sf::Event event)
{
	createButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (createButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedSettingsButton = false;
		isSelectedCreateButton ^= 1;
		isSelectedInputButton = false;
		isSelectedMstButton = false;
		isSelectedShortestPathButton = false;
	}

	if (isSelectedCreateButton) {
		createButton.setBackColor(hoverButtonColor);
		createTextboxN.setVisible();
		createTextboxE.setVisible();

		randomButton.setPosition(sf::Vector2f{ createTextboxN.getPositon().x + createTextboxN.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, createTextboxN.getPositon().y });
		randomButton1.setPosition(sf::Vector2f{ createTextboxE.getPositon().x + createTextboxE.getGlobalBounds().width - randomButton1.getGlobalBounds().width - 5, createTextboxE.getPositon().y });
		okButtonBackground.setPosition(sf::Vector2f{ createTextboxE.getPositon().x, createTextboxE.getPositon().y + createTextboxE.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ createTextboxE.getPositon().x + (createTextboxE.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, createTextboxE.getPositon().y + createTextboxE.getGlobalBounds().height });

		createTextboxN.typedOnNum(event, *m_context->window);
		createTextboxE.typedOnNum(event, *m_context->window);

		if(randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = Utils::rand(1, 12);
			createTextboxN.insertNum(randomNum);
		}

		if (randomButton1.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = Utils::rand(4, 20);
			createTextboxE.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			int n = createTextboxN.getNum();
			createTextboxN.reset();
			createTextboxN.setSelected(false);
			int e = createTextboxE.getNum();
			createTextboxE.reset();
			createTextboxE.setSelected(false);

			// Build graph
			
			deleteOldFrames();
			fGraph.reset();
			graph.reset();
			for (int i = 1; i <= n; i++) {
				fGraph.addNode(randomNodePosition(), std::to_string(i));
			}
			fGraph.setFixed(isFixed);
			if (isDirected) e = std::min(e, n * (n - 1));
			else e = std::min(e, n * (n - 1) / 2);

			for (int i = 1; i <= e; i++) {
				if (n < 2) break;
				int u, v;
				while (1) {
					u = Utils::rand(1, n - 1);
					v = Utils::rand(u + 1, n);
					if (Utils::rand(0, 1)) std::swap(u, v);
					if (!graph.hasEdge(u, v)) break;
				}
				int w = Utils::rand(1, 20);
				fGraph.addEdge(u, v, w, isDirected);
				graph.addEdge(u, v, w, isDirected);
			}
		}
	}
	else {
		createTextboxN.setSelected(false);
		createTextboxN.setInvisible();
		createTextboxE.setSelected(false);
		createTextboxE.setInvisible();
		randomButton1.setPosition(sf::Vector2f(-1000, -1000));
		if (!isSelectedSettingsButton && !isSelectedCreateButton && !isSelectedInputButton && !isSelectedMstButton && !isSelectedShortestPathButton) {
			hideObject();
		}
	}
}

void GraphMainState::handleInputButtonEvents(sf::Event event)
{
	inputButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (inputButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedSettingsButton = false;
		isSelectedCreateButton = false;
		isSelectedInputButton ^= 1;
		isSelectedMstButton = false;
		isSelectedShortestPathButton = false;
	}

	if (isSelectedInputButton) {
		inputButton.setBackColor(hoverButtonColor);
		for (int i = 0; i < numMatrix; i++) {
			inputTextbox[i].setVisible();
		}
		
		uploadFileButton.setPosition(sf::Vector2f(inputTextbox[0].getPositon().x + inputTextbox[0].getGlobalBounds().width - uploadFileButton.getGlobalBounds().width - 5, inputTextbox[numMatrix - 1].getPositon().y + inputTextbox[numMatrix - 1].getGlobalBounds().height));
		okButtonBackground.setSize(sf::Vector2f(inputTextbox[0].getGlobalBounds().width, buttonSize.y));
		okButtonBackground.setPosition(sf::Vector2f( 5 + settingsButton.getPositon().x + settingsButton.getGlobalBounds().width, inputTextbox[numMatrix - 1].getPositon().y + inputTextbox[numMatrix - 1].getGlobalBounds().height));
		okButton.setPosition(sf::Vector2f{ inputTextbox[numMatrix - 1].getPositon().x + (inputTextbox[numMatrix - 1].getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, inputTextbox[numMatrix - 1].getPositon().y + inputTextbox[numMatrix - 1].getGlobalBounds().height});

		for (int i = 0; i < numMatrix; i++) {
			inputTextbox[i].typedOnMatrix(event, *m_context->window);
		}

		

		// Load file
		if (uploadFileButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			auto selection = pfd::open_file("Select a file", "", { "All Files", "*" }).result();

			if (!selection.empty()) {  // Check if the user selected a file
				std::string filename = selection[0];  // Get the file path

				std::ifstream fileIn(filename);
					
				deleteAllFrames();
				graph.reset();
				fGraph.reset();
				if (fileIn.is_open()) {
					int n;
					fileIn >> n;
					for (int i = 1; i <= n; i++) {
						fGraph.addNode(randomNodePosition(), std::to_string(i));
					}
					for (int i = 1; i <= n; i++) {
						for (int j = 1; j <= n; j++) {
							int weight;
							fileIn >> weight;
							if (i == j) continue;
							if (weight == 0) continue;
							fGraph.addEdge(i, j, weight, isDirected);
							graph.addEdge(i, j, weight, isDirected);
						}
					}
				}
				else {
					std::cerr << "Cant open the file\n";
				}
				fileIn.close();
			}
			else {
				std::cout << "No file selected." << std::endl;
			}
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			int n = 0;
			std::vector<std::vector<int>> c;
			std::string st = inputTextbox[0].getText();
			for (auto ch : st) {
				if ('0' <= ch && ch <= '9') {
					n = n * 10 + ch - '0';
				}
				else break;
			}
			c.resize(n);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					c[i].push_back(0);
				}
			}

			for (int i = 1; i < std::min(n + 1, numMatrix); i++) {
				std::string st = inputTextbox[i].getText();
				int num = 0;
				bool notNum = true;
				int j = 0;
				for (auto ch : st) {
					if ('0' <= ch && ch <= '9') {
						num = num * 10 + ch - '0';
						notNum = false;
					}
					else {
						if(j < n) c[i - 1][j++] = num;
						notNum = true;
						num = 0;
					}
				}
				if (notNum == false) {
					if(j < n) c[i - 1][j++] = num;
				}
			}

			for (int i = 0; i < numMatrix; i++) {
				inputTextbox[i].reset();
				inputTextbox[i].setSelected(false);
			}

			deleteAllFrames();
			graph.reset();
			fGraph.reset();
			for (int i = 1; i <= n; i++) {
				fGraph.addNode(randomNodePosition(), std::to_string(i));
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) continue;
					if (c[i][j] == 0) continue;
					fGraph.addEdge(i + 1, j + 1, c[i][j], isDirected);
					graph.addEdge(i + 1, j + 1, c[i][j], isDirected);
				}
			}
		}
	}
	else {
		for (int i = 0; i < numMatrix; i++) {
			inputTextbox[i].setSelected(false);
			inputTextbox[i].setInvisible();
		}
		okButtonBackground.setSize(sf::Vector2f{ 200, buttonSize.y });
		uploadFileButton.setPosition(sf::Vector2f(-1000, -1000));
		if (!isSelectedSettingsButton && !isSelectedCreateButton && !isSelectedInputButton && !isSelectedMstButton && !isSelectedShortestPathButton) {
			hideObject();
		}
	}
}

void GraphMainState::handleMstButtonEvents(sf::Event event)
{
	mstButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (mstButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedSettingsButton = false;
		isSelectedCreateButton = false;
		isSelectedInputButton = false;
		isSelectedMstButton ^= 1;
		isSelectedShortestPathButton = false;
	}

	if (isSelectedMstButton) {
		mstButton.setBackColor(hoverButtonColor);
		okButtonBackground.setPosition(sf::Vector2f{ sf::Vector2f{ 5 + settingsButton.getPositon().x + settingsButton.getGlobalBounds().width, settingsButton.getPositon().y } });
		okButton.setPosition(sf::Vector2f{ createTextboxN.getPositon().x + (createTextboxN.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, settingsButton.getPositon().y });

		if (((okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))) {
			setDirected(false);
			preInitMstFrames();
		}
	}
	else {
		if (!isSelectedSettingsButton && !isSelectedCreateButton && !isSelectedInputButton && !isSelectedMstButton && !isSelectedShortestPathButton) {
			hideObject();
		}
	}
}

void GraphMainState::handleShortestPathButtonEvents(sf::Event event)
{
	shortestPathTextbox.setLimNum((int) fGraph.numNodes);
	shortestPathButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (shortestPathButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedSettingsButton = false;
		isSelectedCreateButton = false;
		isSelectedInputButton = false;
		isSelectedMstButton = false;
		isSelectedShortestPathButton ^= 1;
	}

	if (isSelectedShortestPathButton) {
		shortestPathButton.setBackColor(hoverButtonColor);
		shortestPathTextbox.setVisible();

		randomButton.setPosition(sf::Vector2f{ shortestPathTextbox.getPositon().x + shortestPathTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, shortestPathTextbox.getPositon().y });
		okButtonBackground.setPosition(shortestPathTextbox.getPositon() + sf::Vector2f(0, shortestPathTextbox.getGlobalBounds().height));
		okButton.setPosition(sf::Vector2f{ shortestPathTextbox.getPositon().x + (createTextboxN.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, shortestPathTextbox.getPositon().y + shortestPathTextbox.getGlobalBounds().height});

		shortestPathTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = Utils::rand(1, (int) fGraph.numNodes);
			shortestPathTextbox.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || ((okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))) {
			source = shortestPathTextbox.getNum();
			shortestPathTextbox.reset();
			shortestPathTextbox.setSelected(false);

			//do sth
			if(0 < source && source <= (int) fGraph.numNodes) preInitShortestPathFrames(source);
		}
	}
	else {
		shortestPathTextbox.setSelected(false);
		shortestPathTextbox.setInvisible();
		randomButton.setPosition(sf::Vector2f(-1000, -1000));
		if (!isSelectedSettingsButton && !isSelectedCreateButton && !isSelectedInputButton && !isSelectedMstButton && !isSelectedShortestPathButton) {
			hideObject();
		}
	}
}
