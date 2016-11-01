#include "Precompiled.h"
#include "ButtonBase.h"
#include "MenuButton.h"
#include "GameButton.h"
#include "GraphicsDirector.h"

GraphicsDirector::GraphicsDirector()
{
	//Initialising Menu buttons
	MenuButton newSimulation(gui::ButtonBase::Menu::NEW);
	MenuButton saveSimulation(gui::ButtonBase::Menu::SAVE);
	MenuButton loadSimulation(gui::ButtonBase::Menu::LOAD);
	MenuButton exitSimulation(gui::ButtonBase::Menu::EXIT);
	//Adding MenuButton objects to the vector menuButtons
	menuButtons.push_back(newSimulation);
	menuButtons.push_back(saveSimulation);
	menuButtons.push_back(loadSimulation);
	menuButtons.push_back(exitSimulation);
	//Initialising Game buttons
	GameButton selectObject(gui::ButtonBase::Game::SELECT);
	GameButton addObject(gui::ButtonBase::Game::ADD);
	GameButton eraseObject(gui::ButtonBase::Game::ERASE);
	GameButton modifyObject(gui::ButtonBase::Game::MODIFY);
	GameButton pauseSimulation(gui::ButtonBase::Game::PAUSE);
	////Adding GameButton objects to the vector gameButtons
	gameButtons.push_back(selectObject);
	gameButtons.push_back(addObject);
	gameButtons.push_back(eraseObject);
	gameButtons.push_back(modifyObject);
	gameButtons.push_back(pauseSimulation);
}


GraphicsDirector::~GraphicsDirector()
{

}
