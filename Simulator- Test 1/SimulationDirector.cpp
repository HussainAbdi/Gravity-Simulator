// Page: SimulationDirector.cpp
#include "Precompiled.h"
#include "SimulationDirector.h"



void SimulationDirector::initialPropertiesTwoBody()
{
	//This method is the initialisation for the two body simulation's properties
	//The initial velocity and acceleration of the earth are given here to be used for all parametric calculations
	double earthVelocity = 29785.25733; //29785.25733
	double earthAcceleration = 5.930308701e-3;
	sf::Vector2<double> initialVel = sf::Vector2<double>(0, earthVelocity);
	//The initial velocity, speed and acceleration are set
	this->planets[0]->setVelocity(initialVel);
	this->planets[0]->initialSpeed = earthVelocity;
	this->planets[0]->initialAcceleration = earthAcceleration;
}

void SimulationDirector::initialPropertiesThreeBody()
{
	//This method is the initialisation for the three body simulation's properties
	//This method fisrt does everything that is done is the 'initialPropertiesTwoBody()' method
	//Then the moon's initial velocity and acceleration are given and set
	initialPropertiesTwoBody();
	double moonVelocity = 1018.28955;
	double moonAcceleration = 2.697485973e-3;
	sf::Vector2<double> initialVel = sf::Vector2<double>(0, moonVelocity);
	this->moons[0]->setVelocity(initialVel);
	this->moons[0]->initialSpeed = moonVelocity;
	this->moons[0]->initialAcceleration = moonAcceleration;

}



void SimulationDirector::initTwoBodyDefault()
{
	//Setting Masses
	double earthMass = 5.9722e24;
	double sunMass = 1.98855e30;
	//Initialising bodies
	Star* sun = new Star(sunMass, 20, sf::Vector2<double>(960, 540));
	Planet* earth = new Planet(earthMass, 10, sf::Vector2<double>(960, 140));
	//Setting orbit radius for earth
	earth->setOrbitRadius(400);
	//The sun is to be made immovable for a better simulation
	sun->setImmovable(true);
	//Setting the name of the bodies
	sun->setName("The Sun");
	earth->setName("Earth");
	//Pushing back earth and sun into respective vectors
	this->planets.push_back(earth);
	this->stars.push_back(sun); 
	//The default selected body will be the earth
	this->selectedCelestial = earth;
	initialPropertiesTwoBody();
}

void SimulationDirector::initThreeBody() //Implement 3 body 09/03/17 11:54AM
{
	//Setting masses
	double earthMass = 5.9722e24;
	double sunMass = 1.98855e30;
	double moonMass = 7.34767309e22;
	//Initialising bodies
	Star* sun = new Star(sunMass, 20, sf::Vector2<double>(960, 540)); //A distance of 7773.04218 will represent 1 AU in this sceneario
	Planet* earth = new Planet(earthMass, 10, sf::Vector2<double>(960, 140)); //The y coord of earth will therefore be sun.y - 7773.04218
	Moon* moon = new Moon(moonMass, 5, sf::Vector2<double>(960, 110)); //The y coord of the moon will be earth.y - 20
	//Setting the earth's and moon's orbit radius
	earth->setOrbitRadius(400);
	moon->setOrbitRadius(30);
	//Making the sun immovable for a better simulation
	sun->setImmovable(true);
	//Setting the name of the bodies
	sun->setName("The Sun");
	earth->setName("Earth");
	moon->setName("The Moon");
	//Pushing back celestials into respective vectors
	this->planets.push_back(earth);
	this->stars.push_back(sun);
	this->moons.push_back(moon);
	//The default selected body will be the earth
	this->selectedCelestial = earth;
	initialPropertiesThreeBody();
	
}

void SimulationDirector::initBinary()
{
	//Setting the masses
	double sunMass = 1.98855e30; //Change resolve acceleration for all celestial
	double sunVelocity = 25000; //20,000 for binary. 25,000 for elliptical binary
	//Initialising the binary stars
	Star* sun1 = new Star(sunMass, 50, sf::Vector2<double>(760, 540)); //Change the way resolved in order to get stars for this
	Star* sun2 = new Star(sunMass, 50, sf::Vector2<double>(1160, 540));//Try swapping planets and stars vector?
	//Setting the names
	sun1->setName("Star 1");
	sun2->setName("Star 2");
	//Pushing back celestials into respective vectors
	stars.push_back(sun1);
	stars.push_back(sun2);
	//Setting the initial velocities
	stars[0]->setVelocity(sf::Vector2<double>(0, -sunVelocity));
	stars[1]->setVelocity(sf::Vector2<double>(0, sunVelocity));
	//The default selected body will be star 1
	this->selectedCelestial = sun1;

}

void SimulationDirector::initExperiment()
{
	//The inital celestials for the experimental mode will be the binary system. However, the user can then change things
	initBinary();
}

bool SimulationDirector::isOverCelestial(const sf::RenderWindow &window)
{
	//This method checks if the mouse is over any celestial
	//The size of each celestial vector are stored
	int sizeMoons = moons.size();
	int sizePlanets = planets.size();
	int sizeStars = stars.size();
	//First the moons are checked
	for (int i = 0; i < sizeMoons; i++) {
		if (moons[i]->isMouseOver(window)) {
			this->selectedCelestial = moons[i];
			return true;
		}
	}
	//Then the planets are checked
	for (int i = 0; i < sizePlanets; i++) {
		if (planets[i]->isMouseOver(window)) {
			this->selectedCelestial = planets[i];
			return true;
		}
	}
	//Then the stars are checked
	for (int i = 0; i < sizeStars; i++) {
		if (stars[i]->isMouseOver(window)) {
			this->selectedCelestial = stars[i];
			return true;
		}
	}
	return false;
}

void SimulationDirector::clearVectors()
{
	//Before a new simulation is called, all three vectors must be cleared before new objects can be added to them
	this->planets.clear();
	this->stars.clear();
	this->moons.clear();
}

SimulationDirector::SimulationDirector()
{
	//When the SimulationDirector is initialised, the default demonstration that is shown is the two body simulation
	initTwoBodyDefault();
	//Setting the initial mode of the simulation
	ModeEnum = Mode::TWO;


}


SimulationDirector::~SimulationDirector()
{
}
