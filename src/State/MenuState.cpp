#include "MenuState.h"

MenuState::MenuState(std::shared_ptr<Context>& context) : m_context(context)
{

}

MenuState::~MenuState()
{

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

	buttonPlay.setFront(m_context->assetManager->getFont("arial"));
	buttonPlay.setPosition(sf::Vector2f(100, 300));

	

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
		
		buttonPlay.handleHover(*m_context->window);

		if (event.type == sf::Event::KeyPressed)
		{
			std::string key = std::to_string(event.key.code);
			testingEvent.setString("Key Pressed: " + key);
		}
		else 
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (buttonPlay.isMouseOver(*m_context->window) == true) {
						m_context->stateMachine->addState(std::make_unique<SinglyLinkedListMainState>(m_context), 0);
					}
				}
			}
		
	}
}

void MenuState::update(const sf::Time& dt)
{

}

void MenuState::draw()
{

	m_context->window->clear(sf::Color::Blue);
	m_context->window->draw(background);

	m_context->window->draw(title);
	m_context->window->draw(testingEvent);
	buttonPlay.drawTo(*m_context->window);

	m_context->window->display();
}
