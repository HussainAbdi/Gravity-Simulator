// Page: main.cpp
/*
Henceforth lies the source code for the Gravity Simulator made by Hussain Abdi.
Copyright 2016-2017
*/

#include "Precompiled.h" //Precompiled header to save compile time
#include "GraphicsDirector.h" 
#include "Simulation.h" 
#include "screens.h" //Screens
using namespace std; //Normally should avoid 'using namespace', however, 'std' is an exception in this case

int initIcon(sf::Image &icon, std::string location); //Prototype of intialisation of icon

int main() {
	FreeConsole();
	//Section 1: Initialise Simulator
	//The std::vector class is an array that can be managed.
	//Creating a vector class that points to different cScreen's which represent our screens.
	vector<cScreen*> screens;
	//GraphicsDirector guiDirector;
	Simulation simulation;
	//We are setting our inital screen to screen 0 (Splash Screen).
	int screen = 0;
	//Make window
	//desktop = sf::VideoMode::getDesktopMode();
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1920,1080), "Gravity Simulator"/*,sf::Style::Fullscreen*/);
	//Initialise Icon
	sf::Image icon;
	initIcon(icon, "images/icon/icon.png");
	window.setIcon(462, 462, icon.getPixelsPtr());
	//Adding screens to vector
	SplashScreen splashscreen;
	screens.push_back(&splashscreen);
	MenuScreen menuscreen;
	screens.push_back(&menuscreen);
	SimulatorScreen simulationscreen;
	screens.push_back(&simulationscreen);
	//Test
	sf::Sprite s1;
	//Section 2: Main Loop
	while (window.isOpen()) {
		//sf::Event event;

		//Section 3: Screen loop
		while ((screen >= 0) && (screen != -1))
		{
			screen = screens[screen]->run(window, simulation);
		}
		window.close();
	}
}
//Intialisation of icon
int initIcon(sf::Image &icon, std::string location) {
	if (!icon.loadFromFile(location)) {
		std::cerr << location << " not loaded" << std::endl;
		return -1;
	}
}