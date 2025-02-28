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
		codePanel.setTextColor(textColor);
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
		codePanel.setTextColor(textColor);
	}
}

void SinglyLinkedListMainState::initFunctionButton() {
	buttonSize.x = 120;
	buttonSize.y = 40;
	checkpointY = 650;
	float firstButtonY = checkpointY + 30;
	initButton(createButton, "Create", sf::Vector2f{ 10, firstButtonY });
	initButton(insertButton, "Insert", sf::Vector2f{ 10, firstButtonY + buttonSize.y });
	initButton(deleteButton, "Delete", sf::Vector2f{ 10, firstButtonY + 2 * buttonSize.y });
	initButton(updateButton, "Update", sf::Vector2f{ 10, firstButtonY + 3 * buttonSize.y });
	initButton(searchButton, "Search", sf::Vector2f{ 10, firstButtonY + 4 * buttonSize.y });
	
	randomButton = ImageButton(m_context->assetManager->getTexture("Random"), 1.f, 1.f);
	randomUpdateButton = ImageButton(m_context->assetManager->getTexture("Random"), 1.f, 1.f);
	uploadFileButton = ImageButton(m_context->assetManager->getTexture("UploadFile"), 1.f, 1.f);
	okButton = ImageButton(m_context->assetManager->getTexture("Ok"), 1.f, 1.f);
	
	uploadFileButton.setPosition(sf::Vector2f{ -1000, -1000 });
	randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
	randomUpdateButton.setPosition(sf::Vector2f{ -1000, -1000 });
	okButton.setPosition(sf::Vector2f{ -1000, -1000 });
	okButtonBackground = Label("", 0, sf::Vector2f{ 200, buttonSize.y }, DarkBeigeGrey, textColor, m_context->assetManager->getFont("arial"));
	okButtonBackground.setPosition(sf::Vector2f{ -1000, -1000 });

	initTextbox(insertTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f {5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y});
	insertTextbox.setConstText("v = ");

	initTextbox(deleteTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	deleteTextbox.setConstText("v = ");

	initTextbox(searchTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	searchTextbox.setConstText("v = ");

	initTextbox(createTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	createTextbox.setConstText("n = ");
	createTextbox.setLimit(true, 2);

	initTextbox(updateTextboxX, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	updateTextboxX.setConstText("x = ");
	updateTextboxX.setLimit(true, 9);

	initTextbox(updateTextboxV, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, updateTextboxX.getPositon().y + updateTextboxX.getGlobalBounds().height});
	updateTextboxV.setConstText("v = ");
	updateTextboxV.setLimit(true, 9);
}

void SinglyLinkedListMainState::initCodePanel()
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

void SinglyLinkedListMainState::initTheme()
{
	*m_context->themeType ^= 1;
	themeButton = ImageButton(m_context->assetManager->getTexture("LightTheme"), 1.0f, 1.0f);
	switchTheme();
	themeButton.setPosition(sf::Vector2f{ 1450, 30 });
}

void SinglyLinkedListMainState::initTitle()
{
	title.setCharacterSize(34);
	title.setFont(m_context->assetManager->getFont("Oswald"));
	title.setString("SINGLY LINKED LIST");
	homeButton = ImageButton(m_context->assetManager->getTexture("HomeButton"), 1.0f, 1.0f);
	homeButton.setPosition(sf::Vector2f{ (SCREEN_WIDTH - title.getGlobalBounds().width) / 2 - homeButton.getGlobalBounds().width - 15, 10 });

	title.setFillColor(textColor);
	title.setPosition((SCREEN_WIDTH - title.getGlobalBounds().width) / 2, homeButton.getPosition().y + (homeButton.getGlobalBounds().height - title.getCharacterSize()) / 2);

}

void SinglyLinkedListMainState::initSpeedSlider()
{
	speedSlider = Slider(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - 300) / 2, playButton.getPosition().y + playButton.getGlobalBounds().height + 15 }, sf::Vector2f{ 300, 15.f }, sf::Vector2f{ 20, 20 });
	speedSlider.setColor(LightGray, NavyBlue, GoldenOrange);
	speedSlider.setNumPart(6);
	speedSlider.setText("1.0x", "1.0x", 20, m_context->assetManager->getFont("Neon"), textColor);
}

void SinglyLinkedListMainState::initAniSlider()
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

void SinglyLinkedListMainState::initButton(Button& button, std::string text, sf::Vector2f pos) {
	button = Button(text, buttonSize, 20, normalButtonColor, textColor);
	button.setFont(m_context->assetManager->getFont("Oswald"));
	button.setPosition(pos);
}

SinglyLinkedListMainState::SinglyLinkedListMainState(std::shared_ptr<Context>& context) : m_context(context)
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

		handleButtonEvents(event);
		handleAniSliderEvents(event);
		handleSpeedSliderEvents(event);

	}
	
	createTextbox.handleCursor();
	insertTextbox.handleCursor();
	deleteTextbox.handleCursor();
	searchTextbox.handleCursor();
	updateTextboxX.handleCursor();
	updateTextboxV.handleCursor();
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
	codePanel.draw(*m_context->window);

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
	searchTextbox.drawTo(*m_context->window);
	createTextbox.drawTo(*m_context->window);
	updateTextboxX.drawTo(*m_context->window);
	updateTextboxV.drawTo(*m_context->window);
	randomButton.drawTo(*m_context->window);
	randomUpdateButton.drawTo(*m_context->window);
	uploadFileButton.drawTo(*m_context->window);
	okButtonBackground.drawTo(*m_context->window);
	okButton.drawTo(*m_context->window);
	
	updateFrames();
	m_context->window->display();

}

void SinglyLinkedListMainState::initTextbox(Textbox& textbox, int charSize, sf::Color textColor, sf::Font& font, sf::Vector2f pos)
{
	textbox = Textbox(charSize, textColor, false);
	textbox.setFont(m_context->assetManager->getFont("JetBrainsMono-SemiBold"));
	textbox.setPosition(pos);
	textbox.setBox(sf::Vector2f{200, buttonSize.y}, BeigeGrey);
	textbox.setLimit(true, 9);
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
	insertButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (insertButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton ^= 1;
		isSelectedDeleteButton = false;
		isSelectedSearchButton = false;
		isSelectedUpdateButton = false;
	}

	if (isSelectedInsertButton) {
		insertButton.setBackColor(hoverButtonColor);
		insertTextbox.setVisible();
		randomButton.setPosition(sf::Vector2f{ insertTextbox.getPositon().x + insertTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, insertTextbox.getPositon().y});
		okButtonBackground.setPosition(sf::Vector2f {insertTextbox.getPositon().x, insertTextbox.getPositon().y + insertTextbox.getGlobalBounds().height});
		okButton.setPosition(sf::Vector2f {insertTextbox.getPositon().x + (insertTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, insertTextbox.getPositon().y + insertTextbox.getGlobalBounds().height});
		
		insertTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = std::rand() % 100 + 1;
			insertTextbox.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			int num = insertTextbox.getNum();
			insertTextbox.reset();
			// do sth
		}
	}
	else {
		insertTextbox.setSelected(false);
		insertTextbox.setInvisible();
		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButtonBackground.setPosition(sf::Vector2f{ -1000, 1000 });
		}
	}

}

void SinglyLinkedListMainState::handleDeleteButtonEvents(sf::Event event)
{
	deleteButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (deleteButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton = false;
		isSelectedDeleteButton ^= 1;
		isSelectedSearchButton = false;
		isSelectedUpdateButton = false;
	}

	if (isSelectedDeleteButton) {
		deleteButton.setBackColor(hoverButtonColor);
		deleteTextbox.setVisible();
		randomButton.setPosition(sf::Vector2f{ deleteTextbox.getPositon().x + deleteTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, deleteTextbox.getPositon().y });
		okButtonBackground.setPosition(sf::Vector2f{ deleteTextbox.getPositon().x, deleteTextbox.getPositon().y + deleteTextbox.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ deleteTextbox.getPositon().x + (deleteTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, deleteTextbox.getPositon().y + deleteTextbox.getGlobalBounds().height });
		
		deleteTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = std::rand() % 100 + 1;
			deleteTextbox.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			int num = deleteTextbox.getNum();
			deleteTextbox.reset();
			// do sth
		}
	}
	else {
		deleteTextbox.setSelected(false);
		deleteTextbox.setInvisible();
		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
		}
	}
}

void SinglyLinkedListMainState::handleSearchButtonEvents(sf::Event event)
{
	searchButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (searchButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton = false;
		isSelectedDeleteButton = false;
		isSelectedSearchButton ^= 1;
		isSelectedUpdateButton = false;
	}

	if (isSelectedSearchButton) {
		searchButton.setBackColor(hoverButtonColor);
		searchTextbox.setVisible();
		randomButton.setPosition(sf::Vector2f{ searchTextbox.getPositon().x + searchTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, searchTextbox.getPositon().y });
		okButtonBackground.setPosition(sf::Vector2f{ searchTextbox.getPositon().x, searchTextbox.getPositon().y + searchTextbox.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ searchTextbox.getPositon().x + (searchTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, searchTextbox.getPositon().y + searchTextbox.getGlobalBounds().height });
		
		searchTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = std::rand() % 100 + 1;
			searchTextbox.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			int num = searchTextbox.getNum();
			searchTextbox.reset();
			// do sth
		}
	}
	else {
		searchTextbox.setSelected(false);
		searchTextbox.setInvisible();
		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
		}
	}
}

void SinglyLinkedListMainState::handleHomeButtonEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (homeButton.isMouseOverCircle(*m_context->window))
		{
			m_context->stateMachine->removeState();
		}
	}
}

void SinglyLinkedListMainState::handleCreateButtonEvents(sf::Event event)
{
	createButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (createButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton ^= 1;
		isSelectedInsertButton = false;
		isSelectedDeleteButton = false;
		isSelectedSearchButton = false;
		isSelectedUpdateButton = false;
	}

	if (isSelectedCreateButton) {
		createButton.setBackColor(hoverButtonColor);
		createTextbox.setVisible();
		randomButton.setPosition(sf::Vector2f{ createTextbox.getPositon().x + createTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, createTextbox.getPositon().y });
		uploadFileButton.setPosition(sf::Vector2f{ randomButton.getPosition().x - uploadFileButton.getGlobalBounds().width - 5, createTextbox.getPositon().y});
		okButtonBackground.setPosition(sf::Vector2f{ createTextbox.getPositon().x, createTextbox.getPositon().y + createTextbox.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ createTextbox.getPositon().x + (createTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, createTextbox.getPositon().y + createTextbox.getGlobalBounds().height });

		createTextbox.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = std::rand() % 20;
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

					createTextbox.insertNum((int)nums.size());
					//handle num list



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
			createTextbox.reset();
			// do sth
		}
	}
	else {
		createTextbox.setSelected(false);
		createTextbox.setInvisible();
		uploadFileButton.setPosition(sf::Vector2f{ -1000, -1000 });

		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
		}
	}
}

void SinglyLinkedListMainState::handleUpdateButtonEvents(sf::Event event)
{
	updateButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (updateButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton = false;
		isSelectedDeleteButton = false;
		isSelectedSearchButton = false;
		isSelectedUpdateButton ^= 1;
	}

	if (isSelectedUpdateButton) {
		updateButton.setBackColor(hoverButtonColor);
		updateTextboxX.setVisible();
		updateTextboxV.setVisible();

		randomButton.setPosition(sf::Vector2f{ updateTextboxX.getPositon().x + updateTextboxX.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, updateTextboxX.getPositon().y });
		randomUpdateButton.setPosition(sf::Vector2f{ updateTextboxV.getPositon().x + updateTextboxV.getGlobalBounds().width - randomUpdateButton.getGlobalBounds().width - 5, updateTextboxV.getPositon().y });
		okButtonBackground.setPosition(sf::Vector2f{ updateTextboxV.getPositon().x, updateTextboxV.getPositon().y + updateTextboxV.getGlobalBounds().height });
		okButton.setPosition(sf::Vector2f{ updateTextboxV.getPositon().x + (updateTextboxV.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, updateTextboxV.getPositon().y + updateTextboxV.getGlobalBounds().height });

		updateTextboxX.typedOnNum(event, *m_context->window);
		updateTextboxV.typedOnNum(event, *m_context->window);

		if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = std::rand() % 100 + 1;
			updateTextboxX.insertNum(randomNum);
		}

		if (randomUpdateButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = std::rand() % 100 + 1;
			updateTextboxV.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			int oldV = updateTextboxX.getNum();
			updateTextboxX.reset();
			updateTextboxX.setSelected(false);
			int newV = updateTextboxV.getNum();
			updateTextboxV.reset();
			updateTextboxV.setSelected(false);

			// do sth


		}
	}
	else {
		updateTextboxX.setSelected(false);
		updateTextboxX.setInvisible();
		updateTextboxV.setSelected(false);
		updateTextboxV.setInvisible();
		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			randomUpdateButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButtonBackground.setPosition(sf::Vector2f{ -1000, 1000 });
		}
	}
}

void SinglyLinkedListMainState::handleThemeButtonEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (themeButton.isMouseOver(*m_context->window)) {
			switchTheme();
		}
	}
}

void SinglyLinkedListMainState::handleAniSliderEvents(sf::Event event)
{
	if (aniSlider.getPartIndex() == aniSlider.getNumPart()) {
		pauseButton.setPosition(sf::Vector2f({ -1000, 1000 }));
		playButton.setPosition(sf::Vector2f({ -1000, 1000 }));
		replayButton.setPosition(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - replayButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15 });
	}
	else {
		pauseButton.setPosition(sf::Vector2f({ -1000, 1000 }));
		replayButton.setPosition(sf::Vector2f({ -1000, 1000 }));
		playButton.setPosition(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - playButton.getGlobalBounds().width) / 2, aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15 });
	}
	if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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
}

void SinglyLinkedListMainState::handleSpeedSliderEvents(sf::Event event)
{
	speedSlider.handleEvent(event);
	std::string st = "1.0x";
	st[0] = char(speedSlider.getPartIndex() + 1 + '0');
	speedSlider.setMaxText(st);
}

void SinglyLinkedListMainState::handleButtonEvents(const sf::Event& event)
{
	handleDeleteButtonEvents(event);
	handleInsertButtonEvents(event);
	handleSearchButtonEvents(event);
	handleUpdateButtonEvents(event);
	handleCreateButtonEvents(event);
	handleHomeButtonEvents(event);
	handleThemeButtonEvents(event);

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


