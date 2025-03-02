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

	// Init node and edge
	initNode();
	initEdge();
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
	updateFrames();
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
	searchTextbox.drawTo(*m_context->window);
	createTextbox.drawTo(*m_context->window);
	updateTextboxX.drawTo(*m_context->window);
	updateTextboxV.drawTo(*m_context->window);
	randomButton.drawTo(*m_context->window);
	randomUpdateButton.drawTo(*m_context->window);
	uploadFileButton.drawTo(*m_context->window);
	okButtonBackground.drawTo(*m_context->window);
	okButton.drawTo(*m_context->window);

	std::cerr << "currentframe index" << currentFrameIndex << std::endl;
	std::cerr << "currentframe size" << b_frames.size() << std::endl;
	currentFrame.drawAll(*m_context->window);
	
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
			initInsertFrames(num);
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
			initSearchFrames(num);
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

					initRandomFrames(nums);

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
			initRandomFrames(allElements);
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
void SinglyLinkedListMainState::initNode()
{
	for (int i = 0; i < 18; i++)
	{
		Node node;

        node.setFillColor(sf::Color::White);			// set color for node in white theme
        node.setOutlineColor(sf::Color::Red);
        node.setOutlineThickness(5);
        node.setRadius(20);
        node.setPosition(sf::Vector2f(PADDING_X + i * DISTANCE_X, 400));
        node.setCharacterSize(20);
        node.setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
        node.setTextColor(sf::Color::Black);

        b_nodes[i] = node;

        node.setFillColor(sf::Color::White);			// set color for node in black theme
        node.setOutlineColor(Orange);
        w_nodes[i] = node;
	}
}
void SinglyLinkedListMainState::initEdge()
{
	for (int i = 0; i < 18; i++)
	{
		Edge edge;
		edge.setColor(sf::Color::Black);			// set color for edge in white theme
		edge.setThickness(5);
		edge.setStart(sf::Vector2f(PADDING_X + i * DISTANCE_X, EDGE_Y));
		edge.setEnd(sf::Vector2f(PADDING_X + (i + 1) * DISTANCE_X, EDGE_Y));
		b_edges[i] = edge;
		edge.setColor(sf::Color::White);			// set color for edge in black theme
		edge.setThickness(5);
		edge.setStart(sf::Vector2f(PADDING_X + i * DISTANCE_X, EDGE_Y));
		edge.setEnd(sf::Vector2f(PADDING_X + (i + 1) * DISTANCE_X, EDGE_Y));
		w_edges[i] = edge;
	}
}
void SinglyLinkedListMainState::moveNodeEdge(int index, int index1, int index2, sf::Vector2f start, sf::Vector2f end)
{
	for (int i = index1; i <= index2; i++)
	{
		sf::Vector2f pos;
		pos.x = start.x + (i-index1) * (end.x - start.x) / (index2 - index1);
		pos.y = start.y + (i-index1) * (end.y - start.y) / (index2 - index1);

		sf::Vector2f posEndEdge;
		posEndEdge.x = start.x + (i - index1) * (end.x - start.x) / (index2 - index1);
		posEndEdge.y = EDGE_Y;

		b_nodes[index].setPosition(pos);
		w_nodes[index].setPosition(pos);
		b_edges[index].setStart(sf::Vector2f(start.x, EDGE_Y));
		w_edges[index].setStart(sf::Vector2f(start.x, EDGE_Y));
		b_edges[index].setEnd(posEndEdge);
		w_edges[index].setEnd(posEndEdge);


		b_frames[i].init(b_frames[i - 1]);
		w_frames[i].init(w_frames[i - 1]);
		b_frames[i].addNode("1bnodes" + std::to_string(index), b_nodes[index]);
		w_frames[i].addNode("1wnodes" + std::to_string(index), w_nodes[index]);
		b_frames[i].addEdge("2bedges" + std::to_string(index), b_edges[index]);
		w_frames[i].addEdge("2wedges" + std::to_string(index), w_edges[index]);
		std::cout << "Frame " << i << " Position: " << pos.x << ", " << pos.y << std::endl;

	}
}
void SinglyLinkedListMainState::changeBColor(int index, int index1, int index2, sf::Color from, sf::Color to)
{

	float step =  (index2 - index1);
	float vR = (to.r - from.r)/step;
	float vG = (to.g - from.g) / step;
	float vB = (to.b - from.b) / step;

	for (int i = index1; i <= index2; i++)
	{
		sf::Color color;
		color.r = from.r + vR * (i - index1);
		color.g = from.g + vG * (i - index1);
		color.b = from.b + vB * (i - index1);
		b_nodes[index].setFillColor(color);
		if (i > 0)
			b_frames[i].init(b_frames[i - 1]);
		b_frames[i].addNode("bnodes" + std::to_string(index), b_nodes[index]);
	}
}
void SinglyLinkedListMainState::changeWColor(int index, int index1, int index2, sf::Color from, sf::Color to)
{
	float step = (index2 - index1);
	float vR = (to.r - from.r) / step;
	float vG = (to.g - from.g) / step;
	float vB = (to.b - from.b) / step;
	for (int i = index1; i <= index2; i++)
	{
		sf::Color color;
		color.r = from.r + vR * (i - index1);
		color.g = from.g + vG * (i - index1);
		color.b = from.b + vB * (i - index1);
		w_nodes[index].setFillColor(color);
		w_frames[i].init(w_frames[i - 1]);
		w_frames[i].addNode("wnodes" + std::to_string(index), w_nodes[index]);
	}
}
void SinglyLinkedListMainState::deleteAllFrames()
{
	b_frames.clear();
	w_frames.clear();
	numFrames = 0;
	currentFrameIndex = 0;
	isPlaying = false;
}

void SinglyLinkedListMainState::initRandomFrames(std::vector<int> elements)
{
	int timeRepeat = 0;
	deleteAllFrames();
	LinkedList.removeAll();

	for (int x : elements)
		LinkedList.insert(x);

	codePanel.setText("for x in elements", 0);
	codePanel.setText("    insert(x)", 1);
	codePanel.setText("return", 2);

	std::vector<int> allElements;
	std::cerr << "NumElements: " << elements.size() << std::endl;
	allElements = LinkedList.getAllElements();
	initNode();
	initEdge();


	for(int i = 0;i < 60;i++)
	{
		Engine::Frame b_frame, w_frame;
		b_nodes[0].setString(std::to_string(allElements[0]));
		w_nodes[0].setString(std::to_string(allElements[0]));
		b_frame.addNode("1bnodes0", b_nodes[0]);
		w_frame.addNode("1swnodes0", w_nodes[0]);
		b_frame.addPanel("3bcodePanel", codePanel);
		w_frame.addPanel("3wcodePanel", codePanel);

		b_frames.push_back(b_frame);
		w_frames.push_back(w_frame);
	}
	for (int i = 1; i < allElements.size(); i++)
	{
		int firstIndex = b_frames.size() ;
		int lastIndex = b_frames.size() + 120 - 1;
		for (int j = 0; j < 120; j++)
		{
			Engine::Frame b_frame, w_frame;
			b_nodes[i].setString(std::to_string(allElements[i]));
			w_nodes[i].setString(std::to_string(allElements[i]));

			b_frame.init(b_frames[b_frames.size() - 1]);
			w_frame.init(w_frames[w_frames.size() - 1]);
			b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
			w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
			b_frame.addPanel("3bcodePanel", codePanel);
			w_frame.addPanel("3wcodePanel", codePanel);

			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}

		moveNodeEdge(i, firstIndex, lastIndex, sf::Vector2f(PADDING_X + (i - 1) * DISTANCE_X, 400), sf::Vector2f(PADDING_X + i * DISTANCE_X, 400));
	}

	isPlaying = true;
	numFrames = b_frames.size();
	std::cerr << "NumFrames: " << numFrames << std::endl;
	currentFrameIndex = 0;

}
void SinglyLinkedListMainState::initInsertFrames(int num)
{
	std::vector<int> allElements;
	allElements = LinkedList.getAllElements();

	deleteAllFrames();
	Engine::Frame b_frame, w_frame;

	for(int i = 0;i < allElements.size();i++)
	{
		int x = allElements[i];
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		b_frame.addEdge("2bedges" + std::to_string(i), b_edges[i]);
		w_frame.addEdge("2wedges" + std::to_string(i), w_edges[i]);
	}



	 
}
void SinglyLinkedListMainState::initSearchFrames(int num)
{
	std::vector<int> allElements = LinkedList.getAllElements();
	deleteAllFrames();
	Engine::Frame b_frame, w_frame;

	codePanel.setText("current = head", 0);
	codePanel.setText("while current != NULL and current->data != " + std::to_string(num), 1);
	codePanel.setText("    current = current->next", 2);
	codePanel.setText("if current == NULL", 3);
	codePanel.setText("    return false", 4);
	codePanel.setText("return true", 5);

	initNode();
	initEdge();

	// Khởi tạo khung hình ban đầu
	for (int i = 0; i < allElements.size(); i++)
	{
		int x = allElements[i];
		b_nodes[i].setString(std::to_string(x));
		w_nodes[i].setString(std::to_string(x));
		b_frame.addNode("1bnodes" + std::to_string(i), b_nodes[i]);
		w_frame.addNode("1wnodes" + std::to_string(i), w_nodes[i]);
		if (i > 0)
		{
			b_frame.addEdge("2bedges" + std::to_string(i - 1), b_edges[i - 1]);
			w_frame.addEdge("2wedges" + std::to_string(i - 1), w_edges[i - 1]);
		}
	}
	b_frames.push_back(b_frame);
	w_frames.push_back(w_frame);

	// Tạo hiệu ứng di chuyển từng node
	for (int i = 0; i < allElements.size(); i++)
	{
		int first = b_frames.size();
		int last = first + 120 - 1;
		for (int step = 0; step < 120; step++)
		{
			Engine::Frame b_frame, w_frame;
			b_frame.init(b_frames.back());
			w_frame.init(w_frames.back());


			//if (i > 0)
			//{
			//	changeBEdgeColor(i - 1, step, 30, sf::Color::White, sf::Color::Blue);
			//	changeWEdgeColor(i - 1, step, 30, sf::Color::White, sf::Color::Blue);
			//}

			b_frames.push_back(b_frame);
			w_frames.push_back(w_frame);
		}

		changeBColor(i, first, last, sf::Color::White, sf::Color::Blue);
		changeWColor(i, first, last, sf::Color::White, sf::Color::Blue);


		if (allElements[i] == num)
		{
			int firstIndex = b_frames.size();
			int lastIndex = b_frames.size() + 120 - 1;
			for (int step = 0; step < 120; step++)
			{
				Engine::Frame b_frame, w_frame;
				b_frame.init(b_frames.back());
				w_frame.init(w_frames.back());


				b_frames.push_back(b_frame);
				w_frames.push_back(w_frame);
			}
			changeBColor(i, firstIndex, lastIndex, sf::Color::Blue, sf::Color::Green);
			changeWColor(i, firstIndex, lastIndex, sf::Color::Blue, sf::Color::Green);
			break;
		}
	}

	isPlaying = true;
	numFrames = b_frames.size();
}

void SinglyLinkedListMainState::updateFrames()
{
	if (isPlaying)
	{
		b_nextFrame = b_frames.back();
		w_nextFrame = w_frames.back();
		if (numFrames > 0)
		{
			//std::cerr << currentFrameIndex << std::endl;
			if (currentFrameIndex < numFrames)
			{

				b_currentFrame = b_frames[currentFrameIndex];
				w_currentFrame = w_frames[currentFrameIndex];

				if (*m_context->themeType == 0)
					currentFrame = b_currentFrame;
				else
					currentFrame = w_currentFrame;
				
				currentFrameIndex++;

			}
			else
			{
				if (*m_context->themeType == 0)
					currentFrame = b_frames[currentFrameIndex - 1];
				else
					currentFrame = w_frames[currentFrameIndex - 1];
			}
		}
	}
	



}


