#pragma once
class BackgroundBase: public ObjectBase
{
public:
	BackgroundBase();
	~BackgroundBase();
protected:
	sf::Sprite background;
	sf::Texture image;
};

