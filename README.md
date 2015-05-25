# SuperMarioWorld
An amazing 2D Mario game made with C++ and SFML

How to run it ?
The program uses SFML 2.2, you will need the following SFML DLLs in your executable's folder: sfml-audio-d-2.dll, sfml-graphics-d-2.dll, sfml-system-d-2.dll, sfml-window-d-2.dll and libsndfile-1.dll.

Commands:
- Left and Right arrows to move Mario
- C to run
- Space to jump
- Escape to bring Mario back from the dead

What has been done:
- Communication between GameEngine, GraphicsEngine and SoundEngine
- Display of the window with background, floor and Mario
- Mario can fall at the beginning of the level, then move left and right: the arrows give him an acceleration.
- A debug mode that displays extra information (can be disabled by commenting #define DEBUG_MODE in Debug.hpp)
- Sprite management: a .rect file indicates which textures to use for static sprites and for animations (with any number of frames)
- Friction between Mario and the floor
- Jumps and friction with air
- Sound and music management (Uncomment //StartLevelMusic(_event.m_string); in SoundEngine.cpp for music)
- Level stored in an XML file
- Mario dies if he falls in the hole

What next ?
- Collisions with level
- Scrolling
- Enemies :) 