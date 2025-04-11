#include "../../header/State/MenuState.h"

MenuState::MenuState(std::shared_ptr<Context>& context) : m_context(context)
{

}

MenuState::~MenuState()
{

}

std::pair<Button, ImageButton> MenuState::initButton(char* text, sf::Texture& image, sf::Vector2f pos) {
	Button button;
	ImageButton imgButton;
	button = Button(text, buttonSize, 24, normalButtonColor, textColor);
	button.setFont(m_context->assetManager->getFont("Oswald"));
	button.setLowTextPosition(pos);

	imgButton = ImageButton(image, 1.0f, 1.0f);
	float xPos = button.getPositon().x + (button.getGlobalBounds().width - imgButton.getGlobalBounds().width) / 2;
	float yPos = button.getPositon().y;
	imgButton.setPosition(sf::Vector2f{ xPos, yPos });

	return std::make_pair(button, imgButton);
}

void MenuState::switchTheme() {
	*m_context->themeType ^= 1;
	themeType ^= 1;
	if (*m_context->themeType == 1) { // dark mode
		backgroundColor = LightBlack;
		textColor = sf::Color::White;
		normalButtonColor = Orange;
		hoverButtonColor = LightOrangeYellow;
		themeButton.setBackground(m_context->assetManager->getTexture("LightTheme"));

		// change text color
		for (int i = 0; i < (int)buttons.size(); i++) {
			buttons[i].first.setTextColor(textColor);
		}
		title.setFillColor(textColor);
	}
	else if (*m_context->themeType == 0) { // light mode
		backgroundColor = SuperLightPink;
		textColor = sf::Color::Black;
		normalButtonColor = LightBlue;
		hoverButtonColor = MediumBlue;
		themeButton.setBackground(m_context->assetManager->getTexture("DarkTheme"));

		// change text color
		for (int i = 0; i < (int)buttons.size(); i++) {
			buttons[i].first.setTextColor(textColor);
		}
		title.setFillColor(textColor);
	}
}

void MenuState::init()
{
	testingEvent.setFont(m_context->assetManager->getFont("arial"));
	testingEvent.setCharacterSize(24);
	testingEvent.setFillColor(sf::Color::Black);
	testingEvent.setPosition(100, 200);


	// Init theme
	themeType = *m_context->themeType;
	themeButton = ImageButton(m_context->assetManager->getTexture("LightTheme"), 1.0f, 1.0f);
	switchTheme();

	// Init title
	title.setFont(m_context->assetManager->getFont("Oswald"));
	title.setString("DS VISUALIZATION");
	title.setCharacterSize(130);
	title.setFillColor(textColor);
	title.setPosition((SCREEN_WIDTH - title.getGlobalBounds().width) / 2, 40);

	//Init Button
	buttonSize.x = 250;
	buttonSize.y = 200;
	float spaceX = static_cast<float>((SCREEN_WIDTH - 250 * 3) / 4);
	float spaceY = 50.f;

	buttons.push_back(initButton("Singly Linked List", m_context->assetManager->getTexture("SinglyLinkedList"), sf::Vector2f{spaceX, 375}));
	buttons.push_back(initButton("Heap", m_context->assetManager->getTexture("Heap"), sf::Vector2f{2 * spaceX + buttonSize.x, 375}));
	buttons.push_back(initButton("AVL Tree", m_context->assetManager->getTexture("AVL"), sf::Vector2f{3 * spaceX + 2 * buttonSize.x, 375}));
	buttons.push_back(initButton("Trie", m_context->assetManager->getTexture("Trie"), sf::Vector2f{spaceX, 375 + spaceY + buttonSize.y}));
	buttons.push_back(initButton("2-3-4 Tree", m_context->assetManager->getTexture("Tree234"), sf::Vector2f{2 * spaceX + buttonSize.x, 375 + spaceY + buttonSize.y}));
	buttons.push_back(initButton("Graph", m_context->assetManager->getTexture("Graph"), sf::Vector2f{3 * spaceX + 2 * buttonSize.x, 375 + spaceY + buttonSize.y}));
	themeButton.setPosition(sf::Vector2f{ 1450, 30 });

}

void MenuState::pause()
{

}

void MenuState::resume()
{
}

void MenuState::processEvents()
{
	sf::Event event;
	while (m_context->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->window->close();
			return;
		}

		std::vector<std::string> texture = { "SinglyLinkedList", "Heap", "AVL", "Trie", "Tree234", "Graph" };
		for (int i = 0; i < (int)buttons.size(); i++) {
			buttons[i].second.handleHover(*m_context->window, m_context->assetManager->getTexture(texture[i]), m_context->assetManager->getTexture(texture[i]));
			buttons[i].first.handleHover(*m_context->window, normalButtonColor, hoverButtonColor);

			if (i == 0 && buttons[i].first.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cerr << "Singly linked list\n";
				m_context->stateMachine->addState(std::make_unique<SinglyLinkedListMainState>(m_context), 0);
				break;
			}

			if (i == 1 && buttons[i].first.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cerr << "Heap\n";
				m_context->stateMachine->addState(std::make_unique<HeapMainState>(m_context), 0);
				break;
			}

			if (i == 2 && buttons[i].first.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cerr << "AVL\n";
				m_context->stateMachine->addState(std::make_unique<AVLMainState>(m_context), 0);
				break;
			}

			if (i == 3 && buttons[i].first.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cerr << "Trie " << i << "\n";
				m_context->stateMachine->addState(std::make_unique<TrieMainState>(m_context), 0);
				break;
			}

			if (i == 4 && buttons[i].first.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cerr << "Tree234\n";
				m_context->stateMachine->addState(std::make_unique<Tree234MainState>(m_context), 0);
				break;
			}

			if (i == 5 && buttons[i].first.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cerr << "Graph\n";
				m_context->stateMachine->addState(std::make_unique<GraphMainState>(m_context), 0);
				break;
			}
		}

		if (themeButton.isMouseOver(*m_context->window) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			std::cerr << "Theme Button\n";
			switchTheme();
		}

	}
}

void MenuState::update(const sf::Time& dt)
{

}

void MenuState::draw()
{
	if (themeType != *m_context->themeType) {
		*m_context->themeType ^= 1;
		switchTheme();
	}

	m_context->window->clear(backgroundColor);
	m_context->window->draw(title);
	m_context->window->draw(testingEvent);

	for (int i = 0; i < (int)buttons.size(); i++) {
		buttons[i].first.drawTo(*m_context->window);
		buttons[i].second.drawTo(*m_context->window);
	}
	themeButton.drawTo(*m_context->window);

	m_context->window->display();
}