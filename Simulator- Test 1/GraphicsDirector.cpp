// Page: GraphicsDirector.cpp
#include "GraphicsDirector.h"
#include <string>

void GraphicsDirector::isPaused(bool paused)
{
	//If the pause/play state of the simulation is toggled, the texture is updated to match this
	std::string locationNorm;
	std::string locationHover;
	if (paused) {
		locationNorm = "images/buttons/game-buttons/buttons-filled/pause.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/pause.png";
	}
	else {
		locationNorm = "images/buttons/game-buttons/buttons-filled/play.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/play.png";
	}
	getStateBtn()->setTextures(locationNorm, locationHover);
}


int GraphicsDirector::updateGraphics(gui::ButtonBase::Game type)
{
	//Depending on which button has been clicked, the specific graphics related action will be performed
	//This method handles the creation and visibility of branched buttons when the buttons "Add", "Modify" or "Mode" are clicked
	//For all buttons, if another button is pressed, this method makes sure any branched buttons shown are destroyed and therefore not visible
	switch (type) {
	case gui::ButtonBase::Game::SELECT:
		if (showModeButtons == true) {
			showModeButtons = false;
			clearModeButtons();
		}
		if (showAddButtons == true) {
			showAddButtons = false;
			clearAddButtons();
		}
		if (showModifyButtons == true) {
			showModifyButtons = false;
			clearModifyButtons();
		}
		break;
	case gui::ButtonBase::Game::ADD:
		if (showModeButtons == true) {
			showModeButtons = false;
			clearModeButtons();
		}
		if (showModifyButtons == true) {
			showModifyButtons = false;
			clearModifyButtons();
		}
		if (showAddButtons == false) {
			//If the Add button is clicked, the buttons 'Moon', 'Planet' and 'Star' are created and displayed
			gui::GameButton* moon = new gui::GameButton(gui::ButtonBase::Game::MOON);
			gui::GameButton* planet = new gui::GameButton(gui::ButtonBase::Game::PLANET);
			gui::GameButton* star = new gui::GameButton(gui::ButtonBase::Game::STAR);
			moon->setPosition(sf::Vector2f(241,899));
			planet->setPosition(sf::Vector2f(441,899));
			star->setPosition(sf::Vector2f(686,900));
			gameButtons.push_back(moon);
			gameButtons.push_back(planet);
			gameButtons.push_back(star);
			showAddButtons = true;
			//Set text positons
			inputInfo->setPosition(241, 899);
			userInput->setPosition(600, 899);
		}
		else {
			showAddButtons = false;
			clearAddButtons();
		}
		break;
	case gui::ButtonBase::Game::ERASE:
		if (showModeButtons == true) {
			showModeButtons = false;
			clearModeButtons();
		}
		if (showAddButtons == true) {
			showAddButtons = false;
			clearAddButtons();
		}
		if (showModifyButtons == true) {
			showModifyButtons = false;
			clearModifyButtons();
		}
		break;
	case gui::ButtonBase::Game::MODIFY:
		if (showModeButtons == true) {
			showModeButtons = false;
			clearModeButtons();
		}
		if (showAddButtons == true) {
			showAddButtons = false;
			clearAddButtons();
		}
		if (showModifyButtons == false) {
			//If the modify button is clicked the buttons 'Radius', 'Position', 'Velocity', 'Immov' and 'Name' are created and displayed
			gui::GameButton* radius = new gui::GameButton(gui::ButtonBase::Game::RADIUS);
			gui::GameButton* position = new gui::GameButton(gui::ButtonBase::Game::POSITION);
			gui::GameButton* velocity = new gui::GameButton(gui::ButtonBase::Game::VELOCITY);
			gui::GameButton* immov = new gui::GameButton(gui::ButtonBase::Game::IMMOV);
			gui::GameButton* name = new gui::GameButton(gui::ButtonBase::Game::NAME);
			radius->setPosition(sf::Vector2f(393, 899));
			position->setPosition(sf::Vector2f(650, 900));
			velocity->setPosition(sf::Vector2f(966, 900));
			immov->setPosition(sf::Vector2f(1271, 900));
			name->setPosition(sf::Vector2f(1504, 900));
			gameButtons.push_back(radius);
			gameButtons.push_back(position);
			gameButtons.push_back(velocity);
			gameButtons.push_back(immov);
			gameButtons.push_back(name);
			showModifyButtons = true;
			//Set text positions
			inputInfo->setPosition(751, 899);
			userInput->setPosition(1110, 899);
		}
		else {
			showModifyButtons = false;
			clearModifyButtons();
		}
		break;
	case gui::ButtonBase::Game::MODE:
		if (showAddButtons == true) {
			showAddButtons = false;
			clearAddButtons();
		}
		if (showModifyButtons == true) {
			showModifyButtons = false;
			clearModifyButtons();
		}
		if (showModeButtons == false) {
			//If the mode button is clicked, the buttons 'TwoBody', 'ThreeBody', 'Binary' and 'Experiment' are created and displayed
			gui::GameButton* twoBody = new gui::GameButton(gui::ButtonBase::Game::TWO);
			gui::GameButton* threeBody = new gui::GameButton(gui::ButtonBase::Game::THREE);
			gui::GameButton* binary = new gui::GameButton(gui::ButtonBase::Game::BINARY);
			gui::GameButton* experiment = new gui::GameButton(gui::ButtonBase::Game::EXPERIMENT);
			twoBody->setPosition(sf::Vector2f(817, 902));
			threeBody->setPosition(sf::Vector2f(1063, 899));
			binary->setPosition(sf::Vector2f(1366, 899));
			experiment->setPosition(sf::Vector2f(1562,899));
			gameButtons.push_back(twoBody);
			gameButtons.push_back(threeBody);
			gameButtons.push_back(binary);
			gameButtons.push_back(experiment);
			showModeButtons = true;
		}
		else {
			showModeButtons = false;
			clearModeButtons();
		}
		break;
	case gui::ButtonBase::Game::MENU:
		break;
	case gui::ButtonBase::Game::STATE:
		if (showModeButtons == true) {
			showModeButtons = false;
			clearModeButtons();
		}
		if (showAddButtons == true) {
			showAddButtons = false;
			clearAddButtons();
		}
		if (showModifyButtons == true) {
			showModifyButtons = false;
			clearModifyButtons();
		}
		break;
	//The following are branched buttons. Each of these delete the branched buttons once any of them are clicked.
	//The next four mode-branched buttons change the information for the current simulation
	case gui::ButtonBase::Game::TWO:
		showModeButtons = false;
		clearModeButtons();
		simulationInfo->setString("Current Simulation : Two-Body Earth & Sun\nSimulation method: Parametric equations");
		break;
	case gui::ButtonBase::Game::THREE:
		showModeButtons = false;
		clearModeButtons();
		simulationInfo->setString("Current Simulation : Three-Body Earth, Sun & Moon\nSimulation method: Parametric equations");
		break;
	case gui::ButtonBase::Game::BINARY:
		showModeButtons = false;
		clearModeButtons();
		simulationInfo->setString("Current Simulation : Theoretical binary system\nSimulation method: RK4 Integration");
		break;
	case gui::ButtonBase::Game::EXPERIMENT:
		showModeButtons = false;
		clearModeButtons();
		simulationInfo->setString("Current Simulation : Experimental\nSimulation method: RK4 Integration");
		break;
	//The following three are add-branched buttons
	case gui::ButtonBase::Game::MOON:
		showAddButtons = false;
		clearAddButtons();
		break;
	case gui::ButtonBase::Game::PLANET:
		showAddButtons = false;
		clearAddButtons();
		break;
	case gui::ButtonBase::Game::STAR:
		showAddButtons = false;
		clearAddButtons();
		break;
	//The following five are modify-branched buttons
	//This will update the graphics to output a string for what input is being modified by the user
	case gui::ButtonBase::Game::RADIUS:
		showModifyButtons = false;
		clearModifyButtons();
		inputInfo->setString("New Radius:");
		break;
	case gui::ButtonBase::Game::POSITION:
		showModifyButtons = false;
		clearModifyButtons();
		inputInfo->setString("New X Pos:");
		break;
	case gui::ButtonBase::Game::VELOCITY:
		showModifyButtons = false;
		clearModifyButtons();
		inputInfo->setString("New X Vel:");
		break;
	case gui::ButtonBase::Game::IMMOV:
		showModifyButtons = false;
		clearModifyButtons();
		inputInfo->setString("Immovable (T/F):");
		break;
	case gui::ButtonBase::Game::NAME:
		showModifyButtons = false;
		clearModifyButtons();
		inputInfo->setString("New Name:");
		break;
	}
	return 0;
}

int GraphicsDirector::updateGraphics(gui::ButtonBase::Menu type)
{
	//This method is set up to make a framework for if any graphical changes might be made in the future when menu buttons are clicked
	//In this version of the simulator, it is not used
	return 0;
}

GraphicsDirector::GraphicsDirector()
{
	//Initialise the GraphicsDirector object
	initBackgroundObjects();
	initMenuObjects();
	initGameObjects();
	initText();
}


GraphicsDirector::~GraphicsDirector()
{

}

void GraphicsDirector::initBackgroundObjects()
{
	//Initialising Backgrounds
	gui::Background* splashScreen = new gui::Background(gui::Background::Type::SPLASH); //OMG IT WORKS!! DOCUMENT.
	gui::Background* menuScreen = new gui::Background(gui::Background::Type::MENU);
	gui::Background* simulationScreen = new gui::Background(gui::Background::Type::SIMULATION);
	//Adding Background objects to the vector backgrounds
	backgrounds.push_back(splashScreen);
	backgrounds.push_back(menuScreen);
	backgrounds.push_back(simulationScreen);

}

void GraphicsDirector::initMenuObjects()
{
	//Initialising Menu buttons
	gui::MenuButton* newSimulation = new gui::MenuButton(gui::ButtonBase::Menu::NEW);
	gui::MenuButton* exitSimulation = new gui::MenuButton(gui::ButtonBase::Menu::EXIT);
	//Setting Button Positions
	newSimulation->setPosition(sf::Vector2f(468,502));
	exitSimulation->setPosition(sf::Vector2f(810,730));
	//Adding MenuButton objects to the vector menuButtons
	menuButtons.push_back(newSimulation);
	menuButtons.push_back(exitSimulation);
}

void GraphicsDirector::initGameObjects()
{
	showModeButtons = false;
	showAddButtons = false;
	//Initialising Game buttons
	gui::GameButton* selectObject = new gui::GameButton(gui::ButtonBase::Game::SELECT);
	gui::GameButton* addObject = new gui::GameButton(gui::ButtonBase::Game::ADD);
	gui::GameButton* eraseObject = new gui::GameButton(gui::ButtonBase::Game::ERASE);
	gui::GameButton* modifyObject = new gui::GameButton(gui::ButtonBase::Game::MODIFY);
	gui::GameButton* modeObject = new gui::GameButton(gui::ButtonBase::Game::MODE);
	gui::GameButton* menuObject = new gui::GameButton(gui::ButtonBase::Game::MENU);
	gui::GameButton* stateObject = new gui::GameButton(gui::ButtonBase::Game::STATE);
	//Setting Button Positions
	selectObject->setPosition(sf::Vector2f(139, 977));
	addObject->setPosition(sf::Vector2f(460, 981));
	eraseObject->setPosition(sf::Vector2f(659, 981));
	modifyObject->setPosition(sf::Vector2f(951, 977));
	modeObject->setPosition(sf::Vector2f(1270, 981));
	menuObject->setPosition(sf::Vector2f(1536, 977));
	stateObject->setPosition(sf::Vector2f(49, 47));
	////Adding GameButton objects to the vector gameButtons
	gameButtons.push_back(selectObject);
	gameButtons.push_back(addObject);
	gameButtons.push_back(eraseObject);
	gameButtons.push_back(modifyObject);
	gameButtons.push_back(modeObject);
	gameButtons.push_back(menuObject);
	gameButtons.push_back(stateObject);
}

void GraphicsDirector::initText()
{
	//Initialising the font to be used
	gravityFont = new sf::Font;
	if (!gravityFont->loadFromFile("batmfa.ttf")) {
		std::cout << "Could not load font" << std::endl;
	}
	//For each of the following texts, the positions, font and string has to be set after instantiating
	//Initialise the welcome and help information
	mainInfo = new sf::Text(
		"Welcome to the Gravity Simulator!\nUse the WASD keys to navigate and the UP/DOWN keys to zoom."
		, *gravityFont);
	mainInfo->setPosition(200.0, 0.0);
	//Initialise the default simulation information
	simulationInfo = new sf::Text(
		"Current Simulation: Two Body Earth & Sun\nSimulation method: Parametric equations"
		, *gravityFont);
	simulationInfo->setPosition(200.0, 60.0);
	//Initialise the selected selected information to be updated later
	celestialInfo = new sf::Text(
		"",*gravityFont
	);
	celestialInfo->setPosition(1200.0, 100.0);
	//Initialise the current simulation mode variable
	modeInfo = new sf::Text(
		"", *gravityFont
	);
	modeInfo->setPosition(200.0, 120.0);
	//Initialise the first input information that is needed when adding a new celestial
	inputInfo = new sf::Text(
		"Enter Mass (SF):", *gravityFont
	);
	inputInfo->setPosition(241,899);
	//Initialise the variable that will tell the user what to input when needed
	userInput = new sf::Text{
		"", *gravityFont
	};
	userInput->setPosition(600,899);
}
//The following three methods clear the respective branched buttons so that they are deleted so no longer in memory and therefore not visible
//This is called when they are no longer needed
void GraphicsDirector::clearModeButtons()
{
	for (int i = 0; i < 4; i++) {
		gameButtons.pop_back();
	}
}

void GraphicsDirector::clearAddButtons()
{
	for (int i = 0; i < 3; i++) {
		gameButtons.pop_back();
	}
	inputInfo->setString("Enter Mass (SF):");
}

void GraphicsDirector::clearModifyButtons()
{
	for (int i = 0; i < 5; i++) {
		gameButtons.pop_back();
	}
}

