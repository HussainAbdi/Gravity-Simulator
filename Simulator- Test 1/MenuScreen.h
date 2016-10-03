#pragma once
class MenuScreen : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
public:
	MenuScreen();
	virtual int Run(sf::RenderWindow &window);
};

