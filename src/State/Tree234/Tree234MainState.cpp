#include "Tree234MainState.h"

void Tree234MainState::switchTheme() {
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
		searchButton.setTextColor(textColor);
		speedSlider.setTextColor(textColor);
		title.setFillColor(textColor);
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
		searchButton.setTextColor(textColor);
		speedSlider.setTextColor(textColor);
		title.setFillColor(textColor);
	}
}

void Tree234MainState::initFunctionButton() {
	buttonSize.x = 120;
	buttonSize.y = 40;
	checkpointY = 650;
	float firstButtonY = checkpointY + 30;
	initButton(createButton, "Create", sf::Vector2f{ 10, firstButtonY });
	initButton(insertButton, "Insert", sf::Vector2f{ 10, firstButtonY + buttonSize.y });
	initButton(deleteButton, "Delete", sf::Vector2f{ 10, firstButtonY + 2 * buttonSize.y });
	initButton(searchButton, "Search", sf::Vector2f{ 10, firstButtonY + 3 * buttonSize.y });

	randomButton = ImageButton(m_context->assetManager->getTexture("Random"), 1.f, 1.f);
	uploadFileButton = ImageButton(m_context->assetManager->getTexture("UploadFile"), 1.f, 1.f);
	okButton = ImageButton(m_context->assetManager->getTexture("Ok"), 1.f, 1.f);

	uploadFileButton.setPosition(sf::Vector2f{ -1000, -1000 });
	randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
	okButton.setPosition(sf::Vector2f{ -1000, -1000 });
	okButtonBackground = Label("", 0, sf::Vector2f{ 200, buttonSize.y }, DarkBeigeGrey, textColor, m_context->assetManager->getFont("arial"));
	okButtonBackground.setPosition(sf::Vector2f{ -1000, -1000 });

	initTextbox(insertTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	insertTextbox.setConstText("v = ");

	initTextbox(deleteTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	deleteTextbox.setConstText("v = ");

	initTextbox(createTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	createTextbox.setConstText("n = ");
	createTextbox.setLimit(true, 3);

	initTextbox(searchTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	searchTextbox.setConstText("v = ");
	searchTextbox.setLimit(true, 3);

}

void Tree234MainState::initCodePanel()
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
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 7; j++) {
			codePanelColor[i][j] = LavenderSoft;
		}
	}
}

void Tree234MainState::initTheme()
{
	*m_context->themeType ^= 1;
	themeButton = ImageButton(m_context->assetManager->getTexture("LightTheme"), 1.0f, 1.0f);
	switchTheme();
	themeButton.setPosition(sf::Vector2f{ 1450, 30 });
}

void Tree234MainState::initTitle()
{
	title.setCharacterSize(34);
	title.setFont(m_context->assetManager->getFont("Oswald"));
	title.setString("2-3-4 Tree");
	homeButton = ImageButton(m_context->assetManager->getTexture("HomeButton"), 1.0f, 1.0f);
	homeButton.setPosition(sf::Vector2f{ (SCREEN_WIDTH - title.getGlobalBounds().width) / 2 - homeButton.getGlobalBounds().width - 15, 10 });

	title.setFillColor(textColor);
	title.setPosition((SCREEN_WIDTH - title.getGlobalBounds().width) / 2, homeButton.getPosition().y + (homeButton.getGlobalBounds().height - title.getCharacterSize()) / 2);

}

void Tree234MainState::initSpeedSlider()
{
	speedSlider = Slider(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - 300) / 2, playButton.getPosition().y + playButton.getGlobalBounds().height + 15 }, sf::Vector2f{ 300, 15.f }, sf::Vector2f{ 20, 20 });
	speedSlider.setColor(LightGray, NavyBlue, GoldenOrange);
	speedSlider.setNumPart(6);
	speedSlider.setText("1.0x", "1.0x", 20, m_context->assetManager->getFont("Neon"), textColor);
}

void Tree234MainState::initAniSlider()
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

void Tree234MainState::initButton(Button& button, std::string text, sf::Vector2f pos) {
	button = Button(text, buttonSize, 20, normalButtonColor, textColor);
	button.setFont(m_context->assetManager->getFont("Oswald"));
	button.setPosition(pos);
}

Tree234MainState::Tree234MainState(std::shared_ptr<Context>& context) : m_context(context)
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

	// Init node and edge
	NodePos = sf::Vector2f(SCREEN_WIDTH / 2, homeButton.getPosition().y + homeButton.getGlobalBounds().height + 50);
}

Tree234MainState::~Tree234MainState()
{
}

void Tree234MainState::init()
{



}

void Tree234MainState::pause()
{

}

void Tree234MainState::resume()
{

}

void Tree234MainState::processEvents()
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
			if (event.key.code == sf::Keyboard::Space)
			{
				if (isEnd == false)
					isPaused ^= 1;
			}

		}
		handleSpeedSliderEvents(event);
		handleButtonEvents(event);
		handleAniSliderEvents(event);
	}

	createTextbox.handleCursor();
	insertTextbox.handleCursor();
	deleteTextbox.handleCursor();
	searchTextbox.handleCursor();
}

void Tree234MainState::update(const sf::Time& dt)
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
	updateFrames();
}

void Tree234MainState::draw()
{

	m_context->window->clear(backgroundColor);
	m_context->window->draw(title);
	createButton.drawTo(*m_context->window);
	insertButton.drawTo(*m_context->window);
	deleteButton.drawTo(*m_context->window);
	searchButton.drawTo(*m_context->window);


	themeButton.drawTo(*m_context->window);
	homeButton.drawTo(*m_context->window);
	//codePanel.draw(*m_context->window);

	aniSlider.draw(*m_context->window);
	speedSlider.draw(*m_context->window);

	playButton.drawTo(*m_context->window);
	previousButton.drawTo(*m_context->window);
	nextButton.drawTo(*m_context->window);
	rewindButton.drawTo(*m_context->window);
	forwardButton.drawTo(*m_context->window);
	replayButton.drawTo(*m_context->window);
	pauseButton.drawTo(*m_context->window);

	insertTextbox.drawTo(*m_context->window);
	deleteTextbox.drawTo(*m_context->window);
	createTextbox.drawTo(*m_context->window);
	searchTextbox.drawTo(*m_context->window);
	randomButton.drawTo(*m_context->window);
	uploadFileButton.drawTo(*m_context->window);
	okButtonBackground.drawTo(*m_context->window);
	okButton.drawTo(*m_context->window);
	
	currentFrame.drawAll(*m_context->window);
	if (isSelectedDeleteFrames || isSelectedInsertFrames || isSelectedSearchFrames) {
		codePanel.draw(*m_context->window);
	}
	m_context->window->display();

}

void Tree234MainState::initTextbox(Textbox& textbox, int charSize, sf::Color textColor, sf::Font& font, sf::Vector2f pos)
{
	textbox = Textbox(charSize, textColor, false);
	textbox.setFont(m_context->assetManager->getFont("JetBrainsMono-SemiBold"));
	textbox.setPosition(pos);
	textbox.setBox(sf::Vector2f{ 200, buttonSize.y }, BeigeGrey);
	textbox.setLimit(true, 9);
}


void Tree234MainState::handleInsertButtonEvents(sf::Event event)
{
	insertButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (insertButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton ^= 1;
		isSelectedDeleteButton = false;
		isSelectedSearchButton = false;
	}

	if (isSelectedInsertButton) {
		insertButton.setBackColor(hoverButtonColor);
		insertTextbox.setVisible();

		randomButton.setPosition(sf::Vector2f{ insertTextbox.getPositon().x + insertTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, insertTextbox.getPositon().y });
		okButtonBackground.setPosition(sf::Vector2f{ insertTextbox.getPositon().x, insertTextbox.getPositon().y + insertTextbox.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ insertTextbox.getPositon().x + (insertTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, insertTextbox.getPositon().y + insertTextbox.getGlobalBounds().height });

		insertTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = Utils::rand(0, 99);
			insertTextbox.insertNum(randomNum);
		}


		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
			(okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {

			insertValue = insertTextbox.getNum();
			insertTextbox.reset();
			insertTextbox.setSelected(false);
			
			// do sth
			preInitInsertFrames(insertValue);
		}
	}
	else {
		insertTextbox.setSelected(false);
		insertTextbox.setInvisible();

		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButtonBackground.setPosition(sf::Vector2f{ -1000, 1000 });
		}
	}
}


void Tree234MainState::handleDeleteButtonEvents(sf::Event event)
{
	deleteButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (deleteButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton = false;
		isSelectedDeleteButton ^= 1;
		isSelectedSearchButton = false;
	}

	if (isSelectedDeleteButton) {
		deleteButton.setBackColor(hoverButtonColor);
		deleteTextbox.setVisible();
		randomButton.setPosition(sf::Vector2f{ deleteTextbox.getPositon().x + deleteTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, deleteTextbox.getPositon().y });
		okButtonBackground.setPosition(sf::Vector2f{ deleteTextbox.getPositon().x, deleteTextbox.getPositon().y + deleteTextbox.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ deleteTextbox.getPositon().x + (deleteTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, deleteTextbox.getPositon().y + deleteTextbox.getGlobalBounds().height });

		deleteTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = Utils::rand(0, 99);
			deleteTextbox.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			deleteValue = deleteTextbox.getNum();
			deleteTextbox.reset();
			// do sth
			preInitDeleteFrames(deleteValue);
		}
	}
	else {
		deleteTextbox.setSelected(false);
		deleteTextbox.setInvisible();
		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
		}
	}
}


void Tree234MainState::handleHomeButtonEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (homeButton.isMouseOverCircle(*m_context->window))
		{
			m_context->stateMachine->removeState();
		}
	}
}

void Tree234MainState::handleCreateButtonEvents(sf::Event event)
{
	createTextbox.setLimNum(40);
	createButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (createButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton ^= 1;
		isSelectedInsertButton = false;
		isSelectedDeleteButton = false;
		isSelectedSearchButton = false;
	}

	if (isSelectedCreateButton) {
		createButton.setBackColor(hoverButtonColor);
		createTextbox.setVisible();
		randomButton.setPosition(sf::Vector2f{ createTextbox.getPositon().x + createTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, createTextbox.getPositon().y });
		uploadFileButton.setPosition(sf::Vector2f{ randomButton.getPosition().x - uploadFileButton.getGlobalBounds().width - 5, createTextbox.getPositon().y });
		okButtonBackground.setPosition(sf::Vector2f{ createTextbox.getPositon().x, createTextbox.getPositon().y + createTextbox.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ createTextbox.getPositon().x + (createTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, createTextbox.getPositon().y + createTextbox.getGlobalBounds().height });

		createTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = Utils::rand(0, 63);
			createTextbox.insertNum(randomNum);
		}

		// Load file
		if (uploadFileButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			auto selection = pfd::open_file("Select a file", "", { "All Files", "*" }).result();

			if (!selection.empty()) {  // Check if the user selected a file
				std::string filename = selection[0];  // Get the file path

				std::ifstream fileIn(filename);

				if (fileIn.is_open()) {
					// handle file
					std::vector<int> nums;
					int num;
					while (fileIn >> num) {
						nums.push_back(num);
					}
					for (auto i : nums) std::cerr << i << "\n";
					while ((int)nums.size() > 63) {
						nums.pop_back();
					}
					createTextbox.insertNum((int)nums.size());
					//handle num list
					createTextbox.setSelected(false);
					createNums = nums;
					// do sth
					preInitCreateFrames(createNums);
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
			int num = createTextbox.getNum();
			std::cerr << "Random:" << num << std::endl;
			createTextbox.reset();
			// do sth
			std::vector<int> allElements;
			for (int i = 0; i < num; i++) {
				allElements.push_back(rand() % 100);
			}
			createNums = allElements;
			// do sth
			for (auto x : createNums) std::cerr << x << " ";
			std::cerr << "\n";
			preInitCreateFrames(createNums);

		}
	}
	else {
		createTextbox.setSelected(false);
		createTextbox.setInvisible();
		uploadFileButton.setPosition(sf::Vector2f{ -1000, -1000 });

		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
		}
	}
}

void Tree234MainState::handleSearchButtonEvents(sf::Event event)
{
	searchButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (searchButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton = false;
		isSelectedDeleteButton = false;
		isSelectedSearchButton ^= 1;
	}

	if (isSelectedSearchButton) {
		searchButton.setBackColor(hoverButtonColor);
		searchTextbox.setVisible();

		randomButton.setPosition(sf::Vector2f{ searchTextbox.getPositon().x + searchTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, searchTextbox.getPositon().y });
		okButtonBackground.setPosition(sf::Vector2f{ searchTextbox.getPositon().x, searchTextbox.getPositon().y + searchTextbox.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ searchTextbox.getPositon().x + (searchTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, searchTextbox.getPositon().y + searchTextbox.getGlobalBounds().height });

		searchTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = Utils::rand(0, 99);
			searchTextbox.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			searchValue = searchTextbox.getNum();
			searchTextbox.reset();
			searchTextbox.setSelected(false);

			// do sth
			preInitSearchFrames(searchValue);
		}
	}
	else {
		searchTextbox.setSelected(false);
		searchTextbox.setInvisible();

		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButtonBackground.setPosition(sf::Vector2f{ -1000, 1000 });
		}
	}
}

void Tree234MainState::handleThemeButtonEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (themeButton.isMouseOver(*m_context->window)) {
			switchTheme();
		}
	}
}

void Tree234MainState::handleAniSliderEvents(sf::Event event)
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

void Tree234MainState::handleSpeedSliderEvents(sf::Event event)
{
	speedSlider.handleEvent(event);
	std::string st = "1.0x";
	st[0] = char(speedSlider.getPartIndex() + 1 + '0');
	speedSlider.setMaxText(st);
	*m_context->TIME_PER_FRAME = sf::seconds(1.f / 60.f / static_cast<float>(speedSlider.getPartIndex() + 1));
}

void Tree234MainState::handleButtonEvents(const sf::Event& event)
{
	handleDeleteButtonEvents(event);
	handleInsertButtonEvents(event);
	handleSearchButtonEvents(event);
	handleCreateButtonEvents(event);
	handleHomeButtonEvents(event);
	handleThemeButtonEvents(event);

}

sf::Vector2f Tree234MainState::middlePoint(std::vector<int> &nodes)
{
	float lx = b_nodes[nodes.front()].getPosition().x -  b_nodes[nodes.front()].getGlobalBounds().width / 2;
	float ly = b_nodes[nodes.back()].getPosition().x + b_nodes[nodes.back()].getGlobalBounds().width / 2;
	return b_nodes[nodes.front()].getPosition() + sf::Vector2f((ly - lx) / 2.f - b_nodes[nodes.front()].getGlobalBounds().width / 2, -SIDE / 2);
}

void Tree234MainState::setEdgePos(Tree234::Node* par, Tree234::Node* cur, int id)
{
	b_edges[id].setStart(middlePoint(cur->nodes));
	w_edges[id].setStart(middlePoint(cur->nodes));
	if (cur == par->children[0]) {
		if (par->nodes.size() == 0) return;
		b_edges[id].setEnd(b_nodes[par->nodes[0]].getPosition() + sf::Vector2f(-SIDE / 2, SIDE / 2));
		w_edges[id].setEnd(w_nodes[par->nodes[0]].getPosition() + sf::Vector2f(-SIDE / 2, SIDE / 2));
	}
	if (cur == par->children[1]) {
		if (par->nodes.size() == 0) return;
		b_edges[id].setEnd(b_nodes[par->nodes[0]].getPosition() + sf::Vector2f(SIDE / 2, SIDE / 2));
		w_edges[id].setEnd(w_nodes[par->nodes[0]].getPosition() + sf::Vector2f(SIDE / 2, SIDE / 2));
	}
	if (cur == par->children[2]) {
		if (par->nodes.size() < 2) return;
		b_edges[id].setEnd(b_nodes[par->nodes[1]].getPosition() + sf::Vector2f(SIDE / 2, SIDE / 2));
		w_edges[id].setEnd(w_nodes[par->nodes[1]].getPosition() + sf::Vector2f(SIDE / 2, SIDE / 2));
	}
	if (cur == par->children[3]) {
		if (par->nodes.size() < 3) return;
		b_edges[id].setEnd(b_nodes[par->nodes[2]].getPosition() + sf::Vector2f(SIDE / 2, SIDE / 2));
		w_edges[id].setEnd(w_nodes[par->nodes[2]].getPosition() + sf::Vector2f(SIDE / 2, SIDE / 2));
	}
}

void Tree234MainState::initNode(Node &node, bool isDark)
{
	node.setShape(0);
	node.setSide(SIDE);
	node.setOutlineThickness(-3);
	node.setFillColor(sf::Color::White);
	node.setOutlineColor(isDark ? Orange : sf::Color::Red);
	node.setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
	node.setCharacterSize(20);
	node.setTextColor(sf::Color::Black);
}

void Tree234MainState::initEdge(Edge &edge, bool isDark	)
{
	edge.setColor(isDark ? sf::Color::White : sf::Color::Black);
	edge.setThickness(-3);
}
