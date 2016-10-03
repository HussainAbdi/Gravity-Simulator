#pragma once
class SplashScreen :public cScreen
{
private:
	int alpha_max;
	int alpha_div;
public:
	SplashScreen();
	virtual int Run(sf::RenderWindow &window);
};

