#include "TrieMainState.h"
#include <cmath> // Required for std::pow

TrieMainState::TrieMainState(std::shared_ptr<Context>& context) : m_context(context) {
    // Init theme
    initTheme();

    // Init title
    initTitle();

    // Init function buttons
    initFunctionButton();

    // Init code panel
    initCodePanel();

    // Init animation slider
    initAniSlider();

    // Init speed slider
    initSpeedSlider();

    
    std::vector<std::string> words = { "apple", "banana", "cherry", "date", "fig", "grape" };
    //initCreateFrames(words);
}

TrieMainState::~TrieMainState() {
    deleteAllFrames(); // Clean up frames
}

void TrieMainState::init() {}
void TrieMainState::pause() {}
void TrieMainState::resume() {}

void TrieMainState::processEvents() {
    sf::Event event;
    while (m_context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
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
}

void TrieMainState::update(const sf::Time& dt) {
    pauseButton.setPosition(sf::Vector2f(-1000, -1000));
    playButton.setPosition(sf::Vector2f(-1000, -1000));
    replayButton.setPosition(sf::Vector2f(-1000, -1000));

    if (isEnd)
        replayButton.setPosition(sf::Vector2f{
            aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - replayButton.getGlobalBounds().width) / 2,
            aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15
            });
    else if (isPaused)
        playButton.setPosition(sf::Vector2f{
            aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - playButton.getGlobalBounds().width) / 2,
            aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15
            });
    else
        pauseButton.setPosition(sf::Vector2f{
            aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - pauseButton.getGlobalBounds().width) / 2,
            aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15
            });

    if (!isPaused && isPlaying)
        aniSlider.setPart(currentFrameIndex + 1);

    if (isPaused && isPlaying) {
        int part = aniSlider.getPartIndex();
        currentFrameIndex = part;
    }

    updateFrames();
}

void TrieMainState::draw() {
    m_context->window->clear(backgroundColor);
    m_context->window->draw(title);

    createButton.drawTo(*m_context->window);
    insertButton.drawTo(*m_context->window);
    deleteButton.drawTo(*m_context->window);
    searchButton.drawTo(*m_context->window);

    themeButton.drawTo(*m_context->window);
    homeButton.drawTo(*m_context->window);
    if (currentState == "cteate" || currentState == "insert" || currentState == "delete" || currentState == "search") {
        codePanel.draw(*m_context->window);
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

    insertTextbox.drawTo(*m_context->window);
    deleteTextbox.drawTo(*m_context->window);
    searchTextbox.drawTo(*m_context->window);
    createTextbox.drawTo(*m_context->window);
    okButtonBackground.drawTo(*m_context->window);
    okButton.drawTo(*m_context->window);
    randomButton.drawTo(*m_context->window);
    uploadFileButton.drawTo(*m_context->window);

    currentFrame.drawAll(*m_context->window);
    m_context->window->display();
}

void TrieMainState::initTextbox(Textbox& textbox, int charSize, sf::Color textColor, sf::Font& font, sf::Vector2f pos) {
    textbox = Textbox(charSize, textColor, false);
    textbox.setFont(m_context->assetManager->getFont("JetBrainsMono-SemiBold"));
    textbox.setPosition(pos);
    textbox.setBox(sf::Vector2f{ 200, buttonSize.y }, BeigeGrey);
   
}

void TrieMainState::switchTheme() {
    *m_context->themeType ^= 1;
    if (*m_context->themeType == 1) { // dark mode
        backgroundColor = LightBlack;
        textColor = sf::Color::White;
        normalButtonColor = Orange;
        hoverButtonColor = LightOrangeYellow;
        themeButton.setBackground(m_context->assetManager->getTexture("LightTheme"));

        createButton.setTextColor(textColor);
        insertButton.setTextColor(textColor);
        deleteButton.setTextColor(textColor);
        searchButton.setTextColor(textColor);
        displayButton.setTextColor(textColor);
        title.setFillColor(textColor);
        codePanel.setTextColor(textColor);
    }
    else { // light mode
        backgroundColor = SuperLightPink;
        textColor = sf::Color::Black;
        normalButtonColor = LightBlue;
        hoverButtonColor = MediumBlue;
        themeButton.setBackground(m_context->assetManager->getTexture("DarkTheme"));

        createButton.setTextColor(textColor);
        insertButton.setTextColor(textColor);
        deleteButton.setTextColor(textColor);
        searchButton.setTextColor(textColor);
        displayButton.setTextColor(textColor);
        title.setFillColor(textColor);
        codePanel.setTextColor(textColor);
    }
}

void TrieMainState::initFunctionButton() {
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
    insertTextbox.setConstText("w = ");
    insertTextbox.setLimit(true, 8);

    initTextbox(deleteTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
    deleteTextbox.setConstText("w = ");
    deleteTextbox.setLimit(true, 8);

    initTextbox(searchTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
    searchTextbox.setConstText("w = ");
    searchTextbox.setLimit(true, 8);

    initTextbox(createTextbox, 18, textColor, m_context->assetManager->getFont("JetBrainsMono-Regular"), sf::Vector2f{ 5 + createButton.getPositon().x + createButton.getGlobalBounds().width, createButton.getPositon().y });
    createTextbox.setConstText("n = ");
    createTextbox.setLimit(true, 2);
}

void TrieMainState::initCodePanel() {
    int numLine = 7;
    labelSize = sf::Vector2f(500, static_cast<float>((SCREEN_HEIGHT - 20 - checkpointY) / numLine));
    codePanel = Panel(sf::Vector2f{ SCREEN_WIDTH - 10 - labelSize.x, checkpointY }, labelSize, textColor, LavenderSoft, m_context->assetManager->getFont("JetBrainsMono-Regular"), 18);
    codePanel.add("insert word");
    codePanel.add("if node not found");
    codePanel.add("  create node");
    codePanel.add("");
    codePanel.add("");
    codePanel.add("");
    codePanel.add("");
}

void TrieMainState::initTheme() {
    *m_context->themeType ^= 1;
    themeButton = ImageButton(m_context->assetManager->getTexture("LightTheme"), 1.0f, 1.0f);
    switchTheme();
    themeButton.setPosition(sf::Vector2f{ 1450, 30 });
}

void TrieMainState::initTitle() {
    title.setCharacterSize(34);
    title.setFont(m_context->assetManager->getFont("Oswald"));
    title.setString("Trie");
    homeButton = ImageButton(m_context->assetManager->getTexture("HomeButton"), 1.0f, 1.0f);
    homeButton.setPosition(sf::Vector2f{
        (SCREEN_WIDTH - title.getGlobalBounds().width) / 2 - homeButton.getGlobalBounds().width - 15, 10
        });

    title.setFillColor(textColor);
    title.setPosition((SCREEN_WIDTH - title.getGlobalBounds().width) / 2,
        homeButton.getPosition().y + (homeButton.getGlobalBounds().height - title.getCharacterSize()) / 2);
}

void TrieMainState::initSpeedSlider() {
    speedSlider = Slider(sf::Vector2f{ aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - 300) / 2, playButton.getPosition().y + playButton.getGlobalBounds().height + 15 }, sf::Vector2f{ 300, 15.f }, sf::Vector2f{ 20, 20 });
    speedSlider.setColor(LightGray, NavyBlue, GoldenOrange);
    speedSlider.setNumPart(7);
    speedSlider.setText("0.5x", "1.0x", 20, m_context->assetManager->getFont("Neon"), textColor);
    speedSlider.setPart(1);
}

void TrieMainState::initAniSlider() {
    checkpointY = 650;
    aniSlider = Slider(sf::Vector2f{ buttonSize.x + 50, checkpointY },
        sf::Vector2f{ SCREEN_WIDTH - 10 - labelSize.x - buttonSize.x - 100, 20.f },
        sf::Vector2f{ 20, 20 });
    aniSlider.setColor(LightGray, RoyalBlue, Gold);

    playButton = ImageButton(m_context->assetManager->getTexture("Play"), 1.0f, 1.0f);
    playButton.setPosition(sf::Vector2f{
        aniSlider.getPositon().x + (aniSlider.getGlobalBounds().width - playButton.getGlobalBounds().width) / 2,
        aniSlider.getPositon().y + aniSlider.getGlobalBounds().height + 15
        });

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

void TrieMainState::initButton(Button& button, std::string text, sf::Vector2f pos) {
    button = Button(text, buttonSize, 20, normalButtonColor, textColor);
    button.setFont(m_context->assetManager->getFont("Oswald"));
    button.setPosition(pos);
}

void TrieMainState::handleButtonEvents(const sf::Event& event) {
    handleCreateButtonEvents(event);
    handleInsertButtonEvents(event);
    handleDeleteButtonEvents(event);
    handleSearchButtonEvents(event);
    handleHomeButtonEvents(event);
    handleThemeButtonEvents(event);
}

void TrieMainState::handleCreateButtonEvents(const sf::Event& event) {
   
    auto randomString = []() -> std::string {
        int len = static_cast<int>(Utils::rand(1, 8)); // Use Utils::rand to determine length
        std::string s;
        s.reserve(len);
        for (int i = 0; i < len; ++i) {
            char c = static_cast<char>(Utils::rand('a', 'f')); // Random character from 'a' to 'z'
            s.push_back(c);
        }
        return s;
        };
    
    createButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (createButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        isSelectedCreateButton ^= 1;
        isSelectedInsertButton = false;
        isSelectedDeleteButton = false;
        isSelectedSearchButton = false;
        isSelectedDisplayButton = false;
    }

    if (isSelectedCreateButton) {
        createButton.setBackColor(hoverButtonColor);
        createTextbox.setVisible();
        randomButton.setPosition(sf::Vector2f{
            createTextbox.getPositon().x + createTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5,
            createTextbox.getPositon().y
            });
        uploadFileButton.setPosition(sf::Vector2f{
            randomButton.getPosition().x - uploadFileButton.getGlobalBounds().width - 5,
            createTextbox.getPositon().y
            });
        okButtonBackground.setPosition(sf::Vector2f{
            createTextbox.getPositon().x,
            createTextbox.getPositon().y + createTextbox.getGlobalBounds().height
            });
        okButton.setPosition(sf::Vector2f{
            createTextbox.getPositon().x + (createTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5,
            createTextbox.getPositon().y + createTextbox.getGlobalBounds().height
            });

        createTextbox.typedOnNum(event, *m_context->window);

        if (randomButton.isMouseOverCircle(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int randomNum = std::rand() % 20;
            createTextbox.insertNum(randomNum);
        }

     
        if (uploadFileButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            auto selection = pfd::open_file("Select a file", "", { "All Files", "*" }).result();
            if (!selection.empty()) {
                std::string filename = selection[0];
                std::ifstream fileIn(filename);
                if (fileIn.is_open()) {
                    std::vector<std::string> words;
                    std::string word;
                    while (fileIn >> word) {
                        words.push_back(word);
                    }
                    createTextbox.insertText(std::to_string(words.size()));
                 //   initCreateFrames(words);
                    currentState = "create";
                }
                else {
                    std::cerr << "Can't open the file\n";
                }
                fileIn.close();
            }
            else {
                std::cout << "No file selected." << std::endl;
            }
        }

        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
            (okButton.isMouseOver(*m_context->window) &&
                event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
            int n = std::stoi(createTextbox.getText());
            createTextbox.reset();
            std::vector<std::string> allWords;
            
			std::cerr << "n = " << n << std::endl;
            for (int i = 0; i < n; i++) {

                allWords.push_back(randomString());

                std::cerr << allWords[i] << " ";
            }
			std::cerr << std::endl;
            initCreateFrames(allWords);
            currentState = "create";
        }
    }
    else {
        createTextbox.setSelected(false);
        createTextbox.setInvisible();
        uploadFileButton.setPosition(sf::Vector2f{ -1000, -1000 });
        if (!isSelectedCreateButton && !isSelectedDeleteButton && !isSelectedInsertButton && !isSelectedSearchButton && !isSelectedDisplayButton) {
            randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
            okButton.setPosition(sf::Vector2f{ -1000, -1000 });
        }
    }
}

void TrieMainState::handleInsertButtonEvents(const sf::Event& event) {
    insertButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (insertButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        isSelectedCreateButton = false;
        isSelectedDeleteButton = false;
        isSelectedSearchButton = false;
        isSelectedDisplayButton = false;
        isSelectedInsertButton ^= 1;
    }
    if (isSelectedInsertButton) {
        insertButton.setBackColor(hoverButtonColor);
        insertTextbox.setVisible();
        randomButton.setPosition(sf::Vector2f{
            insertTextbox.getPositon().x + insertTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5,
            insertTextbox.getPositon().y
            });
        okButtonBackground.setPosition(sf::Vector2f{
            insertTextbox.getPositon().x,
            insertTextbox.getPositon().y + insertTextbox.getGlobalBounds().height
            });
        okButton.setPosition(sf::Vector2f{
            insertTextbox.getPositon().x + (insertTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5,
            insertTextbox.getPositon().y + insertTextbox.getGlobalBounds().height
            });

        insertTextbox.typedOnAlpha(event, *m_context->window);

        if (randomButton.isMouseOverCircle(*m_context->window) &&
            event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::vector<std::string> sampleWords = { "lambda", "omega", "sigma" };
            int randomIndex = std::rand() % sampleWords.size();
            insertTextbox.insertText(sampleWords[randomIndex]);
        }

        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
            (okButton.isMouseOver(*m_context->window) &&
                event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
            std::string word = insertTextbox.getText();
            insertTextbox.reset();
            insertTextbox.setSelected(false);
            createInsertFrames(word);
        }
    }
    else {
        insertTextbox.setSelected(false);
        insertTextbox.setInvisible();
        if (!isSelectedCreateButton && !isSelectedInsertButton && !isSelectedDeleteButton && !isSelectedSearchButton && !isSelectedDisplayButton) {
            randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
            okButton.setPosition(sf::Vector2f{ -1000, -1000 });
        }
    }
}

void TrieMainState::handleDeleteButtonEvents(const sf::Event& event) {
    deleteButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (deleteButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        isSelectedCreateButton = false;
        isSelectedInsertButton = false;
        isSelectedSearchButton = false;
        isSelectedDisplayButton = false;
        isSelectedDeleteButton ^= 1;
    }
    if (isSelectedDeleteButton) {
        deleteButton.setBackColor(hoverButtonColor);
        deleteTextbox.setVisible();
        randomButton.setPosition(sf::Vector2f{
            deleteTextbox.getPositon().x + deleteTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5,
            deleteTextbox.getPositon().y
            });
        okButtonBackground.setPosition(sf::Vector2f{
            deleteTextbox.getPositon().x,
            deleteTextbox.getPositon().y + deleteTextbox.getGlobalBounds().height
            });
        okButton.setPosition(sf::Vector2f{
            deleteTextbox.getPositon().x + (deleteTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5,
            deleteTextbox.getPositon().y + deleteTextbox.getGlobalBounds().height
            });

        deleteTextbox.typedOnAlpha(event, *m_context->window);

        if (randomButton.isMouseOverCircle(*m_context->window) &&
            event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::vector<std::string> sampleWords = { "delta", "epsilon", "zeta" };
            int randomIndex = std::rand() % sampleWords.size();
            deleteTextbox.insertText(sampleWords[randomIndex]);
        }

        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
            (okButton.isMouseOver(*m_context->window) &&
                event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
            std::string word = deleteTextbox.getText();
            deleteTextbox.reset();
            deleteTextbox.setSelected(false);
            createDeleteFrames(word);
        }
    }
    else {
        deleteTextbox.setSelected(false);
        deleteTextbox.setInvisible();
        if (!isSelectedCreateButton && !isSelectedInsertButton && !isSelectedDeleteButton && !isSelectedSearchButton && !isSelectedDisplayButton) {
            randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
            okButton.setPosition(sf::Vector2f{ -1000, -1000 });
        }
    }
}

void TrieMainState::handleSearchButtonEvents(const sf::Event& event) {
    searchButton.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);
    if (searchButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        isSelectedCreateButton = false;
        isSelectedInsertButton = false;
        isSelectedDeleteButton = false;
        isSelectedDisplayButton = false;
        isSelectedSearchButton ^= 1;
    }
    if (isSelectedSearchButton) {
        searchButton.setBackColor(hoverButtonColor);
        searchTextbox.setVisible();
        randomButton.setPosition(sf::Vector2f{
            searchTextbox.getPositon().x + searchTextbox.getGlobalBounds().width - randomButton.getGlobalBounds().width - 5,
            searchTextbox.getPositon().y
            });
        okButtonBackground.setPosition(sf::Vector2f{
            searchTextbox.getPositon().x,
            searchTextbox.getPositon().y + searchTextbox.getGlobalBounds().height
            });
        okButton.setPosition(sf::Vector2f{
            searchTextbox.getPositon().x + (searchTextbox.getGlobalBounds().width - okButton.getGlobalBounds().width) / 2 - 5,
            searchTextbox.getPositon().y + searchTextbox.getGlobalBounds().height
            });

        searchTextbox.typedOnAlpha(event, *m_context->window);

        if (randomButton.isMouseOverCircle(*m_context->window) &&
            event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::vector<std::string> sampleWords = { "apple", "banana", "cherry" };
            int randomIndex = std::rand() % sampleWords.size();
            searchTextbox.insertText(sampleWords[randomIndex]);
        }

        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) ||
            (okButton.isMouseOver(*m_context->window) &&
                event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
            std::string word = searchTextbox.getText();
            searchTextbox.reset();
            searchTextbox.setSelected(false);
            deleteAllFrames();
            createSearchFrames(word);
        }
    }
    else {
        searchTextbox.setSelected(false);
        searchTextbox.setInvisible();
        if (!isSelectedCreateButton && !isSelectedInsertButton && !isSelectedDeleteButton && !isSelectedSearchButton && !isSelectedDisplayButton) {
            randomButton.setPosition(sf::Vector2f{ -1000, -1000 });
            okButton.setPosition(sf::Vector2f{ -1000, -1000 });
        }
    }
}


void TrieMainState::handleHomeButtonEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (homeButton.isMouseOverCircle(*m_context->window)) {
            m_context->stateMachine->removeState();
        }
    }
}

void TrieMainState::handleThemeButtonEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (themeButton.isMouseOver(*m_context->window)) {
            switchTheme();
        }
    }
}

void TrieMainState::handleAniSliderEvents(const sf::Event& event) {
    if (numFrames == 0) return;
    aniSlider.setNumPart(numFrames);

    if (!isPlaying)
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
            isPaused = true;
        if (playButton.isMouseOverCircle(*m_context->window))
            isPaused = false;
        if (replayButton.isMouseOverCircle(*m_context->window)) {
            isEnd = false;
            isPaused = false;
            currentFrameIndex = 0;
            aniSlider.setPart(0);
        }
        if (aniSlider.isMouseOverWindow(*m_context->window)) {
            isPaused = true;
            aniSlider.handleEvent(event);
            currentFrameIndex = aniSlider.getPartIndex();
            return;
        }
    }
    aniSlider.handleEvent(event);
    currentFrameIndex = aniSlider.getPartIndex();
}

void TrieMainState::handleSpeedSliderEvents(const sf::Event& event) {
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


