#include <SFML/Graphics.hpp>
class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	void initialise(sf::Font *font, float groundLevel);
	void reinitialise();
	void update(sf::Time t);
	void draw(sf::RenderWindow *window);
	
private:
	void keyboardHandler();
	void textHandler();
	void textInitialise(sf::Font *font);

	sf::RectangleShape shape;
	const float RADIUS = 2.0f;

	sf::Vector2f impulsiveForceL;
	sf::Vector2f impulsiveForceR;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f acceleration;
	sf::Vector2f force;

	const float U = 44.275f;
	const float COEFFICIENT_OF_RESTITUTION = 0.5f;
	const float COEFFICIENT_OF_FRICTION = 0.8f;
	const sf::Vector2f GRAVITY = sf::Vector2f(0.0f, 9.8f);

	sf::Text predictedTimeText, predictedHeightText, realTimeText, realHeightText, distanceMovedText, timeToStopText;

	double preditedTime, predictedHeight, jumpingHeight, timeJumping, distanceMoved, timeToStop;
	bool jump;
	float m_groundLevel;


};

