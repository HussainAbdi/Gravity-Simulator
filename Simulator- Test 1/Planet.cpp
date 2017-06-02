// Page: Planet.cpp
#include "Precompiled.h"
#include "Celestial.h"
#include "Planet.h"


//No way of preventing call of base constructor. However, can pass methods as base parameters which will be processed first. Therefore add three functions which validate and return the correct parameter. 15/02/17 8:09AM
Planet::Planet(double mass, double radius, Vector2d position) : Celestial(getValidatedMass(mass), getValidatedRadius(radius), position)
{
	this->timePeriod = 20;
	this->setFillColor(sf::Color::Blue);
}

Planet::Planet(double mass, double radius, Vector2d position, Vector2d relPosition) : Celestial(getValidatedMass(mass), getValidatedRadius(radius), position, relPosition)
{
	this->timePeriod = 20;
	this->setFillColor(sf::Color::Blue);
}


Planet::~Planet()
{
}

double Planet::getValidatedMass(double mass)
{
	if (mass > 6.0e28) {
		//This value was chosen based on the most massive exoplanet known at the moment
		mass = 6.0e28;
	}?
	if (mass < 6.0e22) {
		//This value was chosen based on the least massive exoplanet known at the moment
		mass = 6.0e22;
	}
	return mass;
}

double Planet::getValidatedRadius(double radius)
{
	//Suitable relative radii limitations have been used to differentiate between the celestials
	if (radius > 75) {
		radius = 75;
	}
	if (radius < 10) {
		radius = 10;
	}
	return radius;
}


