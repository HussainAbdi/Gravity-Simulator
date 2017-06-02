// Page: Moon.cpp
#include "Precompiled.h"
#include "Celestial.h"
#include "Moon.h"



Moon::Moon(double mass, double radius, Vector2d position) : Celestial(getValidatedMass(mass), getValidatedRadius(radius), position)
{
	this->timePeriod = (27.0 / 365.0) * 20; //The ratio of time period for the earth:moon is 365:27
}

Moon::Moon(double mass, double radius, Vector2d position, Vector2d relPosition) : Celestial(getValidatedMass(mass), getValidatedRadius(radius), position, relPosition)
{
	this->timePeriod = (27.0 / 365.0) * 20; //The ratio of time period for the earth:moon is 365:27
}

Moon::~Moon()
{
}

double Moon::getValidatedMass(double mass)
{
	if (mass > 1.5e23) {
		//This value was attained from finding the most massive moon in the solar system
		//This moon is called Ganymede and its mass is 1.4819e23kg
		mass = 1.5e23;
	}
	if (mass < 1.0e14) {
		//This value is an order of magnitude lower than the least massive moon in the solar system (It's name is Deimos)
		//This is done to allow room for other celestial objects such as comets to be used in the simulator without an official class
		mass = 1.0e14;
	}
	return mass;
}

double Moon::getValidatedRadius(double radius)
{
	//Suitable relative radii limitations have been used to differentiate between the celestials
	if (radius > 35) {
		radius = 35;
	}
	if (radius < 5) {
		radius = 5;
	}
	return radius;
}

