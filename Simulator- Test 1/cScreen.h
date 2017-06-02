// Page: cScreen.h
#pragma once
#include "Precompiled.h"
#include "GraphicsDirector.h"
#include "Simulation.h"
/*
This is a virtual object that will be the base class for our different screens.
*/
class cScreen
{
public:
	//Use of polymorphism. The 'Run' function will be used in the different screens, doing different things.
	//This function will return a number. Based on which number is returned, a screen will be output or the application will terminate.
	//In the main, when -1 is returned, the application terminates.
	std::vector<cScreen*> screens;
	virtual int run(sf::RenderWindow &window, Simulation& simulation) = 0;

};

