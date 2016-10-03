#include "Precompiled.h"
/*
Add textures at beginning for different states.
Button class?
*/


MenuScreen::MenuScreen()
{
	//Alpha used here to set opacity of images/textures
	this->alpha_max = 3 * 255; //Maximun opacity
	this->alpha_div = 3; //Minimum opacity
	this->playing = false;

}

int MenuScreen::Run(sf::RenderWindow &window) {
	//sf::Event event;
	//bool Running = true;
	//int alpha = 0;
	sf::Event event;
	bool running = true;
	std::vector<sf::Texture> textures;
	// Test area
	sf::Texture mainMenuNoSave;
	sf::Texture newButtonFilled;
	//
	sf::Texture mainMenuNormal;
	sf::Texture mainMenuHoverNew;
	sf::Texture mainMenuHoverLoad;
	sf::Texture mainMenuHoverSave;
	sf::Texture mainMenuHoverExit;
	sf::Texture mainMenuGreySave;
	sf::Sprite background;
	sf::Sprite buttonNew;
	sf::Sprite buttonLoad;
	sf::Sprite buttonSave;
	sf::Sprite buttonExit;
	int alpha = 0;
	int menu = 0;
	window.setMouseCursorVisible(true);
	if (!mainMenuNoSave.loadFromFile("images/filled buttons/TestNoNew.png"))
	{
		std::cerr << "Error loading Main Menu no save." << std::endl;
		return (-1);
	}
	if (!newButtonFilled.loadFromFile("images/filled buttons/New white.png")) {
		std::cerr << "Error loading save button." << std::endl;
		return (-1);
	}
	background.setTexture(mainMenuNoSave);
	buttonNew.setTexture(newButtonFilled); //682 332
	buttonNew.setPosition(sf::Vector2f(682, 332));
	/*if (!Font.loadFromFile("batmfa.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}
	Menu1.setFont(Font);
	Menu1.setCharacterSize(20);
	Menu1.setString("Play");
	Menu1.setPosition({ 280.f, 160.f });

	Menu2.setFont(Font);
	Menu2.setCharacterSize(20);
	Menu2.setString("Exit");
	Menu2.setPosition({ 280.f, 220.f });

	Menu3.setFont(Font);
	Menu3.setCharacterSize(20);
	Menu3.setString("Continue");
	Menu3.setPosition({ 280.f, 160.f });*/

	if (playing)
	{
		alpha = alpha_max;
	}

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
			//Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu = 0;
					break;
				case sf::Keyboard::Down:
					menu = 1;
					break;
				case sf::Keyboard::Return:
					if (menu == 0)
					{
						//Let's get play !
						playing = true;
						return (1);
					}
					else
					{
						//Let's get work...
						return (-1);
					}
					break;
				case sf::Keyboard::Escape:
					window.close();
					break;
				default:
					break;
				}
			}
		}
		//When getting at alpha_max, we stop modifying the sprite
		if (alpha<alpha_max)
		{
			alpha++;
			background.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
		}
		

		//Clearing screen
		window.clear();
		//Drawing
		window.draw(background);
		window.draw(buttonNew);
		window.display();
	}
}

void loadTexture(sf::Texture texture, std::string location) {

}