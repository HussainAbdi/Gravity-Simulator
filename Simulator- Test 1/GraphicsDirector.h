#pragma once
/*
This class will manage all the graphics to encapsulate it.
*/
class GraphicsDirector
{
public:
	//Graphic Objects
	//I have used std::vector to store all the graphic objects
	//In essence, std::vector is a dynamic array.
	//This means it does not contain a fixed number of objects and new objects can be dynamically added to it during runtime.
	//It also has many features such as 'myVector.push_back'

	std::vector<MenuButton> menuButtons;
	std::vector<GameButton> gameButtons;
	//std::vector<> backgrounds;
	//std::vector<Planet> planets;
	//std::vector<Star> stars;
	//Getters

	//Menu Button Getters
	MenuButton* getNewBtn() { return &this->menuButtons.at(0); };
	MenuButton* getSaveBtn() { return &this->menuButtons.at(1); };
	MenuButton* getLoadBtn() { return &this->menuButtons.at(2); };
	MenuButton* getExitBtn() { return &this->menuButtons.at(3); };
	//Game Button Getters
	GameButton* getSelectBtn() { return &this->gameButtons.at(0); };
	GameButton* getAddBtn() { return &this->gameButtons.at(1); };
	GameButton* getEraseBtn() { return &this->gameButtons.at(2); };
	GameButton* getModifyBtn() { return &this->gameButtons.at(3); };
	GameButton* getPauseBtn() { return &this->gameButtons.at(4); };

	GraphicsDirector();
	~GraphicsDirector();
};

