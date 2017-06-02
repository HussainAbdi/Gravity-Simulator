// Page: MenuButton.h
#pragma once
/*
Derived from ButtonBase.
Stores all properties of Menu buttons.
Menu buttons are display on the main menu screen.
*/
namespace gui {
	class MenuButton : public gui::ButtonBase, public sf::Drawable
	{
	private:
		//Initialising method
		void init();
	public:
		//Constructor
		MenuButton(gui::ButtonBase::Menu type);
		~MenuButton();
		//Getters
		gui::ButtonBase::Menu getButton() { return this->MenuEnum; }
		//Draw method
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		//Execute button action method
		virtual int updateDerived(const sf::RenderWindow &window);
	};
}

