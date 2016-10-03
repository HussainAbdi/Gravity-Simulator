/*
Henceforth lies the source code for the Gravity Simulator made by Hussain Abdi.
Copyright 2016-2017 *insert official symbol here*.
*/
/*
My programming practices:
Enum class types are in uppercase. E.g. gui::type::menubutton::NEW

*/
/*
Next steps:
Change image to fit window size with view.
*/

#include "Precompiled.h" //Precompiled header to save compile time
using namespace std; //Normally should avoid 'using namespace', however, 'std' is an exception.

int main() {
	//Section 1: Initialise Simulator
	//The std::vector class is an array that can be managed.
	//Creating a vector class that points to different cScreen's which represent our screens.
	vector<cScreen*> screens;
	//We are setting our inital screen to screen 0.
	int screen = 0;
	//Make window
	
	//desktop = sf::VideoMode::getDesktopMode();
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktop, "Gravity Simulator", sf::Style::Fullscreen);
	//For splash screen, no mouse.
	window.setMouseCursorVisible(false);
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
		sf::Event event;

		//Section 3: Screen loop
		while (screen >= 0)
		{
			screen = screens[screen]->Run(window); 

		}
	}
}