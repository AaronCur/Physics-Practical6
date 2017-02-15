
//////////////////////////////////////////////////////////// 
// Headers for SFML projects
// include correct library file for release and debug versions
// include opengl library files
// include iostream for console window output
//////////////////////////////////////////////////////////// 

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

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

#include <iostream>
#include <math.h>
#include <iostream> 
#include <sstream>
#include <string.h>

/// <summary>
/// 
/// Physics system that demonstrates a particle being fired with an angle and force
/// Clculates the x and y component of the velocity with respcet to angle
/// Particel bounces in the x and y direction until it stops
/// 
/// </summary>


////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
using namespace std;

int main()
{
	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 800), "First Graphics in C++");

	double timeTaken = 0;
	float timeInAir = 0;
	sf::Text m_text;
	float distanceX = 0.0f;
	float distanceY = 0.0f;
	float maxHeight = 0.0f;
	float maxDistance = 0.0f;
	float degrees = 0.0f;
	float radians = 0.0f;
	float force = 0.0f;

	bool printHeight = false;
	bool timing = false;
	bool distance = false;
	bool bounce = false;
	bool slideRight = false;
	bool slideLeft = false;
	bool printTime = false;
	bool reset = false;

	int count = 0;
	int timeCount = 0;

	double timeSinceLast = 0.0;
	double startPosition = 400;
	// setup any shapes or variables.
	sf::CircleShape player(10);
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0, 420)),
		sf::Vertex(sf::Vector2f(800, 420))
	};

	player.setFillColor(sf::Color::Red);

	sf::Vector2f velocity(0, 0);
	sf::Vector2f position(50, 398);
	sf::Vector2f initialPosition(0, 0);

	//For use in games
	float pixelsToMeters = 20;
	sf::Vector2f gravity(0.0f, 9.8f*pixelsToMeters);
	sf::Vector2f acceleration(0.0f, 0.0f);
	sf::Vector2f initialVelocity(0.0f, 0.0f);


	//Load font
	sf::Font m_font;

	m_font.loadFromFile("C:/windows/fonts/times.ttf");

	sf::Text m_MaxHeightText;
	sf::Text m_TimeInAirText;
	sf::Text m_DistanceXText;
	sf::Text m_AngleText;
	sf::Text m_ForceText;

	sf::Text m_MaxHeight;
	sf::Text m_TimeInAir;
	sf::Text m_DistanceX;
	sf::Text m_Angle;
	sf::Text m_Force;

	std::stringstream m_sMaxHeight;
	std::stringstream m_sTimeInAir;
	std::stringstream m_sDistanceX;
	std::stringstream m_sAngle;
	std::stringstream m_sForce ;

	m_MaxHeightText.setFont(m_font);
	m_TimeInAirText.setFont(m_font);
	m_DistanceXText.setFont(m_font);
	m_AngleText.setFont(m_font);
	m_ForceText.setFont(m_font);

	m_MaxHeight.setFont(m_font);
	m_text.setFont(m_font);
	m_TimeInAir.setFont(m_font);
	m_DistanceX.setFont(m_font);
	m_Angle.setFont(m_font);
	m_Force.setFont(m_font);

	m_sAngle << 0;
	
	
	m_sForce << 0;
	

	// set timepeFrame to 1 60th of a second. 60 frames per second


	// the clock object keeps the time.
	sf::Clock clock;

	const float FPS = 65.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	clock.restart();

	while (window.isOpen())
	{
		// chek if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greate than 1/60 update the world.

		/// <summary>
		/// </summary>
		/// <returns></returns>
		if (timeSinceLastUpdate > timePerFrame)
		{

			//Reset the variables
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && reset == false)
			{
				bounce = false;
				slideRight = false;
				timing = false;
				degrees = 0;
				force = 0;
				velocity.y = 0;
				velocity.x = 0;
				position.x = 50;
				position.y = 398;
				distanceY = 0;
				maxHeight = 0;
				count = 0;
				m_sAngle.str("");
				m_sAngle << 0;
				m_sDistanceX.str("");
				m_sMaxHeight.str("");
				m_sForce.str("");
				m_sForce << 0;
				m_sTimeInAir.str("");

			}
			//Key press to increase angle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && bounce == false)
			{
				if (degrees >=0 && degrees < 90)
				{
					degrees++;
				}
				
				radians = (degrees * (3.14159265359 / 180));
				m_sAngle.str("");
				m_sAngle << degrees;

			}
			//Key press to decrease angle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && bounce == false)
			{
				if (degrees >0 && degrees <= 90)
				{
					degrees--;
				}
				
				radians = (degrees * (3.14159265359 / 180));
				m_sAngle.str("");
				m_sAngle << degrees;
			}
			//Key press to decrease force
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && bounce == false)
			{
				if (force > 0)
				{
					force--;
				}
				
				initialVelocity.x = force * cos(radians);
				initialVelocity.y = force * sin(radians);
				m_sForce.str("");
				m_sForce << force;
			}
			//Key press to increase force
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && bounce == false)
			{

				if (force >=0)
				{
					force++;
				}
				
				initialVelocity.x = force * cos(radians);
				initialVelocity.y = force * sin(radians);

				m_sForce.str("");
				m_sForce << force;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && position.y >= 398 && bounce == false)
			{
				initialPosition.y = position.y;
				velocity.y = velocity.y - initialVelocity.y;

				initialPosition.x = position.x;
				velocity.x = velocity.x + initialVelocity.x;
				slideRight = true;
				bounce = true;
			}
			//To calculate max height of projectile
			distanceY = position.y - initialPosition.y;

			if (maxHeight > distanceY + 0.1)
			{
				maxHeight = distanceY;
			}

			//Calculates how much energy is lost in bounce
			if (bounce == true)
			{
				if (position.y >= 400)
				{
					velocity.y = velocity.y * -0.6f;
					acceleration.x = -0.8*9.81* (velocity.x / sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)));
					std::cout << "friction" << std::endl;
					position.y = 400;
					
				}

				velocity.y = velocity.y + gravity.y * timeSinceLastUpdate.asSeconds();
				// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
				position.y = position.y + velocity.y * timeSinceLastUpdate.asSeconds() + 0.5 * gravity.y *(timeSinceLastUpdate.asSeconds() * timeSinceLastUpdate.asSeconds());
			}
			
			//// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
			if (slideRight == true && position.x >= 1 && position.x < 765)
			{
				if (slideRight == true)
				{
					position.x = position.x + velocity.x * timeSinceLastUpdate.asSeconds() + 0.5 * acceleration.x *(timeSinceLastUpdate.asSeconds() * timeSinceLastUpdate.asSeconds());
					velocity.x = velocity.x + acceleration.x * timeSinceLastUpdate.asSeconds();

					distanceX = position.x - initialPosition.x;
				}

			}


			if (bounce == false)
			{
				velocity.x = 0;
			}

			//Calculates time in the air
			if (position.y < 398)
			{
				timeInAir += timeSinceLastUpdate.asSeconds();
	
				m_sTimeInAir.str("");
				m_sTimeInAir << timeInAir;
			}
			
			if (velocity.x > 0)
			{
				m_sDistanceX.str("");
				m_sDistanceX << distanceX;
			}
			
			//To display max height
			if (bounce == true && velocity.y >= 0 && position.y < 398)
			{
				count = count + 1;
				//Only output max height once
				if (count == 1)
				{

					m_sMaxHeight.str("");
					m_sMaxHeight << -maxHeight;
					
				}

			}

			player.setPosition(position.x, position.y);
			// clear the screen and draw all the shapes

			window.clear();

			//Text objects are drawn when the game is playing

			//Bunch od banter to output info to the screen
			m_AngleText.setString(": Angle");
			m_AngleText.setPosition(700, 40);
			m_AngleText.setScale(1, 1);
			m_AngleText.setColor(sf::Color::White);
			window.draw(m_AngleText);

			m_Angle.setString(m_sAngle.str());
			m_Angle.setPosition(670, 40);
			m_Angle.setScale(1, 1);
			m_Angle.setColor(sf::Color::Yellow);
			window.draw(m_Angle);

			m_ForceText.setString("Force :");
			m_ForceText.setPosition(20, 40);
			m_ForceText.setScale(1, 1);
			m_ForceText.setColor(sf::Color::White);
			window.draw(m_ForceText);

			m_Force.setString(m_sForce.str());
			m_Force.setPosition(105, 40);
			m_Force.setScale(1, 1);
			m_Force.setColor(sf::Color::Yellow);
			window.draw(m_Force);

			m_TimeInAirText.setString(":TimeInAir:");
			m_TimeInAirText.setPosition(325, 10);
			m_TimeInAirText.setScale(0.85, 0.85);
			m_TimeInAirText.setColor(sf::Color::White);
			window.draw(m_TimeInAirText);

			m_TimeInAir.setString(m_sTimeInAir.str());
			m_TimeInAir.setPosition(345, 30);
			m_TimeInAir.setScale(0.85, 0.85);
			m_TimeInAir.setColor(sf::Color::Cyan);
			window.draw(m_TimeInAir);

			m_DistanceXText.setString("X-Distance:");
			m_DistanceXText.setPosition(20, 10);
			m_DistanceXText.setScale(0.85, 0.85);
			m_DistanceXText.setColor(sf::Color::White);
			window.draw(m_DistanceXText);

			m_DistanceX.setString(m_sDistanceX.str());
			m_DistanceX.setPosition(150, 10);
			m_DistanceX.setScale(0.85, 0.85);
			m_DistanceX.setColor(sf::Color::Cyan);
			window.draw(m_DistanceX);

			m_MaxHeightText.setString(":MaxHeight");
			m_MaxHeightText.setPosition(670, 10);
			m_MaxHeightText.setScale(0.85, 0.85);
			m_MaxHeightText.setColor(sf::Color::White);
			window.draw(m_MaxHeightText);

			m_MaxHeight.setString(m_sMaxHeight.str());
			m_MaxHeight.setPosition(580, 10);
			m_MaxHeight.setScale(0.85, 0.85);
			m_MaxHeight.setColor(sf::Color::Cyan);
			window.draw(m_MaxHeight);

			window.draw(player);
			window.draw(line, 2, sf::Lines);



			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}