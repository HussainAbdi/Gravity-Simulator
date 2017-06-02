// Page: GameButton.h
#pragma once
/*
Derived from ButtonBase.
Stores properties of all Game buttons.
Game buttons are buttons displayed during simulation.
*/
namespace gui {
	class GameButton : public gui::ButtonBase, public sf::Drawable
	{
	private:
		//Initialising method
		void init();
	public:
		//Constructor
		GameButton(gui::ButtonBase::Game type);
		~GameButton();
		//Getter
		gui::ButtonBase::Game getButton() { return this->GameEnum; }
		//Draw method
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		//Execute button action method
		virtual int updateDerived(const sf::RenderWindow &window);
		//Change the texture of button, used for the Pause button
		void setTextures(std::string locationNorm, std::string locationHover);
	};
}

