#include "PhysicsObject.h"



PhysicsObject::PhysicsObject()
{
	


	
}

void PhysicsObject::initialise(sf::Font *font, float groundLevel)
{
	m_groundLevel = groundLevel;
	shape.setRadius(1.5f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(sf::Vector2f(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius()));
	velocity = sf::Vector2f(0, 0);
	position = sf::Vector2f(400, 400 - shape.getRadius());
	gravity = sf::Vector2f(0.0f, 9.8f);
	force = sf::Vector2f(0.0f, U * -1);
	jump = false;

	predictedHeightText.setFont(*font);
	predictedTimeText.setFont(*font);
	realHeightText.setFont(*font);
	realTimeText.setFont(*font);

	predictedHeightText.setCharacterSize(12);
	predictedTimeText.setCharacterSize(12);
	realHeightText.setCharacterSize(12);
	realTimeText.setCharacterSize(12);

	predictedHeightText.setPosition(10, 10);
	predictedTimeText.setPosition(10, 30);
	realHeightText.setPosition(10, 50);
	realTimeText.setPosition(10, 70);

	timeJumping = 0;
	jumpingHeight = m_groundLevel;
}
PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::update(sf::Time t)
{
	//Velocity = Velocity + acceleration* timeChange
	velocity = velocity + gravity * t.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jump == false)
	{
		velocity += force;
		jump = true;
		timeJumping = 0;
		jumpingHeight = m_groundLevel;
	}
	// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
	// Position = Position + Velocity*timeChange + 0.5*acceleration*(timeChange)2
	position = position + velocity * t.asSeconds() + 0.5f * gravity * (t.asSeconds() * t.asSeconds());

	if (position.y > m_groundLevel - shape.getRadius())
	{
		position.y = m_groundLevel - shape.getRadius();
		//jumpingHeight += ground.getPosition().y;
		jump = false;
		velocity = sf::Vector2f(0, 0);
	}
	if (position.y - m_groundLevel < jumpingHeight)
	{
		jumpingHeight = (position.y - m_groundLevel);
	}
	if (jump == true)
	{
		timeJumping += t.asSeconds();
	}
	//update shape on screen
	shape.setPosition(position);


	realTimeText.setString("Real Time Jumping: " + std::to_string(timeJumping));
	realHeightText.setString("Real Max Height Jumping: " + std::to_string(jumpingHeight * -1));
	predictedTimeText.setString("Predicted time: " + std::to_string((2 * U) / gravity.y));
	predictedHeightText.setString("Predicted Max Height" + std::to_string((U*U) / (2 * gravity.y)));
}

void PhysicsObject::draw(sf::RenderWindow *window)
{
	window->draw(shape);

	window->draw(realTimeText);
	window->draw(realHeightText);
	window->draw(predictedTimeText);
	window->draw(predictedHeightText);
}
