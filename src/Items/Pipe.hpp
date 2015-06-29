#ifndef PIPE_H
#define PIPE_H

#include "../DisplayableObject.hpp"

/*
*	A Pipe can be used to travel, to spawn enemies
*/
class Pipe : public DisplayableObject
{
	public:
		Pipe(std::string _name, sf::Vector2f _coord, int _pipeId, PipeType _type);

	protected:
		int m_pipeId;
		PipeType m_type;
};

#endif
