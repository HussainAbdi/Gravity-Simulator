#include "Precompiled.h"
#include "ObjectBase.h"
#include "ButtonBase.h"




gui::ButtonBase::ButtonBase(gui::ButtonBase::Menu type): MenuEnum(type), StateEnum(State::NORMAL) //MenuEnum(button) is a way of initialising the members of this class.
{ //Therefore, 'MenuEnum' is initialised to 'button', which is passed through as a parameter
}

gui::ButtonBase::ButtonBase(gui::ButtonBase::Game type): GameEnum(type), StateEnum(State::NORMAL) //^Ditto
{
}

gui::ButtonBase::~ButtonBase()
{
}



void gui::ButtonBase::setState(gui::ButtonBase::State state)
{
	this->StateEnum = state;
}

bool gui::ButtonBase::isMouseOver(const sf::RenderWindow window)
{
	return false;
}

bool gui::ButtonBase::isMousePressedOver(const sf::RenderWindow window)
{
	return false;
}

sf::FloatRect gui::ButtonBase::getBounds()
{
	return this->button.getGlobalBounds();
}



