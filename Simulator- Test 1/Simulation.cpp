// Page: Simulation.cpp
#include "Precompiled.h"
#include "Simulation.h"
#include "Constants.h"

void Simulation::update(double t, double scaledDt, double dt)
{
	if (!paused) {
		SimulationDirector::Mode mode = this->simulationDirector->ModeEnum; //Getting the mode of the simulation
		if (mode == SimulationDirector::Mode::TWO || mode == SimulationDirector::Mode::THREE) { //If the mode is two or three, we want to have circular orbits
			circOrbit(mode, dt);
		}
		else //If the mode is binary or experimental, we want to use RK4 integration
		{
			integrate(t, scaledDt);
		}
	}
	//Output the properties of the selected celestial
	if (this->simulationDirector->selectedCelestial != NULL) {
		Celestial * selectedPlanet = this->simulationDirector->selectedCelestial;
		this->guiDirector->celestialInfo->setString(
			"Name: " + selectedPlanet->getName() + "\n" +
			"Mass: " + selectedPlanet->getStringMass() + "kg\n" +
			"X Velocity " + selectedPlanet->getStringVelocityX() + "m/s\n" +
			"Y Velocity: " + selectedPlanet->getStringVelocityY() + "m/s\n" +
			"Speed: " + selectedPlanet->getStringSpeed() + "m/s\n" +
			"X Acceleration: " + selectedPlanet->getStringAccelerationX() + "m/s*s\n" +
			"Y Acceleration: " + selectedPlanet->getStringAccelerationY() + "m/s*s\n" +
			"Acceleration: " + selectedPlanet->getStringAccelerationMag() + "m/s*s\n" +
			"Force: " + selectedPlanet->getStringForce() + "N\n" +
			"X Pixel Position: " + selectedPlanet->getStringPixelPositionX() + "" + " pixels\n" +
			"Y Pixel Position: " + selectedPlanet->getStringPixelPositionY() + "" + " pixels\n"
		);
	}
	else {
		this->guiDirector->celestialInfo->setString("No celestial body is selected");
	}
}

void Simulation::circOrbit(SimulationDirector::Mode mode, double dt)
{
	if (mode == SimulationDirector::Mode::TWO) {
		//If the current simulation is a two body simulation, initiate a circular orbit for the earth
		this->simulationDirector->planets[0]->circOrbit(this->simulationDirector->stars[0]->getPosition(), dt);
	}
	else {
		//If the current simulation is a three body simulation, initiate a circular orbit for the earth and the moon
		this->simulationDirector->planets[0]->circOrbit(this->simulationDirector->stars[0]->getPosition(), dt);
		this->simulationDirector->moons[0]->circOrbit(this->simulationDirector->planets[0]->getPosition(), dt);
	}
}

void Simulation::updateAcceleration(int planetSize, int starSize, int moonSize)//This function updates the acceleration for each celestial object
{
	//Assigning each derived class object to a base class pointer so that they can be passed through the function efficientAccelerationLoop()
	std::vector<Celestial*> planets(this->simulationDirector->planets.begin(), this->simulationDirector->planets.end());
	std::vector<Celestial*> stars(this->simulationDirector->stars.begin(), this->simulationDirector->stars.end());
	std::vector<Celestial*> moons(this->simulationDirector->moons.begin(), this->simulationDirector->moons.end());
	//Resetting the accelerations to 0
	for (int i = 0; i < planetSize; i++) {
		this->simulationDirector->planets[i]->setAcceleration(sf::Vector2<double>(0, 0));
	}
	for (int i = 0; i < starSize; i++) {
		this->simulationDirector->stars[i]->setAcceleration(sf::Vector2<double>(0, 0));
	}
	for (int i = 0; i < moonSize; i++) {
		this->simulationDirector->moons[i]->setAcceleration(sf::Vector2<double>(0, 0));
	}
	//Having these checks ensures that even with a lack of a certain celestial, all the celestials will be resolved for acceleration
	if (planetSize != 0) {
		efficientAccelerationLoop(planets, planetSize, stars, moons);
	}
	else if (starSize != 0) {
		efficientAccelerationLoop(stars, starSize, planets, moons);
	}
	else if (moonSize != 0) {
		efficientAccelerationLoop(moons, moonSize, planets, stars);
	}
}

int Simulation::buttonAction(gui::ButtonBase::Game type)
{
	//Update the graphics when a button is clicked
	this->guiDirector->updateGraphics(type);
	//Update the simulation when a button is clicked
	//This changes the state of the simulation
	switch (type) {
	case gui::ButtonBase::Game::SELECT:
		if (stateEnum != State::SELECT) {
			stateEnum = State::SELECT;
		}
		else {
			stateEnum = State::OBSERVE;
		}
		break;
	case gui::ButtonBase::Game::ADD:
		if (simulationDirector->ModeEnum == SimulationDirector::Mode::EXPERIMENT) {
			if (stateEnum != State::ADD) {
				stateEnum = State::ADD;
			}
			else {
				stateEnum = State::OBSERVE;
			}
		}
		break;
	case gui::ButtonBase::Game::ERASE:
		if (simulationDirector->ModeEnum == SimulationDirector::Mode::EXPERIMENT) {
			if (stateEnum != State::ERASE) {
				stateEnum = State::ERASE;
			}
			else {
				stateEnum = State::OBSERVE;
			}
		}
		break;
	case gui::ButtonBase::Game::MODIFY:
		if (simulationDirector->ModeEnum == SimulationDirector::Mode::EXPERIMENT) {
			if (stateEnum != State::MODIFY) {
				stateEnum = State::MODIFY;
			}
			else {
				stateEnum = State::OBSERVE;
			}
		}
		break;
	case gui::ButtonBase::Game::MODE:
		break;
	case gui::ButtonBase::Game::MENU:
		return 1;
		break;
	//If the pause button is pressed, then toggle between pause and play for the simulation
	case gui::ButtonBase::Game::STATE:
		if (paused == false) {
			isPaused(true);
			guiDirector->isPaused(true);
		}
		else {
			isPaused(false);
			guiDirector->isPaused(false);
		}
		break;
	//For the next for cases. If one of the mode-branched buttons is pressed, delete all the objects in the three vectors
	//The new simulation is then setup
	//The mode is changed to the mode selected
	case gui::ButtonBase::Game::TWO:
		simulationDirector->clearVectors();
		simulationDirector->initTwoBodyDefault();
		simulationDirector->ModeEnum = SimulationDirector::Mode::TWO;
		break;
	case gui::ButtonBase::Game::THREE:
		simulationDirector->clearVectors();
		simulationDirector->initThreeBody();
		simulationDirector->ModeEnum = SimulationDirector::Mode::THREE;
		break;
	case gui::ButtonBase::Game::BINARY:
		simulationDirector->clearVectors();
		simulationDirector->initBinary();
		simulationDirector->ModeEnum = SimulationDirector::Mode::BINARY;
		break;
	case gui::ButtonBase::Game::EXPERIMENT:
		simulationDirector->clearVectors();
		simulationDirector->initExperiment();
		simulationDirector->ModeEnum = SimulationDirector::Mode::EXPERIMENT;
		break;
	//For the next three. When a add-branched button is clicked, this initiates a series of inputs in order to make a new celestial
	case gui::ButtonBase::Game::MOON:
		stateEnum = State::ADDMOON;
		inputCount = 1;
		break;
	case gui::ButtonBase::Game::PLANET:
		stateEnum = State::ADDPLANET;
		inputCount = 1;
		break;
	case gui::ButtonBase::Game::STAR:
		stateEnum = State::ADDSTAR;
		inputCount = 1;
		break;
	//For the next five. When a modify-branched button is clicked, the value to change is determined
	case gui::ButtonBase::Game::RADIUS:
		stateEnum = State::MODIFYVALUE;
		valueToChange = 2;
		break;
	case gui::ButtonBase::Game::POSITION:
		stateEnum = State::MODIFYVALUE;
		inputCount = 1;
		valueToChange = 3;
		break;
	case gui::ButtonBase::Game::VELOCITY:
		stateEnum = State::MODIFYVALUE;
		inputCount = 1;
		valueToChange = 4;
		break;
	case gui::ButtonBase::Game::IMMOV:
		stateEnum = State::MODIFYVALUE;
		valueToChange = 5;
		break;
	case gui::ButtonBase::Game::NAME:
		stateEnum = State::MODIFYVALUE;
		valueToChange = 6;
		break;
	}
	this->guiDirector->modeInfo->setString("Simulation Mode: " + getStringState()); //Update the modeInfo string with the new simulation mode
	return 0;
}

int Simulation::buttonAction(gui::ButtonBase::Menu type)
{
	this->guiDirector->updateGraphics(type);

	return 0;
}

void Simulation::deleteCelestial(Celestial * celestial)
{
	bool found = false;
	int loopNumber = 1; //This is a counter that is incremented based on which loop the celestial is found in
	int indexNum = NULL; //This will stroe the index number of the celestial to delete
	//For the next three for loops. Each for loop loops through a certain celestial vector to find the celesital to be deleted
	//If the celestial is found, the found boolean is set to true and the index number is stored.
	for (int i = 0; i < simulationDirector->moons.size(); i++) {
		if (simulationDirector->moons[i] == celestial) {
			found = true;
			indexNum = i;
		}
	}
	if (!found) {
		loopNumber++; //The loop number is incremented to indicate we are now looking through the next celestial vector
		for (int i = 0; i < simulationDirector->planets.size(); i++) {
			if (simulationDirector->planets[i] == celestial) {
				found = true;
				indexNum = i;
			}
		}
	}
	if (!found) {
		loopNumber++; //The loop number is incremented to indicate we are now looking through the next celestial vector
		for (int i = 0; i < simulationDirector->stars.size(); i++) {
			if (simulationDirector->stars[i] == celestial) {
				found = true;
				indexNum = i;
			}
		}
	}
	//If the celestial is found, the loop number and index number are used to determine where the celestial is located in memory
	if (found) {
		if (loopNumber == 1) {
			//The auto specifier is used because this allows automatic detection of the type of the object.
			//A standard function within the std library is used to find the celestial within the vector.
			//This is then deleted
			auto it = std::find(this->simulationDirector->moons.begin(), this->simulationDirector->moons.end(), this->simulationDirector->moons[indexNum]);
			if (it != this->simulationDirector->moons.end())
				this->simulationDirector->moons.erase(it);
		}
		else if (loopNumber == 2) {
			auto it = std::find(this->simulationDirector->planets.begin(), this->simulationDirector->planets.end(), this->simulationDirector->planets[indexNum]);
			if (it != this->simulationDirector->planets.end())
				this->simulationDirector->planets.erase(it);
		}
		else {
			auto it = std::find(this->simulationDirector->stars.begin(), this->simulationDirector->stars.end(), this->simulationDirector->stars[indexNum]);
			if (it != this->simulationDirector->stars.end())
				this->simulationDirector->stars.erase(it);
		}

	}
}

void Simulation::isPaused(bool paused)
{
	this->paused = paused;
}

void Simulation::addInput(std::string input)
{
	double inputDouble; //Temporary variable to hold converted string value
	if (inputCount == 1 || inputCount == 2 || inputCount == 3 || inputCount == 4 || inputCount == 5 || inputCount == 6) {
		try {
			(inputDouble = std::stod(input)); //std::stod(stringVariable) converts a string into a double
		}
		catch (...) {
			return; //Handled exception
		}
	}
	if (inputCount == 1) { //Inputting mass
		tempMass = inputDouble; //Double assigned to temporary variable in simulation object
		inputCount++; //inputCount incremented each time to move onto the next value to be input
		this->guiDirector->inputInfo->setString("Radius:"); //String changed each time to show the next value to be input
	}
	else if (inputCount == 2) { //Inputting radius
		tempRadius = inputDouble;
		inputCount++;
		this->guiDirector->inputInfo->setString("X Position:");
	}
	else if (inputCount == 3) { //Inputting X position
		tempPositionX = inputDouble;
		inputCount++;
		this->guiDirector->inputInfo->setString("Y Position:");
	}
	else if (inputCount == 4) { //Inputting Y position
		tempPositionY = inputDouble;
		inputCount++;
		this->guiDirector->inputInfo->setString("X Velocity:");
	}
	else if (inputCount == 5) { //Inputting X velocity
		tempVelX = inputDouble;
		inputCount++;
		this->guiDirector->inputInfo->setString("Y Velocity:");
	}
	else if (inputCount == 6) { //Inputting Y velocity
		tempVelY = inputDouble;
		inputCount++;
		this->guiDirector->inputInfo->setString("Immovable (T/F):");
	}
	else if (inputCount == 7) { //Inputting Immovability
		if (input == "T" || input == "t") {
			tempImmovable = true;
			tempVelX = 0;
			tempVelY = 0;
		}
		else if (input == "F" || input == "f") {
			tempImmovable = false;
		}else{
			return;
		}
		inputCount++;
		this->guiDirector->inputInfo->setString("Name:");
	}
	else if (inputCount == 8){ //Inputting Name
		tempName = input;
		this->guiDirector->inputInfo->setString("Enter Mass (SF):");
		initialiseNewCelestial(); //Once all inputs have been entered, instantiate the new celestial object
		stateEnum = State::OBSERVE; //Simulation state set back to observe
	}
}

void Simulation::changeValue(std::string input)
{
	double inputDouble = 0; //Temporary variable to hold converted string value
	if (valueToChange == 2 || valueToChange == 3 || valueToChange == 4) {
		try {
			inputDouble = std::stod(input); //std::stod(stringVariable) converts a string into a double
		} 
		catch (...) {
			return; //Handling exception
		}
	}
	if (valueToChange == 2) { //Changing radius
		this->simulationDirector->selectedCelestial->setRadius(inputDouble);
		stateEnum = State::OBSERVE;
	}
	//For both position and velocity, since they are vector quantities, a method has to be set up to input two things (X and Y)
	//This is done using the inputCount variable as was done in the 'addInput' method
	else if (valueToChange == 3) { //Changing position
		if (inputCount == 1) {
			tempPositionX = inputDouble;
			inputCount++;
			this->guiDirector->inputInfo->setString("New Y Pos:");
		}
		else {
			this->simulationDirector->selectedCelestial->updatePositionPixelstoAU(tempPositionX,inputDouble);
			stateEnum = State::OBSERVE;
		}
	}
	else if (valueToChange == 4) { //Changing velocity
		if (inputCount == 1) {
			tempVelX = inputDouble;
			inputCount++;
			this->guiDirector->inputInfo->setString("New Y Vel:");
		}
		else {
			this->simulationDirector->selectedCelestial->setVelocity(sf::Vector2<double>(tempVelX,inputDouble));
			stateEnum = State::OBSERVE;
		}
	}
	else if (valueToChange == 5) { //Changing immovability
		if (input == "T") {
			this->simulationDirector->selectedCelestial->setImmovable(true);
			this->simulationDirector->selectedCelestial->setVelocity(sf::Vector2<double>(0, 0));
			this->simulationDirector->selectedCelestial->setAcceleration(sf::Vector2<double>(0, 0));
		}
		else if (input == "F") {
			this->simulationDirector->selectedCelestial->setImmovable(false);
		}
		else {
			return;
		}
		stateEnum = State::OBSERVE;
	}
	else if (valueToChange == 6) { //Changing name
		this->simulationDirector->selectedCelestial->setName(input);
		stateEnum = State::OBSERVE;
	}
	
}

std::string Simulation::getStringState()
{
	//Returns a variable of type string of the current simulation state
	switch (stateEnum) {
	case State::OBSERVE:
		return "Observe";
		break;
	case State::ADD:
		return "Add";
		break;
	case State::SELECT:
		return "Select";
		break;
	case State::ERASE:
		return "Erase";
		break;
	case State::MODIFY:
		return "Modify";
		break;
	case State::ADDMOON:
		return "Add Moon";
		break;
	case State::ADDPLANET:
		return "Add Planet";
		break;
	case State::ADDSTAR:
		return "Add Star";
		break;
	case State::MODIFYVALUE:
		return "Modify Value";
		break;
	}
}

Simulation::Simulation()
{
	//Dynamic memory allocation of SimulationDirector and GraphicsDirector
	this->simulationDirector = new SimulationDirector;
	this->guiDirector = new GraphicsDirector;
	//Sets up initial string for simulation mode information
	this->guiDirector->modeInfo->setString("Simulation Mode: " + getStringState());
}

Simulation::~Simulation()
{
}

//The following method uses the Runge-Kutta 4 numerical method in order to estimate the new positions and velocities of the celestial object
//It uses the Euler method of integration multiple times with different parameters
//Understanding the code requires an understanding of the process of RK4 integration. This can be seen in the 'Algorithm Design' section
void Simulation::integrate(double t, double dt)
{
	//The size of each celestial vector is determined
	int sizePlanets = this->simulationDirector->planets.size();
	int sizeStars = this->simulationDirector->stars.size();
	int sizeMoons = this->simulationDirector->moons.size();
	//Update k1
	//Update k1 velocities
	for (int i = 0; i < sizePlanets; i++) {
		this->simulationDirector->planets[i]->k1.dx = evaluate(this->simulationDirector->planets[i], t, 0.0, Celestial::Derivatives());
	}
	for (int i = 0; i < sizeStars; i++) {
		this->simulationDirector->stars[i]->k1.dx = evaluate(this->simulationDirector->stars[i], t, 0.0, Celestial::Derivatives());
	}
	for (int i = 0; i < sizeMoons; i++) {
		this->simulationDirector->moons[i]->k1.dx = evaluate(this->simulationDirector->moons[i], t, 0.0, Celestial::Derivatives());
	}
	//Find accelerations at this kPosition = k1
	updateAcceleration(sizePlanets, sizeStars, sizeMoons);
	//Update k1 accelerations
	for (int i = 0; i < sizePlanets; i++) {
		this->simulationDirector->planets[i]->k1.dv = this->simulationDirector->planets[i]->getAcceleration();
	}
	for (int i = 0; i < sizeStars; i++) {
		this->simulationDirector->stars[i]->k1.dv = this->simulationDirector->stars[i]->getAcceleration();
	}
	for (int i = 0; i < sizeMoons; i++) {
		this->simulationDirector->moons[i]->k1.dv = this->simulationDirector->moons[i]->getAcceleration();
	}
	//Update k2
	//Update k2 velocities
	for (int i = 0; i < sizePlanets; i++) {
		this->simulationDirector->planets[i]->k2.dx = evaluate(this->simulationDirector->planets[i], t, dt*0.5, this->simulationDirector->planets[i]->k1);
	}
	for (int i = 0; i < sizeStars; i++) {
		this->simulationDirector->stars[i]->k2.dx = evaluate(this->simulationDirector->stars[i], t, dt*0.5, this->simulationDirector->stars[i]->k1);
	}
	for (int i = 0; i < sizeMoons; i++) {
		this->simulationDirector->moons[i]->k2.dx = evaluate(this->simulationDirector->moons[i], t, dt*0.5, this->simulationDirector->moons[i]->k1);
	}
	//Find accelerations at this kPosition = k2
	updateAcceleration(sizePlanets, sizeStars, sizeMoons);
	//Update k2 accelerations
	for (int i = 0; i < sizePlanets; i++) {
		this->simulationDirector->planets[i]->k2.dv = this->simulationDirector->planets[i]->getAcceleration();
	}
	for (int i = 0; i < sizeStars; i++) {
		this->simulationDirector->stars[i]->k2.dv = this->simulationDirector->stars[i]->getAcceleration();
	}
	for (int i = 0; i < sizeMoons; i++) {
		this->simulationDirector->moons[i]->k2.dv = this->simulationDirector->moons[i]->getAcceleration();
	}
	//Update k3
	//Update k3 velocities
	for (int i = 0; i < sizePlanets; i++) {
		this->simulationDirector->planets[i]->k3.dx = evaluate(this->simulationDirector->planets[i], t, dt*0.5, this->simulationDirector->planets[i]->k2);
	}
	for (int i = 0; i < sizeStars; i++) {
		this->simulationDirector->stars[i]->k3.dx = evaluate(this->simulationDirector->stars[i], t, dt*0.5, this->simulationDirector->stars[i]->k2);
	}
	for (int i = 0; i < sizeMoons; i++) {
		this->simulationDirector->moons[i]->k3.dx = evaluate(this->simulationDirector->moons[i], t, dt*0.5, this->simulationDirector->moons[i]->k2);
	}
	//Find accelerations at this kPosition = k3
	updateAcceleration(sizePlanets, sizeStars, sizeMoons);
	//Update k3 accelerations
	for (int i = 0; i < sizePlanets; i++) {
		this->simulationDirector->planets[i]->k3.dv = this->simulationDirector->planets[i]->getAcceleration();
	}
	for (int i = 0; i < sizeStars; i++) {
		this->simulationDirector->stars[i]->k3.dv = this->simulationDirector->stars[i]->getAcceleration();
	}
	for (int i = 0; i < sizeMoons; i++) {
		this->simulationDirector->moons[i]->k3.dv = this->simulationDirector->moons[i]->getAcceleration();
	}
	//Update k4
	//Update k4 velocities
	for (int i = 0; i < sizePlanets; i++) {
		this->simulationDirector->planets[i]->k4.dx = evaluate(this->simulationDirector->planets[i], t, dt, this->simulationDirector->planets[i]->k3);
	}
	for (int i = 0; i < sizeStars; i++) {
		this->simulationDirector->stars[i]->k4.dx = evaluate(this->simulationDirector->stars[i], t, dt, this->simulationDirector->stars[i]->k3);
	}
	for (int i = 0; i < sizeMoons; i++) {
		this->simulationDirector->moons[i]->k4.dx = evaluate(this->simulationDirector->moons[i], t, dt, this->simulationDirector->moons[i]->k3);
	}
	//Find acceleration at this kPosition = k4
	updateAcceleration(sizePlanets, sizeStars, sizeMoons);
	//Update k4 accelerations
	for (int i = 0; i < sizePlanets; i++) {
		this->simulationDirector->planets[i]->k4.dv = this->simulationDirector->planets[i]->getAcceleration();
	}
	for (int i = 0; i < sizeStars; i++) {
		this->simulationDirector->stars[i]->k4.dv = this->simulationDirector->stars[i]->getAcceleration();
	}
	for (int i = 0; i < sizeMoons; i++) {
		this->simulationDirector->moons[i]->k4.dv = this->simulationDirector->moons[i]->getAcceleration();
	}
	//Using RK4 formula to get final position and velocity
	//Final Positions
	for (int i = 0; i < sizePlanets; i++) {
		sf::Vector2<double> k1dx = this->simulationDirector->planets[i]->k1.dx;
		sf::Vector2<double> k2dx = this->simulationDirector->planets[i]->k2.dx;
		sf::Vector2<double> k3dx = this->simulationDirector->planets[i]->k3.dx;
		sf::Vector2<double> k4dx = this->simulationDirector->planets[i]->k4.dx;
		this->simulationDirector->planets[i]->dxdt = (dt / 6.0)*(k1dx + 2.0*(k2dx + k3dx) + k4dx);
	}
	for (int i = 0; i < sizeStars; i++) {
		sf::Vector2<double> k1dx = this->simulationDirector->stars[i]->k1.dx;
		sf::Vector2<double> k2dx = this->simulationDirector->stars[i]->k2.dx;
		sf::Vector2<double> k3dx = this->simulationDirector->stars[i]->k3.dx;
		sf::Vector2<double> k4dx = this->simulationDirector->stars[i]->k4.dx;
		this->simulationDirector->stars[i]->dxdt = (dt / 6.0)*(k1dx + 2.0*(k2dx + k3dx) + k4dx);
	}
	for (int i = 0; i < sizeMoons; i++) {
		sf::Vector2<double> k1dx = this->simulationDirector->moons[i]->k1.dx;
		sf::Vector2<double> k2dx = this->simulationDirector->moons[i]->k2.dx;
		sf::Vector2<double> k3dx = this->simulationDirector->moons[i]->k3.dx;
		sf::Vector2<double> k4dx = this->simulationDirector->moons[i]->k4.dx;
		this->simulationDirector->moons[i]->dxdt = (dt / 6.0)*(k1dx + 2.0*(k2dx + k3dx) + k4dx);
	}
	//Final Velocities
	for (int i = 0; i < sizePlanets; i++) {
		sf::Vector2<double> k1dv = this->simulationDirector->planets[i]->k1.dv;
		sf::Vector2<double> k2dv = this->simulationDirector->planets[i]->k2.dv;
		sf::Vector2<double> k3dv = this->simulationDirector->planets[i]->k3.dv;
		sf::Vector2<double> k4dv = this->simulationDirector->planets[i]->k4.dv;
		this->simulationDirector->planets[i]->dvdt = (dt / 6.0)*(k1dv + 2.0*(k2dv + k3dv) + k4dv);
	}
	for (int i = 0; i < sizeStars; i++) {
		sf::Vector2<double> k1dv = this->simulationDirector->stars[i]->k1.dv;
		sf::Vector2<double> k2dv = this->simulationDirector->stars[i]->k2.dv;
		sf::Vector2<double> k3dv = this->simulationDirector->stars[i]->k3.dv;
		sf::Vector2<double> k4dv = this->simulationDirector->stars[i]->k4.dv;
		this->simulationDirector->stars[i]->dvdt = (dt / 6.0)*(k1dv + 2.0*(k2dv + k3dv) + k4dv);
	}
	for (int i = 0; i < sizeMoons; i++) {
		sf::Vector2<double> k1dv = this->simulationDirector->moons[i]->k1.dv;
		sf::Vector2<double> k2dv = this->simulationDirector->moons[i]->k2.dv;
		sf::Vector2<double> k3dv = this->simulationDirector->moons[i]->k3.dv;
		sf::Vector2<double> k4dv = this->simulationDirector->moons[i]->k4.dv;
		this->simulationDirector->moons[i]->dvdt = (dt / 6.0)*(k1dv + 2.0*(k2dv + k3dv) + k4dv);
	}
	//Setting the position and velocity
	//Setting final positions
	for (int i = 0; i < sizePlanets; i++) {
		sf::Vector2<double> dxdt = this->simulationDirector->planets[i]->dxdt;
		sf::Vector2<double> finalPosition = this->simulationDirector->planets[i]->getPositionAU() + dxdt*dt;
		this->simulationDirector->planets[i]->updatePositionAUtoPixels(finalPosition.x, finalPosition.y);
	}
	for (int i = 0; i < sizeStars; i++) {
		sf::Vector2<double> dxdt = this->simulationDirector->stars[i]->dxdt;
		sf::Vector2<double> finalPosition = this->simulationDirector->stars[i]->getPositionAU() + dxdt*dt;
		this->simulationDirector->stars[i]->updatePositionAUtoPixels(finalPosition.x, finalPosition.y);
	}
	for (int i = 0; i < sizeMoons; i++) {
		sf::Vector2<double> dxdt = this->simulationDirector->moons[i]->dxdt;
		sf::Vector2<double> finalPosition = this->simulationDirector->moons[i]->getPositionAU() + dxdt*dt;
		this->simulationDirector->moons[i]->updatePositionAUtoPixels(finalPosition.x, finalPosition.y);
	}
	//Setting final velocities
	for (int i = 0; i < sizePlanets; i++) {
		sf::Vector2<double> dvdt = this->simulationDirector->planets[i]->dvdt;
		sf::Vector2<double> finalVelocity = this->simulationDirector->planets[i]->getVelocity() + dvdt*dt;
		this->simulationDirector->planets[i]->setVelocity(finalVelocity);
	}
	for (int i = 0; i < sizeStars; i++) {
		sf::Vector2<double> dvdt = this->simulationDirector->stars[i]->dvdt;
		sf::Vector2<double> finalVelocity = this->simulationDirector->stars[i]->getVelocity() + dvdt*dt;
		this->simulationDirector->stars[i]->setVelocity(finalVelocity);
	}
	for (int i = 0; i < sizeMoons; i++) {
		sf::Vector2<double> dvdt = this->simulationDirector->moons[i]->dvdt;
		sf::Vector2<double> finalVelocity = this->simulationDirector->moons[i]->getVelocity() + dvdt*dt;
		this->simulationDirector->moons[i]->setVelocity(finalVelocity);
	}
}

sf::Vector2<double> Simulation::evaluate(Celestial* a,double t, double dt, const Celestial::Derivatives & d)
{
	//This is essentially the Euler method of integration
	//It is called multiple times within 'Integrate()'
	sf::Vector2<double> position;
	sf::Vector2<double> velocity;
	//Calculate and set the new temporary position of the celestial to be used in the acceleration calculations
	position = a->getPositionAU() + d.dx*dt;
	a->setkPosition(position);
	//Calculate and return the new temporary velocity of the celestial to be used in the final RK4 equation
	velocity = a->getVelocity() + d.dv*dt;
	return velocity;
}

void Simulation::efficientAccelerationLoop(std::vector<Celestial*> &mainCelestials, int mainCelestialSize, std::vector<Celestial*> &secondaryCelestial, std::vector<Celestial*> &tertiraryCelestial)
{
	int checkStart = 1; //The first celestial to be checked will be the second one (index stars from 0)
	int celestialSizeFirst; 
	if (mainCelestialSize > 1) {
		celestialSizeFirst = mainCelestialSize - 1; //If the main vector size is not 1, then the size used in the first for loop should be reduced by one.
	}else{
		celestialSizeFirst = mainCelestialSize;
	}
	for (int x = 0; x < celestialSizeFirst ; x++){
		for (int y = checkStart; y < mainCelestialSize; y++) {
			mainCelestials[x]->resolveAcceleration(mainCelestials[y]); 
		}
		checkStart++; //This is the pivotal change which makes this loop efficient. With this , no two pairs will be checked twice.
		for (int i = 0; i < secondaryCelestial.size(); i++) {
			mainCelestials[x]->resolveAcceleration(secondaryCelestial[i]);
		}
		for (int i = 0; i < tertiraryCelestial.size(); i++) {
			mainCelestials[x]->resolveAcceleration(tertiraryCelestial[i]);
		}
	}
}

void Simulation::initialiseNewCelestial() //Create a new celestial using the temporary values stored within the simulation object
{
	if (stateEnum == State::ADDMOON) { //If the state is add moon, then a moon is instantiated
		Moon* newMoon = new Moon(tempMass, tempRadius, sf::Vector2<double>(tempPositionX, tempPositionY));
		newMoon->setVelocity(sf::Vector2<double>(tempVelX, tempVelY));
		newMoon->setImmovable(tempImmovable);
		newMoon->setName(tempName);
		simulationDirector->moons.push_back(newMoon); //Pushed back into moon vector
	}
	else if (stateEnum == State::ADDPLANET) { //If the state is add planet, then a planet is instantiated
		Planet* newPlanet = new Planet(tempMass, tempRadius, sf::Vector2<double>(tempPositionX, tempPositionY));
		newPlanet->setVelocity(sf::Vector2<double>(tempVelX, tempVelY));
		newPlanet->setImmovable(tempImmovable);
		newPlanet->setName(tempName);
		simulationDirector->planets.push_back(newPlanet); //Pushed back into planet vector
	}
	else if (stateEnum == State::ADDSTAR) { //If the state is add star, then a star is instantiated
		Star* newStar = new Star(tempMass, tempRadius, sf::Vector2<double>(tempPositionX, tempPositionY));
		newStar->setVelocity(sf::Vector2<double>(tempVelX, tempVelY));
		newStar->setImmovable(tempImmovable);
		newStar->setName(tempName);
		simulationDirector->stars.push_back(newStar); //Pushed back into star vector
	}
}
