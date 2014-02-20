FlappingBird
============

Open-source clone of the immensely popular smartphone game Flappy Bird.

This project is mostly a test of [SimpleGameEngine](https://github.com/C0deH4cker/SimpleGameEngine),
but it is functional and quite fun to play. My main goal in creating this was to mimic the original as
closely as possible, all without ever cracking it open in IDA or reversing it otherwise. I'd have to
say I was pretty successful there!

There are still some parts to be implemented (such as tracking high scores and displaying a score popup
when you lose, and of course sound), but the game is mostly complete.

GIF:

![Gameplay](http://i.imgur.com/ifHrte9.gif)


## Building ##

To build this project, simply run the following shell commands:

    git clone --recurse-submodules https://github.com/C0deH4cker/FlappingBird
    cd FlappingBird
    make

And that's it! Now just run `./flappingbird` to play!
