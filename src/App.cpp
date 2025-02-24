#include "App.h"


App::App()
	: m_context(std::make_shared<Context>() )
{
	if (m_context->window) {
		m_context->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Data Visualizer App");
	}
	else {
		std::cout << "Error cannot create a window";
	}

	m_context->assetManager->loadTexture("background", "assets/img/background/light.jpg");
	m_context->assetManager->loadTexture("buttonPlay", "assets/img/button/buttonPlay.jpg");
	m_context->assetManager->loadTexture("SinglyLinkedList", "assets/img/button/SinglyLinkedList.png");
	m_context->assetManager->loadTexture("LightTheme", "assets/img/button/LightTheme.png");
	m_context->assetManager->loadTexture("DarkTheme", "assets/img/button/DarkTheme.png");


	m_context->assetManager->loadFont("arial", "assets/font/arial/ARIAL.TTF");
	m_context->assetManager->loadFont("Oswald", "assets/font/Oswald/static/Oswald-Bold.TTF");

	m_context->stateMachine->addState(std::make_unique<MenuState>(m_context), 0);

}

App::~App()
{
}


void App::run()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);


	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_context->window->isOpen())
	{

		sf::Time dt = m_clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			m_dt = TIME_PER_FRAME;
			m_context->stateMachine->processStateChanges();

			if (m_context->stateMachine->getActiveState() == nullptr)
			{
				m_context->window->close();
				break;
			}

			m_context->stateMachine->getActiveState()->processEvents();
			m_context->stateMachine->getActiveState()->update(m_dt);
			m_context->stateMachine->getActiveState()->draw();
		}


	}

}
