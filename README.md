# SuperMarioWorld
An amazing 2D Mario game made with C++ and SFML

## Installation

The project requires SFML 2.x to be compiled. If you don't have it installed yet, you can follow this link or do the commands bellow :
```
git clone git@github.com:SFML/SFML.git SFML
cd SFML
cmake . && make && sudo make install
cd .. && rm -fR SFML
```

To build the application, you can use `cmake` :
```
cd bin
cmake ..
make
```

Then run `./SuperMarioWorld`.

## Commands
- Left and Right arrows to move Mario
- C to run
- Space to jump
- Escape to bring Mario back from the dead

## What has been done ?
- Mario can walk, run, jump, fall, and die if he falls into the hole
- A debug mode that displays extra information (can be disabled by commenting #define DEBUG_MODE in Debug.hpp)
- Sprite management: a .rect file indicates which textures to use for static sprites and for animations (with any number of frames)
- Physics: friction between Mario and the floor / air
- Sound and music management
- Level stored in an XML file (background, characters, floor, foreground items). Foreground items can be animated.
- Collisions (first stable version, to be improved) between the player, the enemies and the foreground items and appropriate reaction

## What next ?
- Enemy spawn in pipes
- Death animations
- Scrolling
- Better graphics ?
