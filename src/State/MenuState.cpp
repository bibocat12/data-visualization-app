#include "MenuState.h"

MenuState::MenuState(std::shared_ptr<Context>& context) : m_context(context)
{

}

MenuState::~MenuState()
{

}

std::pair<Button, ImageButton> MenuState::initButton(char* text, sf::Texture image, sf::Vector2f pos) {
	Button button;
	ImageButton imgButton;
	button = Button(text, sf::Vector2f{ 200, 200 }, 24, Orange, sf::Color::White);
	button.setFont(m_context->assetManager->getFont("arial"));
	button.setLowTextPosition(pos);

	imgButton = ImageButton(image, 1.0f, 1.0f);
	float xPos = button.getPositon().x + (button.getGlobalBounds().width - imgButton.getGlobalBounds().width) / 2;
	float yPos = button.getPositon().y;
	imgButton.setPosition(sf::Vector2f{ xPos, yPos });

	return std::make_pair(button, imgButton);
}

void MenuState::init()
{
	background.setTexture(m_context->assetManager->getTexture("background"));
	background.setScale(0.5, 0.5);
	background.setPosition(0, 0);


	title.setFont(m_context->assetManager->getFont("arial"));
	title.setString("Menu Stage");
	title.setCharacterSize(24);
	title.setFillColor(sf::Color::Black);
	title.setPosition(100, 100);

	testingEvent.setFont(m_context->assetManager->getFont("arial"));
	testingEvent.setCharacterSize(24);
	testingEvent.setFillColor(sf::Color::Black);
	testingEvent.setPosition(100, 200);

	buttons.push_back(initButton("Singly Linked List", m_context->assetManager->getTexture("SinglyLinkedList"), sf::Vector2f{150, 150}));

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
		
		//buttonPlay.handleHover(*m_context->window);
		for(int i = 0; i < (int) buttons.size(); i++) 
		{
			buttons[i].second.handleHover(*m_context->window, m_context->assetManager->getTexture("SinglyLinkedList"), m_context->assetManager->getTexture("SinglyLinkedList"));
		}

		if (event.type == sf::Event::KeyPressed)
		{
			std::string key = std::to_string(event.key.code);
			testingEvent.setString("Key Pressed: " + key);
		}
		else {
			for (int i = 0; i < (int)buttons.size(); i++) {
				buttons[i].first.handleHover(*m_context->window, Orange, Yellow);

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					m_context->stateMachine->addState(std::make_unique<SinglyLinkedListMainState>(m_context), 0);
				}
				break;
			}
		}
		
	}
}

void MenuState::update(const sf::Time& dt)
{

}

void MenuState::draw()
{

	m_context->window->clear(sf::Color(40, 40, 40)); // light black
	//m_context->window->draw(background);

	m_context->window->draw(title);
	m_context->window->draw(testingEvent);
	//buttonPlay.drawTo(*m_context->window);

	for (int i = 0; i < (int) buttons.size(); i++) {
		buttons[i].first.drawTo(*m_context->window);
		buttons[i].second.drawTo(*m_context->window);
	}

	m_context->window->display();
}
