#include "Precompiled.h"
#include "cScreen.h"
#include "SplashScreen.h"
/*
Had to decide whether needed to load one image each time or seperate images. Decided one image. 
Reasons:
Different screen resolution, buttons would be in the right positions.
For many images have to make many sprites, more memory, less effecient. 
Loading image is not to expensive, even if large.
*/


SplashScreen::SplashScreen()
{
	this->alpha_max = 3 * 255;
	this->alpha_div = 3;
}

int SplashScreen::Run(sf::RenderWindow &window) {
	sf::Event event; 
	bool running = true; 
	bool timerStarted = false; //
	sf::Texture splashBackground;
	sf::Sprite sprite;
	int alpha = 0;
	sf::Clock clock;
	sprite.setTexture(*this->getTexture(&splashBackground,"images/Final Splash Screen.png"));
	//For splash screen, mouse should not be visible
	window.setMouseCursorVisible(false);
	//Sprite.setColor(sf::Color(255, 0, 0, alpha));

	while (running)
	{
		//Verifying events
		while (window.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Return) {
					return 1;
				}
			}
		}
		if ((alpha < alpha_max) && (timerStarted == false))
		{
			alpha++;
			sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
			if (alpha + 1 == alpha_max) {
				clock.restart();
				timerStarted = true;
			}
		}
		if (timerStarted == true)
		{
			if (clock.getElapsedTime().asSeconds() >= 2) {
				if (alpha > 0) {
					alpha--;
					sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
				}
				else {
					return 1;
				}
			}
		}
			//Clearing screen
			window.clear();
			//Drawing
			window.draw(sprite);
			window.display();
		}
	}

