#ifndef PIPE_H
#define PIPE_H

#include "DisplayableObject.hpp"

/*
*	A Pipe can be used to travel, to spawn enemies
*/
class Pipe : public DisplayableObject
{
public:
	Pipe(std::string _name, sf::Vector2f _coord, State _state = UNKNOWN);
	Pipe(std::string _name, float _x, float _y, State _state = UNKNOWN);

	void Init();

protected:

};

#endif