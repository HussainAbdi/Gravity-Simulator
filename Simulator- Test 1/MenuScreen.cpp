// Page: MenuScreen.cpp
#include "MenuScreen.h"
/*
*/



MenuScreen::MenuScreen()
{
	//Alpha used here to set opacity of images/textures
	this->alpha_max = 3 * 255; //Maximun opacity
	this->alpha_div = 3; //Minimum opacity
	//Initialise the music
	initMusic();

}

int MenuScreen::run(sf::RenderWindow &window, Simulation& simulation) {
	//Initialise the variables needed for this screen
	sf::Event event;
	bool running = true;
	int alpha = 0;
	window.setMouseCursorVisible(true);
	this->menuMusic.play();

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
			//Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					break;
				case sf::Keyboard::Down:
					break;
				case sf::Keyboard::Return:
					break;
				default:
					break;
				}
			}
			//Mouse Released
			if (event.type == sf::Event::MouseButtonReleased) {
				int buttonNum = NULL;
				for (int i = 0; i < 2; i++) {
					if (simulation.guiDirector->getMenuButtons()[i]->isMouseOver(window)) {
						int screen;
						buttonNum = i;
						screen = simulation.guiDirector->getMenuButtons()[i]->updateDerived(window);
						this->menuMusic.stop();
						if (screen != 1) {
							return screen;
						}
					}
				}

			}
		}
		//Hover animation check
		for (int i = 0; i < 2; i++) {
			simulation.guiDirector->getMenuButtons()[i]->update(window);
		}

		//When getting at alpha_max, we stop modifying the objects
		if (alpha < alpha_max)
		{
			alpha++;
			simulation.guiDirector->getMenu()->setColour(sf::Color(255, 255, 255, alpha / alpha_div));
			for (int i = 0; i < 2; i++) {
				simulation.guiDirector->getMenuButtons()[i]->setColour(sf::Color(255, 255, 255, alpha / alpha_div));
			}
		}


		//Clearing screen
		window.clear();
		//Drawing
		window.draw(*simulation.guiDirector->getMenu());
		for (int i = 0; i < 2; i++) {
			window.draw(*simulation.guiDirector->getMenuButtons()[i]);
		}
		window.display();
	}
}

void MenuScreen::initMusic()
{
	std::string location = "sound/menu/menu-music.wav";
	if (!this->menuMusic.openFromFile(location)) {
		std::cerr << location << " not loaded" << std::endl;
	}
	this->menuMusic.setVolume(100);
	this->menuMusic.setLoop(true);
}