#include <SFML/Graphics.hpp>
class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	void initialise(sf::Font *font, float groundLevel);
	void update(sf::Time t);
	void draw(sf::RenderWindow *window);

	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f gravity;
	sf::Vector2f force;
	const float U = 44.275f;
	sf::Text predictedTimeText, predictedHeightText, realTimeText, realHeightText;
	double preditedTime, predictedHeight, jumpingHeight;
	double timeJumping;
	bool jump;
	float m_groundLevel;
};

