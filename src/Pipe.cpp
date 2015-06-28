#include "Pipe.hpp"

Pipe::Pipe(std::string _name, sf::Vector2f _coord, State _state) : DisplayableObject(_name, _coord, _state)
{
	Init();
}

Pipe::Pipe(std::string _name, float _x, float _y, State _state) : DisplayableObject(_name, _x, _y, _state)
{
	Init();
}

void Pipe::Init()
{

}