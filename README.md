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
- Mario can walk, run, jump, fall, and die if he falls into the hole
- A debug mode that displays extra information (can be disabled by commenting #define DEBUG_MODE in Debug.hpp)
- Sprite management: a .rect file indicates which textures to use for static sprites and for animations (with any number of frames)
- Physics: friction between Mario and the floor / air
- Sound and music management (Uncomment //StartLevelMusic(_event.m_string); in SoundEngine.cpp for music)
- Level stored in an XML file (background, characters, floor, foreground items). Foreground items can be animated.
- Collisions (first stable version, to be improved) between the player, the enemies and the foregroud items and approproate reaction

What next ?
- Dying animations
- Scrolling
- Better graphics ?