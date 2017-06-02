// Page: ObjectBase.h
#pragma once
/*
All objects which are in the simulation (i.e. not a screen or a director) will directly or indirectly inherit this.
This allows encapsulation of data which all objects should/can have.
*/
#include "Precompiled.h"
class ObjectBase
{
protected:
	//Variables for opacity
	int alpha_max; //Maximum opacity. The screen will be fully visible
	int alpha_div; //Minimum opacity. The screen will be completely transparent
	int alpha; //Objects current opacity
	//Getters
	sf::Texture * getTexture(sf::Texture *p_texture, std::string location);
	sf::SoundBuffer * getSoundBuffer(sf::SoundBuffer *p_buffer, std::string location);
public:
	//Constructor
	ObjectBase();
	~ObjectBase();
};
