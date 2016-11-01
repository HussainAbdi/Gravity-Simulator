#pragma once
class MenuButton: public gui::ButtonBase, public sf::Drawable
{
private:
	//Methods
	//Initialising methods
	void Init();
	//void initButtonNew();
	//void initButtonLoad();
	//void initButtonSave();
	//void initButtonExit();
	//Setters
	void setButton(gui::ButtonBase::Menu type);
	
	
public:
	//Constructor
	MenuButton(gui::ButtonBase::Menu type);
	//Getters
	gui::ButtonBase::Menu getButton() { return this->MenuEnum; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~MenuButton();
};

