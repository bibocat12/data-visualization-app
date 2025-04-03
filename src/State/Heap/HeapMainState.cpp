#include "HeapMainState.h"


void HeapMainState::switchTheme() {
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
		extractButton.setTextColor(textColor);
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
		updateButton.setTextColor(textColor);
		extractButton.setTextColor(textColor);
		speedSlider.setTextColor(textColor);
		title.setFillColor(textColor);
	}
}

void HeapMainState::initFunctionButton() {
	buttonSize.x = 120;
	buttonSize.y = 40;
	checkpointY = 650;
	float firstButtonY = checkpointY + 30;
	initButton(createButton, "Create", sf::Vector2f{ 10, firstButtonY });
	initButton(insertButton, "Insert", sf::Vector2f{ 10, firstButtonY + buttonSize.y });
	initButton(deleteButton, "Delete", sf::Vector2f{ 10, firstButtonY + 2 * buttonSize.y });
	initButton(updateButton, "Update", sf::Vector2f{ 10, firstButtonY + 3 * buttonSize.y });
	initButton(extractButton, "Extract", sf::Vector2f{ 10, firstButtonY + 4 * buttonSize.y });

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

	initTextbox(insertTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	insertTextbox.setConstText("v = ");

	initTextbox(deleteTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	deleteTextbox.setConstText("id = ");

	initTextbox(createTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	createTextbox.setConstText("n = ");
	createTextbox.setLimit(true, 3);

	initTextbox(updateTextboxX, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
	updateTextboxX.setConstText("id = ");
	updateTextboxX.setLimit(true, 9);

	initTextbox(updateTextboxV, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, updateTextboxX.getPositon().y + updateTextboxX.getGlobalBounds().height });
	updateTextboxV.setConstText("v = ");
	updateTextboxV.setLimit(true, 9);
}

void HeapMainState::initCodePanel()
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

void HeapMainState::initTheme()
{
	*m_context->themeType ^= 1;
	themeButton = ImageButton(m_context->assetManager->getTexture("LightTheme"), 1.0f, 1.0f);
	switchTheme();
	themeButton.setPosition(sf::Vector2f{ 1450, 30 });
}

void HeapMainState::initTitle()
{
	title.setCharacterSize(34);
	title.setFont(m_context->assetManager->getFont("Oswald"));
	title.setString("Heap");
	homeButton = ImageButton(m_context->assetManager->getTexture("HomeButton"), 1.0f, 1.0f);
	homeButton.setPosition(sf::Vector2f{ (SCREEN_WIDTH - title.getGlobalBounds().width) / 2 - homeButton.getGlobalBounds().width - 15, 10 });

	title.setFillColor(textColor);
	title.setPosition((SCREEN_WIDTH - title.getGlobalBounds().width) / 2, homeButton.getPosition().y + (homeButton.getGlobalBounds().height - title.getCharacterSize()) / 2);

}

void HeapMainState::initSpeedSlider()
{
	speedSlider = Slider(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - 300) / 2, playButton.getPosition().y + playButton.getGlobalBounds().height + 15 }, sf::Vector2f{ 300, 15.f }, sf::Vector2f{ 20, 20 });
	speedSlider.setColor(LightGray, NavyBlue, GoldenOrange);
	speedSlider.setNumPart(7);
	speedSlider.setText("0.5x", "1.0x", 20, m_context->assetManager->getFont("Neon"), textColor);
	speedSlider.setPart(1);
}

void HeapMainState::initAniSlider()
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

void HeapMainState::initButton(Button& button, std::string text, sf::Vector2f pos) {
	button = Button(text, buttonSize, 20, normalButtonColor, textColor);
	button.setFont(m_context->assetManager->getFont("Oswald"));
	button.setPosition(pos);
}

HeapMainState::HeapMainState(std::shared_ptr<Context>& context) : m_context(context)
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

	/*std::vector<int> nums;
	for (int i = 0; i < 31; i++) {
		nums.push_back(rand() % 100);
	}
	heap.create(nums);
	nums = heap.getAllElements();
	createNums = nums;
	preInitCreateFrames(1);*/
}

HeapMainState::~HeapMainState()
{
}

void HeapMainState::init()
{



}

void HeapMainState::pause()
{

}

void HeapMainState::resume()
{

}

void HeapMainState::processEvents()
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
	updateTextboxX.handleCursor();
	updateTextboxV.handleCursor();
}

void HeapMainState::update(const sf::Time& dt)
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

void HeapMainState::draw()
{

	m_context->window->clear(backgroundColor);
	m_context->window->draw(title);
	createButton.drawTo(*m_context->window);

	insertButton.drawTo(*m_context->window);
	deleteButton.drawTo(*m_context->window);
	updateButton.drawTo(*m_context->window);
	extractButton.drawTo(*m_context->window);


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
	updateTextboxX.drawTo(*m_context->window);
	updateTextboxV.drawTo(*m_context->window);
	randomButton.drawTo(*m_context->window);
	randomUpdateButton.drawTo(*m_context->window);
	uploadFileButton.drawTo(*m_context->window);
	okButtonBackground.drawTo(*m_context->window);
	okButton.drawTo(*m_context->window);
	currentFrame.drawAll(*m_context->window);
	if (isSelectedCreateFrames || isSelectedInsertFrames || isSelectedDeleteFrames || isSelectedUpdateFrames || isSelectedExtractFrames) {
		codePanel.draw(*m_context->window);
	}
	m_context->window->display();

}

void HeapMainState::initTextbox(Textbox& textbox, int charSize, sf::Color textColor, sf::Font& font, sf::Vector2f pos)
{
	textbox = Textbox(charSize, textColor, false);
	textbox.setFont(m_context->assetManager->getFont("JetBrainsMono-SemiBold"));
	textbox.setPosition(pos);
	textbox.setBox(sf::Vector2f{ 200, buttonSize.y }, BeigeGrey);
	textbox.setLimit(true, 9);
}


void HeapMainState::handleInsertButtonEvents(sf::Event event)
{
	insertButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (insertButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton ^= 1;
		isSelectedDeleteButton = false;
		isSelectedExtractButton = false;
		isSelectedUpdateButton = false;
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

			preInitInsertFrames(insertValue);
			std::cerr << insertValue << "\n";
		}
	}
	else {
		insertTextbox.setSelected(false);
		insertTextbox.setInvisible();

		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedExtractButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			randomUpdateButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButtonBackground.setPosition(sf::Vector2f{ -1000, 1000 });
		}
	}
}


void HeapMainState::handleDeleteButtonEvents(sf::Event event)
{
	deleteTextbox.setLimNum(std::max(0, heap.Size() - 1));
	deleteButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (deleteButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton = false;
		isSelectedDeleteButton ^= 1;
		isSelectedExtractButton = false;
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
			int randomId = Utils::rand(0, heap.Size() - 1);
			deleteTextbox.insertNum(randomId);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			deleteId = deleteTextbox.getNum();
			deleteTextbox.reset();
			// do sth

			if(deleteId < heap.Size()) preInitDeleteFrames(deleteId);
		}
	}
	else {
		deleteTextbox.setSelected(false);
		deleteTextbox.setInvisible();
		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedExtractButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
		}
	}
}

void HeapMainState::handleExtractButtonEvents(sf::Event event)
{
	extractButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (extractButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton = false;
		isSelectedDeleteButton = false;
		isSelectedExtractButton ^= 1;
		isSelectedUpdateButton = false;
	}

	if (isSelectedExtractButton) {
		extractButton.setBackColor(hoverButtonColor);
		okButtonBackground.setPosition(sf::Vector2f{ sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y } });
		okButton.setPosition(sf::Vector2f{deleteTextbox.getPositon().x + (deleteTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, createButton.getPositon().y});


		if (((okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))) {
			preInitExtractFrames();
		}
	}
	else {
		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedExtractButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
		}
	}
}

void HeapMainState::handleHomeButtonEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (homeButton.isMouseOverCircle(*m_context->window))
		{
			m_context->stateMachine->removeState();
		}
	}
}

void HeapMainState::handleCreateButtonEvents(sf::Event event)
{
	createTextbox.setLimNum(63);
	createButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (createButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton ^= 1;
		isSelectedInsertButton = false;
		isSelectedDeleteButton = false;
		isSelectedExtractButton = false;
		isSelectedUpdateButton = false;
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
					while ((int) nums.size() > 63) {
						nums.pop_back();
					}
					createTextbox.insertNum((int)nums.size());
					//handle num list
					createTextbox.setSelected(false);
					createNums = nums;
					preInitCreateFrames();
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
			preInitCreateFrames();


		}
	}
	else {
		createTextbox.setSelected(false);
		createTextbox.setInvisible();
		uploadFileButton.setPosition(sf::Vector2f{ -1000, -1000 });

		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedExtractButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
		}
	}
}

void HeapMainState::handleUpdateButtonEvents(sf::Event event)
{
	updateTextboxX.setLimNum(std::max(0, heap.Size() - 1));
	updateButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
	if (updateButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		isSelectedCreateButton = false;
		isSelectedInsertButton = false;
		isSelectedDeleteButton = false;
		isSelectedExtractButton = false;
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
			int randomNum = Utils::rand(0, heap.Size() - 1);
			updateTextboxX.insertNum(randomNum);
		}

		if (randomUpdateButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int randomNum = Utils::rand(0, 99);
			updateTextboxV.insertNum(randomNum);
		}

		if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) || (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
			updateId = updateTextboxX.getNum();
			updateTextboxX.reset();
			updateTextboxX.setSelected(false);
			updateValue = updateTextboxV.getNum();
			updateTextboxV.reset();
			updateTextboxV.setSelected(false);
				
			if(updateId < heap.Size()) preInitUpdateFrames(updateId, updateValue);
		}
	}
	else {
		updateTextboxX.setSelected(false);
		updateTextboxX.setInvisible();
		updateTextboxV.setSelected(false);
		updateTextboxV.setInvisible();
		if (!isSelectedUpdateButton) {
			randomUpdateButton.setPosition(sf::Vector2f(-1000, -1000));
		}
		if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedExtractButton && !isSelectedUpdateButton) {
			randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
			randomUpdateButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButton.setPosition(sf::Vector2f{ -1000, -1000 });
			okButtonBackground.setPosition(sf::Vector2f{ -1000, 1000 });
		}
	}
}

void HeapMainState::handleThemeButtonEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (themeButton.isMouseOver(*m_context->window)) {
			switchTheme();
		}
	}
}

void HeapMainState::handleAniSliderEvents(sf::Event event)
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

void HeapMainState::handleSpeedSliderEvents(sf::Event event)
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

void HeapMainState::handleButtonEvents(const sf::Event& event)
{
	handleDeleteButtonEvents(event);
	handleInsertButtonEvents(event);
	handleExtractButtonEvents(event);
	handleUpdateButtonEvents(event);
	handleCreateButtonEvents(event);
	handleHomeButtonEvents(event);
	handleThemeButtonEvents(event);

}

void HeapMainState::initNode(int n)
{
	n = std::max(n, heap.Size());
	for (int i = 0; i < n; i++)
	{
		Node node;

		node.setFillColor(sf::Color::White);			// set color for node in white theme
		node.setOutlineColor(sf::Color::Red);
		node.setOutlineThickness(-3);
		
		node.setRadius(RADIUS);
		if (i == 0) { // the root
			node.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, homeButton.getPosition().y + homeButton.getGlobalBounds().height + 50));
		}
		else {
			int par = heap.parent(i);
			int dep = heap.depth(i);
			if (i % 2 == 1) { // left child
				node.setPosition(sf::Vector2f(static_cast<float>(b_nodes[par].getPosition().x - std::max(minSpaceX, static_cast<float>(spaceX / pow(2, dep - 1)))), static_cast<float>(b_nodes[par].getPosition().y + 2 * RADIUS + spaceY - dep)));
			}
			else { // right child
				node.setPosition(sf::Vector2f(static_cast<float>(b_nodes[par].getPosition().x + std::max(minSpaceX, static_cast<float>(spaceX / pow(2, dep - 1)))), static_cast<float>(b_nodes[par].getPosition().y + 2 * RADIUS + spaceY - dep)));
			}
		}

		node.setCharacterSize(20);
		node.setFont(m_context->assetManager->getFont("JetBrainsMono-Regular"));
		node.setTextColor(sf::Color::Black);


		b_nodes[i] = node;
		b_nodes[i].initTextUnder(DarkGrey, 17);
		b_nodes[i].setTextUnder(std::to_string(i));

		node.setFillColor(sf::Color::White);			// set color for node in black theme
		node.setOutlineColor(Orange);
		w_nodes[i] = node;
		w_nodes[i].initTextUnder(DesaturatedBlue, 17);
		w_nodes[i].setTextUnder(std::to_string(i));
	}
}

void HeapMainState::initEdge(int n)
{
	n = std::max(n, heap.Size());
	sf::Vector2f start, end;
	for (int i = 1; i < n; i++)
	{
		Edge edge;
		edge.setColor(sf::Color::Black);			// set color for edge in white theme
		edge.setThickness(-3);
		if (i % 2 == 1) { // left child
			//find center of the node
			sf::Vector2f center = b_nodes[i].getPosition();
			start = sf::Vector2f(center.x + cos(DEG_TO_RAD(30)) * RADIUS, center.y - sin(DEG_TO_RAD(30)) * RADIUS);

			//find center of parent
			center = b_nodes[heap.parent(i)].getPosition();
			end = sf::Vector2f(center.x - cos(DEG_TO_RAD(30)) * RADIUS, center.y + sin(DEG_TO_RAD(30)) * RADIUS);
		}
		else { // right child

			//find center of the node
			sf::Vector2f center = b_nodes[i].getPosition();
			start = sf::Vector2f(center.x - cos(DEG_TO_RAD(30)) * RADIUS, center.y - sin(DEG_TO_RAD(30)) * RADIUS);

			//find center of parent
			center = b_nodes[heap.parent(i)].getPosition();
			end = sf::Vector2f(center.x + cos(DEG_TO_RAD(30)) * RADIUS, center.y + sin(DEG_TO_RAD(30)) * RADIUS);
		}

		float _tan = abs(end.y - start.y) / abs(end.x - start.x);
		sf::Vector2f posEndEdge;
		if (i % 2 == 1) {
			posEndEdge.x = start.x + abs(end.x - start.x);
		}
		else {
			posEndEdge.x = start.x - abs(end.x - start.x);
		}
		posEndEdge.y = start.y - abs(posEndEdge.x - start.x) * _tan;
		edge.setStart(start);
		edge.setEnd(posEndEdge);
		b_edges[i] = edge;
		edge.setColor(sf::Color::White);			// set color for edge in black theme
		edge.setDirected(false);
		w_edges[i] = edge;
	}
}