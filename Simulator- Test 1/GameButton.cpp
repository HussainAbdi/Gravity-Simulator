// Page: GameButton.cpp
#include "Precompiled.h"
#include "ButtonBase.h"
#include "GameButton.h"




gui::GameButton::GameButton(gui::ButtonBase::Game type): ButtonBase(type)
{
	init();
}

gui::GameButton::~GameButton()
{
}

void gui::GameButton::init()
{
	//Depending on the type of button being initialised, different locations will be selected for the normal and hover textures.
	std::string locationNorm;
	std::string locationHover;
	switch (this->GameEnum) {
	case gui::ButtonBase::Game::SELECT:
		locationNorm = "images/buttons/game-buttons/buttons-filled/select.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/select.png";
		break;
	case gui::ButtonBase::Game::ADD:
		locationNorm = "images/buttons/game-buttons/buttons-filled/add.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/add.png";
		break;
	case gui::ButtonBase::Game::ERASE:
		locationNorm = "images/buttons/game-buttons/buttons-filled/erase.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/erase.png";
		break;
	case gui::ButtonBase::Game::MODIFY:
		locationNorm = "images/buttons/game-buttons/buttons-filled/modify.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/modify.png";
		break;
	case gui::ButtonBase::Game::MODE:
		locationNorm = "images/buttons/game-buttons/buttons-filled/mode.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/mode.png";
		break;
	case gui::ButtonBase::Game::MENU:
		locationNorm = "images/buttons/game-buttons/buttons-filled/menu.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/menu.png";
		break;
	case gui::ButtonBase::Game::STATE:
		locationNorm = "images/buttons/game-buttons/buttons-filled/play.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/play.png";
		break;
	case gui::ButtonBase::Game::TWO:
		locationNorm = "images/buttons/game-buttons/buttons-filled/twobody.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/twobody.png";
		break;
	case gui::ButtonBase::Game::THREE:
		locationNorm = "images/buttons/game-buttons/buttons-filled/threebody.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/threebody.png";
		break;
	case gui::ButtonBase::Game::BINARY:
		locationNorm = "images/buttons/game-buttons/buttons-filled/binary.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/binary.png";
		break;
	case gui::ButtonBase::Game::EXPERIMENT:
		locationNorm = "images/buttons/game-buttons/buttons-filled/experiment.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/experiment.png";
		break;
	case gui::ButtonBase::Game::MOON:
		locationNorm = "images/buttons/game-buttons/buttons-filled/moon.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/moon.png";
		break;
	case gui::ButtonBase::Game::PLANET:
		locationNorm = "images/buttons/game-buttons/buttons-filled/planet.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/planet.png";
		break;
	case gui::ButtonBase::Game::STAR:
		locationNorm = "images/buttons/game-buttons/buttons-filled/star.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/star.png";
		break;
	case gui::ButtonBase::Game::RADIUS:
		locationNorm = "images/buttons/game-buttons/buttons-filled/radius.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/radius.png";
		break;
	case gui::ButtonBase::Game::POSITION:
		locationNorm = "images/buttons/game-buttons/buttons-filled/position.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/position.png";
		break;
	case gui::ButtonBase::Game::VELOCITY:
		locationNorm = "images/buttons/game-buttons/buttons-filled/velocity.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/velocity.png";
		break;
	case gui::ButtonBase::Game::IMMOV:
		locationNorm = "images/buttons/game-buttons/buttons-filled/immov.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/immov.png";
		break;
	case gui::ButtonBase::Game::NAME:
		locationNorm = "images/buttons/game-buttons/buttons-filled/name.png";
		locationHover = "images/buttons/game-buttons/buttons-hover/name.png";
		break;
	}
	//These textures are then assigned
	this->normal = *this->getTexture(&this->normal, locationNorm);
	this->hover = *this->getTexture(&this->hover, locationHover);
	this->button.setTexture(normal);
}

void gui::GameButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->button);
}

int gui::GameButton::updateDerived(const sf::RenderWindow & window)
{
	//Using polymorphism, framework setup to allow integer to be returned when clicked button.
	switch (this->GameEnum) {
	case gui::ButtonBase::Game::SELECT:
		break;
	case gui::ButtonBase::Game::ADD:
		break;
	case gui::ButtonBase::Game::ERASE:
		break;
	case gui::ButtonBase::Game::MODIFY:
		break;
	case gui::ButtonBase::Game::MODE:
		break;
	case gui::ButtonBase::Game::MENU:
		break;
	case gui::ButtonBase::Game::STATE:
		break;
	}
	return NULL; //Currently unused feature (possible extension)
}

void gui::GameButton::setTextures(std::string locationNorm, std::string locationHover)
{
	this->normal = *this->getTexture(&this->normal, locationNorm);
	this->hover = *this->getTexture(&this->hover, locationHover);
	this->button.setTexture(normal);
}
