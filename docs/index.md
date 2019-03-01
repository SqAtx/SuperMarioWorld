# SuperMarioWorld
An amazing 2D Mario game made from scratch with C++ and SFML!

## History
I wrote Super Mario World in 2015, in order to keep my C++ skills sharp. C++ was my main language at the time, but my day job involved only C and C#.

Everything is written from scratch. That includes physics, sprites and levels management, sounds and music... It was a great learning experience.

Unfortunately, while I was aware that unit testing was a thing, it was never mentioned at school and was not something we did at work. So this project doesn't contain unit tests. Please don't judge me on that :)

I have since learned how to write good unit tests and even [given presentations](https://docs.google.com/presentation/d/1iu-rnybaaV2pPEZwXCSvnlJkBOxK_NUuyCoUvUostIA) about testing best practices!

Generally speaking, I don't think the code is very good and my style has probably changed a lot over the years.

This project won't be updated any more. It was a lot of fun to create a video game from scratch, but I don't really write C++ these days.

## What it does
Mario can move, run and jump! 

Enemies are coming out of the pipe and Mario dies if he touches them or if he falls into a hole.

He can kill enemies by jumping on them.

Scrolling is also functional.

I am quite proud of the level management: the levels are stored in XML files that follow a schema definition. To modify the level, you can just modify `activelvl.xml` and reload the game. A great next step to the project would have been to have a level editor to write those XML files. I couldn't make Visual Studio, SFML and Qt to work together, but that would have been a fantastic addition to the game.

The sprite management is pretty cool too: you just need a `.png` file along with a `.rect` file with the same name. The latter includes a sprite name and 4 coordinates on each line. The game with then create a sprite with that name and will associate it to the correct rectangle of the `.png`. You can then use that sprite name in your level XML file. You can even have animated sprites by having several lines in the `.rect` file with sprite names like foo1, foo2, foo3. The game will
understand that it's actually the same sprite and will display the expected animation!


## Running it
### From Visual Studio
I won't write more code but I did update the project so it can be run with Visual Studio 2017. You just need to setup SFML 2.0.


### Releases
There is an alpha release on GitHub but I don't think I did it properly. It's also not quite the latest version, as it doesn't have scrolling.

My last attempt at creating a release with Visual Studio 2017 was not successful. C++ is pretty difficult to compile when you've grown used to building C# projects :) I really want to create a release with the current code, that can be run on any Windows computer without prerequisites. The game is playable and even customizable so it would be fun to be able to share it. And that would be a really nice end to this project!
