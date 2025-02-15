#include "MenuStage.h"

MenuStage::MenuStage(std::shared_ptr<Context>& context) : m_context(context)
{

}

MenuStage::~MenuStage()
{

}

void MenuStage::init()
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

	buttonPlay.setTexture(m_context->assetManager->getTexture("buttonPlay"));
	buttonPlay.setScale(0.5, 0.5);
	buttonPlay.setPosition(100, 300);


}

void MenuStage::pause()
{

}

void MenuStage::resume()
{
}

void MenuStage::processEvents()
{
	sf::Event event;
	while (m_context->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->window->close();
		}
		else
		{
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
						sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->window);
						sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
						if (buttonPlay.getGlobalBounds().contains(mousePosF))
						{
							m_context->stateMachine->addState(std::make_unique<GameState>(m_context), false);

						}
					}
				}
		}
	}
}

void MenuStage::update(const sf::Time& dt)
{

}

void MenuStage::draw()
{

	m_context->window->clear(sf::Color::Blue);
	m_context->window->draw(background);

	m_context->window->draw(title);
	m_context->window->draw(testingEvent);
	m_context->window->draw(buttonPlay);

	m_context->window->display();
}
