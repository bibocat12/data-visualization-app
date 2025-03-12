#include "AVLMainState.h"

AVLMainState::AVLMainState(std::shared_ptr<Context>& context)
{
	m_context = context;
}

AVLMainState::~AVLMainState()
{
}

void AVLMainState::init()
{
}

void AVLMainState::pause()
{
}

void AVLMainState::resume()
{
}

void AVLMainState::processEvents()
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

void AVLMainState::update(const sf::Time& dt)
{

}

void AVLMainState::draw()
{
	m_context->window->clear(sf::Color::Blue);
	Node node;

	node.setRadius(25);
	node.setPosition(sf::Vector2f(100, 100));
	node.setFillColor(sf::Color::Red);
	node.setOutlineColor(sf::Color::Black);
	node.setOutlineThickness(-5);
	node.setString("Hello");
	node.setFont(m_context->assetManager->getFont("arial"));
	node.setTextUnder("20", 20, sf::Color::Red);
	node.drawTo(*m_context->window);
	m_context->window->display();
}

