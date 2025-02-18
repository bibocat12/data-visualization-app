#include "SinglyLinkedListMainState.h"

SinglyLinkedListMainState::SinglyLinkedListMainState(std::shared_ptr<Context>& context) : m_context(context)
{
	startButton = Button("Start", { 200, 50 }, 20, sf::Color::Green, sf::Color::White );
	insertButton = Button("Insert", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);
	deleteButton = Button("Delete", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);
	searchButton = Button("Search", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);
	backButton = Button("Back", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);

	startButton.setPosition(sf::Vector2f(100, 100));
	insertButton.setPosition(sf::Vector2f(100, 200));
	deleteButton.setPosition(sf::Vector2f(100, 300));
	searchButton.setPosition(sf::Vector2f(100, 400));
	backButton.setPosition(sf::Vector2f(100, 500));


	background.setTexture(m_context->assetManager->getTexture("background"));
	background.setScale(0.5, 0.5);
	background.setPosition(0, 0);


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
		startButton.handleHover(*m_context->window);
		insertButton.handleHover(*m_context->window);
		deleteButton.handleHover(*m_context->window);
		searchButton.handleHover(*m_context->window);
		backButton.handleHover(*m_context->window);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (startButton.isMouseOver(*m_context->window))
			{
				m_context->stateMachine->addState(std::make_unique<MenuState>(m_context), 0);
			}
			if (insertButton.isMouseOver(*m_context->window))
			{
				m_context->stateMachine->addState(std::make_unique<MenuState>(m_context), 0);
			}
			if (deleteButton.isMouseOver(*m_context->window))
			{
				m_context->stateMachine->addState(std::make_unique<MenuState>(m_context), 0);
			}
			if (searchButton.isMouseOver(*m_context->window))
			{
				m_context->stateMachine->addState(std::make_unique<MenuState>(m_context), 0);
			}
			if (backButton.isMouseOver(*m_context->window))
			{
				m_context->stateMachine->removeState();
			}
		}
	}
}

void SinglyLinkedListMainState::update(const sf::Time& dt)
{

}

void SinglyLinkedListMainState::draw()
{
	m_context->window->clear();

	m_context->window->draw(background);
	startButton.drawTo(*m_context->window);
	insertButton.drawTo(*m_context->window);
	deleteButton.drawTo(*m_context->window);
	searchButton.drawTo(*m_context->window);
	backButton.drawTo(*m_context->window);

	m_context->window->display();

}
