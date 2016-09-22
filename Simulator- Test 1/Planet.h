#pragma once
class Planet: public Celestial
{
private:

public:
	Planet(float radius, float mass, sf::Vector2f position);
	~Planet();

	void setMass();
	float getMass() { return m_mass; }
	void setRadius();

};

