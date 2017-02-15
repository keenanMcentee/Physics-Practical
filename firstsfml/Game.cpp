#include "Game.h"
sf::Vertex line[] =
{
	sf::Vertex(sf::Vector2f(10, 300)),
	sf::Vertex(sf::Vector2f(790, 300))
};
Game::Game() : window(sf::VideoMode(800, 800), "Go Physics!!")
{
}


Game::~Game()
{
}

void Game::initialise()
{
	
	
	timeSinceLastUpdate = sf::Time::Zero;
	ground.setPosition(10, 700);
	ground.setSize(sf::Vector2f(780, 1));
	ground.setFillColor(sf::Color::Yellow); 
	wall.setPosition(100, 150);
	wall.setSize(sf::Vector2f(1, 550));
	wall.setFillColor(sf::Color::Red);

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "COULDN'T LOAD FONT FILE" << std::endl;
	}

	object.initialise(&font, ground.getPosition().y);

	clock.restart();

}
void Game::processEvents()
{
	//read keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		//object.reinitialise();
	}
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}
void Game::run()
{
	initialise();
	while (window.isOpen())
	{
		processEvents();
		
		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate);
			draw();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}

void Game::update(sf::Time t)
{
	object.update(t);
}

void Game::draw()
{
	window.clear();

	window.draw(ground);
	window.draw(wall);
	//window.draw(line, 2, sf::Lines);
	object.draw(&window);

	window.display();
}