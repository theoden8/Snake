# Snake

![Green snake](./_Icon.jpg)

## Author

Created by Kirill Rodriguez on 08/2014.

## Program

### Purpose

The purpose of this project was at first to practice C++ OOP and OpenGL, but eventually it became a great challenge of fixing the code: checking links, inclusions; handling errors and so on. It was a long way since August 2014.

### Description

This is a snake game with nice AI routing and aiming switches.

### Features

* 1 snake
* 5 routing modes
* 4 aiming modes
* Walls
* Fruits
* 8 sets of icons.
* Pause (freezes the game)
* Safe mode (makes the best AI move when the current player about to crash)
* Running mode (moves only when a button is pressed)
* Adjustable delay between iterations.
* Adjustable number of fruits.
* Does not crash at each obvious bug.

### Ideas

* Mouse control (the current AI aims to get to the mouse pointer)
* Read walls from file.
* More snakes.
* Remote control.

## Usage

### Tools

* GLUT/OpenGL
* cmake

### Compilation

	cmake . && make

### Running

	./_snake  [width] [height] [number-of-fruits]