// Page: MenuButton.cpp
#include "Precompiled.h"
#include "ButtonBase.h"
#include "MenuButton.h"


gui::MenuButton::MenuButton(gui::ButtonBase::Menu type): ButtonBase(type)
{
	init();
}


void gui::MenuButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->button);
}

int gui::MenuButton::updateDerived(const sf::RenderWindow & window)
{
	//Using polymorphism, framework setup to allow integer to be returned when clicked button.
	//This is used to switch to the simulator screen and exit from the application
	switch (this->MenuEnum) {
		case gui::ButtonBase::Menu::NEW:
			return 2;
		case gui::ButtonBase::Menu::EXIT:
			return -1;
			break;
	}
	return 1;
}

gui::MenuButton::~MenuButton()
{
}


void gui::MenuButton::init() {
	//Depending on the type of button being initialised, different locations will be selected for the normal and hover textures.
	std::string locationNorm;
	std::string locationHover;
	switch (this->MenuEnum) {
		case gui::ButtonBase::Menu::NEW:
			locationNorm = "images/buttons/menu-buttons/buttons-filled/new-white.png";
			locationHover = "images/buttons/menu-buttons/buttons-hover/new-hover.png";
			break;
		case gui::ButtonBase::Menu::EXIT:
			locationNorm = "images/buttons/menu-buttons/buttons-filled/exit-white.png";
			locationHover = "images/buttons/menu-buttons/buttons-hover/exit-hover.png";
			break;
	}
	this->normal = *this->getTexture(&this->normal, locationNorm);
	this->hover = *this->getTexture(&this->hover, locationHover);
	this->button.setTexture(normal);
}

