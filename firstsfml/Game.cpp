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
	settings.antialiasingLevel = 8;
	shape.setRadius(7.0f);
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin(sf::Vector2f(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius()));
	velocity = sf::Vector2f(0, 0);
	position = sf::Vector2f(400, 400 - shape.getRadius());
	gravity = sf::Vector2f(0.0f, 9.8f);
	force = sf::Vector2f(0.0f, U * -1);
	jump = false;
	timeSinceLastUpdate = sf::Time::Zero;
	ground.setPosition(10, 400);
	ground.setSize(sf::Vector2f(580, 1));
	ground.setFillColor(sf::Color::Yellow);
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "COULDN'T LOAD FONT FILE" << std::endl;
	}
	
	///*predictedHeightText.setFont(font);
	//predictedTimeText.setFont(font);
	//realHeightText.setFont(font);
	//realTimeText.setFont(font);*/
	//
	//predictedHeightText.setCharacterSize(12);
	//predictedTimeText.setCharacterSize(12);
	//realHeightText.setCharacterSize(12);
	//realTimeText.setCharacterSize(12);

	//predictedHeightText;
	//predictedTimeText;
	//realHeightText;
	//realTimeText;

	clock.restart();

}
void Game::processEvents()
{
	//read keyboard inout
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
			update(timeSinceLastUpdate.asSeconds());
			draw();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}

void Game::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jump == false)
	{
		velocity += force;
		jump = true;
	}
	//Velocity = Velocity + acceleration* timeChange
	velocity = velocity + gravity * dt;
	
	// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
	// Position = Position + Velocity*timeChange + 0.5*acceleration*(timeChange)2
	position = position + velocity * dt + 0.5f * gravity * (dt * dt);

	if (position.y > 400 - shape.getRadius())
	{
		position.y = 400 - shape.getRadius();
		jump = false;
	}
	//update shape on screen
	shape.setPosition(position);

	
}

void Game::draw()
{
	window.clear();
	window.draw(shape);
	window.draw(ground);
	window.draw(line, 2, sf::Lines);
	window.display();
}