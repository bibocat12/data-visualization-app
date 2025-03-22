#include "AVLMainState.h"
#include <cmath> // Required for std::pow

AVLMainState::AVLMainState(std::shared_ptr<Context>& context) : m_context(context) {
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

    std::vector<int> nums = { 2,24,27,34,36,37,43,51,52,56,60,64,85,94,98 };
	initCreateFrames(nums);


}
AVLMainState::~AVLMainState() {
    deleteAllFrames(); // Clean up frames
}

void AVLMainState::init() {}
void AVLMainState::pause() {}
void AVLMainState::resume() {}

void AVLMainState::processEvents() {
    sf::Event event;
    while (m_context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->window->close();
            return;
        }

        // Handle button events
        handleButtonEvents(event);
        handleAniSliderEvents(event);
        handleSpeedSliderEvents(event);
    }

    // Handle textbox events
    createTextbox.handleCursor();
    insertTextbox.handleCursor();
    deleteTextbox.handleCursor();
    searchTextbox.handleCursor();

}

void AVLMainState::update(const sf::Time& dt) {
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

    if (isPaused == true && isPlaying == true) {
        int part = aniSlider.getPartIndex();
        currentFrameIndex = part;
    }

    updateFrames();
}

void AVLMainState::draw() {
    m_context->window->clear(backgroundColor);
    m_context->window->draw(title);

    createButton.drawTo(*m_context->window);
    insertButton.drawTo(*m_context->window);
    deleteButton.drawTo(*m_context->window);
    searchButton.drawTo(*m_context->window);
	inorderButton.drawTo(*m_context->window);

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
	inorderButton.drawTo(*m_context->window);
    okButtonBackground.drawTo(*m_context->window);
    okButton.drawTo(*m_context->window);
	randomButton.drawTo(*m_context->window);
    uploadFileButton.drawTo(*m_context->window);



    currentFrame.drawAll(*m_context->window);
    m_context->window->display();
}

void AVLMainState::initTextbox(Textbox& textbox, int charSize, sf::Color textColor, sf::Font& font, sf::Vector2f pos) {
    textbox = Textbox(charSize, textColor, false);
    textbox.setFont(m_context->assetManager->getFont("JetBrainsMono-SemiBold"));
    textbox.setPosition(pos);
    textbox.setBox(sf::Vector2f{ 200, buttonSize.y }, BeigeGrey);
    textbox.setLimit(true, 9);
}

void AVLMainState::switchTheme() {
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
        searchButton.setTextColor(textColor);
        title.setFillColor(textColor);
        codePanel.setTextColor(textColor);
    }
}

void AVLMainState::initFunctionButton() {
    buttonSize.x = 120;
    buttonSize.y = 40;
    checkpointY = 650;
    float firstButtonY = checkpointY + 30;
    initButton(createButton, "Create", sf::Vector2f{ 10, firstButtonY });
    initButton(insertButton, "Insert", sf::Vector2f{ 10, firstButtonY + buttonSize.y });
    initButton(deleteButton, "Delete", sf::Vector2f{ 10, firstButtonY + 2 * buttonSize.y });
    initButton(searchButton, "Search", sf::Vector2f{ 10, firstButtonY + 3 * buttonSize.y });
	initButton(inorderButton, "Inorder", sf::Vector2f{ 10, firstButtonY + 4 * buttonSize.y });

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
    deleteTextbox.setConstText("v = "); //Deleting by value

    initTextbox(searchTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
    searchTextbox.setConstText("v = ");

    initTextbox(createTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
    createTextbox.setConstText("n = ");
    createTextbox.setLimit(true, 2);
}

void AVLMainState::initCodePanel() {
    int numLine = 7;
    labelSize = sf::Vector2f(500, static_cast<float>((SCREEN_HEIGHT - 20 - checkpointY) / numLine));
    codePanel = Panel(sf::Vector2f{ SCREEN_WIDTH - 10 - labelSize.x,  checkpointY }, labelSize, textColor, LavenderSoft, m_context->assetManager->getFont("JetBrainsMono-Regular"), 18);
    codePanel.add("insert v");
    codePanel.add("if balance > 1");
    codePanel.add("  rotate");
    codePanel.add("");
    codePanel.add("");
    codePanel.add("");
    codePanel.add("");
}

void AVLMainState::initTheme() {
    *m_context->themeType ^= 1;
    themeButton = ImageButton(m_context->assetManager->getTexture("LightTheme"), 1.0f, 1.0f);
    switchTheme();
    themeButton.setPosition(sf::Vector2f{ 1450, 30 });
}

void AVLMainState::initTitle() {
    title.setCharacterSize(34);
    title.setFont(m_context->assetManager->getFont("Oswald"));
    title.setString("AVL Tree");
    homeButton = ImageButton(m_context->assetManager->getTexture("HomeButton"), 1.0f, 1.0f);
    homeButton.setPosition(sf::Vector2f{ (SCREEN_WIDTH - title.getGlobalBounds().width) / 2 - homeButton.getGlobalBounds().width - 15, 10 });

    title.setFillColor(textColor);
    title.setPosition((SCREEN_WIDTH - title.getGlobalBounds().width) / 2, homeButton.getPosition().y + (homeButton.getGlobalBounds().height - title.getCharacterSize()) / 2);
}

void AVLMainState::initSpeedSlider() {
    speedSlider = Slider(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - 300) / 2, playButton.getPosition().y + playButton.getGlobalBounds().height + 15 }, sf::Vector2f{ 300, 15.f }, sf::Vector2f{ 20, 20 });
    speedSlider.setColor(LightGray, NavyBlue, GoldenOrange);
    speedSlider.setNumPart(6);
    speedSlider.setText("1.0x", "1.0x", 20, m_context->assetManager->getFont("Neon"), textColor);
}

void AVLMainState::initAniSlider() {
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

void AVLMainState::initButton(Button& button, std::string text, sf::Vector2f pos) {
    button = Button(text, buttonSize, 20, normalButtonColor, textColor);
    button.setFont(m_context->assetManager->getFont("Oswald"));
    button.setPosition(pos);
}



void AVLMainState::handleButtonEvents(const sf::Event& event) {
    handleCreateButtonEvents(event);
    handleInsertButtonEvents(event);
    handleDeleteButtonEvents(event);
    handleSearchButtonEvents(event);
    handleInorderButtonEvents(event);
    handleHomeButtonEvents(event);
    handleThemeButtonEvents(event);
}
void AVLMainState::handleCreateButtonEvents(const sf::Event& event) {
    createButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (createButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        isSelectedCreateButton ^= 1;
        isSelectedInsertButton = false;
        isSelectedDeleteButton = false;
        isSelectedSearchButton = false;
		isSelectedInorderButton = false;
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
					std::cerr << "create:" << nums.size() << "\n";
                    //handle num list

                    initCreateFrames(nums);
                    currentState = "create";

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
            std::cerr << "create:" << num << std::endl;
            createTextbox.reset();
            // do sth
            std::vector<int> allElements;
			std::map<int, int> checkUnique;
            for (int i = 0; i < num; i++) {
				int x = std::rand() % 100;
                while (checkUnique.find(x) != checkUnique.end()) {
                    x = std::rand() % 1000;
                }
				checkUnique[x] = 1;
				allElements.push_back(x);

            }

            initCreateFrames(allElements);
			currentState = "create";


        }
    }
    else {
        createTextbox.setSelected(false);
        createTextbox.setInvisible();
        uploadFileButton.setPosition(sf::Vector2f{ -1000, -1000 });

        if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton ) {
            randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
            okButton.setPosition(sf::Vector2f{ -1000, -1000 });
        }
    }
}
void AVLMainState::handleInsertButtonEvents(const sf::Event& event) {
    insertButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (insertButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        isSelectedCreateButton = false;
        isSelectedDeleteButton = false;
        isSelectedSearchButton = false;
        isSelectedInorderButton = false;
        isSelectedInsertButton ^= 1;
    }
        if (isSelectedInsertButton == true)
        {
            
            insertButton.setBackColor(hoverButtonColor);
            insertTextbox.setVisible();


            randomButton.setPosition(sf::Vector2f{ insertTextbox.getPositon().x + insertTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5, insertTextbox.getPositon().y });
            okButtonBackground.setPosition(sf::Vector2f{ insertTextbox.getPositon().x, insertTextbox.getPositon().y + insertTextbox.getGlobalBounds().height });
            okButton.setPosition(sf::Vector2f{ insertTextbox.getPositon().x + (insertTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5, insertTextbox.getPositon().y + insertTextbox.getGlobalBounds().height });

            insertTextbox.typedOnNum(event, *m_context->window);
		

            if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int randomNum = std::rand() % 100 + 1;
                insertTextbox.insertNum(randomNum);
            }

            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
                (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {

                int value = insertTextbox.getNum();
                insertTextbox.reset();
                insertTextbox.setSelected(false);
				std::cerr << "insert:" << value << std::endl;
				createInsertFrames(value);
            }
        }
        else
        {


            insertTextbox.setSelected(false);
            insertTextbox.setInvisible();
            if(!isSelectedCreateButton)
            if(!isSelectedInsertButton)
		    if (!isSelectedDeleteButton)
			if (!isSelectedSearchButton)
			{
				randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
				okButton.setPosition(sf::Vector2f{ -1000, -1000 });
			}
        }

   
}
void AVLMainState::handleDeleteButtonEvents(const sf::Event& event) {
    deleteButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (deleteButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        isSelectedCreateButton = false;
        isSelectedInsertButton = false;
        isSelectedSearchButton = false;
        isSelectedInorderButton = false;
		isSelectedDeleteButton ^= 1;
    }
        if (isSelectedDeleteButton)
        {

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
			//std::cerr << "delete:" << std::endl;
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
                (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {

                int value = deleteTextbox.getNum();
                deleteTextbox.reset();
                deleteTextbox.setSelected(false);

				std::cerr << "delete:" << value << std::endl;
                initDeleteFrames(value);
				currentState = "delete";
            }
        }
        else
        {

            deleteTextbox.setSelected(false);
            deleteTextbox.setInvisible();
			if (!isSelectedCreateButton)
				if (!isSelectedInsertButton)
					if (!isSelectedDeleteButton)
						if (!isSelectedSearchButton)
                            {
                                randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
                                okButton.setPosition(sf::Vector2f{ -1000, -1000 });
                            }
        }
        // Handle delete button click
    
}
void AVLMainState::handleSearchButtonEvents(const sf::Event& event) {
    searchButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (searchButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        isSelectedCreateButton = false;
        isSelectedInsertButton = false;
        isSelectedDeleteButton = false;
        isSelectedInorderButton = false;
        isSelectedSearchButton ^= 1;
    }

        if (isSelectedSearchButton)
        {
            
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

            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
                (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {

                int value = searchTextbox.getNum();
                searchTextbox.reset();
                searchTextbox.setSelected(false);
				//std::cerr << "search:" << value << std::endl;
                deleteAllFrames();

                initSearchFrames(value);
				currentState = "search";
				aniSlider.setNumPart(b_frames.size());
				aniSlider.setBreakpoints(breakpoints);
				isPlaying = true;
				isPaused = false;
				isEnd = false;
            }
        }
        else
        {

            searchTextbox.setSelected(false);
            searchTextbox.setInvisible();
			if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton) {
                    randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
                    okButton.setPosition(sf::Vector2f{ -1000, -1000 });
            }

        }
    
}
void AVLMainState::handleInorderButtonEvents(const sf::Event& event)
{
	inorderButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (inorderButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Handle insert button click
        isSelectedCreateButton = false;
        isSelectedInsertButton = false;
        isSelectedDeleteButton = false;
        isSelectedSearchButton = false;
		isSelectedInorderButton ^= 1;
    }
		if (isSelectedInorderButton)
		{

			inorderButton.setBackColor(hoverButtonColor);
			okButtonBackground.setPosition(sf::Vector2f{ 5 + inorderButton.getPositon().x + inorderButton.getGlobalBounds().width, inorderButton.getPositon().y });
			okButton.setPosition(sf::Vector2f{ inorderButton.getPositon().x + (inorderButton.getGlobalBounds().width + 50) , inorderButton.getPositon().y  });
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
                (okButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed
                    && event.mouseButton.button == sf::Mouse::Left))
            {
				createInorderFrames();
            }

		}
		else
		{

			//initInorderFrames();
			if (!isSelectedCreateButton)
				if (!isSelectedInsertButton)
					if (!isSelectedDeleteButton)
						if (!isSelectedSearchButton)
							{
								randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
								okButton.setPosition(sf::Vector2f{ -1000, -1000 });
							}
		}

}

void AVLMainState::handleHomeButtonEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (homeButton.isMouseOverCircle(*m_context->window)) {
            m_context->stateMachine->removeState();
        }
    }
}
void AVLMainState::handleThemeButtonEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (themeButton.isMouseOver(*m_context->window)) {
            switchTheme();
        }
    }
}
void AVLMainState::handleAniSliderEvents(const sf::Event& event) {
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
void AVLMainState::handleSpeedSliderEvents(const sf::Event& event) {
    speedSlider.handleEvent(event);
    std::string st = "1.0x";
    st[0] = char(speedSlider.getPartIndex() + 1 + '0');
    *m_context->TIME_PER_FRAME = sf::seconds(1.f / 60.f / static_cast<float>(speedSlider.getPartIndex() + 1));
    speedSlider.setMaxText(st);
}




