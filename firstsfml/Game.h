#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include <SFML/Graphics.hpp>

#include <iostream>
class Game
{
public:
	Game();
	~Game();


	void run();
	void initialise();
	void update(float dt);
	void draw();
	void processEvents();

	sf::RenderWindow window;
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f gravity;
	sf::Vector2f force;
	const int U = 50;
	sf::Clock clock;
	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate;
	sf::Font font;
	sf::Text predictedTimeText, predictedHeightText, realTimeText, realHeightText;
	sf::RectangleShape ground;
	float preditedTime, predictedHeight, realTime, realHeight;
	bool jump;
	sf::ContextSettings settings;
};

