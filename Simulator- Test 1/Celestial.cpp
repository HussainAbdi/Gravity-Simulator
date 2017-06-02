// Page: Celestial.cpp
#include "Precompiled.h"
#include "Celestial.h"
#include "Constants.h"

void Celestial::resolveAcceleration(Celestial *b)
{
	
	double numerator = G*this->mass*b->mass; //This is the top of the equation used to calculate acceleration. Therefore called numerator.
	Vector2d meterDirectionXtoB = b->kPosition- this->kPosition; //Finding the vector distance
	Vector2d meterDirectionXtoBSquared = Vector2d(meterDirectionXtoB.x*meterDirectionXtoB.x, meterDirectionXtoB.y*meterDirectionXtoB.y); //Vector distance squared
	double magnitudeXtoB = sqrt(meterDirectionXtoBSquared.x + meterDirectionXtoBSquared.y); //Finding the magnitude of the distance
	Vector2d unitMeterDirectionXtoB = meterDirectionXtoB / magnitudeXtoB; //Finding the unit vector using equation: Unit Vector = Vector/Magnitude
	double magForce = numerator / (magnitudeXtoB*magnitudeXtoB); //Finding the magnitude of the force
	Vector2d force = magForce*unitMeterDirectionXtoB; //Finding the vector force by multiplying the magnitude of the force by the unit vector
	if (this->immovable == false) {
		this->acceleration += force*this->inv_mass; //Add to acceleration of this celestial using f = ma, therefore a = f/m
	}
	if (b->immovable == false) {
		//If the other celestial is not immovable, then assign the opposite (negative) acceleration to it. We know that it is equal and opposite because of Newton's third law of motion.
		b->acceleration += -force*b->inv_mass;
	}
}

void Celestial::circOrbit(sf::Vector2f orbitCelestialPosition, double dt)
{
	//The celestial to be orbitted is used as a reference ('orbitCelestialPosition') to calculate the position of the orbiting celestial
	//The x and y functions can be determined using mathematical and physics knowledge
	//They are both sinusoidal and can therefore be expressed through sin and cos.
	double x = orbitCelestialPosition.x + cos(this->orbitAngle)*this->orbitRadius;
	double y = orbitCelestialPosition.y + sin(this->orbitAngle)*this->orbitRadius;
	//The initial speed of the orbitting celestial is used to figure out its x and y velocities at different positions
	double vx = this->initialSpeed*-sin(this->orbitAngle); 
	double vy = this->initialSpeed*cos(this->orbitAngle);
	//The initial acceleration of the orbitting celestial is used to figure out its x and y accelerations at different positions
	double ax = this->initialAcceleration*-cos(this->orbitAngle);
	double ay = this->initialAcceleration*-sin(this->orbitAngle);
	//The new position, velocity and acceleration are set
	this->setPosition(x, y);
	this->setVelocity(sf::Vector2<double>(vx, vy));
	this->setAcceleration(sf::Vector2<double>(ax, ay));
	//The entire parametric equation relies on the orbit angle 
	//This angle is increased until it reaches 2PI (equivalent to 360 degrees) and then resets to 0
	//This is because there are 360 degrees or 2PI radians in a circle.
	if (this->orbitAngle < 2 * PI) {
		this->orbitAngle += (2*PI*dt)/(this->timePeriod);
	}
	else
	{
		this->orbitAngle = 0;
	}
}

bool Celestial::isMouseOver(const sf::RenderWindow & window)
{
	//The method of checking whether the mouse is within the celestial bounds is almost the same as that of the buttons
	//Refer to ButtonBase.cpp for the detailed comments
	sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
	sf::Vector2f convertedMousePos = window.mapPixelToCoords(mousePosInt, window.getView()); //Needs to be converted so that hover works when changing window size
	sf::FloatRect celestialBounds = this->getGlobalBounds();
	bool isOver = (celestialBounds.contains(convertedMousePos));
	return isOver;
}
//The following comments refer to the next two methods ('getSpeed' and 'getAccelerationMag')
//This can be done because any vector quantity can be converted into its magnitude using the equation 'magnitude = sqrt(vectorXSquared + vectorYSquared)'
//For 'getSpeed', the magnitude of velocity is speed
//This calculation is done and the result is convereted into a string which is outputted among the other properties of the selected celestial

double Celestial::getSpeed()
{
	//Uses the x and y velocity of the celestial to calcualte the speed
	double velx = this->velocity.x;
	double vely = this->velocity.y;
	double speed = sqrt(velx*velx + vely*vely);
	return speed;
}

double Celestial::getAccelerationMag()
{
	//Uses the x and y acceleration of the celestial to calculate the acceleration magnitude
	double accx = this->acceleration.x;
	double accy = this->acceleration.y;
	double acceleration = sqrt(accx*accx + accy*accy);
	return acceleration;
}

void Celestial::updatePositionAUtoPixels(double x, double y)
{
	//Update the celestial objects position first by updating the position in meters (this is used in calculations)
	//Then by updating the pixel position
	this->positionAU = Vector2d(x , y);
	setPositionPixel();
}

void Celestial::updatePositionPixelstoAU(double x, double y)
{
	//Used to convet pixel position to meters to be used in calcualtions when a celestial is modified
	//The pixels are converted to meters using the constant 'toMeters'
	//The position is then set in meters and then pixels
	this->positionAU = Vector2d(x*toMeters, y*toMeters);
	setPositionPixel();
}

void Celestial::setkPosition(sf::Vector2<double> p)
{
	//Used within evaluate to set the temporary position that is being used in Runge-Kutta 4 calculations
	if (this->immovable == false) {
		this->kPosition = p;
	}
}

void Celestial::setPositionPixel()
{
	//The 'toPixel' constant is used to convert the meter position into pixel position
	//This pixel posiiton is then set
	this->setPosition(sf::Vector2f(this->getPositionAU()*toPixel));
}

void Celestial::initCelestial(double mass, double radius, Vector2d position) {
	//All the necessary properties are set when a new celestial is created
	this->mass = mass;
	this->setRadius(radius);
	this->setPosition(position.x, position.y);
	this->positionAU = Vector2d(position.x*toMeters, position.y*toMeters);
	this->setImmovkPosition(positionAU);
	this->inv_mass = 1 / this->mass;
	this->setOrigin(radius, radius);
}

//The following comments are about the similarities between the two differnt constructors that are used
//They initliase the new celestial's properties

Celestial::Celestial(double mass, double radius, Vector2d position)
{
	initCelestial(mass, radius, position);
}

Celestial::Celestial(double mass, double radius, Vector2d position, Vector2d relPosition)
{
	initCelestial(mass, radius, relPosition);
	//If the parametric simulation method is being used, the orbitangle is also initialised to 0
	this->orbitAngle = 0;
}



Celestial::~Celestial()
{
}

