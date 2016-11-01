#pragma once
class GameButton: public gui::ButtonBase, public sf::Drawable
{
private:
	void setButton(gui::ButtonBase::Game type);
public:
	GameButton(gui::ButtonBase::Game type);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~GameButton();
};

