# Snake

![Green snake](./_Icon.jpg)

## Author

Created by Kirill Rodriguez on 06/2014.

## Program

### Demo!

![demo](./_demo/demo.gif)

### Purpose

The purpose of this project was at first to practice C++ OOP and OpenGL (GLUT), but eventually it became a great challenge of fixing the code: checking links, inclusions; handling errors and so on. It has been a long way since June 2014 and since the initial code was written far worse than it is now, the code quality remains average.

### Description

This is a snake clone with nice manual and AI controls.

### Features

* 1 snake
* 5 routing modes (4 simple AIs)
* 5 aiming modes
* Walls
* Fruits
* 8 sets of icons.
* Pause (freezes the game)
* Safe mode (makes the best AI move when the current player about to crash)
* Running mode (moves only when a button is pressed)
* Adjustable delay between iterations (keyboard `io`)
* Adjustable number of fruits (keyboard `nm`)
* Adjustable field dimensions (args)
* Has fixes for unobvious bugs
* Has obvious bugs unfixed

### Ideas

* Mouse control (the current AI aims to get to the mouse pointer)
* Read walls from file.
* More snakes.
* Better snake AIs.
* Remote intelligence.

### Contribution

Feel free to submit a pull request or an issue to inform about a bug / error.

## Usage

### Tools

* C++ compiler
* GLUT, OpenGL
* cmake
* make

### Compilation

	cmake . && make

### Running

	./_snake  [width] [height] [number-of-fruits]
	
#### Controls

* Arrows
* p - Toggle pause
* r - Toggle running mode
* g - Toggle safe mode
* 0-4 - change AI (aiming and/or routing)
* 0-9 - change skin
* n/m - delete/add a fruit
* i/o - reduce/increase frame interval
* wasd - game controls (alternatives to arrows)
* ESC - exit