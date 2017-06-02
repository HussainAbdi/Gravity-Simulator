// Page: Background.h
#pragma once
/*
One class for backgrounds with enumeration.
Stores information needed for the background picture. 
An example of a background is the splash screen.
*/
namespace gui { //Look at 'ButtonBase.h' for reason of this namespace.
	class Background : public ObjectBase, public sf::Drawable
	{
	public:
		enum class Type {
			SPLASH, MENU, SIMULATION //The three different screens
		};
		Background(gui::Background::Type type);
		~Background();
		void setColour(sf::Color colour) { this->background.setColor(colour); }
	private:
		//Variables
		sf::Sprite background;
		sf::Texture image;
		Type BackgroundEnum;
		//Methods
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //Method that belongs to SFML. Enables this object to be drawn.
		void init(); //Initialisation method for constructor
		void initBackground(std::string location); //Called by init()
	};
}
