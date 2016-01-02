/*
    Super Mario
    Created on 21/03/15 by Kevin Guillaumond after PSE-Mario school project with Nicolas Djambazian
    Architecture inspired by http://khayyam.developpez.com/articles/cpp/jeux/architecture/
    main.cpp: Creates the Game object and launches the game
*/

#include <thread>
#include "Game.hpp"

int main(int argc, char** argv)
{
    Game* g = new Game();
	g->Run();

    return 0;
}
