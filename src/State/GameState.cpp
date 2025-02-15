#include "GameState.h"

GameState::GameState(std::shared_ptr<Context>& context)
{
	m_context = context;

}

GameState::~GameState()
{

}

void GameState::init()
{
	background.setTexture(m_context->assetManager->getTexture("background"));
	background.setScale(0.5, 0.5);
	background.setPosition(0, 0);
}

void GameState::pause()
{
}

void GameState::resume()
{
}

void GameState::processEvents()
{
	sf::Event event;
	while (m_context->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->window->close();
		}
	}
}

void GameState::update(const sf::Time& dt)
{
}

void GameState::draw()
{
	m_context->window->clear();
	m_context->window->draw(background);
	m_context->window->display();
}

