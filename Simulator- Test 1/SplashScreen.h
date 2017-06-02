// Page: SplashScreen.h
#pragma once
#include "cScreen.h"
/*
This is the class used to display the splash screen.
*/
class SplashScreen :public cScreen
{
private:
	//Variables for opacity
	int alpha_max; //Maximum opacity. The screen will be fully visible
	int alpha_div; //Minimum opacity. The screen will be completely transparent
public:
	//Constructor
	SplashScreen();
	//Refer to cScreen.h for details about this polymorphism
	virtual int run(sf::RenderWindow &window, Simulation& simulation);
};

