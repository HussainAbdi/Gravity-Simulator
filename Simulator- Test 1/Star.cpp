// Page: Star.cpp
#include "Precompiled.h"
#include "Celestial.h"
#include "Star.h"



Star::Star(double mass, double radius, Vector2d position) : Celestial(getValidatedMass(mass),getValidatedRadius(radius), position)
{
	this->setFillColor(sf::Color::Yellow);
}

Star::Star(double mass, double radius, Vector2d position, Vector2d relPosition) : Celestial(getValidatedMass(mass), getValidatedRadius(radius), position, relPosition)
{
	this->setFillColor(sf::Color::Yellow);
}


Star::~Star()
{
}

double Star::getValidatedMass(double mass)
{
	if (mass > 6.3e32) {
		//This was chosen based on the most massive known star. It is called R136a1.
		mass = 6.3e32; 
	}
	if (mass < 2.6e28) {
		//This was chosen based on one of the least massive stars known. It is called AB Pictoris.
		mass = 2.6e28;
	}
	return mass;
}

double Star::getValidatedRadius(double radius)
{
	//Suitable relative radii limitations have been used to differentiate between the celestials
	if (radius > 200) {
		radius = 200;
	}
	if (radius < 50) {
		radius = 50;
	}
	return radius;
}
