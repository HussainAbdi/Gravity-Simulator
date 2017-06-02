// Page: Background.cpp
#include "Precompiled.h"
#include "ObjectBase.h"
#include "Background.h"
//Implementation of Background class


gui::Background::Background(gui::Background::Type type): BackgroundEnum(type)
{
	init();
}


gui::Background::~Background()
{
}

void gui::Background::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->background,states); //SFML method to be able to draw object to screen
}

void gui::Background::init()
{
	//Depending on the type of background needed (determined by the BackgroundEnum), the background will be initialised
	switch (this->BackgroundEnum) {
	case gui::Background::Type::SPLASH:
		initBackground("images/background/final-splash-screen.png");
		break;
	case gui::Background::Type::MENU:
		initBackground("images/background/menu-screen.png");
		break;
	case gui::Background::Type::SIMULATION:
		initBackground("images/background/simulator-screen2.png");
		break;
	}
}

void gui::Background::initBackground(std::string location)
{
	this->background.setTexture(*this->getTexture(&this->image, location)); //Setting the texture (image) of the background
}

