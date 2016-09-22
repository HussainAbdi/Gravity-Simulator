/*
Henceforth lies the source code for the Gravity Simulator made by Hussain Abdi.
Copyright 2016-2017 *insert official symbol here*.
*/

#include "Precompiled.h" //Precompiled header to save compile time
using namespace std; //Normally should avoid 'using namespace', however, 'std' is an exception.

int main() {
	//I have used 'pragma region' to compartmentalise the code into different parts for easy reading. These can be ingored.
#pragma region Section 1: Initialise Simulator
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Planet Simulator");
#pragma endregion
	

#pragma region Section 2: Main loop
	while (window.isOpen()) {
		sf::Event event;

#pragma region Section 3: Input Loop
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

#pragma region Section 4: Render
			window.clear();
			window.display();
#pragma endregion
		}
#pragma endregion
	}
#pragma endregion
}