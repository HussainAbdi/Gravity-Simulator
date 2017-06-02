// Page: SimulatorScreen.h
#pragma once
#include "cScreen.h"

/*
This is the class used to display the simulation screen.
*/
class SimulatorScreen: public cScreen
{
private:
	//Variables for opacity
	int alpha_max; //Maximum opacity. The screen will be fully visible
	int alpha_div; //Minimum opacity. The screen will be completely transparent
	//Toggle Simulation State (Pause/Play) Method
	void togglePause(Simulation& simulation);
public:
	//Constructor
	SimulatorScreen();
	//Refer to cScreen.h for details about this polymorphism
	virtual int run(sf::RenderWindow &window, Simulation& simulation);
};

