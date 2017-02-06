#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 800), "First Graphics in C++");
	
	
	
	double timeTaken = 0;
	float initialVelocityY = 0.0f;
	float initialVelocityX = 0.0f;
	

	float distanceX = 0.0f;
	float distanceY = 0.0f;
	float maxHeight = 0.0f;
	float maxDistance = 0.0f;
	float degrees = 0.0f;
	float radians = 0.0f;
	
	bool printHeight = false;
	bool timing = false;
	bool distance = false;
	bool bounce = false;
	bool slideRight = false;
	bool slideLeft = false;
	bool printTime = false;

	int count = 0;
	int timeCount = 0;
	
	double timeSinceLast = 0.0;
	double startPosition = 400;
	// setup any shapes or variables.
	sf::RectangleShape player(sf::Vector2f(20,20));
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0, 420)),
		sf::Vertex(sf::Vector2f(800, 420))
	};
	
	
	
	player.setFillColor(sf::Color::Red);

	sf::Vector2f velocity(0, 0);
	sf::Vector2f position(150, 398);
	sf::Vector2f initialPosition(0, 0);

	//For use in games
	float pixelsToMeters = 20;
	sf::Vector2f gravity(0.0f, 9.8f*pixelsToMeters);
	sf::Vector2f acceleration(0.0f, 0.0f);
	sf::Vector2f velocityRes(0.0f, 0.0f);
	
	
	//Load font
	

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

		if (timeSinceLastUpdate > timePerFrame)
		{
			/*velocityRes = sqrt((initialVelocityX * initialVelocityX) + (initialVelocityY * initialVelocityY));

			radians = atan2(initialVelocityX, initialVelocityY);
			degrees = (radians * (180 / 3.14159265359) - 90);

			
			*/

			radians = atan2(velocityRes.x, velocityRes.y);
			degrees = (radians * (180 / 3.14159265359) - 90);

			velocityRes.y = degrees * atan (initialVelocityY);
			velocityRes.x = degrees * atan(initialVelocityY);

			if (degrees > 0)
			{
				std::cout << "Angle" << degrees << std::endl;
			}
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				velocity.y = 0;
				velocity.x = 0;
				position.x = 150;
				position.y = 398;
			}
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) )
			{
				initialVelocityY--;
				
			}*/
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			{
				degrees++;

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			{
				degrees--;

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				initialVelocityX++;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			{
				velocityRes++;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				velocityRes--;
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && position.y >= 398 && timing == false && bounce == false )
			{
				initialPosition.y = position.y;
				velocity.y = velocity.y + initialVelocityY;

				initialPosition.x = position.x;
				velocity.x = velocity.x + initialVelocityX;
				timing = true;
				slideRight = true;
				bounce = true;
			}

			if (bounce == true  )
			{
				if (position.y >= 400)
				{
					velocity.y = velocity.y * -0.6f ;
				}
				
				velocity.y = velocity.y + gravity.y * timeSinceLastUpdate.asSeconds();
				// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
				position.y = position.y + velocity.y * timeSinceLastUpdate.asSeconds() + 0.5 * gravity.y *(timeSinceLastUpdate.asSeconds() * timeSinceLastUpdate.asSeconds());

				distanceY = position.y - initialPosition.y;

				if (maxHeight > distanceY + 1)
				{
					maxHeight = distanceY;
				}
				
			}
			if (position.y >= 402)
			{
				bounce = false;
				position.y = 398;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && position.x >= 0 && position.x < 800 && slideRight == false && position.y >= 360 )
			{
				initialPosition.x = position.x;
				//velocity.x = 60.0f;
				velocity.x = velocity.x + 2;
				slideRight = true;
				timing = true;
			}

			
				//// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().
			if (slideRight == true &&  position.x >= 1 && position.x < 765 )
			{
				if (slideRight == true)
				{
					acceleration.x = -0.8*9.81* (velocity.x / sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)));
					//velocity.x = velocity.x * 0.01f;
					position.x = position.x + velocity.x * timeSinceLastUpdate.asSeconds() + 0.5 * acceleration.x *(timeSinceLastUpdate.asSeconds() * timeSinceLastUpdate.asSeconds());
					velocity.x = velocity.x + acceleration.x * timeSinceLastUpdate.asSeconds();

					distanceX = position.x - initialPosition.x;
				}
				
				if (maxDistance < distanceX)
				{
					maxHeight = distanceX;
				}
				
			}
				//position.x = position.x + velocity.x * timeSinceLastUpdate.asSeconds();

			
		
			if (timing == true)
			{
				timeTaken += timeSinceLastUpdate.asSeconds();

				
			}
			if (timing == false)
			{
				timeTaken = 0;
			}
		

			if (slideRight == true && velocity.x < 0.1)
			{
				
				std::cout << "Distance X: " << distanceX << std::endl;
				std::cout << "Time X: " << timeTaken << std::endl;
				slideRight = false;
				timing = false;
			}
			if (bounce == true && velocity.y >= 0 && position.y < 360)
			{
				
				
				count = count + 1;

				if (count == 1)
				{
					std::cout << "Distance Y: " << -maxHeight << std::endl;
					std::cout << "Time Y: " << timeTaken << std::endl;
					timing = false;
					/*if (velocity.y  0)
					{
						std::cout << "Time Y: " << timeTaken << std::endl;
						timing = false;
					}*/
					
				}
				
			}
			
			/*if (bounce == true && velocity.y < 0.1 && position.y > 360 && position.y < 401)
			{
				bounce = false;
			}*/
			
			
			player.setPosition(position.x, position.y);
			// clear the screen and draw all the shapes

			window.clear();
		
			window.draw(player);
			window.draw(line, 2, sf::Lines);

			
		
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}