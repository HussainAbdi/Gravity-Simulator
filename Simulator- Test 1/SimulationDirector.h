// Page: SimulationDirector.h
#pragma once
/*
This class stores information about simulations and manages the celestial objects.
*/
#include "Celestial.h"
#include "Planet.h"
#include "Star.h"
#include "Moon.h"
class SimulationDirector
{
private:
	//Default celestial properties for two-body and three-body simulations
	void initialPropertiesTwoBody();
	void initialPropertiesThreeBody();
public:
	enum class Mode {
		TWO,THREE,BINARY,EXPERIMENT //The four simulation modes
	};
	std::vector<Planet*> planets; //Vetor to store planets
	std::vector<Star*> stars; //Vector to store stars
	std::vector<Moon*> moons; //Vector to store moons

	//Initialising modes methods
	void initTwoBodyDefault();
	void initThreeBody();
	void initBinary();
	void initExperiment();
	//Determines if mouse is over celestial
	bool isOverCelestial(const sf::RenderWindow &window);
	//This will be called to remove all objects from all three celestial vectors.
	void clearVectors();
	//Pointer to selected celestial object
	Celestial* selectedCelestial;
	//Current Mode
	Mode ModeEnum;
	//Constructor
	SimulationDirector();
	~SimulationDirector();

};

