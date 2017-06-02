// Page: ButtonBase.cpp
#include "Precompiled.h"
#include "ButtonBase.h"





gui::ButtonBase::ButtonBase(gui::ButtonBase::Menu type): MenuEnum(type), StateEnum(State::NORMAL) //MenuEnum(type) is a way of initialising the members of this class.
{ //Therefore, 'MenuEnum' is initialised to 'type', which is passed through as a parameter
	initSound();
}

gui::ButtonBase::ButtonBase(gui::ButtonBase::Game type): GameEnum(type), StateEnum(State::NORMAL) //^Ditto
{
	initSound();
}

gui::ButtonBase::~ButtonBase()
{
}



void gui::ButtonBase::setState(gui::ButtonBase::State state)
{
	this->StateEnum = state;
}

bool gui::ButtonBase::isMouseOver(const sf::RenderWindow &window)
{
	sf::Vector2i mousePosInt = sf::Mouse::getPosition(window); //Get mouse coordinates
	//Mouse coordinates need to be converted so that it can be passed as a parameter of the contains() method
	//The coordinates are also mapped to the current view
	sf::Vector2f convertedMousePos = window.mapPixelToCoords(mousePosInt, window.getView()); 
	sf::FloatRect buttonBounds = this->button.getGlobalBounds(); //Get button bounds
	bool isOver = (buttonBounds.contains(convertedMousePos)); //Check if mouse within these bounds
	if (isOver) {
		this->setState(gui::ButtonBase::State::HOVER); //If over, set button to hover state
	}
	else {
		this->setState(gui::ButtonBase::State::NORMAL); //Else, set button to normal state
	}
	return isOver; 
}




void gui::ButtonBase::update(const sf::RenderWindow &window)
{
	if (isMouseOver(window)) {
		//If the mouse is over the button, the hover texture is set to the button and the hover sound is played once
		this->button.setTexture(hover);
		if (!this->playedOnce) {
			this->hoverSound.play();
			playedOnce = true;
		}
	}
	else {
		//Else the button texture is set to normal
		this->button.setTexture(normal);
		playedOnce = false;
	}
}

sf::FloatRect gui::ButtonBase::getBounds()
{
	return this->button.getGlobalBounds();
}

void gui::ButtonBase::initSound()
{
	//Assigning a sound buffer onto a sound. See ButtonBase.h for more details.
	this->hoverBuffer = *this->getSoundBuffer(&this->hoverBuffer, "sound/menu/hover/hover-sound-menu.wav");
	this->hoverSound.setBuffer(hoverBuffer);
}

