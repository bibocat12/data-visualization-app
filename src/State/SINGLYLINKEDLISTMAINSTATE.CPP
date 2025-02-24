#include "SinglyLinkedListMainState.h"


SinglyLinkedListMainState::SinglyLinkedListMainState(std::shared_ptr<Context>& context) : m_context(context)
{
	startButton = Button("Start", { 200, 50 }, 20, sf::Color::Green, sf::Color::White );
	randomButton = Button("Random", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);
	insertButton = Button("Insert", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);
	deleteButton = Button("Delete", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);
	searchButton = Button("Search", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);
	backButton = Button("Back", { 200, 50 }, 20, sf::Color::Green, sf::Color::White);

	startButton.setPosition(sf::Vector2f(100, 100));
	randomButton.setPosition(sf::Vector2f(100, 200));
	insertButton.setPosition(sf::Vector2f(100, 300));
	deleteButton.setPosition(sf::Vector2f(100, 400));
	searchButton.setPosition(sf::Vector2f(100, 500));
	backButton.setPosition(sf::Vector2f(100, 600));

	startButton.setFont(m_context->assetManager->getFont("Oswald"));
	randomButton.setFont(m_context->assetManager->getFont("Oswald"));
	insertButton.setFont(m_context->assetManager->getFont("Oswald"));
	deleteButton.setFont(m_context->assetManager->getFont("Oswald"));
	searchButton.setFont(m_context->assetManager->getFont("Oswald"));
	backButton.setFont(m_context->assetManager->getFont("Oswald"));

	startButton.setText("start");	
	randomButton.setText("random");
	insertButton.setText("insert");
	deleteButton.setText("delete");
	searchButton.setText("search");
	backButton.setText("back");

	startButton.setTextColor(sf::Color::White);


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
		startButton.handleHover(*m_context->window, Orange, Yellow);
		randomButton.handleHover(*m_context->window, Orange, Yellow);
		insertButton.handleHover(*m_context->window, Orange, Yellow);
		deleteButton.handleHover(*m_context->window, Orange, Yellow);
		searchButton.handleHover(*m_context->window, Orange, Yellow);
		backButton.handleHover(*m_context->window, Orange, Yellow);

		handleButtonEvents(event);
		
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
	randomButton.drawTo(*m_context->window);
	insertButton.drawTo(*m_context->window);
	deleteButton.drawTo(*m_context->window);
	searchButton.drawTo(*m_context->window);
	backButton.drawTo(*m_context->window);

	updateFrames();

	m_context->window->display();

}

void SinglyLinkedListMainState::handleButtonEvents( const  sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		std::cerr << "Button pressed\n";
		if (startButton.isMouseOver(*m_context->window))
			handleStartButtonEvents(event);
		else if (insertButton.isMouseOver(*m_context->window))
			handleInsertButtonEvents(event);
		else if (deleteButton.isMouseOver(*m_context->window))
			handleDeleteButtonEvents(event);
		else if (searchButton.isMouseOver(*m_context->window))
			handleSearchButtonEvents(event);
		else if (backButton.isMouseOver(*m_context->window))
			handleBackButtonEvents(event);
		else if (randomButton.isMouseOver(*m_context->window))
		{
			std::cout << "Random Button:";
			handleRandomButtonEvents(event);
		}
	}
}

void SinglyLinkedListMainState::handleRandomButtonEvents(sf::Event event)
{
	std::cout << "Random Button:";
	int n;
	std::cin >> n;
	std::vector<int> allElements;
	for (int i = 0; i < n; i++) {
		allElements.push_back(rand() % 100);
	}


	LinkedList.init(allElements);

	for (int x : LinkedList.getAllElements())
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;

	initRandomFrames();

}

void SinglyLinkedListMainState::handleInsertButtonEvents(sf::Event event)
{
}

void SinglyLinkedListMainState::handleDeleteButtonEvents(sf::Event event)
{
}

void SinglyLinkedListMainState::handleSearchButtonEvents(sf::Event event)
{
}

void SinglyLinkedListMainState::handleBackButtonEvents(sf::Event event)
{
}

void SinglyLinkedListMainState::handleStartButtonEvents(sf::Event event)
{
}



void SinglyLinkedListMainState::initRandomFrames()
{
	int timeRepeat = 0;
	
	std::vector<int> allElements;
	allElements = LinkedList.getAllElements();
	Engine::Frame previousframe;
	for (int i = 0; i < allElements.size(); i++) {
		Engine::Frame frame;
		std::shared_ptr<Node> node = std::make_shared<Node>();
		node->setString(std::to_string(allElements[i]));
		node->setFillColor(sf::Color::Green);
		node->setOutlineColor(sf::Color::Black);
		node->setOutlineThickness(2);
		node->setRadius(20);
		node->setPosition(sf::Vector2f(500 + i * 80, 30));
		if(i != 0)
			frame.init(previousframe);
		frame.addNode(std::to_string(allElements[i]), std::move(node));
		previousframe = frame;
		for (int j = 0; j < 100; j++)
			frames.push_back(frame);
		frames.push_back(frame);
	}

	numFrames = frames.size();
	isPlaying = true;
	currentFrameIndex = 0;

}

void SinglyLinkedListMainState::initInsertFrames()
{
}

void SinglyLinkedListMainState::updateFrames()
{
	if (isPlaying)
	{
		if (numFrames > 0)
		{
			if (currentFrameIndex < numFrames)
			{
				currentFrame = frames[currentFrameIndex];
				currentFrameIndex++;
			}
			else
			{
				currentFrame = frames[currentFrameIndex - 1];
				isPlaying = false;
			}
		}
	}
	currentFrame.drawAll(*m_context->window);

}

