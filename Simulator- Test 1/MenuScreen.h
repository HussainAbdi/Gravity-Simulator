// Page: MenuScreen.h
#pragma once
#include "cScreen.h"
/*
This is the class used to display the menu screen.
*/
class MenuScreen : public cScreen
{
private:
	//Variables for opacity
	int alpha_max; //Maximum opacity. The screen will be fully visible
	int alpha_div; //Minimum opacity. The screen will be completely transparent
	//Background main menu music
	sf::Music menuMusic;
	//Initialise music method
	void initMusic();
public:
	//Constructor
	MenuScreen();
	//Refer cScreen.h for details on this polymorphism
	virtual int run(sf::RenderWindow &window, Simulation& simulation);
};

