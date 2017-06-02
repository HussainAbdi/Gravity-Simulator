// Page: ButtonBase.h
#pragma once
#include "ObjectBase.h"
/*
This is the base button class. 
Stores all basic properties for buttons.
*/
//I am putting this class within a namespace to seperate the GUI from the implementation.
namespace gui {
	class ButtonBase: public ObjectBase
	{
	private:
		void initSound();
	public:
		//Enumerations for different buttons
		enum class Menu {
			NEW, EXIT
		};
		//Enum 'STATE' is the Pause/Play button
		enum class Game {
			SELECT, ADD, ERASE, MODIFY, MODE, MENU, STATE, TWO, THREE, BINARY, EXPERIMENT,
			MOON, PLANET, STAR, RADIUS, POSITION, VELOCITY, IMMOV, NAME
		};
		enum class State {
			NORMAL, HOVER //The two button states
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
		//Setters
		void setColour(sf::Color colour) { this->button.setColor(colour); }
		void setPosition(sf::Vector2f position) { this->button.setPosition(position); }
		//Update the button per timestep
		void update(const sf::RenderWindow &window);
		//Determine whether the mouse is over the button
		bool isMouseOver(const sf::RenderWindow &window);
	protected:
		//GUI
		sf::Sprite button; //The spirte is essentially the button object
		//A texture is assigned to a sprite and this will determine it's dimensions
		sf::Texture normal;
		sf::Texture hover;
		//Enum variables
		//N.B. these enums are declared here so that they can be accessed by derived classes.
		Menu MenuEnum;
		Game GameEnum;
		State StateEnum;
		//Implementation
		sf::Vector2i position; //Position of button
		void setState(gui::ButtonBase::State state); //State of button (Hover or Normal)
		//Here I use a pure vitual function. This is a form of polymorphism.
		//This returns an integer and is used to change the screen
		virtual int updateDerived(const sf::RenderWindow &window) = 0;
		//Sound in SFML is played by using sf::Sound and sf::SoundBuffer.
		//These two work exactly in the same way as sf::Sprite and sf::Texture respectively
		//A sf::SoundBuffer is assigned to a sf::Sound
		sf::Sound hoverSound;
		sf::SoundBuffer hoverBuffer;
		bool playedOnce;
	};

}