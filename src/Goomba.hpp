#ifndef GOOMBA_H
#define GOOMBA_H

#include "MovingObject.hpp"

class Goomba : public MovingObject
{
public:
	Goomba(std::string _name, sf::Vector2f _coord, Direction _dir);
	Goomba(std::string _name, float _x, float _y, Direction _dir);
	~Goomba();

	void Init();

	virtual float GetMaxAbsVelocity_X();
	virtual void Move(Instruction _inst);

	InfoForDisplay GetInfoForDisplay();

private:

	void AddOwnAcceleration();
};

#endif