# fire

## Description
This small program implements Final DOOM's fire effect in C++ by using the SDL
graphical library. It is based on
[this tutorial](https://fabiensanglard.net/doom_fire_psx/) by Fabien Sanglard.
The program runs in full screen and maximum resolution by default.

## Building the Program
To successfully build this program, you'll need to have GNU Make, LLVM Clang,
and the SDL 1 libraries installed on your system. After that, all you have to
do is to issue the `make` command in the project directory.

## Command-Line Switches
There are three command-line switches present.

* `--no-full-screen` runs the program in windowed mode
* `--width [W]` sets the width of the drawing surface if not in full screen
* `--height [H]` sets the height of the drawing surface if not in full screen

## Licensing
The software is under the MIT license. For more information, see the
[license file](LICENSE).
