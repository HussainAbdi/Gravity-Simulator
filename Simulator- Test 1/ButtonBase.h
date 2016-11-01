#pragma once
/*
Base button class. 
*/
//I am putting this class within a namespace to seperate the GUI from the implementation.
namespace gui {
	class ButtonBase: public ObjectBase
	{
	public:
		//Enumerations for different buttons
		enum class Menu {
			NEW, LOAD, SAVE, EXIT
		};
		enum class Game {
			SELECT, ADD, ERASE, MODIFY, PAUSE
		};
		enum class State {
			NORMAL, HOVER
		};
		//Here, I have used a method called overloading. This means I have two contructor declerations, each with different parameters.
		//I have done this since there are two dervied classes from this base class. Both these derived classes need a different base class contructor.
		//Also, this maintains encapsulation since this class is handling its own members.
		ButtonBase(gui::ButtonBase::Menu type);
		ButtonBase(gui::ButtonBase::Game type);
		~ButtonBase();
		//Getters
		sf::FloatRect getBounds();
		gui::ButtonBase::State getState() { return this->StateEnum; }
	protected:
		//GUI
		sf::Sprite button;
		sf::Texture normal;
		sf::Texture hover;
		//Enum variables
		//N.B. these enums are declared here so that they can be accessed by derived classes.
		Menu MenuEnum;
		Game GameEnum;
		State StateEnum;
		//Implementation
		sf::Vector2i position;
		void setState(gui::ButtonBase::State state);
		bool isMouseOver(const sf::RenderWindow window);
		bool isMousePressedOver(const sf::RenderWindow window);
		//Next steps need to get enum working.
		//Find a way for differnt code to run for different enum types, without making too many classes.
	};

}