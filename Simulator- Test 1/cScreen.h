#pragma once
/*
This is a virtual object that will be the base class for our different screens.
*/
class cScreen
{
public:
	//Use of polymorphism. The 'Run' function will be used in the different screens, doing different things.
	//This function will return a number. Based on which number is returned, a screen will be output or the application will terminate.
	//In the main, when -1 is returned, the application terminates.
	virtual int Run(sf::RenderWindow &window) = 0;
	sf::Texture * getTexture(sf::Texture *p_texture, std::string location);
};

