#pragma once
/*
Base button class. 
*/
/*
I am putting this class within a namespace to seperate the GUI from the implementation.
I added two more namespaces (type and button) to further break down the program and prevent unwanted/accidental access as well as easier to read code.

*/
namespace gui {
	namespace type {
		enum class menubutton {
			NEW, LOAD, SAVE, EXIT
		};
		enum class gamebutton {
			SELECT, ADD, ERASE, MODIFY, PAUSE
		};
	}
	namespace button {
		enum class state {
			NORMAL, HOVER
		};
	}
	class ButtonBase : public sf::Drawable
	{
	private:
		//GUI
		sf::Sprite button;
		sf::Texture normal;
		sf::Texture hover;
		int alpha;
		//Implementation
		sf::Vector2i position;
		//Next steps need to get enum working.
		//Find a way for differnt code to run for different enum types, without making too many classes.
	public:
		ButtonBase();
		~ButtonBase();
	};

}