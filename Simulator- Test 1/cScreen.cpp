#include "Precompiled.h"

sf::Texture * cScreen::getTexture(sf::Texture * p_texture, std::string location){
	if (!p_texture->loadFromFile(location)) {
		std::cerr << location << " not loaded" << std::endl;
		return nullptr;
	}
	p_texture->setSmooth(true);
	return p_texture;
}
