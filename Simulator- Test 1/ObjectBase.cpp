// Page: ObjectBase.cpp
#include "ObjectBase.h"



ObjectBase::ObjectBase()
{
	//Alpha used here to set opacity of images/textures
	this->alpha_max = 3 * 255; //Maximun opacity
	this->alpha_div = 3; //Minimum opacity
}


ObjectBase::~ObjectBase()
{
}

sf::Texture * ObjectBase::getTexture(sf::Texture * p_texture, std::string location)
{
	//A texture is loaded from a file in memory and a pointer to the texture is returned
	if (!p_texture->loadFromFile(location)) {
		std::cerr << location << " not loaded" << std::endl;
		return nullptr;
	}
	p_texture->setSmooth(true);
	return p_texture;
}

sf::SoundBuffer * ObjectBase::getSoundBuffer(sf::SoundBuffer * p_buffer, std::string location)
{
	//A sound buffer is loaded from a file in memory and a pointer to the texture is returned
	if (!p_buffer->loadFromFile(location)) {
		std::cerr << location << " not loaded" << std::endl;
		return nullptr;
	}
	return p_buffer;
}
