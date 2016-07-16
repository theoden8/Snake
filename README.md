# Snake

![Green snake](./_Icon.jpg)

## Author

Created by Kirill Rodriguez on 06/2014.

## Program

### Purpose

The purpose of this project was at first to practice C++ OOP and OpenGL, but eventually it became a great challenge of fixing the code: checking links, inclusions; handling errors and so on. It has been a long way since June 2014.

### Description

This is a snake clone with nice manual and AI controls.

### Features

* 1 snake
* 5 routing modes
* 5 aiming modes
* Walls
* Fruits
* 8 sets of icons.
* Pause (freezes the game)
* Safe mode (makes the best AI move when the current player about to crash)
* Running mode (moves only when a button is pressed)
* Adjustable delay between iterations
* Adjustable number of fruits
* Has fixes for unobvious bugs

### Ideas

* Mouse control (the current AI aims to get to the mouse pointer)
* Read walls from file.
* More snakes.
* Remote control.

### Contribution

Feel free to submit a pull request or inform about a bug / error.

## Usage

### Tools

* GLUT/OpenGL
* cmake

### Compilation

	cmake . && make

### Running

	./_snake  [width] [height] [number-of-fruits]