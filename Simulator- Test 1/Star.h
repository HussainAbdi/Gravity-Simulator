// Page: Star.h
#pragma once
/*
Defines the limits on the celestial properties for stars.
*/
class Star: public Celestial
{
public:
	//Constructors
	Star(double mass, double radius, Vector2d position);
	Star(double mass, double radius, Vector2d position, Vector2d relPosition);
	~Star();
private:
	//Validation of mass and radius
	virtual double getValidatedMass(double mass);
	virtual double getValidatedRadius(double radius);
};

