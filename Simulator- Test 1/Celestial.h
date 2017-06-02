// Page: Celestial.h
#pragma once
#include "ObjectBase.h"
/*
Parent/Base class for the Planet and Star classes.
Stores basic properties of all celestial objects.
*/
class Celestial : public sf::CircleShape, public ObjectBase
{
protected:
	typedef sf::Vector2<double> Vector2d; //This is telling the computer that writing Vector2d is equivalent to writing sf::Vector2<double>.
	//The angled brackets are templates which can be used in C++ to use different data types for the same implementation.
	//Therefore, there is also sf::Vector2f, which is a predefined typedef of sf::Vector2<float> within SFML. 
	//sf::Vector2<double> does not have a typedef within the SFML code and therefore I am doing it here.
	//A sf::Vector2<T> class in SFML is a two-dimensional vector. The definition of vector in this case is the same as the Mathematical one.
	//This is not to be confused with std::vector<T> which is a list.

	//Celestial Properties
	std::string name; //Name of the celestial object, used as an identifier during simulation.
	double mass; //Mass
	double inv_mass; //Inverse mass (1/mass). This is useful for calculations.
	Vector2d velocity; //Velocity vector
	Vector2d acceleration; //Acceleration vector
	Vector2d positionAU; //Position vector
	Vector2d kPosition; //Position used in integration calculations for acceleration
	bool immovable; //Used for sun to simplify simulation
	//Vector2d offSet; //This vector stores the default offset in position if using relative coordinates
	//Properties for circular orbit
	double orbitRadius; //The radius of the circle of orbit
	double orbitAngle; //The current angle of the orbit
	double timePeriod;
	//Vector2d orbitCelestialPosition; //Position of celestial planet that is being orbitted
	//Virtual validation methods
	virtual double getValidatedMass(double mass) = 0;
	virtual double getValidatedRadius(double radius) = 0;
	
private:
	void initCelestial(double mass, double radius, Vector2d position); //Method to initialise a basic celestial object
	void setPositionPixel(); //Called when calling updatePosition()
public:
	struct Derivatives {
		sf::Vector2<double> dx; //The derivative of position, which is the velocity
		sf::Vector2<double> dv; //The derivative of velocity, which is the acceleration
	};
	//Orbit variables for use in calculations
	//These will then be outputted
	double initialSpeed; 
	double initialAcceleration;

	//Getters
	std::string getName() { return this->name; }
	double getMass() { return this->mass; } 
	double getInvMass() { return this->inv_mass; }
	Vector2d getVelocity() { return this->velocity; }
	Vector2d getPositionAU() { return this->positionAU; } //Get position in meters
	Vector2d getkPosition() { return this->kPosition; } //Get interpolated position currently being used in calculations
	Vector2d getAcceleration() { return this->acceleration; } //Get acceleration
	double getSpeed(); //Returns the magnitude of the velocity to get the speed. Used for testing.
	double getAccelerationMag();
	bool isImmovable() { return this->immovable; } //Checks whether an object is immovable (see below)
	//String getters for output of text on simulation screen
	std::string getStringMass() {
		std::ostringstream outputStream;
		outputStream << this->mass;
		return outputStream.str();
	} 
	std::string getStringVelocityX() {
		std::ostringstream outputStream;
		outputStream << this->velocity.x;
		return outputStream.str();
	}
	std::string getStringVelocityY() {
		std::ostringstream outputStream;
		outputStream << this->velocity.y;
		return outputStream.str();
	}
	std::string getStringSpeed() {
		std::ostringstream outputStream;
		outputStream << this->getSpeed();
		return outputStream.str();
	}
	std::string getStringAccelerationX() {
		std::ostringstream outputStream;
		outputStream << this->acceleration.x;
		return outputStream.str();
	}
	std::string getStringAccelerationY() {
		std::ostringstream outputStream;
		outputStream << this->acceleration.y;
		return outputStream.str();
	}
	std::string getStringAccelerationMag() {
		std::ostringstream outputStream;
		outputStream << this->getAccelerationMag();
		return outputStream.str();
	}
	std::string getStringForce() {
		std::ostringstream outputStream;
		outputStream << (this->getAccelerationMag())*(this->mass);
		return outputStream.str();
	}
	std::string getStringPixelPositionX() {
		std::ostringstream outputStream;
		outputStream << this->getPosition().x;
		return outputStream.str();
	}
	std::string getStringPixelPositionY() {
		std::ostringstream outputStream;
		outputStream << this->getPosition().y;
		return outputStream.str();
	}
	//Setters
	void updatePositionAUtoPixels(double x, double y); //Uses AU coordinates to set the AU position and then pixel position
	void updatePositionPixelstoAU(double x, double y); //Uses pixel coordinates to set the pixel position and then the AU position
	void setVelocity(sf::Vector2<double> v) { this->velocity = v; }
	void setAcceleration(sf::Vector2<double> a) { this->acceleration = a; }
	void setkPosition(sf::Vector2<double> p); //Sets the position to be used in calculations (in meters)
	void setImmovkPosition(sf::Vector2<double> p) { this->kPosition = p; } //Refers to immov (immovable) because implemented to set the inital position of immovable objects
	void setImmovable(bool i) { this->immovable = i; } //Used to make objects like the sun immovable (an assumption)
	void setOrbitRadius(double radius) { this->orbitRadius = radius; }
	void setName(std::string str) { this->name = str; }
	void setMass(double m) { this->mass = m; }
	//Simulation properties and methods
	void resolveAcceleration(Celestial *b); //Resolve the acceleration between two objects
	void circOrbit(sf::Vector2f orbitCelestialPosition, double dt); //Method called for a circular orbit around an object
	bool isMouseOver(const sf::RenderWindow &window);
	Derivatives k1, k2, k3, k4; //Constants used for RK4 Integration
	/*
	(For above)
	These constants are calculate each timestep. 
	They are then used in a calculation to estimate the position and velocity of each celestial.
	For more information, see Simulation.cpp
	*/
	sf::Vector2<double> dxdt; //Final position
	sf::Vector2<double> dvdt; //Final velocity
	//Constructors
	Celestial(double mass, double radius, Vector2d position);
	Celestial(double mass, double radius, Vector2d position, Vector2d relPosition);
	~Celestial();
	
};

//Example code for double to string
/*
std::ostringstream strs;
strs << dbl;
std::string str = strs.str();
*/