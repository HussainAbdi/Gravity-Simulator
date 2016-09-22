#pragma once
class Celestial: public sf::CircleShape
{
private:
	
	float m_invmass;
	float m_density;
public:
	float m_velocity;
	Celestial(float mass);
	~Celestial();
protected:
	float m_mass;
};

