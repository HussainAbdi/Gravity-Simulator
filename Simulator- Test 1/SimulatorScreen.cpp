// Page: SimulatorScreen.cpp
#include "SimulatorScreen.h"
/*Notes on 26/02/17 7:42PM
When buttons clicked, change state of simulation.
Simulation class will store this state and inputs will be handles accordingly.
Pass simulation state into update of simulation etc.



*/


void SimulatorScreen::togglePause(Simulation& simulation)
{
	//If the pause/play state of the simulation is toggled, the graphics director is informed so that the sprite of the pause buttons can be changed
	if (simulation.paused == false) {
		simulation.isPaused(true);
		simulation.guiDirector->isPaused(true);
	}
	else {
		simulation.isPaused(false);
		simulation.guiDirector->isPaused(false);
	}
}

SimulatorScreen::SimulatorScreen()
{
	//Alpha used here to set opacity of images/textures
	this->alpha_max = 3 * 255; //Maximun opacity
	this->alpha_div = 3; //Minimum opacity
}

int SimulatorScreen::run(sf::RenderWindow & window, Simulation& simulation)
{
	//Initialise simulator variables
	sf::Event event;
	bool running = true;
	int alphaBackground = 0;
	int alpha = 0;
	int maxAlphaBackground = (alpha_max/255)*150;
	std::string input;
	//Setting up timestepping variables
	const double fps = 60;
	double t = 0; //This is the total time passed during the simulation
	double dt = 1/60.0;
	double scaledDt = 300; 
	//Setting up a view for timestepping
	sf::View fixed = window.getView();
	sf::View standard = fixed;
	//Handling time
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time clamp = sf::seconds(0.25);

	
	while (running)
	{
		window.setView(fixed);
		accumulator += clock.getElapsedTime();
		clock.restart();
		if (accumulator.asSeconds() > clamp.asSeconds()) {
			accumulator = clamp;
		}
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
			if (simulation.stateEnum != Simulation::State::ADDMOON || simulation.stateEnum != Simulation::State::ADDPLANET || simulation.stateEnum != Simulation::State::ADDSTAR) {
				if (event.type == sf::Event::KeyPressed)
				{
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						standard.zoom(0.5);
						break;
					case sf::Keyboard::Down:
						standard.zoom(2);
						break;
					case sf::Keyboard::W:
						standard.move(0, -10);
						break;
					case sf::Keyboard::A:
						standard.move(-10, 0);
						break;
					case sf::Keyboard::S:
						standard.move(0, 10);
						break;
					case sf::Keyboard::D:
						standard.move(10, 0);
						break;
					case sf::Keyboard::Return:
						break;
					default:
						break;
					}
				}
			}
			//Mouse Released
			if (event.type == sf::Event::MouseButtonReleased) { 
				for (int i = 0; i < 7; i++) {
					if (simulation.simulationDirector->ModeEnum != SimulationDirector::Mode::EXPERIMENT) {
						if (i == 1) {
							i = 4; //Restrict access to some buttons when not in experiment mode
						}
					}
					if (simulation.guiDirector->getGameButtons()[i]->isMouseOver(window)) { //Check if main game buttons clicked
						int possibleScreen;
						possibleScreen = simulation.buttonAction(simulation.guiDirector->getGameButtons()[i]->getButton());
						if (i == 5) {
							return possibleScreen;
						}
						break;
					}
				}
				if (simulation.guiDirector->showModeButtons) {
					for (int i = 7; i < 11; i++) {
						if (simulation.guiDirector->getGameButtons()[i]->isMouseOver(window)) {
							simulation.buttonAction(simulation.guiDirector->getGameButtons()[i]->getButton()); //Check if mode buttons clicked
							break;
						}
					}
				}
				if (simulation.guiDirector->showAddButtons) {
					for (int i = 7; i < 10; i++) {
						if (simulation.guiDirector->getGameButtons()[i]->isMouseOver(window)) {
							simulation.buttonAction(simulation.guiDirector->getGameButtons()[i]->getButton()); //Check if add buttons clicked
							break;
						}
					}
				}
				if (simulation.guiDirector->showModifyButtons) {
					for (int i = 7; i < 12; i++) {
						if (simulation.guiDirector->getGameButtons()[i]->isMouseOver(window)) {
							simulation.buttonAction(simulation.guiDirector->getGameButtons()[i]->getButton()); //Check if modify buttons clicked
							break;
						}
					}
				}
				if (simulation.stateEnum == Simulation::State::SELECT) {
					window.setView(standard);
					simulation.simulationDirector->isOverCelestial(window); //If in select mode, check if celestials clicked
					window.setView(fixed);
				}
				if (simulation.stateEnum == Simulation::State::ERASE) {
					window.setView(standard);
					if (simulation.simulationDirector->isOverCelestial(window)) {
						simulation.deleteCelestial(simulation.simulationDirector->selectedCelestial);
					}
					window.setView(fixed);
				}
				
			}
			//Text input
			if (event.type == sf::Event::TextEntered)
			{
				if (simulation.stateEnum == Simulation::State::ADDMOON || simulation.stateEnum == Simulation::State::ADDPLANET || simulation.stateEnum == Simulation::State::ADDSTAR || simulation.stateEnum == Simulation::State::MODIFYVALUE) {
					if (event.text.unicode == '\b') {
						if (!input.empty()) {
							input.pop_back(); //If backspace pressed, then delete a character
						}
					}else if (event.text.unicode == 13) { //Through testing, found that unicode for 'return' key is 13
						if (simulation.stateEnum != Simulation::State::MODIFYVALUE) {
							simulation.addInput(input); //If enter pressed and mode is not modify, then add input
						}else{
							simulation.changeValue(input); //If enter pressed and mode is modify, then change that value
						}
						input = ""; //Reset input after pressing enter
					
						//Pass through input to simulation object
					} else if (event.text.unicode < 128) {
						input += static_cast<char>(event.text.unicode);
					}
					simulation.guiDirector->userInput->setString(input); //Update string that will be output
				}
			}
			
		}
		//Hover check buttons
		for (int i = 0; i < 7; i++) {
			if (simulation.simulationDirector->ModeEnum != SimulationDirector::Mode::EXPERIMENT) {
				if (i == 1) {
					i = 4; //No hover animation for some buttons when not in experiment mode to show that they cannot be used
				}
			}
			simulation.guiDirector->getGameButtons()[i]->update(window);
		}
		if (simulation.guiDirector->showModeButtons) {
			for (int i = 7; i < 11; i++) {
				simulation.guiDirector->getGameButtons()[i]->update(window);
			}
		}
		if (simulation.guiDirector->showAddButtons) {
			for (int i = 7; i < 10; i++) {
				simulation.guiDirector->getGameButtons()[i]->update(window);
			}
		}
		if (simulation.guiDirector->showModifyButtons) {
			for (int i = 7; i < 12; i++) {
				simulation.guiDirector->getGameButtons()[i]->update(window);
			}
		}
		//When getting at alpha_max, we stop modifying the objects
		if (alphaBackground< maxAlphaBackground)
		{
			alphaBackground++;
			simulation.guiDirector->getSimulation()->setColour(sf::Color(255, 255, 255, alpha / alpha_div));
		}
		if (alpha < alpha_max) {
			alpha++;
			for (int i = 0; i < 7; i++) {
				simulation.guiDirector->getGameButtons()[i]->setColour(sf::Color(255, 255, 255, alpha / alpha_div));
			}
		}

		//Physics Loop
		while (accumulator.asSeconds() >= dt) {
			//Integrate (within simulation class) get new state
			//Two within simulation class therefore can have one method called 'update'.
			simulation.update(t, scaledDt, dt);
			if (!simulation.paused){
				t += scaledDt;
			}
			accumulator -= sf::seconds(dt);
		}



		//Clearing screen
		window.clear();
		//Drawing all objects
		window.draw(*simulation.guiDirector->getSimulation());
		window.setView(standard);
		for (int i = 0; i < simulation.simulationDirector->planets.size(); i++) {
			window.draw(*simulation.simulationDirector->planets[i]);
		}
		for (int i = 0; i < simulation.simulationDirector->stars.size(); i++) {
			window.draw(*simulation.simulationDirector->stars[i]);
		}
		for (int i = 0; i < simulation.simulationDirector->moons.size(); i++) {
			window.draw(*simulation.simulationDirector->moons[i]);
		}
		window.setView(fixed);
		for (int i = 0; i < 7; i++) {
			window.draw(*simulation.guiDirector->getGameButtons()[i]);
		}
		if (simulation.guiDirector->showModeButtons) {
			for (int i = 7; i < 11; i++) {
				window.draw(*simulation.guiDirector->getGameButtons()[i]);
			}
		}
		if (simulation.guiDirector->showAddButtons) {
			for (int i = 7; i < 10; i++) {
				window.draw(*simulation.guiDirector->getGameButtons()[i]);
			}
		}
		if (simulation.guiDirector->showModifyButtons) {
			for (int i = 7; i < 12; i++) {
				window.draw(*simulation.guiDirector->getGameButtons()[i]);
			}
		}
		window.draw(*simulation.guiDirector->mainInfo);
		window.draw(*simulation.guiDirector->simulationInfo);
		window.draw(*simulation.guiDirector->celestialInfo);
		window.draw(*simulation.guiDirector->modeInfo);
		if (simulation.stateEnum == Simulation::State::ADDMOON || simulation.stateEnum == Simulation::State::ADDPLANET || simulation.stateEnum == Simulation::State::ADDSTAR || simulation.stateEnum == Simulation::State::MODIFYVALUE) {
			window.draw(*simulation.guiDirector->inputInfo);
			window.draw(*simulation.guiDirector->userInput);
		}
		window.display();
	}
	return 0;
}

