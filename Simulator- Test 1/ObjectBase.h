#pragma once
class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();
	sf::Texture * getTexture(sf::Texture *p_texture, std::string location);
};

