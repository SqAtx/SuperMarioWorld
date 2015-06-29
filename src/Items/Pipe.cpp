#include "Pipe.hpp"

Pipe::Pipe(std::string _name, sf::Vector2f _coord, int _pipeId, PipeType _type) : DisplayableObject(_name, _coord, NORMAL), m_pipeId(_pipeId), m_type(_type)
{

}
