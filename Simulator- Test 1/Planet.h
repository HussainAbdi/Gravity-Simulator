// Page: Planet.h
#pragma once
/*
Defines the limits on the celestial properties for planets.
*/
class Planet: public Celestial
{
public:
	//Constructors
	Planet(double mass, double radius, Vector2d position);
	Planet(double mass, double radius, Vector2d position, Vector2d relPosition);
	~Planet();
private:
	//Validation of mass and radius
	virtual double getValidatedMass(double mass);
	virtual double getValidatedRadius(double radius);
};

