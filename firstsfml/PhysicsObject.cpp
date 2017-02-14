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
	shape.setSize(sf::Vector2f(2 * RADIUS, 2 *RADIUS));
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(sf::Vector2f(shape.getPosition().x + RADIUS, shape.getPosition().y + RADIUS));
	velocity = sf::Vector2f(0, 0);
	position = sf::Vector2f(400, m_groundLevel - RADIUS);
	force = sf::Vector2f(0.0f, U * -1);
	jump = false;

	impulsiveForceL = sf::Vector2f(-2,0);
	impulsiveForceR = sf::Vector2f(2,0);


	textInitialise(font);

	timeJumping = 0;
	jumpingHeight = m_groundLevel;
	distanceMoved = 0;
	timeToStop = 0;
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
	//Velocity = Velocity + acceleration* timeChange
	velocity = velocity + GRAVITY * t.asSeconds();

	// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
	// Position = Position + Velocity*timeChange + 0.5*acceleration*(timeChange)2
	position = position + velocity * t.asSeconds() + 0.5f * GRAVITY * (t.asSeconds() * t.asSeconds());

	if (position.y > m_groundLevel - RADIUS)
	{
		position.y = m_groundLevel - RADIUS;
		//jumpingHeight += ground.getPosition().y;
		jump = false;

		velocity.y *= -COEFFICIENT_OF_RESTITUTION;
		velocity.x *= COEFFICIENT_OF_FRICTION;

	}
	if (position.y - m_groundLevel < jumpingHeight)
	{
		jumpingHeight = (position.y - m_groundLevel);
	}
	if (jump == true)
	{
		timeJumping += t.asSeconds();
	}
	if (velocity.x < -0.1f || velocity.x > 0.1f || velocity.y < -0.1f || velocity.y > 0.1f)
	{
		timeToStop += t.asSeconds();
	}
	distanceMoved += sqrt(velocity.x * velocity.x);
	//update shape on screen
	shape.setPosition(position);


	
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
	window->draw(predictedTimeText);
	window->draw(predictedHeightText);
	window->draw(distanceMovedText);
	window->draw(timeToStopText);
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

	predictedHeightText.setCharacterSize(12);
	predictedTimeText.setCharacterSize(12);
	realHeightText.setCharacterSize(12);
	realTimeText.setCharacterSize(12);
	distanceMovedText.setCharacterSize(12);
	timeToStopText.setCharacterSize(12);

	predictedHeightText.setPosition(10, 10);
	predictedTimeText.setPosition(10, 30);
	realHeightText.setPosition(10, 50);
	realTimeText.setPosition(10, 70);
	distanceMovedText.setPosition(500, 10);
	timeToStopText.setPosition(500, 30);
}

/// <summary>
/// Handles any keyboard input.
/// </summary>
void PhysicsObject::keyboardHandler()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jump == false)
	{
		velocity += force;
		jump = true;
		timeJumping = 0;
		jumpingHeight = m_groundLevel;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		velocity += impulsiveForceL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		velocity += impulsiveForceR;
	}
}
void PhysicsObject::textHandler()
{
	realTimeText.setString("Real Time Jumping no bounce: " + std::to_string(timeJumping));
	realHeightText.setString("Real Max Height Jumping: " + std::to_string(jumpingHeight * -1));
	predictedTimeText.setString("Predicted time: " + std::to_string((2 * U) / GRAVITY.y));
	predictedHeightText.setString("Predicted Max Height: " + std::to_string((U*U) / (2 * GRAVITY.y)));
	distanceMovedText.setString("Distance travelled on X-Plane: " + std::to_string(distanceMoved));
	timeToStopText.setString("Total time in motion: " + std::to_string(timeToStop));
}
//void PhysicsObject::reinitialise()
//{
//	velocity = sf::Vector2f(0, 0);
//	position = sf::Vector2f(400, m_groundLevel - RADIUS);
//	jump = false;
//	timeJumping = 0;
//	jumpingHeight = m_groundLevel;
//}