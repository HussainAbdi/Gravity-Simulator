#include "Precompiled.h"
#include "ButtonBase.h"
#include "GameButton.h"



GameButton::GameButton(gui::ButtonBase::Game type): ButtonBase(type)
{
}

void GameButton::draw(sf::RenderTarget & targer, sf::RenderStates state) const
{
}


GameButton::~GameButton()
{
}

void GameButton::setButton(gui::ButtonBase::Game type) {
	this->GameEnum = type;
}

