// Page: SplashScreen.cpp
#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	this->alpha_max = 3 * 255; //Maximum opacity
	this->alpha_div = 3; //Minimum opacity
}

int SplashScreen::run(sf::RenderWindow &window, Simulation& simulation) {
	//Initialise variables needed 
	sf::Event event; 
	bool running = true; 
	bool timerStarted = false;
	int alpha = 0;
	sf::Clock clock;
	//For splash screen, mouse should not be visible
	window.setMouseCursorVisible(false);

	while (running)
	{
		//Verifying events
		while (window.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Return) {
					return 1;
				}
			}
		}
		//Increase opacity until no longer transparent
		if ((alpha < alpha_max) && (timerStarted == false)) 
		{
			alpha++;
			simulation.guiDirector->getSplash()->setColour(sf::Color(255, 255, 255, alpha / alpha_div));
			if (alpha + 1 == alpha_max) {
				clock.restart();
				timerStarted = true;
			}
		}
		if (timerStarted == true)
		{
			if (clock.getElapsedTime().asSeconds() >= 2) { //Wait for 2 seconds before starting to decrease the opacity
				if (alpha > 0) {
					alpha--;
					simulation.guiDirector->getSplash()->setColour(sf::Color(255, 255, 255, alpha / alpha_div));
					//sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
				}
				else {
					return 1; //When no longer visible, switch to main menu screen
				}
			}
		}
			//Clearing screen
			window.clear();
			//Drawing
			window.draw(*simulation.guiDirector->getSplash());
			//window.draw(sprite);
			window.display();
		}
	}

