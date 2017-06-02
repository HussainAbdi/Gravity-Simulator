// Page: Simulation.h
#pragma once
/*
Stores information about Simulations.
Class Simulation handles the physics.
Brings together both directors (simulation and graphics director) in order to handle the simulation.
This encapsulates all the data and provides easy access to almost every class when needed through this class.
*/
#include "SimulationDirector.h"
#include "GraphicsDirector.h"

class Simulation
{
public:
	//Director Pointers
	SimulationDirector* simulationDirector; //Simulation Director pointer
	GraphicsDirector* guiDirector; //Graphics Director pointer
	//Simulation States
	enum class State {
		OBSERVE, SELECT, ADD, ERASE, MODIFY, MODIFYVALUE, ADDMOON, ADDPLANET, ADDSTAR
	};
	//Main update method. Called every timestep
	void update(double t, double scaledDt, double dt); 
	//Action to perform when button is clicked.
	//I have used method overloading to account for the two different types of buttons
	int buttonAction(gui::ButtonBase::Game type);
	int buttonAction(gui::ButtonBase::Menu type);
	//Method to delete a celestial object that is being passed in as a pointer
	void deleteCelestial(Celestial* celestial);
	//Method to check if the simulation is paused
	void isPaused(bool paused);
	//Method to take in string inputs in order to add a new celestial to the simulation
	void addInput(std::string input);
	//Method to change a property of an already existing celestial
	void changeValue(std::string input);
	//Needed variables for adding/modifying a celestial
	int inputCount; //Count for which property is being assigned now
	int valueToChange; //Integer to refer to which propert of a celestial must be modified
	bool paused; //Boolean for if the simulation is in the Pause or Play state
	State stateEnum; //The current state of the simulation
	//Getter
	std::string getStringState(); //Returns the state of the simulation in string form to output
	//Constructor
	Simulation();
	~Simulation();
private:
	//Resets each celestials acceleration and prepares for a call to 'efficientAccelerationLoop'
	void updateAcceleration(int planetSize, int starSize, int moonSize); //Called within 'update' method
	//Simulation Methods
	//Integration method (for binary and experimental modes)
	//This is the brain of the simulation. It uses a numerical method called Runge-Kutta 4 or RK4. Called each timestep.
	//This calculates the new position and velocity for each celestial object in the simulation.
	void integrate(double t, double dt);
	//Parametric method (for two-body and three-body demonstrations)
	//Uses parametric equations to calculate circular orbits
	void circOrbit(SimulationDirector::Mode mode, double dt);
	//Euler integration method
	//Called within 'integrate' method multiple times using different parameters.
	sf::Vector2<double> evaluate(Celestial * a, double t, double dt, const Celestial::Derivatives &d);
	//Loops through each celestial to calcualte and assign their new accelerations
	//Called within the 'updateAcceleration' method
	void efficientAccelerationLoop(std::vector<Celestial*> &mainCelestials, int mainCelestialSize, std::vector<Celestial*> &secondaryCelestial, std::vector<Celestial*> &tertiraryCelestial);
	//Temporary storage of input before new celesital initialisation
	double tempMass;
	double tempRadius;
	double tempPositionX;
	double tempPositionY;
	double tempVelX;
	double tempVelY;
	bool tempImmovable;
	std::string tempName;
	//Method to initialise a new celestial in the simulation
	void initialiseNewCelestial();
};

