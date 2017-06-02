// Page: Moon.h
#pragma once
/*
Defines the limits on the celestial properties for moons.
*/
class Moon : public Celestial
{
public:
	//Constructors
	Moon(double mass, double radius, Vector2d position);
	Moon(double mass, double radius, Vector2d position, Vector2d relPosition);
	~Moon();
private:
	//Validation of mass and radius
	virtual double getValidatedMass(double mass);
	virtual double getValidatedRadius(double radius);
};
