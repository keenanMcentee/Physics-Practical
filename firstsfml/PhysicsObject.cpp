#include "PhysicsObject.h"



PhysicsObject::PhysicsObject()
{
}
/// <summary>
/// Initialises the physics object and all its components.
/// </summary>
/// <param name="font"></param>
/// <param name="groundLevel"></param>
void PhysicsObject::initialise(sf::Font *font, float groundLevel)
{
	m_groundLevel = groundLevel;
	shape.setRadius(RADIUS);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(sf::Vector2f(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius()));
	position = sf::Vector2f(101+ RADIUS, m_groundLevel - RADIUS);

	shape.setPosition(position);
	
	velocity = sf::Vector2f(0, 0);
	
	force = sf::Vector2f(0.0f, U * -1);
	jump = false;
	m_angle = 0;
	m_speed = 0;
	impulsiveForceL = sf::Vector2f(-2,0);
	impulsiveForceR = sf::Vector2f(2,0);


	textInitialise(font);

	timeJumping = 0;
	jumpingHeight = m_groundLevel;
	distanceMoved = 0;
	timeToStop = 0;
	m_angle = 0;
	m_speed = 0;
	launched = false;
}
PhysicsObject::~PhysicsObject()
{
}
/// <summary>
/// Updates the Physics object and all its components.
/// </summary>
/// <param name="t"></param>
void PhysicsObject::update(sf::Time t)
{
	keyboardHandler();
	previousPosX = position.x;
	//Velocity = Velocity + acceleration* timeChange
	velocity = velocity + GRAVITY * t.asSeconds();

	// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
	// Position = Position + Velocity*timeChange + 0.5*acceleration*(timeChange)2
	position = position + velocity * t.asSeconds() + 0.5f * GRAVITY * (t.asSeconds() * t.asSeconds());

	
	if (position.y - m_groundLevel < jumpingHeight)
	{
		jumpingHeight = (position.y - m_groundLevel);
	}
	if (jump == true)
	{
		timeJumping += t.asSeconds();
	}
	
	distanceMoved += sqrt((position.x - previousPosX) * (position.x - previousPosX));
	//update shape on screen
	shape.setPosition(position);

	if (position.y > m_groundLevel - RADIUS)
	{
		position.y = m_groundLevel - RADIUS;
		//jumpingHeight += ground.getPosition().y;
		if (jump == true && timeToStop > 1/PIXELS_TO_METERS)
		{
			jump = false;
		}


		velocity.y *= -COEFFICIENT_OF_RESTITUTION;
		velocity.x *= COEFFICIENT_OF_FRICTION;

	}
	if (velocity.x < -0.1f*PIXELS_TO_METERS || velocity.x > 0.1f*PIXELS_TO_METERS || velocity.y < -0.1f*PIXELS_TO_METERS || velocity.y > 0.1f*PIXELS_TO_METERS)
	{
		timeToStop += t.asSeconds();
	}
}
/// <summary>
/// Renders the object and text to the screen.
/// </summary>
/// <param name="window"></param>
void PhysicsObject::draw(sf::RenderWindow *window)
{
	textHandler();

	window->draw(shape);

	window->draw(realTimeText);
	window->draw(realHeightText);
	//window->draw(predictedTimeText);
	//window->draw(predictedHeightText);
	window->draw(distanceMovedText);
	window->draw(timeToStopText);
	window->draw(angleText);
	window->draw(speedText);

}
/// <summary>
/// Sets up the text objects for displaying our messages to the screen.
/// </summary>
/// <param name="font"></param>
void PhysicsObject::textInitialise(sf::Font *font)
{
	predictedHeightText.setFont(*font);
	predictedTimeText.setFont(*font);
	realHeightText.setFont(*font);
	realTimeText.setFont(*font);
	distanceMovedText.setFont(*font);
	timeToStopText.setFont(*font);
	angleText.setFont(*font);
	speedText.setFont(*font);

	predictedHeightText.setCharacterSize(12);
	predictedTimeText.setCharacterSize(12);
	realHeightText.setCharacterSize(12);
	realTimeText.setCharacterSize(12);
	distanceMovedText.setCharacterSize(12);
	timeToStopText.setCharacterSize(12);
	angleText.setCharacterSize(12);
	speedText.setCharacterSize(12);

	predictedHeightText.setPosition(10, 10);
	predictedTimeText.setPosition(10, 30);
	realHeightText.setPosition(10, 100);
	realTimeText.setPosition(10, 130);
	distanceMovedText.setPosition(500, 10);
	timeToStopText.setPosition(500, 30);
	angleText.setPosition(500, 130);
	speedText.setPosition(500, 150);
}

/// <summary>
/// Handles any keyboard input.
/// </summary>
void PhysicsObject::keyboardHandler()
{
	angleInRads = m_angle * std::acos(-1) / 180;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jump == false && launched == false)
	{
		
		velocity += sf::Vector2f(m_speed * cos(angleInRads), m_speed * sin(angleInRads));
		jump = true;
		launched = true;
		timeJumping = 0;
		jumpingHeight = m_groundLevel;
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		velocity += impulsiveForceL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		velocity += impulsiveForceR;
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && launched == false)
	{
		if (m_angle < 90)
			m_angle += 0.5;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && launched == false)
	{
		if (m_angle > 0)
			m_angle -= 0.5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && launched == false)
	{
		if (m_speed < 500)
			m_speed += (0.5 * PIXELS_TO_METERS);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && launched == false)
	{
		if (m_speed > 0)
			m_speed -= (0.5* PIXELS_TO_METERS);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		reinitialise();
	}
}
void PhysicsObject::textHandler()
{
	float u = m_speed * sin(angleInRads);
	realTimeText.setString("Real Time Jumping no bounce: " + std::to_string(timeJumping));
	realHeightText.setString("Real Max Height Jumping: " + std::to_string(jumpingHeight * -1));
	predictedTimeText.setString("Predicted time: " + std::to_string(((2*u) / GRAVITY.y)/2)); //	2*U / G
	predictedHeightText.setString("Predicted Max Height: " + std::to_string((u*u) / (2 * GRAVITY.y))); //	(U * U) / 2G
	distanceMovedText.setString("Distance travelled on X-Plane: " + std::to_string(distanceMoved));
	timeToStopText.setString("Total time in motion: " + std::to_string(timeToStop));
	angleText.setString("Angle: " + std::to_string(m_angle));
	speedText.setString("Speed: " + std::to_string(m_speed));
}
void PhysicsObject::reinitialise()
{
	velocity = sf::Vector2f(0, 0);
	position = sf::Vector2f(110, m_groundLevel - RADIUS);
	jump = false;
	launched = false;
	timeJumping = 0;
	jumpingHeight = m_groundLevel;
	distanceMoved = 0;
	timeToStop = 0;
}