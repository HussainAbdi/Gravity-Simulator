// Page: GraphicsDirector.h
#pragma once
#include "Precompiled.h"
#include "ButtonBase.h"
#include "MenuButton.h"
#include "GameButton.h"
#include "Background.h"

/*
This class will manage all the graphics to encapsulate it.
*/
class GraphicsDirector
{
private:
	//Initialisation Methods
	void initBackgroundObjects();
	void initMenuObjects();
	void initGameObjects();
	void initText();

	//Vectors to store buttons
	std::vector<gui::MenuButton*> menuButtons;
	std::vector<gui::GameButton*> gameButtons;
	std::vector<gui::Background*> backgrounds;

	//Methods to remove branched buttons from vector stack
	void clearModeButtons();
	void clearAddButtons();
	void clearModifyButtons();

public:
	//Graphic Objects
	//I have used std::vector to store all the graphic objects
	//In essence, std::vector is a dynamic array.
	//This means it does not contain a fixed number of objects and new objects can be dynamically added to it during runtime.
	//It also has many features such as 'myVector.push_back'

	//Getters
	//Menu Button Getters
	gui::MenuButton* getNewBtn() { return this->menuButtons.at(0); }
	gui::MenuButton* getSaveBtn() { return this->menuButtons.at(1); }
	gui::MenuButton* getLoadBtn() { return this->menuButtons.at(2); }
	gui::MenuButton* getExitBtn() { return this->menuButtons.at(3); }
	//Game Button Getters
	gui::GameButton* getSelectBtn() { return this->gameButtons.at(0); }
	gui::GameButton* getAddBtn() { return this->gameButtons.at(1); }
	gui::GameButton* getEraseBtn() { return this->gameButtons.at(2); }
	gui::GameButton* getModifyBtn() { return this->gameButtons.at(3); }
	gui::GameButton* getModeBtn() { return this->gameButtons.at(4); }
	gui::GameButton* getMenuBtn() { return this->gameButtons.at(5); }
	gui::GameButton* getStateBtn() { return this->gameButtons.at(6); }
	//Background Getters
	gui::Background* getSplash() { return this->backgrounds.at(0); }
	gui::Background* getMenu() { return this->backgrounds.at(1); }
	gui::Background* getSimulation() { return this->backgrounds.at(2); }
	//Const Vector Getters
	//I have made these public constant getters for the vectors.
	//Using const means that they cannot be changed. However, they are still useful.
	//For example, I can use a for loop and draw all of them. This is done in SimulatorScreen.cpp.
	const std::vector<gui::MenuButton*> getMenuButtons() const { return this->menuButtons; }
	const std::vector<gui::GameButton*> getGameButtons() const { return this->gameButtons; }
	const std::vector<gui::Background*> getBackgrounds() const { return this->backgrounds; }
	//Check if simulation is paused and update graphics accordingly
	void isPaused(bool paused);
	//Simulation text info
	sf::Text* mainInfo;
	sf::Text* simulationInfo;
	sf::Text* celestialInfo;
	sf::Text* modeInfo;
	sf::Text* inputInfo;
	sf::Text* userInput;
	sf::Font* gravityFont;
	//Carry out the button action
	int updateGraphics(gui::ButtonBase::Game type);
	int updateGraphics(gui::ButtonBase::Menu type);
	//Branched buttons variables
	bool showModeButtons;
	bool showAddButtons;
	bool showModifyButtons;
	//Constructor
	GraphicsDirector();
	~GraphicsDirector();
};

