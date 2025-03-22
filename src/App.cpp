#include "App.h"
#include <SFML/System.hpp>
#include "State/MenuState.h"

App::App()
	: m_context(std::make_shared<Context>())
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	if (m_context->window) {
		m_context->window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Data Visualizer App", sf::Style::Default, settings);
	}
	else {
		std::cout << "Error cannot create a window";
	}

	m_context->assetManager->loadTexture("background", "assets/img/background/light.jpg");
	m_context->assetManager->loadTexture("buttonPlay", "assets/img/button/buttonPlay.jpg");
	m_context->assetManager->loadTexture("SinglyLinkedList", "assets/img/button/SinglyLinkedList.png");
	m_context->assetManager->loadTexture("LightTheme", "assets/img/button/LightTheme.png");
	m_context->assetManager->loadTexture("DarkTheme", "assets/img/button/DarkTheme.png");
	m_context->assetManager->loadTexture("HomeButton", "assets/img/button/HomeButton.png");
	m_context->assetManager->loadTexture("Play", "assets/img/button/Play.png");
	m_context->assetManager->loadTexture("Next", "assets/img/button/Next.png");
	m_context->assetManager->loadTexture("Previous", "assets/img/button/Previous.png");
	m_context->assetManager->loadTexture("Forward", "assets/img/button/Forward.png");
	m_context->assetManager->loadTexture("Rewind", "assets/img/button/Rewind.png");
	m_context->assetManager->loadTexture("Replay", "assets/img/button/Replay.png");
	m_context->assetManager->loadTexture("Pause", "assets/img/button/Pause.png");
	m_context->assetManager->loadTexture("Random", "assets/img/button/Random.png");
	m_context->assetManager->loadTexture("Ok", "assets/img/button/Ok.png");
	m_context->assetManager->loadTexture("UploadFile", "assets/img/button/UploadFile.png");


	m_context->assetManager->loadFont("arial", "assets/font/arial/ARIAL.TTF");
	m_context->assetManager->loadFont("Oswald", "assets/font/Oswald/static/Oswald-Bold.TTF");
	m_context->assetManager->loadFont("Oswald-Light", "assets/font/Oswald/static/Oswald-Light.TTF");
	m_context->assetManager->loadFont("JetBrainsMono-Regular", "assets/font/JetBrains_Mono/static/JetBrainsMono-Regular.TTF");
	m_context->assetManager->loadFont("JetBrainsMono-SemiBold", "assets/font/JetBrains_Mono/static/JetBrainsMono-SemiBold.TTF");
	m_context->assetManager->loadFont("Neon", "assets/font/Neon/Neon.TTF");

	m_context->themeType = std::make_unique<int>(0);
	m_context->TIME_PER_FRAME = std::make_unique<sf::Time>(sf::seconds(1.f / 60.f)); // Default to 60 FPS
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
	srand(time(NULL));
	m_context->window->setVerticalSyncEnabled(false);
	m_context->window->setFramerateLimit(0);
	while (m_context->window->isOpen())
	{

		sf::Time dt = m_clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > *m_context->TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= *m_context->TIME_PER_FRAME;
			m_context->stateMachine->processStateChanges();

			if (m_context->stateMachine->getActiveState() == nullptr)
			{
				m_context->window->close();
				break;
			}

			m_context->stateMachine->getActiveState()->processEvents();
			m_dt = *m_context->TIME_PER_FRAME;
			m_context->stateMachine->getActiveState()->update(m_dt);
			m_context->stateMachine->getActiveState()->draw();
		}


	}

}