#include "Precompiled.h"
#include "ButtonBase.h"
#include "MenuButton.h"


MenuButton::MenuButton(gui::ButtonBase::Menu type): ButtonBase(type)
{
	Init();
}


MenuButton::~MenuButton()
{
}

void MenuButton::setButton(gui::ButtonBase::Menu type) {
	this->MenuEnum = type;
}



void MenuButton::Init() {
	switch (this->MenuEnum) {
		case gui::ButtonBase::Menu::NEW:
			this->button.setTexture(*this->getTexture(&this->normal,"images/"))
			//initButtonNew();
			break;
		case gui::ButtonBase::Menu::LOAD:
			//initButtonLoad();
			break;
		case gui::ButtonBase::Menu::SAVE:
			//initButtonSave();
			break;
		case gui::ButtonBase::Menu::EXIT:
			//initButtonExit();
			break;

	}
}

/*void MenuButton::initButtonNew()
{
}

void MenuButton::initButtonLoad()
{
}

void MenuButton::initButtonSave()
{
}

void MenuButton::initButtonExit()
{
}*/

